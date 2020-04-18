CC=cc
CFLAGS = -v

ANDROID_APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

base16Test: base16Test.c base16.c
	$(CC) $(CFLAGS) -o $@ $^

test: base16Test
	./$^ encode 中国
	./$^ decode e4b8ade59bbd

clean:
	rm -rf base16Test
	rm -rf libs
	rm -rf obj

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(ANDROID_APP_PLATFORM) $(NDK_BUILD_FLAGS)

.PHONY: clean ndk-build
