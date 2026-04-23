//
// Created by George Viznyuk on 23/04/2026.
//

#include <stdio.h>
#include <stdlib.h>

#include "files.h"

#define BUFFER_SIZE 4096


void backup(const FILES_LIST *files) {
    for (int i = 0; i < files->count; ++i) {
        FILE_DETAILS *details = files->details[i];

        char *backup_path = join_path_with_alloc("backup", details->name);

        FILE *src = fopen(details->path, "rb");
        FILE *dst = fopen(backup_path, "wb");

        free(backup_path);

        if (src == NULL || dst == NULL) {
            perror("failed to open a file");
            if (src)
                fclose(src);
            continue;
        }

        char buffer[BUFFER_SIZE];
        size_t bytes;

        while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
            fwrite(buffer, 1, bytes, dst);
        }

        printf("Backup finished for: %s\n", details->name);

        fclose(src);
        fclose(dst);
    }
}
