#include "include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
	if (argc < 2) {
		usage(argv[0]);
	}

	argc--; argv++;

	for (command *cmd = commands; cmd->name; cmd++) {
		if (strcmp(argv[0], cmd->name) == 0) {
			return cmd->fn(argc, argv);
		}
	}

	fprintf(stderr, "Unknown command '%s'\n", argv[0]);
	usage(argv[0]);
}
