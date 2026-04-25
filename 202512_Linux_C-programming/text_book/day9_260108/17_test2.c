#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//test1 - 360도 센서 입력된 거리값 중 가장 가까운 거리와방향
//손으로 하면 10~12 / 랜덤 배웠으니까 랜덤 360개(상승폭의 제한 +- 10 or 50?정도)
//방향도 알려주는/ 입력조건 360개
int main(void)
{  
    srand(time(NULL));

    int i, min_index;
    double dist[360];
    double min_value;

    dist[0] = (rand() % 50001) / 100.0;
    min_value = dist[0];
    min_index = 0;
    
    for (i = 1; i < 360; i++) {
        dist[i] = (rand() % 50001) / 100.0;
        if (min_value > dist[i]) {
            min_value = dist[i];
            min_index = i;
        }
    }

    printf("가장 가까운 거리(cm): %.2lf\n", min_value);
    printf("가장 가까운 거리의 방향(deg): %d\n", min_index);

    return 0;

}