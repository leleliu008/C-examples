#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <git2.h>

int do_git_rev_parse(const char * repositoryDIR, const char * ref, bool shortOutput) {
    if (repositoryDIR == NULL) {
        repositoryDIR = ".";
    }

    if (repositoryDIR[0] == '\0') {
        repositoryDIR = ".";
    }

    if (ref == NULL) {
        return 1;
    }

    if (ref[0] == '\0') {
        return 2;
    }

    git_libgit2_init();

    git_repository  * gitRepo   = NULL;
    const git_error * gitError  = NULL;

    git_oid gitOid;

    char sha1sum[41] = {0};

    // https://libgit2.org/libgit2/#HEAD/group/clone/git_repository_open_ext
    int resultCode = git_repository_open_ext(&gitRepo, repositoryDIR, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);

    if (resultCode != GIT_OK) {
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/reference/git_reference_name_to_id
    resultCode = git_reference_name_to_id(&gitOid, gitRepo, ref);

    if (resultCode != GIT_OK) {
        goto clean;
    }

    for (int i = 0; i < 20; i++) {
        int j = i << 1;
        sprintf(&sha1sum[j], "%02x", (unsigned int)(gitOid.id[i]));
    }

    if (shortOutput) {
        sha1sum[7] = '\0';
    }

    printf("%s\n", sha1sum);

clean:
    if (resultCode != GIT_OK) {
        gitError = git_error_last();

        if (gitError == NULL) {
            if (resultCode == GIT_ENOTFOUND) {
                fprintf(stderr, "the given reference name '%s' is not found.\n", ref);
            } else if (resultCode == GIT_EINVALIDSPEC) {
                fprintf(stderr, "the given reference name '%s' is not valid.\n", ref);
            }
        } else {
            fprintf(stderr, "%s\n", gitError->message);
        }
    }

    git_repository_state_cleanup(gitRepo);

    git_repository_free(gitRepo);

    git_libgit2_shutdown();

    return resultCode;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return do_git_rev_parse(NULL, NULL, false);
    } else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        printf("usage: %s [repositoryDIR] [ref] [--short]", argv[0]);
    } else {
        bool shortOutput = false;

        for (int i = 3; i < argc; i++) {
            if (strcmp(argv[i], "--short") == 0) {
                shortOutput = true;
            } else {
                fprintf(stderr, "unrecognized option: %s\n", argv[1]);
            }
        }

        return do_git_rev_parse(argv[1], argv[2], shortOutput);
    }
}
