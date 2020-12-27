/* #include <bits/stdc++.h> */
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>


static bool stop = false;

static void handle_term(int sig)
{
    stop = true;
}

int main(int argc, char* argv[])
{
    signal(SIGTERM, handle_term);

    if (argc < 3)
    {
        printf("usage:%s ip_address port_number backlog\n", basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);


    struct sockaddr_in address;
    bzero(&address, sizeof(address));

    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));

    ret = listen(sock, backlog);
    sleep(20);

    struct sockaddr_in client;
    socklen_t client_addrlenth = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlenth);
    if (connfd < 0)
    {
        printf("errno is: %d\n", errno);
    }
    else {
        char remote[INET_ADDRSTRLEN];
        printf("connected with ip:%s and port:%d\n", inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN), ntohs(client.sin_port));

    }

    close(sock);
    return 0;


    return 0;
}

