CC=cc
CFLAGS += -Os -v

ANDROID_APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

BRANCH=mbedtls-2.14
BASE_URL_H=https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/include/mbedtls
BASE_URL_C=https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/library

sha224Test: sha224Test.c mbedtls/*.c
	$(CC) $(CFLAGS) -o $@ $^

test: sha224Test
	./$< -x abc
	@printf "%b\n" "--------------"
	./$< -X abc

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(ANDROID_APP_PLATFORM) $(NDK_BUILD_FLAGS)

clean:
	rm -rf libs
	rm -rf obj
	rm -f  sha224Test

download-src:
	([ -d mbedtls ] || mkdir -p mbedtls) && cd mbedtls && \
    printf "%s" "#define MBEDTLS_SHA256_C" > config.h && { \
        for item in sha256.h platform_util.h threading.h; \
        do \
            curl -LO $(BASE_URL_H)/$${item}; \
        done \
    } && { \
        for item in sha256.c platform_util.c threading.c; \
        do \
            curl -LO $(BASE_URL_C)/$${item}; \
        done \
    } && \
    sed -i    's@mbedtls/@@g' * 2> /dev/null || \
    sed -i "" 's@mbedtls/@@g' *

.PHONY: ndk-build clean download-src
