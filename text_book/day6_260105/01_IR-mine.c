#include <stdio.h>

// 나의 IR 코드 - 임계 값 기준으로 cnt
int main(void)
{
    int i, N, threshold;
    int label[15] = {0};
    int black_count = 0, white_count = 0;
    int value[15] = {0};
    double index_avg;

    printf("센서 개수 입력: ");
    scanf("%d", &N);
    printf("센서 값 입력(value): ");
    for ( i = 0; i < N; i++) {
        scanf("%d", &value[i]);
    }
    printf("\n임계값 입력: ");
    scanf("%d", &threshold);

    for (i = 0; i < N; i++) {
        if(value[i] >= threshold) {
            label[i] = 0;
            black_count++;
        } else {
            label[i] = 1;
            white_count++;
        }
        index_avg += i * label[i];
    }

    if (black_count <= 0) {
        index_avg = 0.0;
    } else {
        index_avg = index_avg / black_count;
    }

    printf("label = ");
    for(i < 0; i = N; i++) {
        printf("%2d", label[i]);
    }
    printf("\nblack count = %d", black_count);
    if (black_count <= 0) {
        printf("라인 없음");
    } else {
        printf("index_avg = %lf\n", index_avg);
    }

}