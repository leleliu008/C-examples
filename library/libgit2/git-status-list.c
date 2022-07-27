#include <git2.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int do_git_status_list(const char * repositoryDIR) {
    if ((repositoryDIR == NULL) || (strcmp(repositoryDIR, "") == 0)) {
        repositoryDIR = ".";
    }

    git_libgit2_init();

    git_repository * gitRepo   = NULL;
    const git_error* gitError  = NULL;

    git_status_list* gitStatusList = NULL;

    int resultCode = GIT_OK;

    resultCode = git_repository_open_ext(&gitRepo, repositoryDIR, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    git_status_options gitStatusOptions = GIT_STATUS_OPTIONS_INIT;
    gitStatusOptions.flags = GIT_STATUS_OPT_DEFAULTS;

    // https://libgit2.org/libgit2/#HEAD/group/status/git_status_list_new
    resultCode = git_status_list_new(&gitStatusList, gitRepo, &gitStatusOptions);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    const size_t count = git_status_list_entrycount(gitStatusList);

    for (size_t i = 0; i < count; i++) {
        // https://libgit2.org/libgit2/#HEAD/type/git_status_entry
        const git_status_entry * gitStatusEntry = git_status_byindex(gitStatusList, i);

        if (gitStatusEntry->head_to_index != NULL) {
            printf("%d  %s\n", gitStatusEntry->status, gitStatusEntry->head_to_index->new_file.path);
        }

        if (gitStatusEntry->index_to_workdir != NULL) {
            printf("%d  %s\n", gitStatusEntry->status, gitStatusEntry->index_to_workdir->new_file.path);
        }
    }

clean:
    if (resultCode != GIT_OK) {
        fprintf(stderr, "%s\n", gitError->message);
    }

    git_repository_free(gitRepo);
    git_status_list_free(gitStatusList);

    git_libgit2_shutdown();

    return resultCode;
}

static void show_help_then_exit(int exitCode) {
    const char *helpStr = "Usage: git-status-list [repositoryDIR]\n";

    if (exitCode == 0) {
        fprintf(stdout, "%s", helpStr);
    } else {
        fprintf(stderr, "%s", helpStr);
    }

    exit(exitCode);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return do_git_status_list(NULL);
    }

    if (strcmp(argv[1], "--help") == 0) {
        show_help_then_exit(0);
    } else if (strcmp(argv[1], "-h") == 0) {
        show_help_then_exit(0);
    } else {
        return do_git_status_list(argv[1]);
    }
}
