#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <git2.h>

int do_git_branch_list(const char * repositoryDIR, git_branch_t branchType) {
    if (repositoryDIR == NULL) {
        repositoryDIR = ".";
    }

    if (repositoryDIR[0] == '\0') {
        repositoryDIR = ".";
    }

    git_libgit2_init();

    git_repository * gitRepo   = NULL;
    const git_error* gitError  = NULL;

    git_branch_iterator * gitBranchIterator = NULL;

    // https://libgit2.org/libgit2/#HEAD/group/clone/git_repository_open_ext
    int resultCode = git_repository_open_ext(&gitRepo, repositoryDIR, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/branch/git_branch_iterator_new
    resultCode = git_branch_iterator_new(&gitBranchIterator, gitRepo, branchType);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    for (;;) {
        git_reference * gitReference = NULL;
        git_branch_t    gitBranchType;

        // https://libgit2.org/libgit2/#HEAD/group/branch/git_branch_next
        resultCode = git_branch_next(&gitReference, &gitBranchType, gitBranchIterator);

        if (resultCode == GIT_ITEROVER) {
            resultCode =  GIT_OK;
            break;
        }

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        const char * branchName = NULL;

        // https://libgit2.org/libgit2/#HEAD/group/branch/git_branch_name
        resultCode = git_branch_name(&branchName, gitReference);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        // https://libgit2.org/libgit2/#HEAD/group/branch/git_branch_is_head
        if (git_branch_is_head(gitReference)) {
            printf("*  %s\n", branchName);
        } else {
            printf("   %s\n", branchName);
        }

        git_reference_free(gitReference);
    }

clean:
    if (resultCode != GIT_OK) {
        fprintf(stderr, "%s\n", gitError->message);
    }

    git_branch_iterator_free(gitBranchIterator);
    git_repository_free(gitRepo);

    gitBranchIterator = NULL;
    gitRepo = NULL;

    git_libgit2_shutdown();

    return resultCode;
}

static void show_help_then_exit(int exitCode) {
    const char * const helpStr = "Usage: git-branch-list [repositoryDIR] [local|remote|all]";

    if (exitCode == 0) {
        fprintf(stdout, "%s\n", helpStr);
    } else {
        fprintf(stderr, "%s\n", helpStr);
    }

    exit(exitCode);
}

int main(int argc, char* argv[]) {
    switch(argc) {
        case 1:
            return do_git_branch_list(NULL, GIT_BRANCH_LOCAL);
        case 2:
            if (strcmp(argv[1], "--help") == 0) {
                show_help_then_exit(0);
            } else if (strcmp(argv[1], "-h") == 0) {
                show_help_then_exit(0);
            } else {
                return do_git_branch_list(argv[1], GIT_BRANCH_LOCAL);
            }
        case 3:
            if (strcmp(argv[2], "local") == 0) {
                return do_git_branch_list(argv[1], GIT_BRANCH_LOCAL);
            } else if (strcmp(argv[2], "remote") == 0) {
                return do_git_branch_list(argv[1], GIT_BRANCH_REMOTE);
            } else if (strcmp(argv[2], "all") == 0) {
                return do_git_branch_list(argv[1], GIT_BRANCH_ALL);
            } else {
                show_help_then_exit(1);
            }
        default:
            show_help_then_exit(1);
    }
}
