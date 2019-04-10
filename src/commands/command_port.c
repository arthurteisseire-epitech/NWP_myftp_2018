/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_port.c
*/

#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
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

static void fill_socket(sock_t *data_sock, char *port_str)
{
    data_sock->size_info = sizeof(data_sock->info);
    data_sock->info.sin_port = get_port(port_str);
    data_sock->info.sin_family = AF_INET;
    data_sock->fd = socket(AF_INET, SOCK_STREAM,
        getprotobyname("TCP")->p_proto);
}

int command_port(__attribute((unused))poll_t *poll, connection_t *conn,
    const char *input)
{
    char *ip_str = find_second_arg(input);
    char *port_str = split_arg(ip_str);

    if (port_str == NULL ||
        !inet_aton(ip_str, &conn->data_sock.info.sin_addr)) {
        send_message(conn->sock.fd, CODE_COMMAND_NOT_FOUND,
            "Invalid port command.");
        return (-1);
    }
    fill_socket(&conn->data_sock, port_str);
    send_message(conn->sock.fd, CODE_SUCCESS,
        "PORT command successful. Consider using PASV.");
    conn->mode = ACTIVE;
    free(ip_str);
    return (0);
}
