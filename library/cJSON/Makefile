CC=cc
CFLAGS += -Os -v
APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

cJSONTest: *.c
	$(CC) $(CFLAGS) -o $@ $^ && ./$@

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(APP_PLATFORM) $(NDK_BUILD_FLAGS)
clean:
	rm -rf libs
	rm -rf obj
	rm -rf cJSONTest

download-src:
	curl -LO https://raw.githubusercontent.com/DaveGamble/cJSON/master/cJSON.h
	curl -LO https://raw.githubusercontent.com/DaveGamble/cJSON/master/cJSON.c

.PHONY: ndk-build clean download-src
