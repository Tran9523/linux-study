
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        perror("Usage: Input argument");
        exit(1);
    }

    printf("Number of argument: %d\n", argc);
    for (i = 1; i < argc; i++) {
        printf("Argument %d (argc[%d]): %s\n", i, i, argv[i]);
    }

    printf("\nDetails of arguments.\n");
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            printf("argv[%d] is a option: %s\n", i, argv[i]);
        } else {
            printf("argv[%d] is a argument: %s\n", i, argv[i]);
        }
    }

    exit(0);
}

/*
peter@peter:~/test/linux-study/skill_book/chap3_2$ gcc 202.c
peter@peter:~/test/linux-study/skill_book/chap3_2$ ./a.out
Usage: Input argument: Success
peter@peter:~/test/linux-study/skill_book/chap3_2$ ./a.out -a -h -l hello linux c
Number of argument: 7
Argument 1 (argc[1]): -a
Argument 2 (argc[2]): -h
Argument 3 (argc[3]): -l
Argument 4 (argc[4]): hello
Argument 5 (argc[5]): linux
Argument 6 (argc[6]): c

Details of arguments.
argv[1] is a option: -a
argv[2] is a option: -h
argv[3] is a option: -l
argv[4] is a argument: hello
argv[5] is a argument: linux
argv[6] is a argument: c
*/