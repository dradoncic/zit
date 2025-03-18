#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
	const char* progname = argv[0];

	if (argc < 2) 
		usage(progname);

	argc--; argv++;

	for (command *cmd = commands; cmd-> name; cmd++) {
		if (strcmp(argv[0], cmd->name) == 0) {
			return cmd->fn(argc, argv);
		}
	}

	fprintf(stderr, "%s: unknown command '%s'\n", progname, argv[0]);
	usage(progname);
	return 1;
}
