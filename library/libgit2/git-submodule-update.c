#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>

#include <git2.h>

static int git_submodule_foreach_callback(git_submodule * submodule, const char * name, void * payload) {
    unsigned int status = 0;

    int ret = git_submodule_status(&status, (git_repository*)payload, name, GIT_SUBMODULE_IGNORE_UNTRACKED);

    if (ret != GIT_OK) {
        const git_error * error = git_error_last();
        fprintf(stderr, "%s\n", error->message);
        return ret;
    }

    printf("status of (%s):%u\n", name, status);

    return git_submodule_update(submodule, true, NULL);
}

int do_git_submodule_update_init(const char * gitRepoPath) {
    git_libgit2_init();

    git_repository * gitRepo = NULL;

    // https://libgit2.org/libgit2/#HEAD/group/repository/git_repository_init
    int ret = git_repository_init(&gitRepo, gitRepoPath, false);

    if (ret != GIT_OK) {
        const git_error * error = git_error_last();
        fprintf(stderr, "%s\n", error->message);
    }

    ret = git_submodule_foreach(gitRepo, git_submodule_foreach_callback, gitRepo);

    if (ret != GIT_OK) {
        const git_error * error = git_error_last();
        fprintf(stderr, "%s\n", error->message);
    }

    git_repository_free(gitRepo);

    git_libgit2_shutdown();

    return ret;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("%s [ -C <WORKING-DIR> ]\n", argv[0]);
        return 0;
    }

    const char * workingDirPath = ".";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-C") == 0) {
            i++;
            workingDirPath = argv[i];

            if (workingDirPath == NULL) {
                fprintf(stderr, "-C option should have non-empty value.");
                return 1;
            }
        } else {
            fprintf(stderr, "unrecognized option: %s", argv[i]);
            return 2;
        }
    }

    return do_git_submodule_update_init(workingDirPath);
}
