CC = cc
CFLAGS = -v

ANDROID_APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

LRCTest: LRCTest.c LRC.c ../base16/base16.c
	$(CC) $(CFLAGS) -o $@ $^

test: LRCTest
	./$^ hex 01A07CFF02

clean:
	rm -f LRCTest
	rm -rf libs
	rm -rf obj

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(ANDROID_APP_PLATFORM) $(NDK_BUILD_FLAGS)

.PHONY: clean ndk-build
