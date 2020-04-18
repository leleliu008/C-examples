CC = cc
CFLAGS = -v

ANDROID_APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

URLTest: URLTest.c URL.c
	$(CC) $(CFLAGS) -o $@ $^

test: URLTest
	./$^ encode こんにちは💯
	./$^ decode %E3%81%93%E3%82%93%E3%81%AB%E3%81%A1%E3%81%AF%F0%9F%92%AF

clean:
	rm -f URLTest
	rm -rf libs
	rm -rf obj

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(ANDROID_APP_PLATFORM) $(NDK_BUILD_FLAGS)

.PHONY: clean ndk-build
