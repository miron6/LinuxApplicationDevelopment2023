#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

int remove(char *filename) {
    int (*orig_remove)(char *) = dlsym(RTLD_NEXT, "remove");
    if (strstr(filename, "PROTECT") != NULL) {
		return 1;
	}
    return orig_remove(filename);
}
