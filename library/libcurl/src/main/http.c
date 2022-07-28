#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <http.h>

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

static size_t write_data_to_file(void * ptr, size_t size, size_t nmemb, void * stream) {
    return fwrite(ptr, size, nmemb, (FILE *)stream);
}

static void show_help_then_exit(int exitCode) {
	const char * helpStr = "Usage: http <URL> [--verbose] [--show-progress] [-o FILENAME]\n";

    if (exitCode == 0) {
        fprintf(stdout, "%s\n", helpStr);
    } else {
        fprintf(stderr, "%s\n", helpStr);
    }

	exit(exitCode);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        show_help_then_exit(0);
    }

    if (strcmp(argv[1], "--help") == 0) {
        show_help_then_exit(0);
    } else if (strcmp(argv[1], "-h") == 0) {
        show_help_then_exit(0);
    }

    bool verbose = false;
    bool showProgress = false;

    const char * outputFilePath = NULL;
    const char * p = NULL;

    size_t index = 2;

    for (;;) {
        p = argv[index];

        if (p == NULL) {
            break;
        }

        if (strcmp(p, "--verbose") == 0) {
            verbose = true;
        } else if (strcmp(p, "--show-progress") == 0) {
            showProgress = true;
        } else if (strcmp(p, "-o") == 0) {
            index++;
            outputFilePath = argv[index];
            if ((outputFilePath == NULL) || (strcmp(outputFilePath, "") == 0)) {
                show_error_then_exit("-o argument's value is not given.", "", 1);
            }
        } else {
            show_error_then_exit("unrecognized argument: ", p, 1);
        }

        index++;
    }

    printf("verbose=%d\n", verbose);
    printf("showProgress=%d\n", showProgress);

    FILE * outputFile = NULL;
    
    if (outputFilePath != NULL) {
        outputFile = fopen(outputFilePath, "wb");
        if (outputFile == NULL) {
            perror(outputFilePath);
            return 1;
        }
    }

    return http_fetch(argv[1], outputFile, verbose, showProgress);
}
