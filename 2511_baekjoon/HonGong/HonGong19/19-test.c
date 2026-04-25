#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/* 입력 매크로 */
#define INPUT(a, op, b) scanf("%d %c %d", &a, &op, &b)

/* 사칙연산 매크로 */
#define CALC(a, op, b) \
    ((op) == '+' ? (a) + (b) : \
     (op) == '-' ? (a) - (b) : \
     (op) == '*' ? (a) * (b) : \
     (op) == '/' ? (a) / (b) : 0)

int main(void)
{
    int a, b;
    char op;
    int result;

    while (1)
    {
        printf("수식 입력(종료 Ctrl+Z) : ");

        if (INPUT(a, op, b) == EOF)
        {
            printf("\n프로그램 종료\n");
            break;
        }

        result = CALC(a, op, b);

        printf("%d %c %d = %d\n", a, op, b, result);
    }

    return 0;
}
