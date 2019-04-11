/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** begin_with.c
*/

#include <stdbool.h>
#include <string.h>

bool begin_with(const char *pre, const char *str)
{
    size_t len_pre = strlen(pre);
    size_t len_str = strlen(str);

    return (len_str < len_pre ? false : strncasecmp(pre, str, len_pre) == 0);
}
