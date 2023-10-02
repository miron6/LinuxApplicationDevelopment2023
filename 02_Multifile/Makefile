CC=cc
CFLAGS=-fPIC
ONE_ARG=1
THREE_ARGS=1 2 3
RES_FILE_1=1.res
RES_FILE_2=2.res
RES_FILE_3=3.res
ERR_FILE_1=1.err
ERR_FILE_2=2.err
ERR_FILE_3=3.err
TRASH=*.res *.err *.out *.so *.o *~ o.* *.a
GENERATES=prog prog-a prog-so

all:	prog test

prog:	const.o fun.o prog.o
	$(CC) $^ -o $@

fun.o:	outlib.h

liboutput_static.a:	fun.o const.o
	ar -rcs $@ $^

liboutput.so:	fun.o const.o
	$(CC) -shared $^ -o $@

prog-so:	prog.o liboutput.so
	$(CC) -L. $< -loutput -o $@

prog-a:	prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@

test-prog:	prog
	./$^ 2> $(ERR_FILE_1) 1> $(RES_FILE_1)
	./$^ 2>> $(ERR_FILE_1) 1>> $(RES_FILE_1) $(ONE_ARG)
	./$^ 2>> $(ERR_FILE_1) 1>> $(RES_FILE_1) $(THREE_ARGS)
	@sed -i 's|$<|binary|' $(ERR_FILE_1)

test-prog-a:	prog-a
	./$^ 2> $(ERR_FILE_2) 1> $(RES_FILE_2)
	./$^ 2>> $(ERR_FILE_2) 1>> $(RES_FILE_2) $(ONE_ARG)
	./$^ 2>> $(ERR_FILE_2) 1>> $(RES_FILE_2) $(THREE_ARGS)
	@sed -i 's|$<|binary|' $(ERR_FILE_2)

test-prog-so:	prog-so
	LD_LIBRARY_PATH=`pwd` ./$^ 2> $(ERR_FILE_3) 1> $(RES_FILE_3)
	LD_LIBRARY_PATH=`pwd` ./$^ 2>> $(ERR_FILE_3) 1>> $(RES_FILE_3) $(ONE_ARG)
	LD_LIBRARY_PATH=`pwd` ./$^ 2>> $(ERR_FILE_3) 1>> $(RES_FILE_3) $(THREE_ARGS)
	@sed -i 's|$<|binary|' $(ERR_FILE_3)

test:	test-prog test-prog-a test-prog-so
	cmp $(RES_FILE_1) $(RES_FILE_2)
	cmp $(RES_FILE_1) $(RES_FILE_3)
	cmp $(RES_FILE_2) $(RES_FILE_3)
	cmp $(ERR_FILE_1) $(ERR_FILE_2)
	cmp $(ERR_FILE_1) $(ERR_FILE_3)
	cmp $(ERR_FILE_2) $(ERR_FILE_3)

.PHONY: clean
clean:
	rm -f $(GENERATES) $(TRASH)
