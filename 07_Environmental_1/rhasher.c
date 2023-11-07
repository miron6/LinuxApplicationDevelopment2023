#include <rhash.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include "config.h"

#if READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

size_t getlinewrap(char **line) {
#ifdef READLINE
	printf("HUI");
	if (*line) {
		free(*line);
	}
	*line = readline(NULL);
	if (*line == NULL) {
		return -1;
	}
	return strlen(*line);
#else
    size_t len = 0;
    return getline(line, &len, stdin);
#endif
}

int calc_hash(char *message, char *result, unsigned int hash_id, int enc) {
	unsigned char hash[64];
	int res_code;
	if (message[0] == '"' && message[strlen(message) - 1] == '"') {
		res_code = rhash_msg(hash_id, message + 1, strlen(message) - 1, hash);
	} else {
		res_code = rhash_file(hash_id, message, hash);
	}
	if (res_code < 0) {
		fprintf(stderr, "Hash calculation failed. Reason: ");
		fprintf(stderr, "%s\n", strerror(errno));
		return 1;
	}
	rhash_print_bytes(result, hash, rhash_get_digest_size(hash_id), enc);
	return 0;
}

int main(int argc, char **argv) {
	rhash_library_init();
	char *input = NULL;
	printf("> ");
	while (getlinewrap(&input) != -1) {
		char *cmd = strtok(input, " ");
		int enc = isupper(cmd[0]) ? RHPR_HEX : RHPR_BASE64;
		unsigned int hash_id;
		if (!strcasecmp(cmd, "md5")) {
			hash_id = RHASH_MD5;
		} else if (!strcasecmp(cmd, "sha1")) {
			hash_id = RHASH_SHA1;
		} else if (!strcasecmp(cmd, "tth")) {
			hash_id = RHASH_TTH;
		} else if (!strcasecmp(cmd, "md4")) {
			hash_id = RHASH_MD4;
		} else {
			fprintf(stderr, "Wrong hash type. Available: md5, sha1, tth, md4\n");
			printf("> ");
			continue;
		}
		char *message = strtok(NULL, " ");
		message = strtok(message, "\n");
		if (message == NULL || *message == '\0') {
			fprintf(stderr, "Empty input\n");
			printf("> ");
			continue;
		}
		char res[1024];
		if (calc_hash(message, res, hash_id, enc) == 0) {
			printf("%s\n", res);
		}
		printf("> ");
	}
	if (input != NULL) {
		free(input);
	}
}