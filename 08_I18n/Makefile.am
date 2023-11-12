AM_CFLAGS=-Wall -O0
bin_PROGRAMS=predictor
predictor_SOURCES=src/predictor.c

locale:
	mkdir -p ru_RU.UTF-8/LC_MESSAGES
	msgfmt po/ru.po -o ru_RU.UTF-8/LC_MESSAGES/predictor.mo

clean:
	git clean -df
