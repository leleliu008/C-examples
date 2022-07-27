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
    if (completed_steps == total_steps) {
        ProgressPayload * progressPayload = (ProgressPayload*)payload;
        git_indexer_progress indexerProgress = progressPayload->indexerProgress;

        if (indexerProgress.received_objects != 0) {
            printf("Receiving objects: 100%% (%u/%u), %.2f KiB, done.\n", indexerProgress.received_objects, indexerProgress.total_objects, indexerProgress.received_bytes / 1024.0);
        }

        if (indexerProgress.indexed_deltas != 0) {
            printf("Resolving deltas: 100%% (%u/%u), done.\n", indexerProgress.indexed_deltas, indexerProgress.total_deltas);
        }
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

int do_git_pull(const char * repositoryDIR, const char * remoteName, const char * refspec) {
    if ((repositoryDIR == NULL) || (strcmp(repositoryDIR, "") == 0)) {
        repositoryDIR = ".";
    }

    if ((remoteName == NULL) || (strcmp(remoteName, "") == 0)) {
        remoteName = "origin";
    }

    git_libgit2_init();

    git_repository * gitRepo         = NULL;

    git_remote     * gitRemote       = NULL;

    git_reference  * gitBranchLocal  = NULL;
    git_reference  * gitBranchRemote = NULL;

    git_index                   * gitIndex                 = NULL;
    git_index_conflict_iterator * gitIndexConflictIterator = NULL;

    git_annotated_commit * headCommit = NULL;

    git_commit      * gitCommitLocal  = NULL;
    git_commit      * gitCommitRemote = NULL;

    git_object      * gitObject       = NULL;

    git_tree        * gitTree         = NULL;

    git_signature   * gitSignature    = NULL;

    const git_error * gitError        = NULL;

    int resultCode = GIT_OK;

    resultCode = git_repository_open_ext(&gitRepo, repositoryDIR, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    git_config * gitConfig = NULL;

    // https://libgit2.org/libgit2/#HEAD/group/repository/git_repository_config
    resultCode = git_repository_config(&gitConfig, gitRepo);

    if (resultCode != GIT_OK) {
        git_config_free(gitConfig);
        gitError = git_error_last();
        goto clean;
    }

    const char * userName = NULL;
    const char * userEmail= NULL;

    git_config_entry * gitConfigEntry = NULL;

    //https://libgit2.org/libgit2/#HEAD/group/config/git_config_get_string
    resultCode = git_config_get_entry(&gitConfigEntry,  gitConfig, "user.name");

    if (resultCode != GIT_OK) {
        git_config_free(gitConfig);
        git_config_entry_free(gitConfigEntry);
        gitError = git_error_last();
        goto clean;
    }

    userName = gitConfigEntry->value;

    resultCode = git_config_get_entry(&gitConfigEntry, gitConfig, "user.email");

    git_config_free(gitConfig);
    git_config_entry_free(gitConfigEntry);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    userEmail = gitConfigEntry->value;

    //printf("user.name  = %s\n", userName);
    //printf("user.email = %s\n", userEmail);

    // https://libgit2.org/libgit2/#HEAD/group/remote/git_remote_lookup
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

    resultCode = git_branch_lookup(&gitBranchLocal, gitRepo, "master", GIT_BRANCH_LOCAL);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    resultCode = git_branch_lookup(&gitBranchRemote, gitRepo, "origin/master", GIT_BRANCH_REMOTE);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    const git_oid * gitOidOfBranchRemote = git_reference_target(gitBranchRemote);
    const git_oid * gitOidOfBranchLocal  = git_reference_target(gitBranchLocal);

    // no new contents fetched, thus no need to perform merge
    if (memcmp(gitOidOfBranchRemote->id, gitOidOfBranchLocal->id, 20) == 0) {
        goto clean;
    }

    char sha1sumOfBranchRemote[41] = {0};
    char sha1sumOfBranchLocal[41]  = {0};

    for (int i = 0; i < 20; i++) {
        int index = 2 * i;
        sprintf(&sha1sumOfBranchRemote[index], "%02x", (unsigned int)(gitOidOfBranchRemote->id[i]));
        sprintf(&sha1sumOfBranchLocal[index],  "%02x", (unsigned int)(gitOidOfBranchLocal ->id[i]));
    }

    //printf("sha1sumOfBranchRemote=%s\n", sha1sumOfBranchRemote);
    //printf("sha1sumOfBranchLocal =%s\n", sha1sumOfBranchLocal);

    resultCode = git_repository_set_head(gitRepo, git_reference_name(gitBranchLocal));

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/annotated/git_annotated_commit_from_ref
    resultCode = git_annotated_commit_from_ref(&headCommit, gitRepo, gitBranchRemote);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    git_merge_analysis_t   gitMergeAnalysis;
    git_merge_preference_t gitMergePreference;

    // https://libgit2.org/libgit2/#HEAD/group/merge/git_merge_analysis
    resultCode = git_merge_analysis(&gitMergeAnalysis, &gitMergePreference, gitRepo, (const git_annotated_commit **)(&headCommit), 1);

    if (gitMergeAnalysis & GIT_MERGE_ANALYSIS_FASTFORWARD && gitMergePreference != GIT_MERGE_PREFERENCE_NO_FASTFORWARD) {
		printf("fast-forwarding your working tree\n");
		printf("from commit %s\n", sha1sumOfBranchLocal);
		printf("to   commit %s\n", sha1sumOfBranchRemote);

        // https://libgit2.org/libgit2/#HEAD/group/reference/git_reference_peel
		resultCode = git_reference_peel(&gitObject, gitBranchRemote, GIT_OBJ_COMMIT);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        //git_reference *HEAD = NULL;
        // https://libgit2.org/libgit2/#HEAD/group/repository/git_repository_head
		resultCode = git_repository_head(&gitBranchLocal, gitRepo);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        // https://libgit2.org/libgit2/#HEAD/group/commit/git_commit_tree
		resultCode = git_commit_tree(&gitTree, (git_commit*)gitObject);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        git_checkout_options gitCheckoutOptions = GIT_CHECKOUT_OPTIONS_INIT;
        gitCheckoutOptions.checkout_strategy    = GIT_CHECKOUT_SAFE;
        gitCheckoutOptions.progress_cb          = git_checkout_progress_callback;
        gitCheckoutOptions.progress_payload     = &progressPayload;

        // https://libgit2.org/libgit2/#HEAD/group/checkout/git_checkout_tree
		resultCode = git_checkout_tree(gitRepo, (git_object*)gitTree, &gitCheckoutOptions);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        //git_reference * newHEAD = NULL;
        // https://libgit2.org/libgit2/#HEAD/group/reference/git_reference_set_target
		resultCode = git_reference_set_target(&gitBranchLocal, gitBranchLocal, git_commit_id((git_commit*)gitObject), NULL);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
        }

		goto clean;
	}

    git_merge_options    gitMergeOptions    = GIT_MERGE_OPTIONS_INIT;

    git_checkout_options gitCheckoutOptions = GIT_CHECKOUT_OPTIONS_INIT;
    gitCheckoutOptions.checkout_strategy    = GIT_CHECKOUT_SAFE;
    gitCheckoutOptions.progress_cb          = git_checkout_progress_callback;
    gitCheckoutOptions.progress_payload     = &progressPayload;

    // https://libgit2.org/libgit2/#HEAD/group/merge/git_merge
    resultCode = git_merge(gitRepo, (const git_annotated_commit **)(&headCommit), 1, &gitMergeOptions, &gitCheckoutOptions);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/repository/git_repository_index
    resultCode = git_repository_index(&gitIndex, gitRepo);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    if (git_index_has_conflicts(gitIndex)) {
        resultCode = git_index_conflict_iterator_new(&gitIndexConflictIterator, gitIndex);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        const git_index_entry* ancestor_out = NULL;
        const git_index_entry* our_out = NULL;
        const git_index_entry* their_out = NULL;

        while (git_index_conflict_next(&ancestor_out, &our_out, &their_out, gitIndexConflictIterator) != GIT_ITEROVER) {
            if (ancestor_out) printf("ancestor: %s\n", ancestor_out->path);
            if (our_out)      printf("our: %s\n", our_out->path);
            if (their_out)    printf("their: %s\n", their_out->path);
        }

        // git checkout --theirs <file>
        git_checkout_options gitCheckoutOptions = GIT_CHECKOUT_OPTIONS_INIT;
        gitCheckoutOptions.checkout_strategy |= GIT_CHECKOUT_USE_THEIRS;

        resultCode = git_checkout_index(gitRepo, gitIndex, &gitCheckoutOptions);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }
    }

    goto clean;

    // https://libgit2.org/libgit2/#HEAD/group/commit/git_commit_lookup
    resultCode = git_commit_lookup(&gitCommitRemote, gitRepo, git_reference_target(gitBranchRemote));

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    resultCode = git_commit_lookup(&gitCommitLocal,  gitRepo, git_reference_target(gitBranchLocal));

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/index/git_index_update_all
    resultCode = git_index_update_all(gitIndex, NULL, NULL, NULL);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/index/git_index_write
    resultCode = git_index_write(gitIndex);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    git_oid gitOid = {0};

    //https://libgit2.org/libgit2/#HEAD/group/index/git_index_write_tree
    resultCode = git_index_write_tree(&gitOid, gitIndex);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/tree/git_tree_lookup
    resultCode = git_tree_lookup(&gitTree, gitRepo, &gitOid);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/signature/git_signature_now
    resultCode = git_signature_now(&gitSignature, userName, userEmail);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    git_oid newCommitId;
    // https://libgit2.org/libgit2/#HEAD/group/commit/git_commit_create_v
    resultCode = git_commit_create_v(&newCommitId, gitRepo, git_reference_name(gitBranchLocal), gitSignature, gitSignature, "UTF-8", "pull commit", gitTree, 2, gitCommitLocal, gitCommitRemote);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

clean:
    if (resultCode == GIT_OK) {
        printf("%s\n", "Already up to date.");
    } else {
        fprintf(stderr, "%s\n", gitError->message);
    }

    git_repository_state_cleanup(gitRepo);

    git_repository_free(gitRepo);
    git_remote_free(gitRemote);
    git_reference_free(gitBranchLocal);
    git_reference_free(gitBranchRemote);
    git_commit_free(gitCommitLocal);
    git_commit_free(gitCommitRemote);
    git_annotated_commit_free(headCommit);
    git_tree_free(gitTree);
    git_index_free(gitIndex);
    git_object_free(gitObject);
    git_signature_free(gitSignature);
    git_index_conflict_iterator_free(gitIndexConflictIterator);

    git_libgit2_shutdown();

    return resultCode;
}

static void show_help_then_exit(int exitCode) {
    const char *helpStr = "Usage: git-pull [repositoryDIR] [remoteName] [refspec]]\n";

    if (exitCode == 0) {
        fprintf(stdout, "%s\n", helpStr);
    } else {
        fprintf(stderr, "%s\n", helpStr);
    }

    exit(exitCode);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return do_git_pull(NULL, NULL, NULL);
    }

    if (strcmp(argv[1], "--help") == 0) {
        show_help_then_exit(0);
    } else if (strcmp(argv[1], "-h") == 0) {
        show_help_then_exit(0);
    }

    if (argv[2] == NULL) {
        return do_git_pull(argv[1], NULL, NULL);
    } else {
        return do_git_pull(argv[1], argv[2], argv[3]);
    }
}
