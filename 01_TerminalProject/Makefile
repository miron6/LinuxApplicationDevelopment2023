CC=gcc
LFLAGS=-lncursesw
OUT=Show

.PHONY: build
build: Show.c
	$(CC) $< $(LFLAGS) -o $(OUT)

.PHONY: clean
clean:
	rm -f *.o $(OUT) a.out
