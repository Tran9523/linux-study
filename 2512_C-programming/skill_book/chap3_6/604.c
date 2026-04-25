
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 128
#define FIFO_FORWARD "fifo_fw.io"
#define FIFO_BACKWARD "fifo_bk.io"

void
main(int argc, char *argv[])
{
    int i;
    int n_proc = 4;
    int *fd_f, *fd_b;
    pid_t *pid;
    char buf[SIZE];

    if (argc != 2) {
        perror("Usage: ./a.out <job_name (add|sub|mul)>");
        exit(1);
    }

    fd_f = (int *)calloc(n_proc, sizeof(int));
    fd_b = (int *)calloc(n_proc, sizeof(int));
    pid = (pid_t *)calloc(n_proc, sizeof(pid_t));

    if (remove(FIFO_FORWARD) == 0
        && remove(FIFO_BACKWARD) == 0) {
            printf("[Parent]: Delete existing fifo file.\n");
        } else {
            printf("[Parent]: File not exist. pass\n");
        }
    
    printf("[Parent]: Creating fifo file.\n");
    if (mkfifo(FIFO_FORWARD, 0644) == -1
        || mkfifo(FIFO_BACKWARD, 0644) == -1) {
            perror("mkfifo() failed");
            exit(1);
        }

    for(i = 0; i < n_proc; i++) {
        pid[i] = fork();
        if (pid[i] > 0) {
            if ((fd_f[i] = open(FIFO_FORWARD, O_RDWR)) == -1) {
                perror("open() failed");
                exit(1);
            }

            if ((fd_b[i] = open(FIFO_BACKWARD, O_RDONLY)) == -1) {
                perror("open() failed");
                exit(1);
            }

            if (write(fd_f[i], argv[1], sizeof(argv[1])) == -1) {
                perror("write() failed");
                exit(1);
            }

            wait(NULL);

            if (read(fd_b[i], buf, SIZE) == -1) {
                perror("read() failed");
                exit(1);
            }

            if (!strcmp(buf, argv[1])) {
                printf("[Parent]: received [%s]\n", buf);
            }
        } else if (pid[i] == 0) {
            if ((fd_f[i] = open(FIFO_FORWARD, O_RDONLY)) == -1) {
                perror("open() failed");
                exit(1);
            }

            if ((fd_b[i] = open(FIFO_BACKWARD, O_RDWR)) == -1) {
                perror("open() failed");
                exit(1);
            }

            if (read(fd_f[i], buf, SIZE) == -1) {
                perror("read() failed");
                exit(1);
            }

            switch (i) {
            case 0:
                if (!strcmp(buf, "add")) {
                    printf("[Child 1]: Addition is my job.\n");
                    strcpy(buf, "child 1: job complete");
                }
                break;
            case 1:
                if (!strcmp(buf, "sub")) {
                    printf("[Child 2]: Subtraction is my job.\n");
                    strcpy(buf, "child 2: job complete");
                }
                break;
            case 2:
                if (!strcmp(buf, "mul")) {
                    printf("[Child 3]: Multiplication is my job.");
                    strcpy(buf, "child 3: job complete");
                }
                break;
            case 3:
                printf("[Child 4]: I'm echo process.\n");
                break;
        }

        write(fd_b[i], buf, sizeof(buf));

        exit(0);
    }
    }

    free(fd_f);
    free(fd_b);
    free(pid);

    exit(0);
}

/*
peter@peter:~/test/linux-study/skill_book/chap3_6$ gcc 604.c
peter@peter:~/test/linux-study/skill_book/chap3_6$ ./a.out add
[Parent]: File not exist. pass
[Parent]: Creating fifo file.
[Child 1]: Addition is my job.
[Parent]: received [add]
[Parent]: received [add]
[Child 4]: I'm echo process.
[Parent]: received [add]
peter@peter:~/test/linux-study/skill_book/chap3_6$ ./a.out sub
[Parent]: Delete existing fifo file.
[Parent]: Creating fifo file.
[Parent]: received [sub]
[Child 2]: Subtraction is my job.
[Parent]: received [sub]
[Child 4]: I'm echo process.
[Parent]: received [sub]
peter@peter:~/test/linux-study/skill_book/chap3_6$ ./a.out mul
[Parent]: Delete existing fifo file.
[Parent]: Creating fifo file.
[Parent]: received [mul]
[Parent]: received [mul]
[Child 3]: Multiplication is my job.[Child 4]: I'm echo process.
[Parent]: received [mul]
peter@peter:~/test/linux-study/skill_book/chap3_6$ ./a.out hello
[Parent]: Delete existing fifo file.
[Parent]: Creating fifo file.
[Parent]: received [hello]
[Parent]: received [hello]
[Parent]: received [hello]
[Child 4]: I'm echo process.
[Parent]: received [hello]
개판
switch 문으로 추정되는데 일단은 강종하는 방법 배우고 종료 다음 과정 넘어가기
*/