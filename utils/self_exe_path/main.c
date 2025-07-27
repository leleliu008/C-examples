#include <stdio.h>
#include <limits.h>

#include "self.h"

int main() {
    char p[PATH_MAX];

    int ret = selfpath(p);

    if (ret > 0) {
        printf("%d:%s\n", ret, p);
        return 0;
    } else {
        return ret;
    }
}
