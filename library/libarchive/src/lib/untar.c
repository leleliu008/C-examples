#include <string.h>
#include <untar.h>

int untar_list(const char * inputFilePath, int flags) {
	if (inputFilePath != NULL && strcmp(inputFilePath, "-") == 0) {
		inputFilePath = NULL;
    }

    struct archive *ar = archive_read_new();
    struct archive *aw = archive_write_disk_new();

    archive_read_support_filter_all(ar);
    archive_read_support_format_tar(ar);

    archive_write_disk_set_options(aw, flags);

    int resultCode = 0;

	if ((resultCode = archive_read_open_filename(ar, inputFilePath, 10240))) {
        goto clean;
    }

    struct archive_entry *entry = NULL;

	for (;;) {
		resultCode = archive_read_next_header(ar, &entry);

		if (resultCode == ARCHIVE_EOF) {
			break;
        }

		if (resultCode == ARCHIVE_OK) {
		    printf("%s\n", archive_entry_pathname(entry));
        } else {
            goto clean;
        }
	}

clean:
	archive_read_close(ar);
	archive_read_free(ar);

	archive_write_close(aw);
  	archive_write_free(aw);

    return resultCode;
}

int untar_extract(const char * outputDir, const char * inputFilePath, int flags, bool verbose, size_t stripComponentsNumber) {
	if (inputFilePath != NULL && strcmp(inputFilePath, "-") == 0) {
		inputFilePath = NULL;
    }

	struct archive *ar = archive_read_new();
	struct archive *aw = archive_write_disk_new();

    archive_read_support_filter_all(ar);
    archive_read_support_format_tar(ar);

	archive_write_disk_set_options(aw, flags);

	int resultCode = 0;

	if ((resultCode = archive_read_open_filename(ar, inputFilePath, 10240))) {
        goto clean;
    }

	struct archive_entry *entry = NULL;

	for (;;) {
		resultCode = archive_read_next_header(ar, &entry);

		if (resultCode == ARCHIVE_EOF) {
			break;
        }

		if (resultCode != ARCHIVE_OK) {
            goto clean;
        }

        const char * entry_pathname = archive_entry_pathname(entry);

        size_t entry_pathname_length = strlen(entry_pathname);

        if (stripComponentsNumber > 0) {
            bool contains_slash = false;

            for (size_t i = 0; i < entry_pathname_length; i++) {
                if (entry_pathname[i] == '/') {
                    entry_pathname = entry_pathname + i + 1;
                    contains_slash = true;
                    break;
                }
            }

            if (!contains_slash) {
                break;
            }
        }

		if (verbose) {
			printf("x %s\n", entry_pathname);
        }

        if ((outputDir != NULL) && (strcmp(outputDir, "") != 0)) {
            size_t outputFilePathLength = strlen(outputDir) + entry_pathname_length + 2;
            char outputFilePath[outputFilePathLength];
            memset(outputFilePath, 0, outputFilePathLength);
            sprintf(outputFilePath, "%s/%s", outputDir, entry_pathname);
            archive_entry_set_pathname(entry, outputFilePath);
        }

        resultCode = archive_write_header(aw, entry);

        if (resultCode != ARCHIVE_OK) {
            goto clean;
        }

        const void * dataBuff;
        size_t       dataSize;
#if ARCHIVE_VERSION_NUMBER >= 3000000
        int64_t offset;
#else
        off_t   offset;
#endif

        for (;;) {
            resultCode = archive_read_data_block(ar, &dataBuff, &dataSize, &offset);

            if (resultCode == ARCHIVE_EOF) {
                break;
            }

            if (resultCode != ARCHIVE_OK) {
                goto clean;
            }

            resultCode = archive_write_data_block(aw, dataBuff, dataSize, offset);

            if (resultCode != ARCHIVE_OK) {
                goto clean;
            }
        }

        resultCode = archive_write_finish_entry(aw);

        if (resultCode != ARCHIVE_OK) {
            goto clean;
        }
	}

clean:
	archive_read_close(ar);
	archive_read_free(ar);
	
	archive_write_close(aw);
  	archive_write_free(aw);

    return resultCode;
}
