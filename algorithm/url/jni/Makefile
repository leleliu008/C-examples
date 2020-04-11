CC = cc

URLTest: URLTest.c URL.c
	$(CC) $(CFLAGS) -o $@ $^

test: URLTest
	./$^ encode こんにちは💯
	./$^ decode %E3%81%93%E3%82%93%E3%81%AB%E3%81%A1%E3%81%AF%F0%9F%92%AF

clean:
	rm URLTest

.PHONY: clean
