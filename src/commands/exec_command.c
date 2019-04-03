/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** exec_command.c
*/

#include <unistd.h>
#include <string.h>
#include "command.h"

bool startsWith(const char *pre, const char *str)
{
    size_t len_pre = strlen(pre);
    size_t len_str = strlen(str);

    return (len_str < len_pre ? false : strncasecmp(pre, str, len_pre) == 0);
}

void exec_command(poll_t *poll, connection_t *conn)
{
    char input[64] = {0};
    int rd_bytes = read(conn->sock.fd, input, sizeof(input));

    input[rd_bytes] = '\0';
    for (int i = 0; commands[i].name; ++i)
        if (startsWith(commands[i].name, input))
            commands[i].f(poll, conn, input);
}
