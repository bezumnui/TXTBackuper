//
// Created by George Viznyuk on 23/04/2026.
//

#ifndef SCANER_H
#define SCANER_H

#include "files.h"

FILES_LIST* get_txt_files_with_alloc(char path[]);
void free_files_list(FILES_LIST *list);
#endif //SCANER_H
