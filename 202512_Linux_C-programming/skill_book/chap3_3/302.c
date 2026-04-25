
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

int read_file_and_print(int fd);

void
main(int argc, char *argv[])
{
    int fd;
    int f_size;
    char buf[SIZE];
    char *f_name = "301.txt";

    printf("\nThis program reads and changes file size.\n\n");

    if ((fd = open(f_name, O_RDONLY)) == -1) {
        perror("open() failed");
        exit(1);
    }
    f_size = read_file_and_print(fd);
    printf("Original file size: %d bytes.\n\n", f_size);

    close(fd);

    if (truncate(f_name, 100) == -1) {  // if( (scanf --) ) samesame
        perror("truncate() failed");
        exit(1);
    }
    if ((fd = open(f_name, O_RDONLY)) == -1) {
        perror("open() failed");
        exit(1);
    }
    f_size = read_file_and_print(fd);
    printf("Truncated file size: %d bytes.\n\n", f_size);

    close(fd);

    if ((fd = open(f_name, O_RDWR)) == -1) {
        perror("open() failed");
        exit(1);
    }
    if (ftruncate(fd, 50) == -1) {
        perror("ftruncate() failed");
        exit(1);
    }
    f_size = read_file_and_print(fd);
    printf("Ftruncated file size: %d bytes.\n\n", f_size);

    close(fd);

    exit(0);
}

int
read_file_and_print(int fd)
{
    int r_count, f_size = 0;
    char buf[SIZE] = {};

    printf("----------FILE DATA----------\n");
    while ((r_count = read(fd, buf, SIZE)) > 0) {
        printf("%s", buf);
        f_size += r_count;
    }
    printf("\n-----------------------------\n");

    return f_size;
}
/*
peter@peter:~/test/linux-study/skill_book/chap3_3$ gcc 302.c
peter@peter:~/test/linux-study/skill_book/chap3_3$ ./a.out

This program reads and changes file size.

----------FILE DATA----------
There are a variety pf substances in the water which     includes bacteria and parasites that causes various type     of diseases in both human and animal bodies. Previously,     the optical microscope was generally used for observing     and analyzing the water samples in the laboratory.

-----------------------------
Original file size: 291 bytes.

----------FILE DATA----------
There are a variety pf substances in the water which     includes bacteria and parasites that causes
-----------------------------
Truncated file size: 100 bytes.

----------FILE DATA----------
There are a variety pf substances in the water whi
-----------------------------
Ftruncated file size: 50 bytes.

*/