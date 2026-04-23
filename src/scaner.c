//
// Created by George Viznyuk on 23/04/2026.
//

#include "files.h"
#include <stdio.h>
#include <dirent.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILES 1024


FILES_LIST *get_txt_files_with_alloc(char *path) {
    struct dirent *entry;
    FILES_LIST *list = malloc(sizeof(FILES_LIST));
    list->details = malloc(sizeof(FILE_DETAILS*) * MAX_FILES);
    if (list == NULL) {
        return NULL;
    }

    const DIR *dp = opendir(path);

    if (dp == NULL) {
        list->status = FAILED_NO_DIR;
        return list;
    }

    int count = 0;

    while ((entry = readdir(dp))) {
        if (list->count + 1 >= MAX_FILES)
            break;

        if (!strstr(entry->d_name, ".txt"))
            continue;

        FILE_DETAILS *details = malloc(sizeof(FILE_DETAILS));
        list->details[list->count++] = details;


        strncpy(details->name, entry->d_name, sizeof(details->name));

        char *file_path = join_path_with_alloc(path, entry->d_name);

        struct stat st;
        if (stat(file_path, &st) == 0) {
            details->size = st.st_size;
            details->timestamp = st.st_birthtimespec.tv_sec;
        }
        strncpy(details->path, file_path, (int) fmin(sizeof(details->path) * sizeof(char), strlen(file_path)));

        free(file_path);
    }
    list->status = STATUS_OK;
    return list;
}

void free_files_list(FILES_LIST *list) {
    for (int i = 0; i < list->count; ++i) {
        free(list->details[i]);
    }
    free(list->details);
    free(list);
}
