/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** main.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "myftp.h"
#include "utils.h"
#include "socket.h"

long int get_port(const char *port_str)
{
    long port;
    char *endptr = (char *) port_str;

    port = strtol(port_str, &endptr, 10);
    if (port_str == endptr || port < 1 || port > 65535)
        exit_with("error: '%s' isn't a number between 1 and 65535", port_str);
    return port;
}

int main(int ac, char *av[])
{
    if (ac != 3)
        return (84);
    start_ftp(get_port(av[1]), av[2]);
    return (0);
}
