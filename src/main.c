/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** main.c
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    struct sockaddr_in serv;
    socklen_t len = sizeof(serv);
    int sockfd;
    int connfd;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    printf("%s\n", inet_ntoa(serv.sin_addr));
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sockfd, (struct sockaddr *) &serv, len);
    listen(sockfd, 1);
    connfd = accept(sockfd, NULL, NULL);
    write(connfd, "Hello World!\n", sizeof("Hello World!\n"));
    return (0);
}