#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include <git2.h>

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
    const char * const userHomeDir = getenv("HOME");

    if (userHomeDir == NULL) {
        return 1;
    }

    size_t userHomeDirLength = strlen(userHomeDir);

    if (userHomeDirLength == 0U) {
        return 1;
    }

    size_t  sshPrivateKeyFilePathLength = userHomeDirLength + 20U;
    char    sshPrivateKeyFilePath[sshPrivateKeyFilePathLength];
    memset( sshPrivateKeyFilePath, 0, sshPrivateKeyFilePathLength);
    snprintf(sshPrivateKeyFilePath, sshPrivateKeyFilePathLength, "%s/.ssh/id_rsa", userHomeDir);

    struct stat st;

    if ((stat(sshPrivateKeyFilePath, &st) == 0) && S_ISREG(st.st_mode)) {
        git_credential_ssh_key_new(credential, username_from_url, NULL, sshPrivateKeyFilePath, NULL);
        return 0;
    }

    snprintf(sshPrivateKeyFilePath, sshPrivateKeyFilePathLength, "%s/.ssh/id_ed25519", userHomeDir);

    if ((stat(sshPrivateKeyFilePath, &st) == 0) && S_ISREG(st.st_mode)) {
        git_credential_ssh_key_new(credential, username_from_url, NULL, sshPrivateKeyFilePath, NULL);
        return 0;
    }

    return 1;
}

int do_git_signature_now(git_repository * gitRepo, git_signature ** gitSignature) {
    const char * userName  = NULL;
    const char * userEmail = NULL;

    git_config * gitConfig = NULL;
    git_config_entry * gitConfigEntry = NULL;

    // https://libgit2.org/libgit2/#HEAD/group/repository/git_repository_config
    int resultCode = git_repository_config(&gitConfig, gitRepo);

    if (resultCode != GIT_OK) {
        goto clean;
    }

    //https://libgit2.org/libgit2/#HEAD/group/config/git_config_get_string
    resultCode = git_config_get_entry(&gitConfigEntry,  gitConfig, "user.name");

    if (resultCode != GIT_OK) {
        goto clean;
    }

    userName = gitConfigEntry->value;

    // https://libgit2.org/libgit2/#HEAD/group/config/git_config_get_entry
    resultCode = git_config_get_entry(&gitConfigEntry, gitConfig, "user.email");

    if (resultCode != GIT_OK) {
        goto clean;
    }

    userEmail = gitConfigEntry->value;

    //printf("user.name  = %s\n", userName);
    //printf("user.email = %s\n", userEmail);

    // https://libgit2.org/libgit2/#HEAD/group/signature/git_signature_now
    resultCode = git_signature_now(gitSignature, userName, userEmail);

clean:
    git_config_free(gitConfig);
    git_config_entry_free(gitConfigEntry);

    return resultCode;
}

int create_tracking_reference(git_repository * gitRepo, const char * localeTrackingBranchNameFull, const char * remoteTrackingBranchNameFull) {
    git_reference * localeTrackingBranchRef = NULL;
    git_oid         trackingBranchOid = {0};

    int resultCode = git_reference_name_to_id(&trackingBranchOid, gitRepo, remoteTrackingBranchNameFull);

    if (resultCode != GIT_OK) {
        goto clean;
    }

    resultCode = git_reference_create(&localeTrackingBranchRef, gitRepo, localeTrackingBranchNameFull, &trackingBranchOid, false, NULL);

    if (resultCode == GIT_EEXISTS) {
        resultCode = GIT_OK;
    }

clean:
    git_reference_free(localeTrackingBranchRef);

    return resultCode;
}

int check_if_is_a_empty_dir(const char * dirpath) {
    DIR * dir = opendir(dirpath);

    if (dir == NULL) {
        return -1;
    }

    for (;;) {
        errno = 0;

        struct dirent * dir_entry = readdir(dir);

        if (dir_entry == NULL) {
            if (errno == 0) {
                closedir(dir);
                return 1;
            } else {
                int ret = errno;
                closedir(dir);
                errno = ret;
                return -1;
            }
        }

        if ((strcmp(dir_entry->d_name, ".") == 0) || (strcmp(dir_entry->d_name, "..") == 0)) {
            continue;
        }

        closedir(dir);
        return 0;
    }
}

