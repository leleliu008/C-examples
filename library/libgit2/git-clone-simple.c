#include <git2.h>
#include <stdio.h>

// https://libgit2.org/docs/guides/101-samples/
int do_git_clone(const char * url, const char * filepath) {
    git_libgit2_init();

    git_repository * gitRepo = NULL;

    // https://libgit2.org/libgit2/#HEAD/group/clone/git_clone
    int resultCode = git_clone(&gitRepo, url, filepath, NULL);

    if (resultCode != 0) {
        const git_error * error = git_error_last();
        fprintf(stderr, "%s\n", error->message);
    }

    git_repository_free(gitRepo);

    git_libgit2_shutdown();

    return resultCode;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("%s <URL> <PATH>\n", argv[0]);
        return 0;
    }
    return do_git_clone(argv[1], argv[2]);
}
