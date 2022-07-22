#include <stdio.h>
#include <string.h>
#include <untar.h>

#define COLOR_RED    "\033[0;31m"      // Red
#define COLOR_GREEN  "\033[0;32m"      // Green
#define COLOR_YELLOW "\033[0;33m"      // Yellow
#define COLOR_BLUE   "\033[0;94m"      // Blue
#define COLOR_PURPLE "\033[0;35m"      // Purple
#define COLOR_OFF    "\033[0m"         // Reset

static void print(const char * s) {
    write(1, s, strlen(s));
}

static void println(const char * s) {
    write(1, s, strlen(s));
    write(1, "\n", 1);
}

static void note(const char * s1, const char * s2) {
    printf("%s🔔  %s%s%s\n", COLOR_YELLOW, s1, s2, COLOR_OFF);
}

static void warn(const char * s1, const char * s2) {
    printf("%s🔥  %s%s%s\n", COLOR_YELLOW, s1, s2, COLOR_OFF);
}

static void show_error_then_exit(const char * s1, const char * s2, int exitCode) {
    printf("%s💔  %s%s%s\n", COLOR_YELLOW, s1, s2, COLOR_OFF);
	exit(exitCode);
}

static void show_help_then_exit(int exitCode) {
	const char *helpStr = "Usage: untar --help\n       untar -h\n       untar list FILE\n       untar extract FILE [--verbose] [--output-dir DIR] [--strip-components NUM]\n";

    if (exitCode == 0) {
        write(1, helpStr, strlen(helpStr));
    } else {
        write(2, helpStr, strlen(helpStr));
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
    } else if (strcmp(argv[1], "list") == 0) {
        untar_list(argv[2], ARCHIVE_EXTRACT_TIME);
    } else if (strcmp(argv[1], "extract") == 0) {
        bool verbose = false;
        const char * outputDir = NULL;
        size_t stripComponentsNumber = 0;
        const char * p = NULL;
        size_t index = 3;

        for (;;) {
            p = argv[index];

            if (p == NULL) {
                break;
            }

            if (strcmp(p, "--verbose") == 0) {
                verbose = true;
            } else if (strcmp(p, "--output-dir") == 0) {
                index++;
                outputDir = argv[index];
                if (outputDir == NULL) {
                    show_error_then_exit("--output-dir argument's value is not given.", "", 1);
                }
            } else if (strcmp(p, "--strip-components") == 0) {
                index++;
                stripComponentsNumber = atoi(argv[index]);
                printf("--strip-components=%lu\n", stripComponentsNumber);
            } else {
                show_error_then_exit("unrecognized argument: ", p, 1);
            }

            index++;
        }

		untar_extract(outputDir, argv[2], ARCHIVE_EXTRACT_TIME, verbose, stripComponentsNumber);
    } else {
        show_error_then_exit("unrecognized action: ", argv[1], 1);
    }

	return 0;
}
