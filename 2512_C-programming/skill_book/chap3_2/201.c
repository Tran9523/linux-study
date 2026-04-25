
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void main(void)
{
    int fd;

    if ((fd = open("/proc/cpu", O_RDONLY)) == -1) {
        switch (errno) {
            case EACCES:
                printf("\nPermission denied.\n");
                break;
            case EEXIST:
                printf("\nFile exists.\n");
                break;
            case EINVAL:
                printf("\nInvalid flags.\n");
                break;
            case EISDIR:
                printf("\nIt is directory. Not a file.\n");
                break;
            case ENOMEM:
                printf("\nInsufficient kernel memory was available.\n");
                break;
            case ETXTBSY:
                printf("\nFile is busy.\n");
                break;
            default:
                printf("\nThis error is not defined.\n");
                break;
        }
        perror("\nperror()   ");
        printf("\nstrerror(): %s\n\n", strerror(errno));
        exit(1);
    }

    exit(0);
}

/*
peter@peter:~/test/linux-study/skill_book/chap3_2$ gcc 201.c
peter@peter:~/test/linux-study/skill_book/chap3_2$ ./a.out

This error is not defined.

perror()   : No such file or directory

strerror(): No such file or directory

*/