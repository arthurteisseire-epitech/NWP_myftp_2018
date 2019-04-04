/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** send_message.c
*/

#include "code.h"

static void print_message(int fd, enum code_e code, const char *str, int i)
{
    if (str)
        dprintf(fd, "%d %s %s\r\n", code, codes[i].message, str);
    else
        dprintf(fd, "%d %s\r\n", code, codes[i].message);
}

void send_message(int fd, enum code_e code, const char *str)
{
    for (int i = 0; codes[i].message; ++i)
        if (codes[i].code == code) {
            print_message(fd, code, str, i);
            return;
        }
    dprintf(fd, "%d Code not implemented\r\n", code);
}

