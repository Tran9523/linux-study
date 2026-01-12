#include <stdio.h>
//17-5.c 구조체 관련 함수 만들때, 반환형 표현 주의... 헷갈려보임
struct vision {
    double left;
    double right;
};

struct vision exchange (struct vision robot);   // exchange라는 함수를 만든거임
            //반환형이 구조체일뿐
void exch_point(struct vision *robot);  // 값을 안 바꾸고 주소로 접근하니 void 반환형

int main(void)
{
    struct vision robot;
    printf("시력 입력: ");
    scanf("%lf%lf", &(robot.left), &(robot.right)); 
    exch_point(&robot);
    //robot = exchange(robot);
    printf("바뀐 시력: %.1lf  %.1lf\n", robot.left, robot.right);

    return 0;
}

struct vision exchange(struct vision robot)
{
    double temp;

    temp = robot.left;
    robot.left = robot.right;
    robot.right = temp;

    return robot;           // 보내는 형태가 구조체임을 확인
}

void exch_point(struct vision *robot)
{
    double temp;

    temp = robot->left;     //robot->left = (*robot).left
    robot->left = robot->right;
    robot->right = temp;

}