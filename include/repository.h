#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <stdbool.h>

#define ZIT_DIR ".zit"
#define ROOT "."
#define DEFAULT_DIR_MODE 0755

#define OBJECTS "/objects"
#define REFS "/refs"
#define TAGS "/refs/tags"
#define HEADS "/refs/heads"
#define HEAD "/HEAD"

#define OBJECTS_L (sizeof(OBJECTS)) 
#define REFS_L (sizeof(REFS)) 
#define TAGS_L (sizeof(TAGS)) 
#define HEADS_L (sizeof(HEADS)) 
#define HEAD_L (sizeof(HEAD)) 

typedef struct {
    char* path;             // root path of the repository
    char* path_zit_dir;     // full path of the .zit directory
    char* path_objects;     // the object store
    char* path_refs;        // the reference store
    char* path_refs_tags;   // the reference tags store
    char* path_refs_heads;  // the reference heads stores
    char* path_head;        // reference the current HEAD
    int is_bare;            // bare repository flag
} repository;


// functionality to create and/or open zit repositories
repository* initialize(const char* path, int bare);
repository* ropen(const char* path);


// helper functions for memory management and validation
void clean_repo(repository* repo);
static bool valid(const char* path);
static repository* fill(const char* path, int bare);


#endif