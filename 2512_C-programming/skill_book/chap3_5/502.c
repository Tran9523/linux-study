
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void signal_handler(int sig);

void
main(int argc, char *argv[])
{
    int count = 0;
    sigset_t mask;

    if (argc != 2 || argv[1][0] != '-') {
        perror("Usage: ./a.out -[h]");
        exit(1);
    }

    getopt(argc, argv, "h");

    switch (argv[1][1]) {
        case 'h':
            if (signal(SIGINT, signal_handler) == SIG_ERR) {
                perror("signal() failed");
                exit(1);
            }
            for (;;) {
                printf("I'm still running...\n");
                sleep(1);
                count++;
                if (count == 10) {
                    if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
                        perror("signal() failed");
                        exit(1);
                    }
                }
            }
            break;
    }

    exit(0);
}

static void
signal_handler(int sig)
{
    printf("Handler is called !!\n");
}

/*
peter@peter:~/test/linux-study/skill_book/chap3_5$ gcc 502.c
peter@peter:~/test/linux-study/skill_book/chap3_5$ ./a.out -h
I'm still running...
^CHandler is called !!
I'm still running...
I'm still running...
^CHandler is called !!
I'm still running...
I'm still running...
^CHandler is called !!
I'm still running...
Handler is called !!
I'm still running...
^CI'm still running...
I'm still running...
I'm still running...
I'm still running...
I'm still running...
I'm still running...
I'm still running...
I'm still running...
I'm still running...
I'm still running...
Ctrl+C 를 9초안에 빠르게 눌러야 됨
*/