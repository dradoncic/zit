#include <stdio.h>
#include <stdlib.h>

int cmd_list_files(int argc, char** argv) {
    fprintf(stdout, "%s\n", argv[0]);
    exit(1);
}