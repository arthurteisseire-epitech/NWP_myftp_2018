/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** main.c
*/

#include <sys/types.h>
#include <sys/socket.h>

int main()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}