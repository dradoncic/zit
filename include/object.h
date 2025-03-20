#ifndef OBJECT_H
#define  OBJECT_H

#include <zlib.h>
#include <stdlib.h>
#include "repository.h"

/*
<type> <size>\0<content>
hash[0:2] --> directory
hash[2:] --> filename 
*/

typedef enum {
    OBJ_BLOB,
    OBJ_TREE,
    OBJ_COMMIT,
    OBJ_TAG
} obj_type;

typedef struct {
    obj_type type;  
    char hash[41];      // SHA-1 hash (40 characters + null delimiter)
    size_t size;        // object size (bytes)
    char* data;         // raw content (for blobs, commits, etc.)

    int (*serialize)(repository* repo, struct object* obj);
    int (*deserialize)(repository* repo, struct object* obj, const char* hash);
} object;


// functionality to create and/or open select objects
object* create_object(obj_type type, const char* data, size_t size);
object* open_object(repository* repo, const char* hash);

// helper functions for specified object types
int serialize_blob(repository* repo, object obj);
int deserialize_blob(repository* repo, object obj, const char* hash);
int serialize_commit(repository* repo, object obj);
int deserialize_commit(repository* repo, object obj, const char* hash);
int serialize_tree(repository* repo, object obj);
int deserialize_tree(repository* repo, object obj, const char* hash);
int serialize_tag(repository* repo, object obj);
int deserialize_tag(repository* repo, object obj, const char* hash);

#endif