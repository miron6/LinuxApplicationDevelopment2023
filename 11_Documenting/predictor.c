/**
 * @file predictor.c
 * @author miron6
 * @brief Magic number predictor
 * @version 0.1.0
 * @date 05.12.23
 * 
 * Udage: predictor [OPTIONS]
 * - -\-help, -h        show this message
 * - -\-vesrion, -v     print version
 * - -\-roman, -r       use roman numbers
*/
#include <stdio.h>
#include <locale.h>
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#define _(STRING) gettext(STRING)
#define HELP_TEXT _("predictor is an oracle that magically predicts the number you have chosen from 1 to 100\n\
\n\
Usage: predictor [OPTIONS]\n\
\n\
    --help, -h      show this message\n\
    --vesrion, -v   print version\n\
    --roman, -r     use roman numbers\n\
\n\
")

static char *roman_nums[] = {
    "N", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
    "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
    "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX",
    "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
    "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
    "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
    "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
    "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX",
    "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
    "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};

/**
 * Converts number from decimal numeric system to roman numeric system
 * @param num Decimal number from 1 to 100
 * 
 * @returns Point to char representation of number in roman numeric system  
*/
char *dec_to_roman(int num) {
	return roman_nums[num];
}


/**
 * Converts number from roman numeric system to decimal numeric system
 * @param roman_num Roman number from I (1) to C (100)
 * 
 * @returns Integer decimal number that corresponds given roman number. If number is out of range return -1 
*/
int roman_to_dec(char *roman_num) {
    for (int i = 0; i < sizeof(roman_nums); i++) {
		if (!strcasecmp(roman_num, roman_nums[i])) {
			return i;
		}
	}
	return -1;
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("predictor", getenv("PWD"));
    textdomain("predictor");
    int left = 0, right = 100, curr;
    char answ[5];
    int roman = 0;
    if (argc > 1) {
        if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
            printf(HELP_TEXT);
            return 0;
        } else if (!strcmp(argv[1], "--version") || !strcmp(argv[1], "-v")) {
            printf(VERSION);
            return 0;
        } else if (!strcmp(argv[1], "--roman") || !strcmp(argv[1], "-r")) {
            roman = 1;
        }
    }
    if (roman) {
        printf(_("Guess the number between %s and %s\n"), dec_to_roman(1), dec_to_roman(100));
    } else {
        printf(_("Guess the number between 0 and 100\n"));
    }
    while(left < right) {
        curr = (left + right) / 2;
        if (roman) {
            printf(_("Is your number greater then %s? [Yes/No]\n"), dec_to_roman(curr));
        } else {
            printf(_("Is your number greater then %d? [Yes/No]\n"), curr);
        }
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
    if (roman) {
        printf(_("I guess your number is %s\n"), dec_to_roman(left));
    } else {
        printf(_("I guess your number is %d\n"), left);
    }
}
