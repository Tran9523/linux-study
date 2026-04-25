#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//test2 최소 3개 찾기
int main(void)
{  
    srand(time(NULL));

    int i, j;
    int temp1;
    double temp2;
    int min_index[3] = {-1, -1, -1};
    double dist[360];
    double min_value[3] = {500, 500, 500};

    for (i = 0; i < 360; i++) {
        dist[i] = (rand() % 50001) / 100.0;
        if (dist[i] < min_value[2]) {
            min_value[2] = dist[i];
            min_index[2] = i;
            for (j = 2; j > 0; j--) {
                if (min_value[j-1] > min_value[j]) {
                    temp1 = min_index[j-1];
                    min_index[j-1] = min_index[j];
                    min_index[j] = temp1;
                    temp2 = min_value[j-1];
                    min_value[j-1] = min_value[j];
                    min_value[j] = temp2;
                }
            }
        }
    }

    printf("\t[Lidar 최소 거리 Top3]\n");
    printf("가장 가까운 거리(cm): ");
    printf("%.2lf & %.2lf & %.2lf\n", min_value[0], min_value[1], min_value[2]);
    printf("가장 가까운 거리의 방향(deg): ");
    printf("%d & %d & %d\n", min_index[0], min_index[1], min_index[2]);

    return 0;

}