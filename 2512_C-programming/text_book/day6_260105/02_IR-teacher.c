#include <stdio.h>

//교수님 IR 코드 _ 함수 추가로 가독성 좋게
#define MAX_N 16

void classify_by_threshold(const int value[], int label[], int n, int threshold);
int count_black(const int label[], int n);
double average_index_of_black(const int label[], int n);

int main(void)
{
    int N, threshold;
    int value[MAX_N];
    int label[MAX_N];

    printf("센서 개수 입력(1~%d): ", MAX_N);
    scanf("%d", &N);

    printf("센서 값 %d개 입력: ", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &value[i]);
    }

    printf("임계값 입력: ");
    scanf("%d", &threshold);
    
    classify_by_threshold(value, label, N, threshold);
    int black_count = count_black(label, N);
    double center = average_index_of_black(label, N);

    printf("\nlabel = ");
    for (int i = 0; i < N; i++) {
        printf("%d  ", label[i]);
    }
    printf("\nblack_count = %d\n", black_count);
    if (black_count == 0) {
        printf("라인 없음 \n");
    } else {
        printf("index_avg = %.2lf\n", center);
    }

    return 0;
}

void classify_by_threshold(const int value[], int label[], int n, int threshold)
{
    for (int i = 0; i < n; i++) {
        if (value[i] < threshold){
            label[i] = 1;
        } else {
            label[i] = 0;
        }
    }
}

int count_black(const int label[], int n)
{
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += label[i];
    }
    return cnt;
}

double average_index_of_black(const int label[], int n)
{
    int sum = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        sum += i * label[i];
        cnt += label[i];
    }
    if (cnt == 0) return -1.0;
    return (double)sum / cnt;
}