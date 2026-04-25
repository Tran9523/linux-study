#include <stdio.h>

int main(void)
{
    int a, b, c;
    int x;
    float y;

    printf("ax^2 + bx + c = y\n");

    printf("Enter a, b, c: ");
    scanf("%d %d %d", &a, &b, &c);

    printf("Enter x : ");
    scanf("%5d", &x);

    y = a*x*x + b*x + c;

    printf("The answer is %5.2f\n", y);

    printf("Student member s increased %-+3.3f%%", 14.3333);
    return 0;
}