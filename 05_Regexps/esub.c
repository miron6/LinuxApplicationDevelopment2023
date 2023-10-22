#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>

#define ERROR_BUF_SIZE 1024
#define MAX_BAGS 10

typedef struct string_wrap {
    char *str;
    size_t size;
} string_wrap;

void add_char(string_wrap *s, char ch) {
    if (s->str == NULL) {
        s->size = 1;
        s->str = malloc(s->size * sizeof(char));
    } else {
        (s->size)++;
        s->str = realloc(s->str, s->size * sizeof(char));
    }
    s->str[(s->size) - 1] = ch;
}

void esub(string_wrap *res, const char *sub, const char *init_str, regmatch_t* bags, int bags_max_num) {
    for (int i = 0; sub[i]; i++) {
        char curr_ch = sub[i];
        char next_ch = sub[i + 1];
        if (curr_ch != '\\' || !next_ch || (next_ch < '0' || next_ch > '9')) {
            add_char(res, curr_ch);
            if (next_ch == '\\') {
                i++;
            }
        } else {
            int bag_num = atoi(&next_ch);
            if (bag_num >= bags_max_num) {
                fprintf(stderr, "Reg Exp group number %d does not exist is original string\n", bag_num);
                exit(1);
            }
            for (int j = bags[bag_num].rm_so; j < bags[bag_num].rm_eo; j++) {
                add_char(res, init_str[j]);
            }
            i++;
        }
    }
    add_char(res, 0);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <regexp> <substitution> <string>\n", argv[0]);
        return 1;
    }
    const char *regexp_s = argv[1];
    const char *subst = argv[2];
    const char *init_str = argv[3];
    int error;
    regex_t regexp;
    if ((error = regcomp(&regexp, regexp_s, REG_EXTENDED)) != 0) {
        char err[ERROR_BUF_SIZE];
        regerror(error, &regexp, err, ERROR_BUF_SIZE);
        fprintf(stderr, "%s\n", err);
        return 1;
    }
    regmatch_t bags[MAX_BAGS];
    if (regexec(&regexp, init_str, MAX_BAGS, bags, 0) == REG_NOMATCH) {
        puts(init_str);
        return 0;
    }
    string_wrap res = {NULL, 0};
    esub(&res, subst, init_str, bags, regexp.re_nsub + 1);
    char *res_str = calloc(strlen((&res)->str) + strlen(init_str) + 1, sizeof(char));
    strncpy(res_str, init_str, bags[0].rm_so);
    strcat(res_str, (&res)->str);
    strcat(res_str, init_str + bags[0].rm_eo);
    puts(res_str);
    regfree(&regexp);
    free((&res)->str);
    free(res_str);
    return 0;
}
