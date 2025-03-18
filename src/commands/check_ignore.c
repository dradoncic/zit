#include <stdio.h>
#include <stdlib.h>

int cmd_check_ignore(int argc, char** argv) {
    fprintf(stdout, "%s\n", argv[0]);
    exit(1);
}