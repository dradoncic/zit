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


// external functions to interact with objects
object* create_object(obj_type type, const char* data, size_t size);
object* open_object(repository* repo, const char* hash);
void clean_obj(object* obj);

// some more internal functions that are going to 
static int compute_hash(const char* header, size_t header_size, const char* content, size_t content_size, char* out_hash);
static int write_object_file(repository* repo, const char* hash, const char* content, size_t size);
static int read_object_file(repository* repo, const char* hash, char** content, size_t* size);
static const char* obj_type_to_string(obj_type type);
static obj_type string_to_obj_type(const char* type_str);

// helper functions for specified object types
static int serialize_blob(repository* repo, object obj);
static int deserialize_blob(repository* repo, object obj, const char* hash);
static int serialize_commit(repository* repo, object obj);
static int deserialize_commit(repository* repo, object obj, const char* hash);
static int serialize_tree(repository* repo, object obj);
static int deserialize_tree(repository* repo, object obj, const char* hash);
static int serialize_tag(repository* repo, object obj);
static int deserialize_tag(repository* repo, object obj, const char* hash);


#endif