/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** code.h
*/

#ifndef PSU_MYFTP_2018_CODE_H
#define PSU_MYFTP_2018_CODE_H

#include <stdio.h>

enum code_e {
    CODE_CONNECTION = 220,
    CODE_USER = 331,
    CODE_LOGIN_FIRST = 503,
    CODE_LOGIN_INCORRECT = 530,
    CODE_LOGIN_SUCCESS = 230,
    CODE_COMMAND_NOT_FOUND = 500,
    CODE_QUIT = 221,
};

struct code_message_s {
    enum code_e code;
    char *message;
};

static const struct code_message_s codes[] = {
    {CODE_CONNECTION, "(vsFTPd 3.0.0)"},
    {CODE_USER, "Please specify the password."},
    {CODE_LOGIN_FIRST, "Login with USER first."},
    {CODE_LOGIN_INCORRECT, "Login incorrect."},
    {CODE_LOGIN_SUCCESS, "Login successful."},
    {CODE_COMMAND_NOT_FOUND, "Unknown command."},
    {CODE_QUIT, "Goodbye."},
    {0, NULL},
};

static inline void send_message(int fd, enum code_e code)
{
    for (int i = 0; codes[i].message; ++i)
        if (codes[i].code == code) {
            dprintf(fd, "%d %s\n", code, codes[i].message);
            return;
        }
    dprintf(fd, "%d Code not implemented\n", code);
}

#endif
