#include <stdio.h>
#include <stdlib.h>

int cmd_ls_tree(int argc, char** argv) {
    fprintf(stdout, "%s\n", argv[0]);
    exit(1);
}