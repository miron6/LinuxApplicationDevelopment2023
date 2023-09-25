#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define DEFAULT_LINES_SIZE 256
#define ESCAPE 27
#define SPACE 32
#define INDENT 3
#define HEADER 2

struct file_wrapper {
    char* filename;
    char** lines;
    size_t length;
};

struct file_wrapper *wrap_file(FILE *f, char *filename) {
    struct file_wrapper* wrapped_f = malloc(sizeof(struct file_wrapper));
    if (wrapped_f == NULL) {
        return NULL;
    }
    wrapped_f->filename = strdup(filename);
    size_t lines_size = DEFAULT_LINES_SIZE;
    wrapped_f->length = 0;
    wrapped_f->lines = malloc(sizeof(char*) * lines_size);
	if (wrapped_f->lines == NULL) {
        return NULL;
    }
    size_t len = 0;
    size_t read;
    while ((read = getline(&(wrapped_f->lines[wrapped_f->length++]), &len, f)) != -1) {
        if (wrapped_f->length == lines_size) {
            lines_size = lines_size * 2;
            wrapped_f->lines = realloc(wrapped_f->lines, sizeof(char*) * lines_size);
            if (wrapped_f->lines == NULL) {
                return NULL;
            }
        }
    }
    // stub the end with newlines to show all the content inside box
    for (int i = 0; i < HEADER + 1; i++) {
        if (wrapped_f->length == lines_size) {
            lines_size = lines_size * 2;
            wrapped_f->lines = realloc(wrapped_f->lines, sizeof(char*) * lines_size);
            if (wrapped_f->lines == NULL) {
                return NULL;
            }
        }
        wrapped_f->lines[wrapped_f->length++] = strdup("\n");
    }
    return wrapped_f;
}

void free_file_wrapper(struct file_wrapper *f) {
    for (int i = 0; i < f->length; i++) {
        free(f->lines[i]);
    }
    free(f->lines);
    free(f->filename);
    free(f);
}

void show(struct file_wrapper *f) {
    int position = 0;
    initscr();
    noecho();
    cbreak();
    printw("File: %s\n", f->filename);
    printw("Lines: %ld\n", f->length - 1 - HEADER);
    int height = LINES - HEADER * INDENT;
    int width = COLS - HEADER * INDENT;
    WINDOW* window = newwin(height + HEADER, width, INDENT, INDENT);
    refresh();
    while (true) {
        werase(window);
        wprintw(window, "\n");
        for (int i = position, line = 0; (line < height) && (i < f->length - 1 - HEADER); line ++, i++) {
            wprintw(window, "%6d %s", i + 1, f->lines[i]);
        }
        box(window, 0, 0);
        wrefresh(window);
        int c = getch();
        if (c == SPACE) {
            if (LINES + position - INDENT < f->length) {
                position++;
            }
        } else if (c == ESCAPE) {
            break;
        }
    }
    endwin();
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "No such file: '%s'\n", filename);
        return 1;
    }
    struct file_wrapper *file = wrap_file(f, filename);
    if (file == NULL) {
        fprintf(stderr, "Error occurred while reading '%s'\n", filename);
        return 1;
    }
    fclose(f);
    show(file);
    free_file_wrapper(file);
    return 0;
}
