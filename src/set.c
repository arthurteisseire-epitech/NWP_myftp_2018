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
        exit_with("failed to allocate memory");
    return set;
}
