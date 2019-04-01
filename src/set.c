/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** set.c
*/

#include <stdlib.h>
#include "myftp.h"

set_t *set_init(void)
{
    set_t *set = calloc(1, sizeof(set_t));

    if (set == NULL)
        exit_with("failed to allocate memory for set");
    return set;
}

void set_add_fd(set_t *set, fd_t fd)
{
    set->readfds = realloc(set->readfds, sizeof(fd) * (set->size + 1));
    if (set->readfds == NULL)
        exit_with("failed to realloc readfds");
    set->readfds[set->size] = fd;
    ++set->size;
}
