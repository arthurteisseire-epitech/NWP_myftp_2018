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
    CODE_STATUS_OK = 150,
    CODE_OK = 200,
    CODE_HELP_OK = 214,
    CODE_USER = 331,
    CODE_LOGIN_FIRST = 503,
    CODE_LOGIN_INCORRECT = 530,
    CODE_LOGIN_SUCCESS = 230,
    CODE_COMMAND_NOT_FOUND = 500,
    CODE_QUIT = 221,
    CODE_FAILED = 550,
    CODE_SUCCESS = 250,
    CODE_PASSIVE_MODE = 227,
    CODE_TRANSFER_COMPLETE = 226,
    CODE_NO_MODE = 425,
};

struct code_message_s {
    enum code_e code;
    char *message;
};

static const struct code_message_s codes[] = {
    {CODE_CONNECTION,        "(vsFTPd 3.0.0)"},
    {CODE_USER,              "Please specify the password."},
    {CODE_LOGIN_FIRST,       "Login with USER first."},
    {CODE_LOGIN_INCORRECT,   "Login incorrect."},
    {CODE_LOGIN_SUCCESS,     "Login successful."},
    {CODE_COMMAND_NOT_FOUND, "Unknown command."},
    {CODE_FAILED,            "Failed"},
    {CODE_SUCCESS,           "Success"},
    {CODE_OK,                "ok."},
    {CODE_HELP_OK,           "Help ok."},
    {CODE_QUIT,              "Goodbye."},
    {CODE_PASSIVE_MODE,      "Entering Passive Mode"},
    {CODE_STATUS_OK,         "File status ok about to open connection."},
    {CODE_TRANSFER_COMPLETE, "Transfer complete."},
    {CODE_NO_MODE,           "Use PORT or PASV first."},
    {0, NULL},
};

void send_message(int fd, enum code_e code, const char *str);

#endif
