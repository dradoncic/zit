#include "../../include/object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

object* create_object(obj_type type,  const char* data, size_t size) {
    object* obj = malloc(sizeof(object));
    if (!obj) return NULL;

    obj->type = type;
    obj->size = size;
    obj->data = malloc(strlen(data) + 1);
    obj->data = strdup(data);

    switch (type) {
        case OBJ_BLOB:
            obj->serialize = serialize_blob;
            obj->deserialize = deserialize_blob;
            break;
        case OBJ_TAG:
            obj->serialize = serialize_tag;
            obj->deserialize = deserialize_tag;
            break;
        case OBJ_TREE:
            obj->serialize = serialize_tree;
            obj->deserialize = deserialize_tree;
            break;
        case OBJ_COMMIT:
            obj->serialize = serialize_commit;
            obj->deserialize = deserialize_commit;
            break;
    }

    return  obj;
}


void clean_obj(object* obj) {
    if (!obj) return;
    free(obj->data);
    free(obj);
}