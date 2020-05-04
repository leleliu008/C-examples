ifeq ($(shell uname -s), Darwin)
	LD_SUFFIX = .dylib
else
	LD_SUFFIX = .so
endif

LD_FILE_NAME = libadd$(LD_SUFFIX)

override CFLAGS += -Os

libadd: add.c
	$(CC) $(CFLAGS) -shared -fPIC -o $(LD_FILE_NAME) $^

compile_time_do_not_link: compile_time_do_not_link.c
	$(CC) $(CFLAGS)  -o $@ $^

compile_time_do_not_link_test: compile_time_do_not_link
	./$< $(LD_FILE_NAME)

compile_time_link: compile_time_link.c
	$(CC) $(CFLAGS) -L. -ladd -o $@ $^

compile_time_link_test: compile_time_link
	./$<

clean:
	rm -f $(LD_FILE_NAME)
	rm -f compile_time_do_not_link
	rm -f compile_time_link

.PHONY: clean
