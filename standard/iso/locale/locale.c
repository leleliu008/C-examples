#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>

int main() {
    //setlocale(LC_ALL, "zh_CN.UTF-8");
    setlocale(LC_ALL, "en_US.UTF-8");

    time_t tt = time(NULL);
    struct tm *tms = localtime(&tt);

    char buff[30] = {0};
    strftime(buff, sizeof(buff), nl_langinfo(D_T_FMT), tms);

    printf("现在是当地时间：%s\n", buff);

    return 0;
}
