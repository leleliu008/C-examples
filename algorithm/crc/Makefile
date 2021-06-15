CC = cc
CFLAGS = -v

ANDROID_APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

CRCTest: CRCTest.c CRC.c ../base16/base16.c
	$(CC) $(CFLAGS) -o $@ $^

test: CRCTest
	./$^ hex 8301

clean:
	rm -f CRCTest
	rm -rf libs
	rm -rf obj

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(ANDROID_APP_PLATFORM) $(NDK_BUILD_FLAGS)

.PHONY: clean ndk-build
