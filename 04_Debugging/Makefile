CC=gcc
FLAGS=-g -O0

range:	range.c
	$(CC) $(FLAGS) $^ -o $@

gdb.1:
	gdb < cmd_1.gdb ./range 2>/dev/null | grep "@@@" | sed "s|@@@||" > gdb.1

gdb.2:
	gdb < cmd_2.gdb ./range 2>/dev/null | grep "@@@" | sed "s|@@@||" > gdb.2

test:	range gdb.1 gdb.2
	cmp res.1 gdb.1
	cmp res.2 gdb.2

.PHONY: clean
clean:
	rm -f gdb.1 gdb.2 range
