/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_port.c
*/

#include <arpa/inet.h>
#include <string.h>
#include "utils.h"
#include "code.h"
#include "poll.h"

static void replace(char *str, char old, char new)
{
    for (int i = 0; str[i]; ++i)
        if (str[i] == old)
            str[i] = new;
}

static char *split_arg(char *arg)
{
    char *substr = arg;

    replace(arg, ',', '.');
    for (int i = 0; i < 4; ++i) {
        substr = strstr(substr, ".");
        if (substr == NULL || *substr == '\0')
            return (NULL);
        if (i == 3)
            *substr = '\0';
        ++substr;
    }
    return (substr);
}

static in_port_t get_port(char *str)
{
    int left = strtol(str, &str, 10);
    int right;

    ++str;
    right = strtol(str, &str, 10);
    return (htons(left * 256 + right));
}

int command_port(__attribute((unused))poll_t *poll, connection_t *conn,
    const char *input)
{
    char *ip_str = find_second_arg(input);
    char *port_str = split_arg(ip_str);

    if (port_str == NULL ||
        !inet_aton(ip_str, (struct in_addr *) &conn->data_sock.info)) {
        send_message(conn->sock.fd, CODE_COMMAND_NOT_FOUND,
            "Invalid port command.");
        return (-1);
    }
    conn->data_sock.size_info = sizeof(conn->data_sock.info);
    conn->data_sock.info.sin_port = get_port(port_str);
    send_message(conn->sock.fd, CODE_SUCCESS,
        "PORT command successful. Consider using PASV.");
    conn->mode = ACTIVE;
    free(ip_str);
    return (0);
}
