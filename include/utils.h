#ifndef UTILS_H
#define UTILS_H

typedef struct {
	const char *name;
	int (*fn)(int, char**);
	const char *help;
} command;

extern command commands[];

void usage(const char* progname);

int file_exists(const char* path);

int dir_exists(const char* path);


#endif 
