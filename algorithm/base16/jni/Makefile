CC=cc

base16Test: base16Test.c base16.c
	$(CC) $(CFLAGS) -o $@ $^

test: base16Test
	./$^ encode 中国
	./$^ decode e4b8ade59bbd

clean:
	rm base16Test

.PHONY: clean
