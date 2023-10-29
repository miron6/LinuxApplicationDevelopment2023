#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

enum ERROR_CODES {
    INCORRECT_ARGS_ERR = 1,
    SAME_NAME_ERR      = 2,
    INFILE_OPEN_ERR    = 3,
    OUTFILE_OPEN_ERR   = 4,
    FFULSH_ERR         = 5,
    INFILE_CLOSE_ERR   = 6,
    OUTFILE_CLOSE_ERR  = 7,
    OUTFILE_RM_ERR     = 8,
    UNDEFINED_ERR      = 9,
    FSEEK_ERR          = 10,
    OUTFILE_FTELL_ERR  = 11,
    SIZE_DIFFER_ERR    = 12,
    INFILE_RM_ERR      = 13,
};

int main(int argc, char **argv) {
    FILE *infile, *outfile;
    char *infile_name = argv[1], *outfile_name = argv[2];
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return INCORRECT_ARGS_ERR;
    }
    if (!strcmp(infile_name, outfile_name)) {
        return 0;
    }
    infile = fopen(infile_name, "r");
    if (infile == NULL) {
        fprintf(stderr, "Failed to open infile\n");
        return INFILE_OPEN_ERR;
    }
    outfile = fopen(outfile_name, "w");
    if (outfile == NULL) {
        fprintf(stderr, "Failed to open outfile\n");
        return OUTFILE_OPEN_ERR;
    }
    char c;
    int infile_len = 0;
    while((c = fgetc(infile)) != EOF) {
        infile_len++;
        fputc(c, outfile);
        if (fflush(outfile) != 0) {
            fprintf(stderr, "Failed to fflush outfile buffer\n");
            return FFULSH_ERR;
        };
    }
    if (fclose(infile) != 0) {
        fprintf(stderr, "Failed to close infile\n");
        return INFILE_CLOSE_ERR;
    }
    if (errno != 0) {
        fprintf(stderr, "Something went wrong\n");
        if (fclose(outfile) != 0) {
            fprintf(stderr, "Failed to close outfile\n");
            return OUTFILE_CLOSE_ERR;
        }
        if (remove(outfile_name) != 0) {
            fprintf(stderr, "Failed to remove outfile\n");
            return OUTFILE_RM_ERR;
        }
        return UNDEFINED_ERR;
    }
    if (fseek(outfile, 0, SEEK_END) != 0) {
        fprintf(stderr, "Failed to fseek outfile\n");
        return FSEEK_ERR;
    }
    int outfile_len = 0;
    if ((outfile_len = ftell(outfile)) == -1) {
        fprintf(stderr, "Failed to call ftell on outfile\n");
        return OUTFILE_FTELL_ERR;
    }
    if (infile_len != outfile_len) {
        fprintf(stderr, "File sizes differs: %d %d\n", infile_len, outfile_len);
        return SIZE_DIFFER_ERR;
    }
    if (fclose(outfile) != 0) {
        fprintf(stderr, "Failed to close outfile\n");
        return OUTFILE_CLOSE_ERR;
    }
    if (remove(infile_name) != 0) {
        fprintf(stderr, "Failed to remove outfile\n");
        return INFILE_RM_ERR;
    }
    return 0;
}
