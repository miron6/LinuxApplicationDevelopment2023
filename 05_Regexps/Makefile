CC=gcc
FLAGS=-Wall

esub:	esub.c
	$(CC) $(FLAGS) $< -o $@

test:	esub
	echo "123456789" | sed -E "s/[0-9].*/abcdefghij/" > sed_1.test
	./esub "[0-9].*" "abcdefghij" "123456789" > esub_1.test
	diff sed_1.test esub_1.test

	echo "SomeWord" | sed -E "s/Some/\0\0Double/" > sed_2.test
	./esub "Some" "\0\0Double" "SomeWord" > esub_2.test
	diff sed_2.test esub_2.test

	echo "1234567" | sed -E "s/[a-z].*/nothing_to_change/" > sed_3.test
	./esub "[a-z].*" "nothing_to_change" "1234567" > esub_3.test
	diff sed_3.test esub_3.test

	echo "foobarbaz" | sed -E 's/foo(.*)b(.)z/\2\1\2\0/' > sed_4.test
	./esub "foo(.*)b(.)z" "\2\1\2\0" "foobarbaz" > esub_4.test
	diff sed_4.test esub_4.test

.PHONY: clean
clean:
	rm -f esub *.test
