#include <git2.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int do_git_remote_list(const char * repositoryDIR) {
    if ((repositoryDIR == NULL) || (strcmp(repositoryDIR, "") == 0)) {
        repositoryDIR = ".";
    }

    git_libgit2_init();

    git_repository * gitRepo   = NULL;
    const git_error* gitError  = NULL;

    int resultCode = GIT_OK;

    resultCode = git_repository_open_ext(&gitRepo, repositoryDIR, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    git_strarray stringArrayList;
    resultCode = git_remote_list(&stringArrayList, gitRepo);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    for (size_t i = 0; i < stringArrayList.count; i++) {
        printf("%s\n", stringArrayList.strings[i]);
    }

clean:
    if (resultCode != GIT_OK) {
        fprintf(stderr, "%s\n", gitError->message);
    }

    git_repository_free(gitRepo);

    git_libgit2_shutdown();

    return resultCode;
}

static void show_help_then_exit(int exitCode) {
    const char *helpStr = "Usage: git-fetch [repositoryDIR]\n";

    if (exitCode == 0) {
        fprintf(stdout, "%s", helpStr);
    } else {
        fprintf(stderr, "%s", helpStr);
    }

    exit(exitCode);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return do_git_remote_list(NULL);
    }

    if (strcmp(argv[1], "--help") == 0) {
        show_help_then_exit(0);
    } else if (strcmp(argv[1], "-h") == 0) {
        show_help_then_exit(0);
    } else {
        return do_git_remote_list(argv[1]);
    }
}
