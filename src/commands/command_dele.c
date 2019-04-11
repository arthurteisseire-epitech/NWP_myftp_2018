/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** commande_dele.c
*/

#include "code.h"
#include "utils.h"
#include "poll.h"

int command_dele(__attribute((unused))poll_t *poll, connection_t *conn,
    const char *input)
{
    char *path = get_file_path_from_input(conn->user.path, input);

    if (remove(path) == -1)
        send_message(conn->sock.fd, CODE_FAILED, "to remove");
    else
        send_message(conn->sock.fd, CODE_SUCCESS, "to remove");
    return (0);
}
