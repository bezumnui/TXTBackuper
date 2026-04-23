//
// Created by George Viznyuk on 23/04/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* join_path_with_alloc(const char *path, const char *name) {
    int path_len = strlen(path) + sizeof('/') + strlen(name) + sizeof('\x00');
    char *result = malloc(path_len);
    sprintf(result, "%s/%s", path, name);
    return result;
}
