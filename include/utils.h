#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

typedef struct {
	const char *name;
	int (*fn)(int, char**);
	const char *help;
} command;

extern command commands[];

void usage(const char* progname);

bool file_exists(const char* path);

bool dir_exists(const char* path);

#endif 
