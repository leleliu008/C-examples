#include <stdio.h>
#include <locale.h>
#include <langinfo.h>

int main() {
    setlocale(LC_ALL, "zh_CN.UTF-8");
    //setlocale(LC_ALL, "en_US.UTF-8");

    const char* codeset = nl_langinfo(CODESET);
    printf("%s\n", codeset);
    return 0;
}
