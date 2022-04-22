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
            int solarYear  = 1900 + tms->tm_year;
            int solarMonth = 1 + tms->tm_mon;
            int solarDay   = tms->tm_mday;

            char *chineseLunarDate = get_chinese_lunar_date(solarYear, solarMonth, solarDay);
            char *chineseFestival  = get_chinese_festival3(solarYear, solarMonth, solarDay, chineseLunarDate);
            char *chineseJieQi     = get_chinese_jieqi(solarYear, solarMonth, solarDay);

            char result[50] = {0};
            sprintf(result, "%02d:%02d:%02d %4d-%02d-%02d %s 周%s", tms->tm_hour, tms->tm_min, tms->tm_sec, solarYear, solarMonth, solarDay, chineseLunarDate, week[tms->tm_wday]);

            if (NULL != chineseLunarDate) {
                free(chineseLunarDate);
            }

            if (NULL != chineseFestival) {
                strcat(result, " ");
                strcat(result, chineseFestival);
                free(chineseFestival);
            }

            if (NULL != chineseJieQi) {
                strcat(result, " ");
                strcat(result, chineseJieQi);
                free(chineseJieQi);
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
