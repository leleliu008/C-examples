CC=cc
CFLAGS += -Os -v

APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

BRANCH=mbedtls-2.14
BASE_URL_H=https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/include/mbedtls
BASE_URL_C=https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/library

base64Test: *.c
	$(CC) $(CFLAGS) -o $@ $^

test: base64Test
	./$< encode abc
	@printf "%b\n" "--------------"
	./$< decode YQ== 

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(APP_PLATFORM) $(NDK_BUILD_FLAGS)

clean:
	rm -rf libs
	rm -rf obj
	rm -f  base64Test

download-src:
	printf "%s" "#define MBEDTLS_BASE64_C" > config.h && \
	curl -LO $(BASE_URL_H)/base64.h && \
	curl -LO $(BASE_URL_C)/base64.c && \
	sed -i    's@mbedtls/@@g' base64.c 2> /dev/null && \
	sed -i "" 's@mbedtls/@@g' base64.c

.PHONY: ndk-build clean download-src
