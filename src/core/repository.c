#include "../../include/repository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

repository* initialize(const char* path, int bare) {
    repository *repo = malloc(sizeof(repository));

    if (!repo) 
        return NULL;
    
    repo->is_bare = bare;

    if (bare) {
        repo->path = strdup(path);
        repo->path_zit_dir = strdup(path);
    } else {
        repo->path = strdup(path);
        repo->path_zit_dir = malloc(strlen(path) + strlen(ZIT_DIR) + 2);
        snprintf(repo->path_zit_dir, strlen(path) + strlen(ZIT_DIR) + 2, "%s/%s", path, ZIT_DIR);
    }

    repo->path_objects = malloc(strlen(repo->path_zit_dir + 8));
    repo->path_refs = malloc(strlen(repo->path_zit_dir + 6)); 
    repo->path_head = malloc(strlen(repo->path_zit_dir + 6));

    snprintf(repo->path_objects, (strlen(repo->path_zit_dir) + 8), "%s/objects", repo->path_zit_dir);
    snprintf(repo->path_refs, (strlen(repo->path_zit_dir) + 6), "%s/refs", repo->path_zit_dir);
    snprintf(repo->path_head, (strlen(repo->path_zit_dir) + 6), "%s/HEAD", repo->path_zit_dir);

    if (mkdir(repo->path_zit_dir, DEFAULT_DIR_MODE) == -1 && errno != EEXIST) {
        perror("Failed to create .zit directory");
        destroy(repo);
        return NULL;
    }

    struct stat file_info;
    const char* dirs[] = {
        repo->path_objects,
        repo->path_refs, 
        NULL
    };

    for (const char **dir = dirs; *dir; dir++) {
        if (mkdir(*dir, DEFAULT_DIR_MODE) == -1 && errno != EEXIST) {
            perror("Failed to create subdirectory");
            destroy(repo);
            return NULL;
        }
    }

    FILE* head = fopen(repo->path_head, "w");
    if (!head) {
        perror("Failed to create HEAD file");
        destroy(repo);
        return NULL;
    }

    fprintf(head, "ref: refs/heads/main\n");
    fclose(head);

    return repo;
}

void destory(repository* repo) {
    if (!repo) return;
    free(repo->path);
    free(repo->path_zit_dir);
    free(repo->path_objects);
    free(repo->path_refs);
    free(repo->path_head);
    free(repo);
}