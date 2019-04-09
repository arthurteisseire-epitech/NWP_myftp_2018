/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** utils.h
*/

#ifndef PSU_MYFTP_2018_UTILS_H
#define PSU_MYFTP_2018_UTILS_H

#include <stdlib.h>
#include <stdbool.h>
#include "command.h"

void *safe_malloc(size_t size);
void exit_with(const char *msg, ...);
bool begin_with(const char *pre, const char *str);
char *concat(const char *str1, const char *str2);
char *find_second_arg(const char *input);
char *get_file_path_from_input(const char *root, const char *user_path,
    const char *input);
char *get_dir_path_from_input(const char *root, const char *user_path,
    const char *input);
char *get_user_path(const char *path);
bool is_admin(const struct user_s *user);

#endif
