#include "../include/commands.h"
#include <stdio.h>
#include <stdlib.h>

int cmd_cat_file(int argc, char** argv) {
    fprintf(stdout, "%s", argv[0]);
    exit(1);
}