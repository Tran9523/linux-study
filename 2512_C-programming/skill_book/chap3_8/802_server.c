
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USER 10
#define MAX_MSGLEN 1024

void
main(int argc, char *argv[])
{
    int ports;
    int sv_sockfd, cl_sockfd;
    int cl_len, rv_len;
    char rv_buffer[MAX_MSGLEN];
    struct sockaddr_in sv_addr, cl_addr;

    if (argc != 3 || argv[1][0] != '-') {
        perror("Usage: ./a.out -p <portnum>");
        exit(1);
    }

    getopt(argc, argv, "p");

    ports = atoi(argv[2]);
    if (ports < 1023 || ports > 65535) {
        perror("portnum must be (1023 < portnum < 65536)");
        exit(1);
    }

    memset(&sv_addr, 0, sizeof(sv_addr));
    sv_addr.sin_family = AF_INET;
    sv_addr.sin_port = htons(ports);
    sv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((sv_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket() failed");
        exit(1);
    }

    if (bind(sv_sockfd, (struct sockaddr *)&sv_addr,
        sizeof(sv_addr)) == -1) {
        perror("bind() failed");
        exit(1);
    }

    if (listen(sv_sockfd, MAX_USER) == -1) {
        perror("listen() failed");
        exit(1);
    }

    cl_len = sizeof(cl_addr);
    if ((cl_sockfd = accept(sv_sockfd,
        (struct sockaddr *)&cl_addr, &cl_len)) == -1) {
        perror("accept() failed");
        exit(1);
        }
    
    while (!0) {
        if ((rv_len = recv(cl_sockfd, rv_buffer,
            MAX_MSGLEN-1, 0)) == -1) {
            perror("recv() failed");
            exit(1);
        }

        if (rv_len == 0 || !strncmp(rv_buffer, "quit", 4)) {
            printf("[Server]: Client left. Terminate.\n");
            break;
        }

        rv_buffer[rv_len] = '\0';
        printf("[Client]: %s", rv_buffer);

        if (send(cl_sockfd, rv_buffer, rv_len, 0) != rv_len) {
            perror("send() failed");
            exit(1);
        }
    }

    close(cl_sockfd);

    exit(0);
}

/*
peter@peter:~/test/linux-study/skill_book/chap3_8$ gcc 802_server.c -o server
peter@peter:~/test/linux-study/skill_book/chap3_8$ gcc 802_client.c -o client
peter@peter:~/test/linux-study/skill_book/chap3_8$ ./server -p 432 > server.log &
[3] 28312
portnum must be (1023 < portnum < 65536): Success
peter@peter:~/test/linux-study/skill_book/chap3_8$ ./server -p 9432 > server.log &
[3]   Exit 1                  ./server -p 432 > server.log
[3] 28453
peter@peter:~/test/linux-study/skill_book/chap3_8$ ./client -p 9432
[Client]: Send message to server: hello?
[Server]: hello?
[Client]: Send message to server: I'm a new client
[Server]: I'm a new client
[Client]: Send message to server: byebye
[Server]: byebye
[Client]: Send message to server: quit
[Client]: Terminate.
[3]   Done                    ./server -p 9432 > server.log
peter@peter:~/test/linux-study/skill_book/chap3_8$ cat server.log
[Client]: hello?
[Client]: I'm a new client
[Client]: byebye
[Server]: Client left. Terminate.
*/