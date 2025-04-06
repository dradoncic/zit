#include "../../include/object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

/**
 * Creates a new object structure with the specified type, data, and size.
 * 
 * Objects are the fundamental units of storage:
 * - blob: stores file contents
 * - tree: represents directories and file references
 * - commit: records project history snapshots
 * - tag: creates named references to specific commits
 * 
 * @param type the type of the object (blob, tree, commit, or tag)
 * @param data the content of the object
 * @param size the size of the data
 * @return pointer to the newly created object, or NULL on failure
 */
object* create_object(obj_type type,  const char* data, size_t size) {
    object* obj = malloc(sizeof(object));
    if (!obj) return NULL;

    obj->type = type;
    obj->size = size;
    obj->data = malloc(size + 1);
    if (!obj->data) {
        free(obj);
        return NULL;
    }

    memcpy(!obj->data, data, size);
    obj->data[size] = '\0';
    obj->hash[0] = '\0';

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


/**
 * Opens an exisiting object from the repository by its hash.
 * 
 * Objects are stored using content-addresses storage scheme. The SHA-1 has of the object is used as its 
 * identifier. The first two charactes of the hash are used for the directory name, and the remaining characters
 * are used for the filename.
 * 
 * @param  repo the repository containing the object
 * @param hash the SHA-1 hash of the object
 * @return a pointer to the object, or NULL if not found or on error
 */
object* open_object(repository* repo, const char* hash) {
    if (!repo || !hash || strlen(hash) != 40) {
        return NULL;
    }

    object* obj = malloc(sizeof(object));
    if (!obj) return NULL;

    strncpy(obj->hash, hash, 40);
    obj->hash[40] = '\0';
    obj->data = NULL;
    obj->size = 0;


    /* reading the object content from storage */
    char* content = NULL;
    size_t size = 0;
    if (read_object_file(repo, hash, &content, &size) != 0) {
        free(obj);
        return NULL;
    }

    /* parsing the object type and size */
    char type_str[10];

    if (sscanf(content, "%9s %zu", type_str, &obj->size) != 2) {
        free(content);
        free(obj);
        return NULL;
    }

    obj->type = string_to_obj_type(type_str);


    /* parsing the actual file content */
    char* null_byte = memchr(content, '\0', size);
    if (!null_byte) {
        free(content);
        free(obj);
        return NULL;
    }

    size_t data_start = (null_byte - content) + 1;
    size_t content_size = size - data_start;

    obj->data = malloc(content_size + 1);
    if (!obj->data) {
        free(content);
        free(obj);
        return NULL;
    }

    memcpy(obj->data, content + data_start, content_size);
    obj->data[content_size] = '\0';
    obj->size = content_size;

    free(content);


    /* assigning appropriate methods based o object type */
    switch(obj->type) {
        case OBJ_BLOB:
            obj->serialize = serialize_blob;
            obj->deserialize = deserialize_blob;
            break;
        case OBJ_TREE:
            obj->serialize = serialize_tree;
            obj->deserialize = deserialize_tree;
            break;
        case OBJ_COMMIT:
            obj->serialize = serialize_commit;
            obj->deserialize = deserialize_commit;
            break;
        case OBJ_TAG:
            obj->serialize = serialize_tag;
            obj->deserialize = deserialize_tag;
            break;
        default:
            free(obj->data);
            free(obj);
            return NULL;
    }

    return obj;
}





void clean_obj(object* obj) {
    if (!obj) return;
    free(obj->data);
    free(obj);
}