#define SYNC_MODE_CLONE 1
#define SYNC_MODE_PULL  2

int do_git_sync(const char * repositoryDIR, const char * remoteName, const char * remoteUrl, const char * refspec) {
    if ((repositoryDIR == NULL) || (strcmp(repositoryDIR, "") == 0)) {
        repositoryDIR = ".";
    }

    int resultCode = GIT_OK;

    int syncMode = SYNC_MODE_CLONE;

    struct stat st;

    if (stat(repositoryDIR, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            resultCode = check_if_is_a_empty_dir(repositoryDIR);

            if (resultCode == -1) {
                perror(repositoryDIR);
                return 1;
            }

            if (resultCode == 1) {
                syncMode = SYNC_MODE_CLONE;
            } else {
                syncMode = SYNC_MODE_PULL;
            }
        } else {
            fprintf(stderr, "%s exist and it is not a git repository.", repositoryDIR);
            return 1;
        }
    } else {
        syncMode = SYNC_MODE_CLONE;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////

    git_libgit2_init();

    //////////////////////////////////////////////////////////////////////////////////////////////

    git_refspec * gitRefSpec = NULL;

    const char * refspecSrc = NULL;
    const char * refspecDst = NULL;

    if ((refspec != NULL) && strcmp(refspec, "") != 0) {
        resultCode = git_refspec_parse(&gitRefSpec, refspec, true);

        if (resultCode != GIT_OK) {
            const git_error * gitError = git_error_last();
            fprintf(stderr, "%s\n", gitError->message);
            git_libgit2_shutdown();
            return resultCode;
        }

        refspecSrc = git_refspec_src(gitRefSpec);
        refspecDst = git_refspec_dst(gitRefSpec);

        //printf("string:%s\n", git_refspec_string(gitRefSpec));
        //printf("src:%s\n", refspecSrc);
        //printf("dst:%s\n", refspecDst);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////

    git_repository   * gitRepo        = NULL;

    git_config       * gitConfig      = NULL;
    git_config_entry * gitConfigEntry = NULL;

    git_remote       * gitRemote      = NULL;

    git_reference  * localeTrackingBranchRef = NULL;
    git_reference  * remoteTrackingBranchRef = NULL;

    git_index                   * gitIndex                 = NULL;
    git_index_conflict_iterator * gitIndexConflictIterator = NULL;

    git_annotated_commit * headCommit = NULL;

    git_commit      * gitCommitLocal  = NULL;
    git_commit      * gitCommitRemote = NULL;

    git_object      * gitObject       = NULL;

    git_tree        * gitTree         = NULL;

    git_signature   * gitSignature    = NULL;

    const git_error * gitError        = NULL;

    char * localeTrackingBranchName = NULL;
    char * remoteTrackingBranchName = NULL;

    //////////////////////////////////////////////////////////////////////////////////////////////

    if (syncMode == SYNC_MODE_CLONE) {
        resultCode = git_repository_init(&gitRepo, repositoryDIR, false);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            fprintf(stderr, "%s\n", gitError->message);
            git_repository_state_cleanup(gitRepo);
            git_repository_free(gitRepo);
            git_libgit2_shutdown();
            return resultCode;
        }

        if ((remoteName == NULL) || (strcmp(remoteName, "") == 0)) {
            remoteName = "origin";
        }

        if ((remoteUrl == NULL) || (strcmp(remoteUrl, "") == 0)) {
            fprintf(stderr, "init this empty git repo need you specify the remote url.\n");
            git_repository_state_cleanup(gitRepo);
            git_repository_free(gitRepo);
            git_libgit2_shutdown();
            return 1;
        }

        //https://libgit2.org/libgit2/#HEAD/group/remote/git_remote_create
        resultCode = git_remote_create(&gitRemote, gitRepo, remoteName, remoteUrl);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            fprintf(stderr, "%s\n", gitError->message);
            git_repository_state_cleanup(gitRepo);
            git_repository_free(gitRepo);
            git_libgit2_shutdown();
            return resultCode;
        }
    } else {
        resultCode = git_repository_open_ext(&gitRepo, repositoryDIR, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            fprintf(stderr, "%s\n", gitError->message);
            git_repository_state_cleanup(gitRepo);
            git_repository_free(gitRepo);
            git_libgit2_shutdown();
            return resultCode;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////

    if (syncMode == SYNC_MODE_PULL) {
        git_reference * HEADRef = NULL;

        resultCode = git_reference_lookup(&HEADRef, gitRepo, "HEAD");

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            fprintf(stderr, "%s\n", gitError->message);
            git_reference_free(HEADRef);
            git_repository_state_cleanup(gitRepo);
            git_repository_free(gitRepo);
            git_remote_free(gitRemote);
            git_libgit2_shutdown();
            return 1;
        }

        const char * HEADPointToRefName = git_reference_symbolic_target(HEADRef);

        if ((remoteName == NULL) || (strcmp(remoteName, "") == 0)) {
            if (HEADPointToRefName != NULL) {
                size_t HEADPointToRefNameLength = strlen(HEADPointToRefName);

                if (strncmp(HEADPointToRefName, "refs/heads/", HEADPointToRefNameLength > 11 ? 11 : HEADPointToRefNameLength) != 0) {
                    // read from repo's .git/config
                    // [branch "master"]
                    //   remote = origin
                    //   merge = refs/heads/master
                    if ((remoteName == NULL) || (strcmp(remoteName, "") == 0)) {
                        const char * currentBranchName = &HEADPointToRefName[11];
                        size_t currentBranchNameLength = HEADPointToRefNameLength - 11;

                        if (currentBranchNameLength > 0) {
                            size_t   keyLength = currentBranchNameLength + 15;
                            char     key[keyLength];
                            memset(  key, 0, keyLength);
                            snprintf(key, keyLength, "branch.%s.remote", currentBranchName);

                            // https://libgit2.org/libgit2/#HEAD/group/repository/git_repository_config
                            resultCode = git_repository_config(&gitConfig, gitRepo);

                            if (resultCode != GIT_OK) {
                                git_config_free(gitConfig);
                                git_config_entry_free(gitConfigEntry);
                                git_repository_state_cleanup(gitRepo);
                                git_repository_free(gitRepo);
                                git_remote_free(gitRemote);
                                git_libgit2_shutdown();
                                return 1;
                            }

                            //https://libgit2.org/libgit2/#HEAD/group/config/git_config_get_string
                            resultCode = git_config_get_entry(&gitConfigEntry,  gitConfig, key);

                            if (resultCode != GIT_OK) {
                                git_config_free(gitConfig);
                                git_config_entry_free(gitConfigEntry);
                                git_repository_state_cleanup(gitRepo);
                                git_repository_free(gitRepo);
                                git_remote_free(gitRemote);
                                git_libgit2_shutdown();
                                return 1;
                            }

                            remoteName = gitConfigEntry->value;
                        }
                    }
                }
            }
        }

        if ((remoteName == NULL) || (strcmp(remoteName, "") == 0)) {
            remoteName = "origin";
        }

        // https://libgit2.org/libgit2/#HEAD/group/remote/git_remote_lookup
        resultCode = git_remote_lookup(&gitRemote, gitRepo, remoteName);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            fprintf(stderr, "%s\n", gitError->message);
            git_repository_state_cleanup(gitRepo);
            git_repository_free(gitRepo);
            git_remote_free(gitRemote);
            git_libgit2_shutdown();
            return resultCode;
        }

        const char * gitRemoteUrl = git_remote_url(gitRemote);

        if ((remoteUrl == NULL) || (strcmp(remoteUrl, "") == 0)) {
            remoteUrl = gitRemoteUrl;
        } else {
            if (strcmp(gitRemoteUrl, remoteUrl) != 0) {
                fprintf(stderr, "remote url not mismatch.\nexpect: %s\nactual: %s\n", remoteUrl, gitRemoteUrl);
                git_repository_state_cleanup(gitRepo);
                git_repository_free(gitRepo);
                git_remote_free(gitRemote);
                git_libgit2_shutdown();
                return resultCode;
            }
        }
    }

    size_t remoteNameLength = strlen(remoteName);

    //////////////////////////////////////////////////////////////////////////////////////////////

    ProgressPayload progressPayload = {0};

    git_remote_callbacks gitRemoteCallbacks = GIT_REMOTE_CALLBACKS_INIT;

	gitRemoteCallbacks.sideband_progress = git_transport_message_callback;
	gitRemoteCallbacks.transfer_progress = git_indexer_progress_callback;
	gitRemoteCallbacks.credentials       = git_credential_acquire_callback;
	gitRemoteCallbacks.payload           = &progressPayload;

    git_fetch_options gitFetchOptions = GIT_FETCH_OPTIONS_INIT;
    gitFetchOptions.callbacks = gitRemoteCallbacks;

    if (refspecSrc == NULL) {
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

    //////////////////////////////////////////////////////////////////////////////////////////////

    if (syncMode == SYNC_MODE_CLONE) {
        const git_remote_head ** remoteRefs = NULL;
        size_t remoteRefsSize = 0;

        resultCode = git_remote_ls(&remoteRefs, &remoteRefsSize, gitRemote);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        if (remoteRefsSize == 0) {
            fprintf(stderr, "an empty repository.");
            goto clean;
        }

        printf("\nFrom %s\n", remoteUrl);

        for (size_t i = 1; i < remoteRefsSize; i++) {
            size_t  localeTrackingBranchNameLength = strlen(remoteRefs[i]->name) - 11 + 1;
            char    localeTrackingBranchName[localeTrackingBranchNameLength];
            memset( localeTrackingBranchName, 0, localeTrackingBranchNameLength);
            strncpy(localeTrackingBranchName, &((remoteRefs[i]->name)[11]), localeTrackingBranchNameLength - 1);

            size_t remoteTrackingBranchNameLength = remoteNameLength + localeTrackingBranchNameLength + 15;
            char   remoteTrackingBranchName[remoteTrackingBranchNameLength];
            memset(remoteTrackingBranchName, 0, remoteTrackingBranchNameLength);
            snprintf(remoteTrackingBranchName, remoteTrackingBranchNameLength, "refs/remotes/%s/%s", remoteName, localeTrackingBranchName);

            printf("* branch            %-20s -> %s\n", remoteRefs[i]->name, remoteTrackingBranchName);
        }

        printf("\n");

        git_buf gitBuf = {0};

        resultCode = git_remote_default_branch(&gitBuf, gitRemote);

        if (resultCode != GIT_OK) {
            git_buf_free(&gitBuf);
            gitError = git_error_last();
            goto clean;
        }

        // refs/heads/master
        size_t  localeTrackingBranchNameLength = gitBuf.size - 11 + 1;
        char    localeTrackingBranchName[localeTrackingBranchNameLength];
        memset( localeTrackingBranchName, 0, localeTrackingBranchNameLength);
        strncpy(localeTrackingBranchName, &gitBuf.ptr[11], localeTrackingBranchNameLength - 1);

        size_t remoteTrackingBranchNameLength = remoteNameLength + localeTrackingBranchNameLength + 2;
        char   remoteTrackingBranchName[remoteTrackingBranchNameLength];
        memset(remoteTrackingBranchName, 0, remoteTrackingBranchNameLength);
        snprintf(remoteTrackingBranchName, remoteTrackingBranchNameLength, "%s/%s", remoteName, localeTrackingBranchName);

        //printf("localeTrackingBranchName=%s\n", localeTrackingBranchName);
        //printf("remoteTrackingBranchName=%s\n", remoteTrackingBranchName);

        git_buf_free(&gitBuf);

        resultCode = git_branch_lookup(&remoteTrackingBranchRef, gitRepo, remoteTrackingBranchName, GIT_BRANCH_REMOTE);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        const git_oid * remoteTrackingBranchHeadOid = git_reference_target(remoteTrackingBranchRef);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        resultCode = git_reference_create(&localeTrackingBranchRef, gitRepo, "refs/heads/master", remoteTrackingBranchHeadOid, false, NULL);

        if (resultCode == GIT_EEXISTS) {
            resultCode = GIT_OK;
        }

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        // https://libgit2.org/libgit2/#HEAD/group/annotated/git_annotated_commit_from_ref
        resultCode = git_annotated_commit_from_ref(&headCommit, gitRepo, remoteTrackingBranchRef);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        // https://libgit2.org/libgit2/#HEAD/group/reference/git_reference_peel
        resultCode = git_reference_peel(&gitObject, remoteTrackingBranchRef, GIT_OBJ_COMMIT);

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
        resultCode = git_reference_set_target(&localeTrackingBranchRef, localeTrackingBranchRef, git_commit_id((git_commit*)gitObject), NULL);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
        }

        goto clean;
    }

    if (syncMode == SYNC_MODE_PULL) {
    }

    if (refspecSrc == NULL) {
        const git_remote_head ** remoteRefs = NULL;
        size_t remoteRefsSize = 0;

        resultCode = git_remote_ls(&remoteRefs, &remoteRefsSize, gitRemote);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        if (remoteRefsSize == 0) {
            fprintf(stderr, "an empty repository.");
            goto clean;
        }

        //for (size_t i = 0; i < remoteRefsSize; i++) {
        //    printf("remoteRef: %s\n", remoteRefs[i]->name);
        //}

        git_buf gitBuf = {0};

        resultCode = git_remote_default_branch(&gitBuf, gitRemote);

        if (resultCode != GIT_OK) {
            git_buf_free(&gitBuf);
            gitError = git_error_last();
            goto clean;
        }

        // refs/heads/master
        size_t localeTrackingBranchNameLength = gitBuf.size - 11;
        localeTrackingBranchName = (char*)calloc(localeTrackingBranchNameLength + 1, sizeof(char));

        if (localeTrackingBranchName == NULL) {
            git_buf_free(&gitBuf);
            resultCode = 1;
            goto clean;
        }

        size_t remoteTrackingBranchNameLength = remoteNameLength + localeTrackingBranchNameLength + 2;
        remoteTrackingBranchName = (char*)calloc(remoteTrackingBranchNameLength, sizeof(char));

        if (remoteTrackingBranchName == NULL) {
            git_buf_free(&gitBuf);
            resultCode = 1;
            goto clean;
        }

        strncpy(localeTrackingBranchName, &gitBuf.ptr[11], localeTrackingBranchNameLength);
        snprintf(remoteTrackingBranchName, remoteTrackingBranchNameLength, "%s/%s", remoteName, localeTrackingBranchName);

        char localeTrackingBranchNameFull[gitBuf.size + 1];
        memset(localeTrackingBranchNameFull, 0, gitBuf.size + 1);

        size_t remoteTrackingBranchNameFullLength = remoteTrackingBranchNameLength + 14;
        char   remoteTrackingBranchNameFull[remoteTrackingBranchNameFullLength];
        memset(remoteTrackingBranchNameFull, 0, remoteTrackingBranchNameFullLength);

        strncpy(localeTrackingBranchNameFull, gitBuf.ptr, gitBuf.size);
        snprintf(remoteTrackingBranchNameFull, remoteTrackingBranchNameFullLength, "refs/remotes/%s", remoteTrackingBranchName);

        //printf("localeTrackingBranchName=%s\n", localeTrackingBranchName);
        //printf("remoteTrackingBranchName=%s\n", remoteTrackingBranchName);
        //printf("localeTrackingBranchNameFull=%s\n", localeTrackingBranchNameFull);
        //printf("remoteTrackingBranchNameFull=%s\n", remoteTrackingBranchNameFull);

        git_buf_free(&gitBuf);

        resultCode = create_tracking_reference(gitRepo, localeTrackingBranchNameFull, remoteTrackingBranchNameFull);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        printf("From %s\n", remoteUrl);
        printf("* branch            %s        -> %s\n", localeTrackingBranchName, remoteTrackingBranchName);
        printf("* branch            %s        -> %s\n", localeTrackingBranchName, localeTrackingBranchName);

    } else {
        if (refspecDst == NULL) { // dst part is also not given, thus just do fetching, no need to update local branches.
            printf("From %s\n", remoteUrl);
            printf("* branch            %s        -> FETCH_HEAD\n", refspecSrc);
            goto clean;
        } else {
            size_t refspecDstLength = strlen(refspecDst);

            if (strncmp(refspecDst, "refs/remotes/", refspecDstLength > 13 ? 13 : refspecDstLength) == 0) {
                printf("From %s\n", remoteUrl);
                printf("* branch            %s        -> %s\n", refspecSrc, refspecDst);

                const char * p = &refspecDst[13];
                char c;
                size_t i = 0;

                for (;;) {
                    c = p[i];

                    if (c == '/' || c == '\0') {
                        break;
                    }

                    i++;
                }

                if (strncmp(remoteName, p, remoteNameLength > i ? i : remoteNameLength) != 0) {
                    goto clean;
                }

                size_t localeTrackingBranchNameLength = strlen(refspecDst) - 13;
                localeTrackingBranchName = (char*)calloc(localeTrackingBranchNameLength + 1, sizeof(char));

                if (localeTrackingBranchName == NULL) {
                    resultCode = 1;
                    goto clean;
                }

                size_t remoteTrackingBranchNameLength = remoteNameLength + localeTrackingBranchNameLength + 2;
                remoteTrackingBranchName = (char*)calloc(remoteTrackingBranchNameLength, sizeof(char));

                if (remoteTrackingBranchName == NULL) {
                    resultCode = 1;
                    goto clean;
                }

                strncpy(localeTrackingBranchName, &refspecDst[13], localeTrackingBranchNameLength);
                snprintf(remoteTrackingBranchName, remoteTrackingBranchNameLength, "%s/%s", remoteName, localeTrackingBranchName);

                if (syncMode == SYNC_MODE_CLONE) {
                    goto clean;
                }
            } else if (strncmp(refspecDst, "remotes/", refspecDstLength > 8 ? 8 : refspecDstLength) == 0) {
                printf("From %s\n", remoteUrl);
                printf("* branch            %s        -> %s\n", refspecSrc, refspecDst);

                size_t n = strlen(refspecDst) - 8;
                strncpy(localeTrackingBranchName, &refspecDst[8], n > 100 ? 100 : n);
                snprintf(remoteTrackingBranchName, 100, "%s/%s", remoteName, localeTrackingBranchName);

                size_t localeTrackingBranchNameLength = strlen(refspecDst) - 8;
                localeTrackingBranchName = (char*)calloc(localeTrackingBranchNameLength + 1, sizeof(char));

                if (localeTrackingBranchName == NULL) {
                    resultCode = 1;
                    goto clean;
                }

                size_t remoteTrackingBranchNameLength = remoteNameLength + localeTrackingBranchNameLength + 2;
                remoteTrackingBranchName = (char*)calloc(remoteTrackingBranchNameLength, sizeof(char));

                if (remoteTrackingBranchName == NULL) {
                    resultCode = 1;
                    goto clean;
                }

                strncpy(localeTrackingBranchName, &refspecDst[13], localeTrackingBranchNameLength);
                snprintf(remoteTrackingBranchName, remoteTrackingBranchNameLength, "%s/%s", remoteName, localeTrackingBranchName);


                if (syncMode == SYNC_MODE_CLONE) {
                    goto clean;
                }
            } else if (strncmp(refspecDst, "refs/tags/", refspecDstLength > 10 ? 10 : refspecDstLength) == 0) {
                printf("From %s\n", remoteUrl);
                printf("* branch            %s        -> %s\n", refspecSrc, refspecDst);

                goto clean;
            } else if (strncmp(refspecDst, "tags/", refspecDstLength > 5 ? 5 : refspecDstLength) == 0) {
                printf("From %s\n", remoteUrl);
                printf("* branch            %s        -> %s\n", refspecSrc, refspecDst);

                goto clean;
            } else if (strncmp(refspecDst, "refs/", refspecDstLength > 5 ? 5 : refspecDstLength) == 0) {
                printf("From %s\n", remoteUrl);
                printf("* branch            %s        -> %s\n", refspecSrc, refspecDst);

                goto clean;
            } else { // this case, update local branch
                size_t localeTrackingBranchNameLength = strlen(refspecDst);
                localeTrackingBranchName = (char*)calloc(localeTrackingBranchNameLength + 1, sizeof(char));

                if (localeTrackingBranchName == NULL) {
                    resultCode = 1;
                    goto clean;
                }

                size_t remoteTrackingBranchNameLength = remoteNameLength + localeTrackingBranchNameLength + 2;
                remoteTrackingBranchName = (char*)calloc(remoteTrackingBranchNameLength, sizeof(char));

                if (remoteTrackingBranchName == NULL) {
                    resultCode = 1;
                    goto clean;
                }

                strncpy(localeTrackingBranchName, refspecDst, localeTrackingBranchNameLength);
                snprintf(remoteTrackingBranchName, remoteTrackingBranchNameLength, "%s/%s", remoteName, localeTrackingBranchName);

                size_t localeTrackingBranchNameFullLength = localeTrackingBranchNameLength + 12;
                char   localeTrackingBranchNameFull[localeTrackingBranchNameFullLength];
                memset(localeTrackingBranchNameFull, 0, localeTrackingBranchNameFullLength);

                size_t remoteTrackingBranchNameFullLength = remoteTrackingBranchNameLength + 14;
                char   remoteTrackingBranchNameFull[remoteTrackingBranchNameFullLength];
                memset(remoteTrackingBranchNameFull, 0, remoteTrackingBranchNameFullLength);

                snprintf(localeTrackingBranchNameFull, localeTrackingBranchNameFullLength, "refs/heads/%s",   localeTrackingBranchName);
                snprintf(remoteTrackingBranchNameFull, remoteTrackingBranchNameFullLength, "refs/remotes/%s", remoteTrackingBranchName);

                printf("localeTrackingBranchName=%s\n", localeTrackingBranchName);
                printf("remoteTrackingBranchName=%s\n", remoteTrackingBranchName);
                printf("localeTrackingBranchNameFull=%s\n", localeTrackingBranchNameFull);
                printf("remoteTrackingBranchNameFull=%s\n", remoteTrackingBranchNameFull);

                if (syncMode == SYNC_MODE_CLONE) {
                    goto clean;
                }
            }
        }
    }

    resultCode = git_branch_lookup(&localeTrackingBranchRef, gitRepo, localeTrackingBranchName, GIT_BRANCH_LOCAL);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    resultCode = git_branch_lookup(&remoteTrackingBranchRef, gitRepo, remoteTrackingBranchName, GIT_BRANCH_REMOTE);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    const git_oid * remoteTrackingBranchHeadOid = git_reference_target(remoteTrackingBranchRef);
    const git_oid * trackingBranchHeadOid  = git_reference_target(localeTrackingBranchRef);

    // tracking branch's HEAD SHA-1 is equal to remote tracking branch's HEAD SHA-1, means no need to perform merge
    if (memcmp(remoteTrackingBranchHeadOid->id, trackingBranchHeadOid->id, 20) == 0) {
        goto clean;
    }

    char sha1sumOfBranchRemote[41] = {0};
    char sha1sumOfBranchLocal[41]  = {0};

    size_t i, j;
    for (i = 0; i < 20; i++) {
        j = 2 * i;
        sprintf(&sha1sumOfBranchRemote[j], "%02x", (unsigned int)(remoteTrackingBranchHeadOid->id[i]));
        sprintf(&sha1sumOfBranchLocal[j],  "%02x", (unsigned int)(trackingBranchHeadOid ->id[i]));
    }

    printf("sha1sumOfBranchRemote=%s\n", sha1sumOfBranchRemote);
    printf("sha1sumOfBranchLocal =%s\n", sha1sumOfBranchLocal);

    resultCode = git_repository_set_head(gitRepo, git_reference_name(localeTrackingBranchRef));

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    // https://libgit2.org/libgit2/#HEAD/group/annotated/git_annotated_commit_from_ref
    resultCode = git_annotated_commit_from_ref(&headCommit, gitRepo, remoteTrackingBranchRef);

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
		resultCode = git_reference_peel(&gitObject, remoteTrackingBranchRef, GIT_OBJ_COMMIT);

        if (resultCode != GIT_OK) {
            gitError = git_error_last();
            goto clean;
        }

        //git_reference *HEAD = NULL;
        // https://libgit2.org/libgit2/#HEAD/group/repository/git_repository_head
		resultCode = git_repository_head(&localeTrackingBranchRef, gitRepo);

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
		resultCode = git_reference_set_target(&localeTrackingBranchRef, localeTrackingBranchRef, git_commit_id((git_commit*)gitObject), NULL);

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
    resultCode = git_commit_lookup(&gitCommitRemote, gitRepo, git_reference_target(remoteTrackingBranchRef));

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    resultCode = git_commit_lookup(&gitCommitLocal,  gitRepo, git_reference_target(localeTrackingBranchRef));

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

    resultCode = do_git_signature_now(gitRepo, &gitSignature);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

    git_oid newCommitId;
    // https://libgit2.org/libgit2/#HEAD/group/commit/git_commit_create_v
    resultCode = git_commit_create_v(&newCommitId, gitRepo, git_reference_name(localeTrackingBranchRef), gitSignature, gitSignature, "UTF-8", "pull commit", gitTree, 2, gitCommitLocal, gitCommitRemote);

    if (resultCode != GIT_OK) {
        gitError = git_error_last();
        goto clean;
    }

clean:
    if (resultCode == GIT_OK) {
        printf("%s\n", "Already up to date.");
    } else {
        if (gitError != NULL) {
            fprintf(stderr, "%s\n", gitError->message);
        }
    }

    free(localeTrackingBranchName);
    free(remoteTrackingBranchName);

    git_repository_state_cleanup(gitRepo);
    git_repository_free(gitRepo);
    git_refspec_free(gitRefSpec);
    git_remote_free(gitRemote);
    git_reference_free(localeTrackingBranchRef);
    git_reference_free(remoteTrackingBranchRef);
    git_commit_free(gitCommitLocal);
    git_commit_free(gitCommitRemote);
    git_annotated_commit_free(headCommit);
    git_tree_free(gitTree);
    git_index_free(gitIndex);
    git_object_free(gitObject);
    git_signature_free(gitSignature);
    git_index_conflict_iterator_free(gitIndexConflictIterator);

    git_config_free(gitConfig);
    git_config_entry_free(gitConfigEntry);

    git_libgit2_shutdown();

    return resultCode;
}

static void show_help_then_exit(int exitCode) {
    const char *helpStr = "Usage: git-sync <repositoryDIR> <remoteName> <remoteUrl> [refspec]\n";

    if (exitCode == 0) {
        fprintf(stdout, "%s\n", helpStr);
    } else {
        fprintf(stderr, "%s\n", helpStr);
    }

    exit(exitCode);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        show_help_then_exit(1);
    }

    return do_git_sync(argv[1], argv[2], argv[3], argv[4]);
}
