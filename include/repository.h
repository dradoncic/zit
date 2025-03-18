#ifndef REPOSITORY_H
#define REPOSITORY_H

#define ZIT_DIR ".zit"
#define DEFAULT_DIR_MODE 0755

typedef struct {
    char* path;             // root path of the repository
    char* path_zit_dir;     // full path of the .zit directory
    char* path_objects;     // the object store
    char* path_refs;        // the reference store
    char* path_head;        // reference the current HEAD
    int is_bare;            // bare repository flag
} repository;

repository* initialize(const char* path, int bare);

static int valid(const char* path);

static repository* fill(const char* path, int bare);

repository* open(const char* path);

void destroy(repository* repo);

#endif