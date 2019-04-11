/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** my_realpath.c
*/

#include <stdlib.h>
#include "utils.h"

char *my_realpath(const char *path)
{
    char *tmp = realpath(path, NULL);
    char *real_path = NULL;

    if (tmp)
        real_path = concat(tmp, "/");
    free(tmp);
    return (real_path);
}
