#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <git2.h>

int do_git_config_list(const char * level) {
    git_libgit2_init();

    git_config_iterator * gitConfigIterator = NULL;
    git_config_entry    * gitConfigEntry    = NULL;
    git_config          * gitConfig         = NULL;
    const git_error     * gitError          = NULL;

    // https://libgit2.org/libgit2/#HEAD/group/config/git_config_open_default
    int resultCode = git_config_open_default(&gitConfig);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/config/git_config_open_level
    if (strcmp(level, "system") == 0) {
        resultCode = git_config_open_level(&gitConfig, gitConfig, GIT_CONFIG_LEVEL_SYSTEM);
    } else if (strcmp(level, "local") == 0) {
        resultCode = git_config_open_level(&gitConfig, gitConfig, GIT_CONFIG_LEVEL_LOCAL);
    }

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/config/git_config_iterator_new
    resultCode = git_config_iterator_new(&gitConfigIterator, gitConfig);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/config/git_config_next
    while (git_config_next(&gitConfigEntry, gitConfigIterator) == 0) {
        printf("%-20s%s\n", gitConfigEntry->name, gitConfigEntry->value);
    }

clean:
    if (resultCode != GIT_OK) {
        fprintf(stderr, "%s\n", gitError->message);
    }

    git_config_iterator_free(gitConfigIterator);
    git_config_free(gitConfig);

    git_libgit2_shutdown();

    return resultCode;
}

static void show_help_then_exit(int exitCode) {
    const char * const helpStr = "Usage: git-config-list <system|global|local>\n";

    if (exitCode == 0) {
        fprintf(stdout, "%s", helpStr);
    } else {
        fprintf(stderr, "%s", helpStr);
    }

    exit(exitCode);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        show_help_then_exit(0);
    }

    if (strcmp(argv[1], "--help") == 0) {
        show_help_then_exit(0);
    } else if (strcmp(argv[1], "-h") == 0) {
        show_help_then_exit(0);
    } else {
        if ((strcmp(argv[1], "system") == 0) || (strcmp(argv[1], "global") == 0) || (strcmp(argv[1], "local") == 0)) {
            return do_git_config_list(argv[1]);
        } else {
            show_help_then_exit(1);
        }
    }
}
