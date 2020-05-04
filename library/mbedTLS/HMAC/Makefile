CC=cc
CFLAGS += -Os -v

ANDROID_APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

#BRANCH=mbedtls-2.14
BRANCH=development
BASE_URL_H=https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/include/mbedtls
BASE_URL_C=https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/library

hmacTest: hmacTest.c mbedtls/*.c
	$(CC) $(CFLAGS) -o $@ $^

test: hmacTest
	./$< -x 123456 abc
	@printf "%b\n" "--------------"
	./$< -X 123456 abc

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(ANDROID_APP_PLATFORM) $(NDK_BUILD_FLAGS)

clean:
	rm -rf libs
	rm -rf obj
	rm -f  hmacTest

download-src:
	([ -d mbedtls ] || mkdir -p mbedtls) && cd mbedtls && \
	printf "%b" "#define MBEDTLS_MD_C\n#define MBEDTLS_SHA256_C" > config.h && { \
		for item in sha256.h md.h md_internal.h platform_util.h platform.h threading.h error.h; \
   		do \
			curl -LO $(BASE_URL_H)/$${item}; \
		done \
	} && { \
		for item in sha256.c md.c platform_util.c platform.c threading.c error.c; \
		do \
			curl -LO $(BASE_URL_C)/$${item}; \
		done \
	} && \
	sed -i    's@mbedtls/@@g' * 2> /dev/null || \
	sed -i "" 's@mbedtls/@@g' *

.PHONY: ndk-build clean download-src
