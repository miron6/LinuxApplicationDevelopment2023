#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if ((argc < 2) || (argc > 4)) {
        printf("Usage: %s [M] [N] [S]\n", argv[0]);
        exit(-1);
    }
    int start = 0;
    int end = 0;
    int step = 1;
    if (argc == 2) {
        end = atoi(argv[1]);
    } else if (argc == 3) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
    } else if (argc == 4) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
        step = atoi(argv[3]);
    }
    if ((start - end) * step > 0 ) {
        printf("Wrong param values\n");
        exit(-1);
    }
    for (int i = start; i < end; i += step) {
        printf("%d\n", i);
    }
    return 0;
}
