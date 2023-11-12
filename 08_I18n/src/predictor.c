#include <stdio.h>
#include <locale.h>
#include <libintl.h>
#include <stdlib.h>
#include <string.h>

#define _(STRING) gettext(STRING)

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("predictor", getenv("PWD"));
    textdomain("predictor");
    int left = 0, right = 100, curr;
    char answ[5];
    printf(_("Guess the number between 0 and 100\n"));
    while(left < right) {
        curr = (left + right) / 2;
        printf(_("Is your number greater then %d? [Yes/No]\n"), curr);
        while(1) {
            scanf("%s", answ);
            // unfortunately, `strcasecmp` can not work with multibytes symbs (e.g. UTF-8)
            // so in ru locale user must enter only lowercase answers
            if (strcasecmp(answ, _("yes")) == 0 || strcasecmp(answ, _("y")) == 0) {
                left = curr + 1;
                break;
            } else if (strcasecmp(answ, _("no")) == 0 || strcasecmp(answ, _("n")) == 0) {
                right = curr;
                break;
            } else {
                printf(_("Don't understand you... Answer [Yes] or [No]\n"));
            }
        }
    }
    printf(_("I guess your number is %d\n"), left);
}