#include <git2.h>
#include <stdio.h>
#include <stdbool.h>

// https://libgit2.org/docs/guides/101-samples/
bool is_valid_git_repo(const char * dir) {
    git_libgit2_init();

    git_repository * gitRepo = NULL;

    // https://libgit2.org/libgit2/#HEAD/group/clone/git_clone
    int resultCode = git_repository_open_ext(&gitRepo, dir, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);

    if (resultCode != 0) {
        const git_error * error = git_error_last();
        fprintf(stderr, "%s\n", error->message);
    }

    git_repository_free(gitRepo);

    git_libgit2_shutdown();

    if (resultCode == 0) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("%s <PATH>\n", argv[0]);
        return 0;
    }

    if (is_valid_git_repo(argv[1])) {
        return 0;
    } else {
        return 1;
    }
}
