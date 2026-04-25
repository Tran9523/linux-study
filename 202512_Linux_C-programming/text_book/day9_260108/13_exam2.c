#include <stdio.h>
//연습문제 2 (그래도 헷갈림 지피티)
//첫 *p을 가져오기전에 값을 10->11 그 결과 arr[3] = {11, 20, 30}
//그리고 *p(11)를 가져오고나서 한 칸 이동
//arr[1] 을 가져와서(20) 이후 그 값을 1 증가, 그래서 arr[3] = {11, 21, 30}
//증가된 값을 그대로 가져옴(21)
int main(void)
{
    int arr[3] = {10, 20, 30};
    int *p = arr;

    printf("%d\n", ++*p);
    printf("%d\n", *p++);
    printf("%d\n", (*p)++);
    printf("%d\n", *p);

    return 0;
}