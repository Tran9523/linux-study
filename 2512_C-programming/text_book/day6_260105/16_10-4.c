#include <stdio.h>

//10-4.c 포인터의 간격은 자동으로 sizeof 되어 들어감
int main(void)
{
    int ary[5] = {10, 20, 30, 40, 50};  // 여기서 ary[]로도 입력해도 동일
    int *pa = ary;
    int *pb = pa + 3;

    printf("pa : %u\n", pa);
    printf("pb : %u\n", pb);
    pa++;
    printf("pb - pa : %u\n", pb - pa);  // 여기서 2 나오는게 중요(int size가 4임에도)
                                        //  (값 8) / sizeof(int) = 8 / 4 = 2
    printf("앞에 있는 배열 요소의 값 출력: ");
    if (pa < pb) printf("*pa출력 = %d\n", *pa);
    else printf("*pb출력 = %d\n", *pb);

    return 0;
}