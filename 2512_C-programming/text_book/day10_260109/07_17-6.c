#include <stdio.h>

//17-6.c 출력 형태 주목 [ (*ps). == ps-> == yuni. ]
struct score {
    int kor;
    int eng;
    int math;
};

int main(void)
{
    struct score yuni = {90, 80, 70};
    struct score *ps = &yuni;   //가리키는 형태가 구조체인거지 pi가 구조체는 아님

    printf("kor: %d\n", (*ps).kor);
    printf("eng: %d\n", ps->eng);       //이 형태가 보편
    printf("math: %d\n", ps -> math);
}