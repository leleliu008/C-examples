ifeq ($(shell uname -s), Darwin)
	LD_SUFFIX = .dylib
else
	LD_SUFFIX = .so
endif

LD_FILE_NAME = libadd$(LD_SUFFIX)

override CFLAGS += -Os

main: main.c
	$(CC) $(CFLAGS) -DLD_FILE_NAME=\"$(LD_FILE_NAME)\" -o $@ $^

test: main
	./$<

libadd: add.c
	$(CC) $(CFLAGS) -shared -fPIC -o $(LD_FILE_NAME) $^

clean:
	rm -rf $(LD_FILE_NAME)
	rm -rf main

.PHONY: clean
