/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** concat.c
*/

#include <string.h>
#include "utils.h"

char *concat(const char *str1, const char *str2)
{
    char *res = safe_malloc(strlen(str1) + strlen(str2) + 1);

    strcpy(res, str1);
    strcat(res, str2);
    return (res);
}

