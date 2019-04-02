/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** exit_with.c
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void exit_with(const char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(84);
}
