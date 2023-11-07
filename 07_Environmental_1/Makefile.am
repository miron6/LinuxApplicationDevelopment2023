AM_FLAGS=-Wall -O0 -g
bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c

TESTS=run-tests.sh

test:
	chmod +x run-tests.sh
	./run-tests.sh

clean:
	git clean -df
