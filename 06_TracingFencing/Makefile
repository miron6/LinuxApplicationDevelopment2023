CC=gcc
LFLAGS=-Wall -O0
OUT=move

move:	move.c
	$(CC) $< $(LFLAGS) -o $(OUT)

protect_lib:	protect.c
	$(CC) -shared -Wall -fPIC protect.c -o protect_lib.so -ldl

pre_test:
	cat /dev/random | head | base64 -w0 > test_source.txt

.PHONY: test
test:	move protect_lib pre_test run_tests.sh protect_lib.so
	./run_tests.sh
	rm -f test_source.txt in.txt PROTECTED__in.txt

.PHONY: clean
clean:
	rm -f *.o $(OUT) a.out protect_lib.so *.txt