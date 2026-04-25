
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void proc_sum(int *data);

void
main(int argc, char *argv[])
{
    int pid, c_pid, status;
    int data[SIZE] = {20, 24, 37, 36, 31};

    if (argc != 2 || argv[1][0] != '-') {
        perror("Usage: ./a.out -[w|p]");
        exit(1);
    }

    getopt(argc, argv, "wp");

    switch (argv[1][1]) {
        case 'w':
            pid = fork();
            if (pid == -1) {
                perror("fork() failed");
                exit(1);
            } else if (pid != 0) {
                printf("[Parent]: Waiting for child process...\n");
                c_pid = wait(&status);
                if (WIFEXITED(status)) {
                    printf("[Parent]: child process %d exited: %x\n",
                    c_pid, status);
                } else {
                    printf("[Parent]: child process exited abnormally.\n");
                }
            } else {
                printf("[Child]: Processing...\n");
                proc_sum(data);
                exit(5);
            }
            break;
        case 'p':
            pid = fork();
            if (pid == -1) {
                perror("fork() failed");
                exit(1);
            } else if (pid != 0) {
                while (waitpid(pid, &status, WNOHANG) == 0) {
                    printf("[Parent]: Waiting for child process...\n");
                    sleep(1);
                }
                printf("[Parent]: child process %d exited: %x\n",
                pid, status);
            } else {
                printf("[Child]: Processing...\n");
                proc_sum(data);
                sleep(5);
                exit(0);
            }
            break;
    }

    exit(0);
}

void
proc_sum(int *data)
{
    int i;
    int sum = 0;

    for (i = 0; i < SIZE; i++) {
        sum += *(data+i);
    }
    printf("[Child]: %d\n", sum);

    return;
}
/*
peter@peter:~/test/linux-study/skill_book/chap3_4$ gcc 402.c
peter@peter:~/test/linux-study/skill_book/chap3_4$ ./a.out -w
[Parent]: Waiting for child process...
[Child]: Processing...
[Child]: 148
[Parent]: child process 5107 exited: 500
peter@peter:~/test/linux-study/skill_book/chap3_4$ ./a.out -p
[Parent]: Waiting for child process...
[Child]: Processing...
[Child]: 148
[Parent]: Waiting for child process...
[Parent]: Waiting for child process...
[Parent]: Waiting for child process...
[Parent]: Waiting for child process...
[Parent]: child process 5135 exited: 0
*/