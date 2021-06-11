bin_PROGRAMS=test
test_SOURCES=test.c

noinst_PROGRAMS = packcc
packcc_LINK     = $(CC_FOR_BUILD) $(LDFLAGS_FOR_BUILD) -o $@

packcc.o: packcc.c
	$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) $(CPPFLAGS_FOR_BUILD) -c -o $@ $<
