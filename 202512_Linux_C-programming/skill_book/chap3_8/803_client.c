
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h> // 추가
#include <sys/socket.h>
#include <sys/types.h> // 추가
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IP_ADDR "127.0.0.1"
#define MAX_MSGLEN 1024

void
main(int argc, char *argv[])
{
    int i, quit;
    int ports;
    int sockfd;
    int r_len;
    char s[INET_ADDRSTRLEN];
    char buffer[MAX_MSGLEN];
    fd_set fd_mstr, fd_read;
    struct addrinfo hints, *info;

    if (argc != 3 || argv[1][0] != '-') {
        perror("Usage: ./a.out -p <portnum>");
        exit(1);
    }
    getopt(argc, argv, "p");

    ports = atoi(argv[2]);
    if (ports < 1024 || ports > 65535) {
        perror("portnum must be (1023 < portnum < 65536)");
        exit(1);
    }

    quit = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((r_len = getaddrinfo(IP_ADDR, argv[2], &hints, &info)) != 0) {
        perror("getaddrinfo() failed");
        exit(1);
    }

    if ((sockfd = socket(info->ai_family, info->ai_socktype,
        info->ai_protocol)) == -1) {
            perror("socket() failed");
            exit(1);
        }
    
    if (connect(sockfd, info->ai_addr, info->ai_addrlen) == -1) {
        perror("connect() failed");
        exit(1);
    }

    inet_ntop(info->ai_family,
        &((struct sockaddr_in *)info->ai_addr)->sin_addr,
        s, sizeof(s));
    printf("[Client]: Connecting to %s...\n", s);

    freeaddrinfo(info);

    FD_ZERO(&fd_mstr);
    FD_SET(0, &fd_mstr);
    FD_SET(sockfd, &fd_mstr);

    while (!0) {
        fd_read = fd_mstr;
        if (select(sockfd+1, &fd_read, 0, 0, 0) == -1) {
            perror("select() failed");
            exit(1);
        }

        for (i = 0; i < sockfd+1; i++) {
            if (FD_ISSET(i, &fd_read)) {
                if (i == 0) {
                    printf("[Client]: Enter the message: ");
                    fgets(buffer, sizeof(buffer), stdin);

                    if (!strncmp(buffer, "quit", 4)) {
                        quit = 1;
                        break;
                    }

                    if (send(sockfd, buffer, strlen(buffer), 0) == -1) {
                        perror("send() failed");
                        close(sockfd);
                        exit(1);
                    }
                } else if (i == sockfd) {
                    if ((r_len = recv(sockfd, buffer,
                        MAX_MSGLEN-1, 0)) == -1) {
                        perror("recv() failed");
                        close(sockfd);
                        exit(1);
                        }

                    if (r_len == 0) {
                        printf("\n[Client]: Server disconnected.\n");
                        quit = 1;
                        break;
                    }

                    buffer[r_len] = '\0';
                    printf("[Server]: %s\n", buffer);
                }
            }
        }

        if (quit) {
            printf("\n[Client]: Exit program.\n");
            close(sockfd);
            break;
        }
    }

    exit(0);
}

/*
peter@peter:~/test/linux-study/skill_book/chap3_8$ ./client -p 51000
[Client]: Connecting to 127.0.0.1...
hello -> 아마 여기서 엔터를 쳤으면 정확히 교재가 원하는데로 갔을 듯
[Client]: Enter the message: good time bad times
[Client]: Enter the message: quit
[Client]: Enter the message: 
[Client]: Exit program.
*/