//
// Created by George Viznyuk on 23/04/2026.
//

#ifndef FILES_H
#define FILES_H

#define FAILED_NO_DIR -2
#define FAILED -1
#define STATUS_OK 0
#include <time.h>

typedef struct FILE_DETAILS_ {
    char name[256];
    char path[512 * sizeof(char)];
    size_t size;
    time_t timestamp;
} FILE_DETAILS;

typedef struct FILES_LIST_ {
    FILE_DETAILS **details;
    int count;
    int status;
} FILES_LIST;


char* join_path_with_alloc(const char *path, const char *name);

#endif //FILES_H
