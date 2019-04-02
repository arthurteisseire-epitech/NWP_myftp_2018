/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** safe_alloc.c
*/

#include <stdlib.h>
#include "utils.h"

void *safe_malloc(size_t size)
{
    void *p = malloc(size);

    if (p == NULL)
        exit_with("failed to malloc");
    return (p);
}
