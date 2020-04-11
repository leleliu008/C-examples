CC = cc

LRCTest: LRCTest.c LRC.c ../../base16/jni/base16.c
	$(CC) $(CFLAGS) -o $@ $^

test: LRCTest
	./$^ hex 01A07CFF02

clean:
	rm LRCTest

.PHONY: clean
