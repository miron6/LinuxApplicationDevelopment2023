CC=gcc
LFLAGS=-Wall

.PHONY: run
run:	maze.c
	@$(CC) $(LFLAGS) maze.c -o maze
	@echo "apply first patch"
	@patch -o maze1.c < 1.patch
	@$(CC) $(LFLAGS) maze1.c -o maze1
	@echo "apply second patch"
	@patch -o maze2.c < 2.patch
	@$(CC) $(LFLAGS) maze2.c -o maze2
	@echo "apply third patch"
	@patch -o maze3.c < 3.patch
	@$(CC) $(LFLAGS) maze3.c -o maze3
	./maze
	./maze1 8
	./maze2 " @" 7
	./maze3 1337 ".@" 8
	./maze3 666 ".@" 8

clean:
	rm -f maze maze1 maze2 maze3 maze1.c maze2.c maze3.c
