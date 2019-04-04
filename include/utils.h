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

void *safe_malloc(size_t size);
void exit_with(const char *msg, ...);
bool begin_with(const char *pre, const char *str);
char *concat(const char *str1, const char *str2);
char *find_second_arg(const char *input);

#endif
