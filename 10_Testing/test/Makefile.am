TESTS = clear_null_buf_test init_free_test pop_test grow_trunc_test push_test
check_PROGRAMS = clear_null_buf_test init_free_test pop_test grow_trunc_test push_test

CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.ts.c:
	checkmk $< > $@