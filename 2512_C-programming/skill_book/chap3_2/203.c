
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void get_numbers(double *x, double *y);
double addition(double x, double y);
double substraction(double x, double y);
double multiplication(double x, double y);
double division(double x, double y);

void
main(int argc, char *argv[])
{
    int opt;
    double x, y, r;

    if (argc != 2 || argv[1][0] != '-') {
        perror("Usage: ./a.out -a -s -m -d");
        exit(1);
    }

    while ((opt = getopt(argc, argv, "asmd")) != -1) {
        if (opt != '?') {
            get_numbers(&x, &y);
        } else {
            exit(1);
        }
    }

    switch (argv[1][1]) {
        case 'a':
            r = addition(x, y);
            break;
        case 's':
            r = substraction(x, y);
            break;
        case 'm':
            r = multiplication(x, y);
            break;
        case 'd':
            r = division(x, y);
            break;
    }
    printf("Result: %.3f\n", r);

    exit(0);
}

void
get_numbers(double *x, double *y)
{
    printf("Enter the number x: ");
    scanf("%lf", x);
    printf("Enter the number y: ");
    scanf("%lf", y);
}

double
addition(double x, double y)
{
    return x + y;
}

double
substraction(double x, double y)
{
    return x - y;
}

double
multiplication(double x, double y)
{
    return x * y;
}

double
division(double x, double y)
{
    if (x == 0 || y == 0) {
        return 0.0;
    } else {
        return x / y;
    }
}

/*
peter@peter:~/test/linux-study/skill_book/chap3_2$ gcc 203.c
peter@peter:~/test/linux-study/skill_book/chap3_2$ ./a.out w
Usage: ./a.out -a -s -m -d: Success
peter@peter:~/test/linux-study/skill_book/chap3_2$ ./a.out -w
./a.out: invalid option -- 'w'
peter@peter:~/test/linux-study/skill_book/chap3_2$ ./a.out -a
Enter the number x: 1
Enter the number y: 2
Result: 3.000
peter@peter:~/test/linux-study/skill_book/chap3_2$ ./a.out -s
Enter the number x: 3
Enter the number y: 4
Result: -1.000
peter@peter:~/test/linux-study/skill_book/chap3_2$ ./a.out -m
Enter the number x: 2
Enter the number y: 3
Result: 6.000
peter@peter:~/test/linux-study/skill_book/chap3_2$ ./a.out -d
Enter the number x: 2
Enter the number y: 3
Result: 0.667
peter@peter:~/test/linux-study/skill_book/chap3_2$ ./a.out -d
Enter the number x: 2
Enter the number y: 0
Result: 0.000
*/