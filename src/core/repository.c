#include "../../include/repository.h"
#include "../../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

repository* initialize(const char* path, int bare) {
    repository *repo = malloc(sizeof(repository));

    if (!repo) return NULL;
    
    repo->is_bare = bare;

    if (bare) {
        repo->path = strdup(path);
        repo->path_zit_dir = strdup(path);
    } else {
        repo->path = strdup(path);
        repo->path_zit_dir = malloc(strlen(path) + strlen(ZIT_DIR) + 2);
        snprintf(repo->path_zit_dir, strlen(path) + strlen(ZIT_DIR) + 2, "%s/%s", path, ZIT_DIR);
    }

    repo->path_objects = malloc(strlen(repo->path_zit_dir) + OBJECTS_L);
    repo->path_refs = malloc(strlen(repo->path_zit_dir) + REFS_L);
    repo->path_refs_tags = malloc(strlen(repo->path_zit_dir) + TAGS_L);
    repo->path_refs_heads = malloc(strlen(repo->path_zit_dir) + HEADS_L);
    repo->path_head = malloc(strlen(repo->path_zit_dir) + HEAD_L);

    snprintf(repo->path_objects, (strlen(repo->path_zit_dir) + OBJECTS_L), "%s%s", repo->path_zit_dir, OBJECTS);
    snprintf(repo->path_refs, (strlen(repo->path_zit_dir) + REFS_L), "%s%s", repo->path_zit_dir, REFS);
    snprintf(repo->path_refs_tags, (strlen(repo->path_zit_dir) + TAGS_L), "%s%s", repo->path_zit_dir, TAGS);
    snprintf(repo->path_refs_heads, (strlen(repo->path_zit_dir) + HEADS_L), "%s%s", repo->path_zit_dir, HEADS);
    snprintf(repo->path_head, (strlen(repo->path_zit_dir) + HEAD_L), "%s%s", repo->path_zit_dir, HEAD);

    if (mkdir(repo->path_zit_dir, DEFAULT_DIR_MODE) == -1 && errno != EEXIST) {
        perror("Failed to create .zit directory");
        destroy(repo);
        return NULL;
    }

    const char* dirs[] = {
        repo->path_objects,
        repo->path_refs,
        repo->path_refs_tags,
        repo->path_refs_heads,
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


repository* open(const char* inpath) {
    char* path = inpath ? realpath(inpath, NULL) : getcwd(NULL, 0);
    if (!path) return NULL;

    repository* repo = NULL;

    if (valid(path)) {
        repo = fill(path, 1);
    }

    if (!repo) {
        char* fullpath = NULL;
        if (asprintf(&fullpath, "%s/.zit", path) == -1 || !fullpath) {
            free(path);
            return NULL;
        }

        if (valid(fullpath)) {
            repo = fill(fullpath, 0);
        }

        free(fullpath);
    }

    free(path);
    return repo;
}


bool valid(const char* path) {
    if (!dir_exists(path)) {
        return false;
    }

    char* path_objects = malloc(strlen(path) + OBJECTS_L);
    char* path_refs = malloc(strlen(path) + REFS_L);
    char* path_refs_tags = malloc(strlen(path) + TAGS_L);
    char* path_refs_heads = malloc(strlen(path) + HEADS_L);
    char* path_head = malloc(strlen(path) + HEAD_L);

    if (!path_objects || !path_refs || !path_refs_tags || !path_refs_heads || !path_head) {
        free(path_objects);
        free(path_refs);
        free(path_refs_tags);
        free(path_refs_heads);
        free(path_head);
        return false;
    }

    snprintf(path_objects, strlen(path) + OBJECTS_L, "%s%s", path, OBJECTS);
    snprintf(path_refs, strlen(path) + REFS_L, "%s%s", path, REFS);
    snprintf(path_refs_tags, strlen(path) + TAGS_L, "%s%s", path, TAGS);
    snprintf(path_refs_heads, strlen(path) + HEADS_L, "%s%s", path, HEADS);
    snprintf(path_head, strlen(path) + HEAD_L, "%s%s", path, HEAD);

    bool is_valid = dir_exists(path_objects) &&
                    dir_exists(path_refs) &&
                    dir_exists(path_refs_heads) &&
                    dir_exists(path_refs_tags) &&
                    file_exists(path_head);

    free(path_objects);
    free(path_refs);
    free(path_refs_tags);
    free(path_refs_heads);
    free(path_head);

    return is_valid;
}

repository* fill(const char* path, int bare) {
    repository* repo = malloc(sizeof(repository));
    if (!repo) return NULL;

    if (!bare) {
        size_t root_path_len = strlen(path) - strlen(ZIT_DIR);
        repo->path = malloc(root_path_len + 1);
        if (!repo->path) {
            free(repo);
            return NULL;
        }
        strncpy(repo->path, path, root_path_len);
        repo->path[root_path_len] = '\0';
        repo->path_zit_dir = strdup(path);
    } else {
        repo->path = strdup(path);
        repo->path_zit_dir = strdup(path);
    }

    repo->path_objects = malloc(strlen(path) + 9);
    repo->path_refs = malloc(strlen(path) + 6);
    repo->path_refs_tags = malloc(strlen(path) + 11);
    repo->path_refs_heads = malloc(strlen(path) + 12);
    repo->path_head = malloc(strlen(path) + 6);
    repo->is_bare = bare;

    snprintf(repo->path_objects, (strlen(path) + 9), "%s/objects", path);
    snprintf(repo->path_refs, (strlen(path) + 6), "%s/refs", path);
    snprintf(repo->path_refs_tags, (strlen(path) + 11), "%s/refs/tags", path);
    snprintf(repo->path_refs_heads, (strlen(path) + 12), "%s/refs/heads", path);
    snprintf(repo->path_head, (strlen(path) + 6), "%s/HEAD", path);

    return repo;
}

void destroy(repository* repo) {
    if (!repo) return;
    free(repo->path);
    free(repo->path_zit_dir);
    free(repo->path_objects);
    free(repo->path_refs);
    free(repo->path_refs_tags);
    free(repo->path_refs_heads);
    free(repo->path_head);
    free(repo);
}