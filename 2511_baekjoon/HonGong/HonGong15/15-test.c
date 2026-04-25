#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void swap(const char* type, void* a, void* b);

int main(void)
{
    int age1, age2;
    double height1, height2;

    printf("첫 번째 사람의 나이와 키 입력 : ");
    scanf("%d %lf", &age1, &height1);

    printf("두 번째 사람의 나이와 키 입력 : ");
    scanf("%d %lf", &age2, &height2);

    // 나이 교환
    swap("int", &age1, &age2);

    // 키 교환
    swap("double", &height1, &height2);

    printf("첫 번째 사람의 나이와 키 : %d, %.1f\n", age1, height1);
    printf("두 번째 사람의 나이와 키 : %d, %.1f\n", age2, height2);

    return 0;
}

void swap(const char* type, void* a, void* b)
{
    if (strcmp(type, "int") == 0)
    {
        int temp = *(int*)a;
        *(int*)a = *(int*)b;
        *(int*)b = temp;
    }
    else if (strcmp(type, "double") == 0)
    {
        double temp = *(double*)a;
        *(double*)a = *(double*)b;
        *(double*)b = temp;
    }
}