/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** exec_command.c
*/

#include <unistd.h>
#include <string.h>
#include "code.h"
#include "utils.h"
#include "myftp.h"
#include "command.h"

static int exec_guest_command(poll_t *poll, connection_t *conn,
    const char *input)
{
    for (int i = 0; guest_commands[i].name; ++i)
        if (begin_with(guest_commands[i].name, input))
            return (guest_commands[i].f(poll, conn, input));
    return (COMMAND_NOT_FOUND);
}

static int exec_admin_command(poll_t *poll, connection_t *conn,
    const char *input)
{
    for (int i = 0; admin_commands[i].name; ++i)
        if (begin_with(admin_commands[i].name, input))
            return (admin_commands[i].f(poll, conn, input));
    return (COMMAND_NOT_FOUND);
}

static int exec_any_command(poll_t *poll, connection_t *conn, const char *input)
{
    int status;

    status = exec_guest_command(poll, conn, input);
    if (status == COMMAND_NOT_FOUND)
        status = exec_admin_command(poll, conn, input);
    return (status);
}

void exec_command(poll_t *poll, connection_t *conn, const char *input)
{
    int status;

    if (!is_admin(&conn->user)) {
        status = exec_guest_command(poll, conn, input);
        if (status == COMMAND_NOT_FOUND) {
            send_message(conn->sock.fd, CODE_LOGIN_INCORRECT, NULL);
            status = 0;
        }
    } else {
        status = exec_any_command(poll, conn, input);
    }
    if (status == COMMAND_NOT_FOUND)
        send_message(conn->sock.fd, CODE_COMMAND_NOT_FOUND, NULL);
}

void exec_all_commands(poll_t *poll, connection_t *conn)
{
    char *input = NULL;
    size_t rd_bytes = 0;
    FILE *socket = fdopen(conn->sock.fd, "r");

    while (getline(&input, &rd_bytes, socket) > 0)
        if (strcmp(input, "\r\n") != 0)
            exec_command(poll, conn, input);
}
