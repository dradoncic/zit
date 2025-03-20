#include  "repository.h"
#include <zlib.h>
#include <stdlib.h>

/*
we are going to be implementing Zit objects, as Zit is a content-addressed filesystem

zit uses objects to store quite a lot of things: first and foremost, the actual files it keeps 
in version control -- source code

commits are objects, as well as tags

the path were zit stores a given objevt is computed by calculating the SHA-1 hash of its contents --
the first 2 characters being the directory name, and the rest as the file name

object storage system

<type> <size>\0<content>

*/

typedef enum {
    OBJ_COMMIT, 
    OBJ_TREE, 
    OBJ_BLOB,
    OBJ_TAG
} objtype;

typedef struct {
    objtype type;
    char hash[41];
    size_t size;
    char* data;

    int (*serialize)(repository* repo, object* obj);
    int (*deserialize)(repository* repo, object* obj, const char* hash);
} object;

int serialize_blob(repository* repo, object obj);
int deserialize_blob(repository* repo, object obj, const char* hash);
int serialize_commit(repository* repo, object obj);
int deserialize_commit(repository* repo, object obj, const char* hash);
int serialize_tree(repository* repo, object obj);
int deserialize_tree(repository* repo, object obj, const char* hash);
int serialize_tag(repository* repo, object obj);
int deserialize_tag(repository* repo, object obj, const char* hash);

object* create_object(objtype type, const char* data, size_t size);