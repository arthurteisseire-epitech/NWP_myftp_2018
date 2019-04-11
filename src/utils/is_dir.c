/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** is_dir.c
*/

#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>

bool is_dir(const char *path)
{
    DIR *dir = opendir(path);

    if (dir) {
        closedir(dir);
        return (true);
    }
    return (false);
}
