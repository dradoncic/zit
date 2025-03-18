#include <stdio.h>
#include <stdlib.h>

int cmd_add(int argc, char** argv) {
    fprintf(stdout, "%s\n", argv[0]);
    exit(1);
}