#include "../../include/repository.h"
#include "../../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>


int cmd_add(int argc, char** argv) {
    repository* repo = open(ROOT);
    if (!repo) {
        fprintf(stderr, "Failed to open the repository.\n");
        return 1;
    }

    // now we have to add in all the logic to add our changes to the staging area.

    clean_repo(repo);

    return 0;
}