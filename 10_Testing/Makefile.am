SUBDIRS = src test

gitclean:	maintainer-clean
	git clean -fd

gcov:	check
	$(MAKE) -C src gcov

gcov-json:	check
	$(MAKE) -C src gcov-json

gcov-simple:	check
	$(MAKE) -C src gcov-simple
