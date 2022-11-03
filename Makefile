CFLAGS := -O2 -g2 -Wall -fno-omit-frame-pointer

libmustleak.so: mustleak.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $< -lpthread

testprog: testprog.c
	$(CC) $(CFLAGS) -o $@ $<

testprog-fork: testprog-fork.c
	$(CC) $(CFLAGS) -o $@ $<

test-linux: libmustleak.so testprog
	LD_PRELOAD=./libmustleak.so MUSTLEAK_DEBUG=1 MUSTLEAK_STOP_COUNT=10 ./testprog

test-darwin: libmustleak.so testprog
	DYLD_INSERT_LIBRARIES=./libmustleak.so MUSTLEAK_DEBUG=1 MUSTLEAK_STOP_COUNT=10 ./testprog

all: libmustleak.so

.PHONY: clean
clean:
	$(RM) -rf *.so *.dylib *.dSYM testprog testprog-fork