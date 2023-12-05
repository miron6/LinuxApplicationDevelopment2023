bin_PROGRAMS=predictor
pkgdata_DATA=ru/LC_MESSAGES/predictor.mo predictor.1
H2M=help2man

@DX_RULES@

all-local:	doxygen-doc

ru/LC_MESSAGES/predictor.mo:	ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

%.1:	%
	-$(H2M) --no-info --output=$@ --name='@PACKAGE_NAME@' ./predictor

web-doc:
	firefox doxygen-doc/html/index.html

clean:
	rm -rf messages*.pot predictor.o predictor *.po~ ru

gitclean:	maintainer-clean
	git clean -fd
