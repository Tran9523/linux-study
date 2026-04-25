
#include <stdio.h>
#include <stdlib.h>

#define SIZE 2048

static int **array_allocation(int value);
static void array_free(int **array);

void
main(int argc, char *argv[])
{
    int i, j, k;
    int **A, **B, **Y;
    double sum;

    A = array_allocation(1);
    B = array_allocation(3);
    Y = array_allocation(0);

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            sum = 0.0;
            for (k =0; k < SIZE; k++) {
                sum += A[i][k] * B[k][j];
            }
            Y[i][j] = (int)sum;
        }
    }

    sum = 0.0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            sum += (double)Y[i][j];
        }
    }
    printf("Sum of result array: %.2lf\n", sum);

    array_free(A);
    array_free(B);
    array_free(Y);

    exit(0);
}

int **
array_allocation(int value)
{
    int i, j;
    int **array;

    array = (int **)calloc(SIZE, sizeof(int *));
    for (i = 0; i < SIZE; i++) {
        array[i] = (int *)calloc(SIZE, sizeof(int));

        for (j = 0; j < SIZE; j++) {
            array[i][j] = value;
        }
    }

    return array;
}

static void array_free(int **array)
{
    if (!array) return;
    for (int i = 0; i < SIZE; i++) {
        free(array[i]);
    }
    free(array);
}

/*
peter@peter:~/test/linux-study/skill_book/chap3_9$ gcc 901_single.c -o single
peter@peter:~/test/linux-study/skill_book/chap3_9$ time ./single
^C              // 계산이 너무 오래 걸려서 멈춘것처럼 표현되어 강종함

real    0m17.948s
user    0m17.610s
sys     0m0.216s

peter@peter:~/test/linux-study/skill_book/chap3_9$ gcc 901_single.c -o single
peter@peter:~/test/linux-study/skill_book/chap3_9$ time ./single
Sum of result array: 25769803776.00

real    1m12.888s
user    1m12.633s
sys     0m0.165s
*/
// 다시 실행해봐도 1분 넘게 걸리는 코드 ㅇㅇ;; array_free 와는 무관