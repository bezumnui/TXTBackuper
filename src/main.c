//
// Created by George Viznyuk on 23/04/2026.
//
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "scaner.h"
#include "backup.h"

#define PIPE_READ 0
#define PIPE_WRITE 1

void fill_buffer_details(const FILES_LIST *list, FILE_DETAILS *buffer) {
    if (buffer == NULL) {
        return;
    }

    for (int i = 0; i < list->count; i++) {
        buffer[i] = *list->details[i];
    }
}


void send_files_to_child(int fd[2], FILES_LIST *list) {

    if (list == NULL) {
        perror("failed to allocate space");
        return;
    }

    if (list->status == FAILED_NO_DIR) {
        printf("failed. Dir does not exist");
        return;
    }

    if (list->status != STATUS_OK) {
        perror("failed to assemble file list");
        return;
    }


    FILE_DETAILS *buffer = malloc(sizeof(FILE_DETAILS) * list->count);


    fill_buffer_details(list, buffer);

    write(fd[PIPE_WRITE], buffer, sizeof(FILE_DETAILS) * list->count);
    free(buffer);
}

int main(int argc, char *argv[]) {
    int fd[2];
    pid_t pid;

    if (argc < 2) {
        printf("failed to run: No path mentioned.\n");
        return 1;
    }

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
    } else if (pid == 0) {
        signal(SIGINT, exit);
        logger_entrypoint(fd);
    } else {
        close(fd[PIPE_READ]);
        FILES_LIST *list = get_txt_files_with_alloc(argv[1]);
        send_files_to_child(fd, list);
        close(fd[PIPE_WRITE]);
        backup(list);
        free_files_list(list);
    }

    return 0;
}
