CC=cc
CFLAGS += -Os -v
LDFLAGS =

APP_PLATFORM = android-21
NDK_BUILD_FLAGS = V=1

qrencodeTest: qrencodeTest.c
	$(CC) $(CFLAGS) $(LDFLAGS) -lqrencode -o $@ $^

test: qrencodeTest
	./$< http://blog/fpliu.com/it

ndk-build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=$(APP_PLATFORM) $(NDK_BUILD_FLAGS)

clean:
	rm -rf libs
	rm -rf obj
	rm -rf qrencodeTest

download-src:
	curl -LO https://mirrors.tuna.tsinghua.edu.cn/debian/pool/main/q/qrencode/qrencode_4.0.2.orig.tar.bz2 && \
	tar vxf qrencode_4.0.2.orig.tar.bz2

.PHONY: ndk-build clean download-src
