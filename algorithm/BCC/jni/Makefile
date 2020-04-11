CC = cc

BCCTest: BCCTest.c BCC.c ../../base16/jni/base16.c
	$(CC) $(CFLAGS) -o $@ $^

test: BCCTest
	./$^ hex 01A07CFF02

clean:
	rm BCCTest
	
.PHONY: clean
