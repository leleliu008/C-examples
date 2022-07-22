#ifndef HTTP_H
#define HTTP_H

    #include <stdio.h>
    #include <stdbool.h>

    #ifdef __cplasplas
        extern "C"
    #endif

        int http_fetch(char * url, FILE * outputFile, bool verbose, bool showProgress);

    #ifdef __cplasplas
        }
    #endif
#endif
