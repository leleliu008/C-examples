#ifndef UNTAR_H
#define UNTAR_H

    #include <stdlib.h>
    #include <stdbool.h>

    #include <archive.h>
    #include <archive_entry.h>

    #ifdef __cplasplas
        extern "C"
    #endif

        int untar_list(const char * inputFilePath, int flags);
        int untar_extract(const char * outputDir, const char * inputFilePath, int flags, bool verbose, size_t stripComponentsNumber);

    #ifdef __cplasplas
        }
    #endif
#endif
