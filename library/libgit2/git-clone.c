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

// https://libgit2.org/libgit2/#HEAD/group/callback/git_checkout_progress_cb
void git_checkout_progress_callback(const char *path, size_t completed_steps, size_t total_steps, void *payload) {
    ProgressPayload * progressPayload = (ProgressPayload*)payload;

    if (completed_steps == total_steps) {
        printf("Receiving objects: 100%% (%u/%u), %.2f KiB, done.\n", progressPayload->indexerProgress.received_objects, progressPayload->indexerProgress.total_objects, progressPayload->indexerProgress.received_bytes / 1024.0);
        printf("Resolving deltas: 100%% (%u/%u), done.\n", progressPayload->indexerProgress.indexed_deltas, progressPayload->indexerProgress.total_deltas);
    }
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

// https://libgit2.org/docs/guides/101-samples/
int do_git_clone(const char * url, const char * filepath) {
    git_libgit2_init();

    ProgressPayload progressPayload = {0};

    git_repository * gitRepo = NULL;

    git_checkout_options gitCheckoutOptions = GIT_CHECKOUT_OPTIONS_INIT;

    gitCheckoutOptions.checkout_strategy    = GIT_CHECKOUT_SAFE;
	gitCheckoutOptions.progress_cb          = git_checkout_progress_callback;
	gitCheckoutOptions.progress_payload     = &progressPayload;

    git_clone_options    gitCloneOptions    = GIT_CLONE_OPTIONS_INIT;

	gitCloneOptions.checkout_opts = gitCheckoutOptions;
	gitCloneOptions.fetch_opts.callbacks.credentials       = git_credential_acquire_callback;
	gitCloneOptions.fetch_opts.callbacks.sideband_progress = git_transport_message_callback;
	gitCloneOptions.fetch_opts.callbacks.transfer_progress = git_indexer_progress_callback;
	gitCloneOptions.fetch_opts.callbacks.payload           = &progressPayload;
    gitCloneOptions.bare = false;

    printf("Cloning into '%s'...\n", filepath);

    // https://libgit2.org/libgit2/#HEAD/group/clone/git_clone
    int resultCode = git_clone(&gitRepo, url, filepath, &gitCloneOptions);

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
