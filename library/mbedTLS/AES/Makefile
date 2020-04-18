CC=cc
CFLAGS += -Os -v

ANDROID_APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

BRANCH=mbedtls-2.14

aesTest: *.c ../../../algorithm/base16/base16.c
	$(CC) $(CFLAGS) -o $@ $^

test: aesTest
	./$< encode abc
	@printf "%b\n" "------------------------------------------"
	./$< decode EBBF70FEF806D11C4F1FA1007597105A

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(ANDROID_APP_PLATFORM) $(NDK_BUILD_FLAGS)

AES.class: AES.java
	javac -cp . $^

AES-java: AES.class
	java -cp . AES abc

clean:
	rm -rf libs
	rm -rf obj
	rm -rf aesTest

download-src:
	printf "%b\n" "#define MBEDTLS_AES_C\n#define MBEDTLS_CIPHER_MODE_CBC" > config.h && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/include/mbedtls/aes.h && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/library/aes.c && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/include/mbedtls/platform_util.h && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/library/platform_util.c && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/include/mbedtls/platform.h && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/library/platform.c && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/include/mbedtls/threading.h && \
	curl -LO https://raw.githubusercontent.com/ARMmbed/mbedtls/$(BRANCH)/library/threading.c && \
	sed -i    's@mbedtls/@@g' aes.c platform_util.h platform_util.c platform.c threading.h threading.c 2> /dev/null || \
	sed -i "" 's@mbedtls/@@g' aes.c platform_util.h platform_util.c platform.c threading.h threading.c

.PHONY: ndk-build clean download-src
