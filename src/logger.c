//
// Created by George Viznyuk on 23/04/2026.
//
#include <stdio.h>
#include "logger.h"

#include <stdlib.h>
#include <unistd.h>
#include "files.h"

#define PIPE_READ 0
#define PIPE_WRITE 1

void logger_entrypoint(int fd[]) {
    close(fd[PIPE_WRITE]);
    FILE_DETAILS details;

    printf("Files logging...\n");
    printf("timestamp           size          name\n");

    while (read(fd[0], &details, sizeof(FILE_DETAILS)) > 0) {
        printf("%lu          %lub           %s\n", details.timestamp, details.size, details.name);
    }

    close(fd[PIPE_READ]);

}