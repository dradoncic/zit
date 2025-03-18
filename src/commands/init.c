#include "../../include/repository.h"
#include <stdio.h>
#include <stdlib.h>

int cmd_init(int argc, char** argv) {
    int bare = 0;
    const char* path = ".";

    repository* repo = initialize(path, bare);
    if (!repo) {
        fprintf(stderr, "Failed to initialize repository\n");
        return 1;
    }

    printf("Initialized zit %s Zit repository at %s\n", bare ? "bare" : "empty", repo->path_zit_dir);

    destroy(repo);
    return 0;
}