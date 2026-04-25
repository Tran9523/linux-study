#include <stdio.h>

//로봇 이동 계산 하기(by 함수)
//a, b를 사용하기 위해 주소로 넘겨주고 그 값으로 처리하는 느낌
typedef struct {
    int x;
    int y;
} Position;

void move(Position *p, int dx, int dy);
int move_value(int *a, int *b);

int main(void)
{
    int a, b;
    Position robot = {0, 0};

    printf("1회 이동\n");
    if (move_value(&a, &b)) move(&robot, a, b);

    printf("2회 이동\n");
    if (move_value(&a, &b)) move(&robot, a, b);
    
    printf("로봇 최종 위치: [%d / %d]\n", robot.x, robot.y);

    return 0;
}

void move(Position *p, int dx, int dy)
{
    p->x += dx;
    p->y += dy;
}

int move_value(int *a, int *b)
{
    printf("위치 이동할 값을 입력하세요[x, y]: ");
    if (scanf("%d%d", a, b) != 2) {
        printf("입력 오류\n");
        return 0;
    }
    return 1;

}