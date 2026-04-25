
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

#define MAX_USER 5
#define MAX_MSGLEN 1024

void
main(int argc, char *argv[])
{
    int i, j;
    int ports;
    int fdmax;
    int s_sockfd, c_sockfd;
    socklen_t c_len;//int c_len
    int r_len;
    char s[INET_ADDRSTRLEN];
    char buffer[MAX_MSGLEN];
    fd_set fd_mstr, fd_read;
    struct addrinfo hints, *info;
    struct sockaddr_storage c_addr;

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

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((r_len = getaddrinfo(0, argv[2], &hints, &info)) != 0) {
        perror("getaddrinfo() failed");
        exit(1);
    }

    if ((s_sockfd = socket(info->ai_family, info->ai_socktype,
        info->ai_protocol)) == -1) {
            perror("socket() failed");
            exit(1);
        }
    
    if (bind(s_sockfd, info->ai_addr, info->ai_addrlen) == -1) {
        perror("bind() failed");
        close(s_sockfd);
        exit(1);
    }

    freeaddrinfo(info);

    if (listen(s_sockfd, MAX_USER) == -1) {
        perror("listen() failed");
        exit(1);
    }

    FD_ZERO(&fd_mstr);      // gpt 추가한 줄
    FD_SET(s_sockfd, &fd_mstr);
    fdmax = s_sockfd;

    while (!0) {
        fd_read = fd_mstr;
        if (select(fdmax+1, &fd_read, 0, 0, 0) == -1) {
            perror("select() failed");
            exit(1);
        }

        for (i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &fd_read)) {
                if (i == s_sockfd) {
                    c_len = sizeof(c_addr);
                    if ((c_sockfd = accept(s_sockfd, (struct sockaddr *)
                        &c_addr, &c_len)) == -1) {
                            perror("accept() failed");
                        } else {
                            FD_SET(c_sockfd, &fd_mstr);
                            if (c_sockfd > fdmax) {
                                fdmax = c_sockfd;
                            }
                            printf("[Server]: new client from %s [Socket %d]\n",
                                inet_ntop(c_addr.ss_family,
                                &((struct sockaddr_in *)&c_addr)->sin_addr,
                                s, sizeof(s)), c_sockfd);
                        }
                } else {
                    if ((r_len = recv(i, buffer, sizeof(buffer), 0)) <= 0) {
                        if (r_len == 0) {
                            printf("[Server]: [Socket %d] has left.\n", i);
                        } else {
                            perror("recv() failed");
                        }
                        close(i);
                        FD_CLR(i, &fd_mstr);
                    } else {
                        buffer[r_len] = '\0';
                        printf("[Server]: [Socket %d]: %s", i, buffer);

                        for (j = 0; j <= fdmax; j++) {
                            if (j == s_sockfd) {
                                continue;
                            }
                            if (j == i) {
                                continue;
                            }
                            if (!FD_ISSET(j, &fd_mstr)) {
                                continue;
                            }
                            if (send(j, buffer, strlen(buffer), 0) == -1) {
                                perror("send() failed");
                            }
                        }
                    }
                }
            }
        }
    }

    exit(0);
}

/*
peter@peter:~/test/linux-study/skill_book/chap3_8$ ./server -p 51000 <- 이거 먼저
[Server]: new client from 127.0.0.1 [Socket 4] <- 이후 클라이언트에서 접속
  
[Server]: [Socket 4]: hello
[Server]: [Socket 4]: good time bad times
[Server]: [Socket 4] has left.
*/