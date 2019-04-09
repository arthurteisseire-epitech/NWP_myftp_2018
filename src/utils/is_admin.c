/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** is_admin.c
*/

#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "myftp.h"
#include "command.h"

bool is_admin(const struct user_s *user)
{
    return (user->name != NULL &&
        user->password != NULL &&
        strcmp(user->name, USERNAME) == 0 &&
        strcmp(user->password, PASSWORD) == 0);
}

