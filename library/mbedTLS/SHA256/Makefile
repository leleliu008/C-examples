CC=cc
CFLAGS += -Os -v

ANDROID_APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

BRANCH=mbedtls-2.14

sha256Test: *.c
	$(CC) $(CFLAGS) -o $@ $^

test: sha256Test
	./$< -x abc
	@printf "%b\n" "--------------"
	./$< -X abc

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(ANDROID_APP_PLATFORM) $(NDK_BUILD_FLAGS)

clean:
	rm -rf libs
	rm -rf obj
	rm -f  sha256Test

download-src:
	printf "%s" "#define MBEDTLS_SHA256_C" > config.h && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/include/mbedtls/sha256.h && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/library/sha256.c && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/include/mbedtls/platform_util.h && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/library/platform_util.c && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/include/mbedtls/threading.h && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/library/threading.c && \
	sed -i    's@mbedtls/@@g' sha256.c platform_util.h platform_util.c threading.h threading.c 2> /dev/null || \
	sed -i "" 's@mbedtls/@@g' sha256.c platform_util.h platform_util.c threading.h threading.c

.PHONY: ndk-build clean download-src
