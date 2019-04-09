/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** find_second_arg.c
*/

#include <string.h>
#include <stdio.h>

char *find_second_arg(const char *input)
{
    char *p = (char *) input;

    p += strcspn(p, " \r\n");
    p += strspn(p, " \r\n");
    p = strndup(p, strcspn(p, " \r\n"));
    return (p);
}
