#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <libgen.h>

#include <curl/curl.h>

#include <http.h>

static size_t write_callback(void * ptr, size_t size, size_t nmemb, void * stream) {
    return fwrite(ptr, size, nmemb, (FILE *)stream);
}

int http_fetch(const char * url, FILE * outputFile, bool verbose, bool showProgress) {
    if (outputFile == NULL) {
        int urlLength = strlen(url);
        int urlCopyLength = urlLength + 1;
        char urlCopy[urlCopyLength];
        memset(urlCopy, 0, urlCopyLength);
        strncpy(urlCopy, url, urlLength);

        const char * filename = basename(urlCopy);

        outputFile = fopen(filename, "wb");

        if (outputFile == NULL) {
            perror(filename);
            return 1;
        }
    }

    curl_global_init(CURL_GLOBAL_ALL);

    CURL * curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, outputFile);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    // https://curl.se/libcurl/c/CURLOPT_VERBOSE.html
    if (verbose) {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    } else {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
    }

    // https://curl.se/libcurl/c/CURLOPT_NOPROGRESS.html
    if (showProgress) {
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
    } else {
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    }

    ///////////////////////////////////////////////////////////////////////////////////

    // https://www.openssl.org/docs/man1.1.1/man3/SSL_CTX_set_default_verify_paths.html
    const char * const SSL_CERT_FILE = getenv("SSL_CERT_FILE");

    if ((SSL_CERT_FILE != NULL) && (SSL_CERT_FILE[0] != '\0')) {
        // https://curl.se/libcurl/c/CURLOPT_CAINFO.html
        curl_easy_setopt(curl, CURLOPT_CAINFO, SSL_CERT_FILE);
    }

    ///////////////////////////////////////////////////////////////////////////////////

    const char * const SSL_CERT_DIR = getenv("SSL_CERT_DIR");

    if ((SSL_CERT_DIR != NULL) && (SSL_CERT_DIR[0] != '\0')) {
        // https://curl.se/libcurl/c/CURLOPT_CAPATH.html
        curl_easy_setopt(curl, CURLOPT_CAPATH, SSL_CERT_DIR);
    }

    ///////////////////////////////////////////////////////////////////////////////////

    const char * const DNS_SERVERS = getenv("CURLOPT_DNS_SERVERS");

    if ((DNS_SERVERS != NULL) && (DNS_SERVERS[0] != '\0')) {
        // https://curl.se/libcurl/c/CURLOPT_DNS_SERVERS.html
        curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, DNS_SERVERS);
    }

    ///////////////////////////////////////////////////////////////////////////////////

    CURLcode curlcode = curl_easy_perform(curl);
    
    if (curlcode != CURLE_OK) {
        fprintf(stderr, "%s\n", curl_easy_strerror(curlcode));
    }

    fclose(outputFile);

    curl_easy_cleanup(curl);

    curl_global_cleanup();

    return curlcode;
}
