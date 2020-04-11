CC = cc

CRCTest: CRCTest.c CRC.c ../../base16/jni/base16.c
	$(CC) $(CFLAGS) -o $@ $^

test: CRCTest
	./$^ hex 8301

clean:
	rm CRCTest
	
.PHONY: clean
