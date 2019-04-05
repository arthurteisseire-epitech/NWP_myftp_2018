/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** get_path.c
*/

#include <string.h>
#include "utils.h"

static char *get_path(const char *user_path, const char *input_path)
{
    char *path = safe_malloc(strlen(user_path) + strlen(input_path) + 2);

    strcpy(path, user_path);
    strcat(path, input_path);
    return (path);
}

char *get_file_path_from_input(const char *root, const char *user_path,
    const char *input)
{
    char *input_path = find_second_arg(input);
    char *path = get_path(user_path, input_path);
    char *real_path = concat(root, path);

    free(input_path);
    free(path);
    return (real_path);
}

char *get_dir_path_from_input(const char *root, const char *user_path,
    const char *input)
{
    char *file_path = get_file_path_from_input(root, user_path, input);
    char *real_path = concat(file_path, "/");

    free(file_path);
    return (real_path);
}
