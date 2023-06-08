#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <git2.h>

// https://libgit2.org/docs/guides/101-samples/
int do_git_init(const char * gitRepoPath, const char * defaultBranch, bool bare) {
    git_libgit2_init();

    git_repository * gitRepo = NULL;

    git_repository_init_options gitRepoInitOptions = GIT_REPOSITORY_INIT_OPTIONS_INIT;

    if (bare) {
        gitRepoInitOptions.flags |= GIT_REPOSITORY_INIT_BARE;
    }

    if ((defaultBranch != NULL) && (defaultBranch[0] != '\0')) {
        gitRepoInitOptions.initial_head = defaultBranch;
    }

    // https://libgit2.org/libgit2/#HEAD/group/repository/git_repository_init_ext
    int resultCode = git_repository_init_ext(&gitRepo, gitRepoPath, &gitRepoInitOptions);

    if (resultCode != 0) {
        const git_error * error = git_error_last();
        fprintf(stderr, "%s\n", error->message);
    }

    git_repository_free(gitRepo);

    git_libgit2_shutdown();

    return resultCode;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("%s [ -C <WORKING-DIR> ] [ --bare ] [ --default-branch <BRANCH-NAME>]\n", argv[0]);
        return 0;
    }

    const char * workingDirPath = ".";
    const char * branchName = NULL;
    bool bare = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--bare") == 0) {
            bare = true;
        } else if (strcmp(argv[i], "--default-branch") == 0) {
            i++;
            branchName = argv[i];

            if (branchName == NULL) {
                fprintf(stderr, "--default-branch option should have non-empty value.");
                return 1;
            }
        } else if (strcmp(argv[i], "-C") == 0) {
            i++;
            workingDirPath = argv[i];

            if (workingDirPath == NULL) {
                fprintf(stderr, "-C option should have non-empty value.");
                return 1;
            }

        } else {
            fprintf(stderr, "unrecognized option: %s", argv[i]);
        }
    }

    return do_git_init(workingDirPath, branchName, bare);
}
