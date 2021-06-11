#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chinese-calendar.h>

static void help(int exitCode) {
    printf("usage:\n");
    printf("    chinese-calendar -h|--help\n");
    printf("    chinese-calendar -V|--version\n\n");
    printf("    chinese-calendar --now\n");
    exit(exitCode);
}

static void version() {
    printf("%s\n", "1.0.0");
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        if (strcmp("-h", argv[1]) == 0) {
            help(0);
        } else if (strcmp("--help", argv[1]) == 0) {
            help(0);
        } else if (strcmp("-V", argv[1]) == 0) {
            version();
        } else if (strcmp("--version", argv[1]) == 0) {
            version();
        } else if (strcmp("--now", argv[1]) == 0) {
            const char* week[] = {"日", "一", "二", "三", "四", "五", "六"};

            time_t now = time(NULL);
            struct tm *tms = localtime(&now);
            int year  = 1900 + tms->tm_year;
            int month = 1 + tms->tm_mon;
            int day   = tms->tm_mday;

            char *lunar = solar2lunar(year, month, day);
            char *jieRi = jieri(year, month, day, lunar);
            char *jieQi = jieqi(year, month, day);

            char result[50] = {0};
            sprintf(result, "%02d:%02d:%02d %4d-%02d-%02d %s 周%s", tms->tm_hour, tms->tm_min, tms->tm_sec, year, month, day, lunar, week[tms->tm_wday]);
            free(lunar);
            if (NULL != jieRi) {
                strcat(result, " ");
                strcat(result, jieRi);
                free(jieRi);
            }
            if (NULL != jieQi) {
                strcat(result, " ");
                strcat(result, jieQi);
                free(jieQi);
            }
            printf("%s\n", result);
        } else {
            help(1);
        }
    } else {
        help(1);
    }
    return 0;
}
