/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** main.c
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    struct sockaddr_in addr;
    int sockfd;

    addr.sin_family = AF_INET;
    addr.sin_port = 2000;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    return (0);
}