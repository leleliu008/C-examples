#include <git2.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

typedef struct {
    git_indexer_progress indexerProgress;
} ProgressPayload;

// https://libgit2.org/libgit2/#HEAD/group/callback/git_transport_message_cb
int git_transport_message_callback(const char *str, int len, void *payload) {
    (void)payload; /* unused */
	printf("remote: %.*s", len, str);
	fflush(stdout);
	return 0;
}

// https://libgit2.org/libgit2/#HEAD/group/callback/git_indexer_progress_cb
int git_indexer_progress_callback(const git_indexer_progress *stats, void *payload) {
    ProgressPayload * progressPayload = (ProgressPayload*)payload;
    progressPayload->indexerProgress = *stats;
    return 0;
}

// https://libgit2.org/libgit2/#HEAD/group/credential/git_credential_ssh_key_new
// https://libgit2.org/libgit2/#HEAD/group/callback/git_credential_acquire_cb
int git_credential_acquire_callback(git_credential **credential, const char *url, const char *username_from_url, unsigned int allowed_types, void *payload) {
    const char * userHomeDir = getenv("HOME");
    int userHomeDirLength = strlen(userHomeDir);

    int length = userHomeDirLength + 20;
    char sshPrivateKeyFilePath[length];
    memset(sshPrivateKeyFilePath, 0, length);
    sprintf(sshPrivateKeyFilePath, "%s/.ssh/id_rsa", userHomeDir);

    struct stat st;

    if ((stat(sshPrivateKeyFilePath, &st) == 0) && S_ISREG(st.st_mode)) {
        git_credential_ssh_key_new(credential, username_from_url, NULL, sshPrivateKeyFilePath, NULL);
        return 0;
    }

    sprintf(sshPrivateKeyFilePath, "%s/.ssh/id_ed25519", userHomeDir);

    if ((stat(sshPrivateKeyFilePath, &st) == 0) && S_ISREG(st.st_mode)) {
        git_credential_ssh_key_new(credential, username_from_url, NULL, sshPrivateKeyFilePath, NULL);
        return 0;
    }

    return 1;
}

int do_git_fetch(const char * repositoryDIR, const char * remoteName, const char * refspec) {
    if ((repositoryDIR == NULL) || (strcmp(repositoryDIR, "") == 0)) {
        repositoryDIR = ".";
    }

    if ((remoteName == NULL) || (strcmp(remoteName, "") == 0)) {
        remoteName = "origin";
    }

    git_libgit2_init();

    git_repository * gitRepo   = NULL;
    git_remote     * gitRemote = NULL;
    const git_error* gitError  = NULL;

    int resultCode = GIT_OK;

    resultCode = git_repository_open_ext(&gitRepo, repositoryDIR, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    resultCode = git_remote_lookup(&gitRemote, gitRepo, remoteName);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    ProgressPayload progressPayload = {0};

    git_remote_callbacks gitRemoteCallbacks = GIT_REMOTE_CALLBACKS_INIT;

	gitRemoteCallbacks.sideband_progress = git_transport_message_callback;
	gitRemoteCallbacks.transfer_progress = git_indexer_progress_callback;
	gitRemoteCallbacks.credentials       = git_credential_acquire_callback;
	gitRemoteCallbacks.payload           = &progressPayload;

    git_fetch_options gitFetchOptions = GIT_FETCH_OPTIONS_INIT;
    gitFetchOptions.callbacks = gitRemoteCallbacks;

    if (refspec == NULL) {
        resultCode = git_remote_fetch(gitRemote, NULL, &gitFetchOptions, NULL);
    } else {
        git_strarray refspecArray = {.count = 1};
        char* strings[1] = {(char*)refspec};
        refspecArray.strings = strings;
        resultCode = git_remote_fetch(gitRemote, &refspecArray, &gitFetchOptions, NULL);
    }

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

clean:
    if (resultCode != GIT_OK) {
        fprintf(stderr, "%s\n", gitError->message);
    }

    git_repository_free(gitRepo);
    git_remote_free(gitRemote);

    git_libgit2_shutdown();

    return resultCode;
}

static void show_help_then_exit(int exitCode) {
    const char *helpStr = "Usage: git-fetch [repositoryDIR] [remoteName] [refspec]]\n";

    if (exitCode == 0) {
        fprintf(stdout, "%s", helpStr);
    } else {
        fprintf(stderr, "%s", helpStr);
    }

    exit(exitCode);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return do_git_fetch(NULL, NULL, NULL);
    }

    if (strcmp(argv[1], "--help") == 0) {
        show_help_then_exit(0);
    } else if (strcmp(argv[1], "-h") == 0) {
        show_help_then_exit(0);
    }

    if (argv[2] == NULL) {
        return do_git_fetch(argv[1], NULL, NULL);
    } else {
        return do_git_fetch(argv[1], argv[2], argv[3]);
    }
}
