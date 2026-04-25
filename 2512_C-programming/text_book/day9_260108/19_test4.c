#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//test3 heap에다가 넣기 (1초간 데이터 저장)
#define HZ 10
int main(void)
{  
    srand(time(NULL));

    int i, min_index, dist = 0;
    int data = HZ * 360;
    int min_value = 501;
    int step = 10, size = 10;

    int *pi = (int *)calloc(size, sizeof(int));
    //pi = (int *)malloc(sizeof(int) * data);
    if (pi == NULL) {
        printf("메모리가 부족합니다.\n");
        exit(1);
    }

    for (i = 0; i < data; i++) {
        if (i >= size) {
            size += step;
            int *tmp = realloc(pi, size * sizeof(int));
            if (!tmp) {
                free(pi);
                printf("메모리가 부족합니다\n");
                exit(1);
            }
            pi = tmp;
        }
        dist = rand() % 501;
        pi[i] = dist;
        if (dist < min_value) {
            min_value = dist;
            min_index = i % 360;
        }
    }

    printf("가장 가까운 거리(cm): %d\n", min_value);
    printf("가장 가까운 거리의 방향(deg): %d\n", min_index);
    
    free(pi);
    
    return 0;
}