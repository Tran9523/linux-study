#include <stdio.h>

//17-9.c - current는 처음 선언할때 값이 없었음(정확히는 head로 쭉 대체해도 동일)
//GPT: 포인터 변수는 주소 하나만 가진다!! = current는 구조체나 함수가 아닌 포인터임
struct list{
    int num;
    struct list *next;      // 형태가 같은 자기 참조형
};

int main(void)
{
    struct list a = {10, 0}, b = {20, 0}, c = {30, 0};  // a = (10, 0_ptr)
    struct list *head = &a, *current;   // *** 매우 중요, head는 &a 인거고 current랑 무관
                            // 구조체 a를 가리키는 포인터 head인거고 자체가 구조체는 아님
    a.next = &b;    // a= 10, 200번지
    b.next = &c;

    printf("head->num : %d\n", head->num);
    printf("head->next->num : %d\n", head->next->num);

    printf("list all: ");
    current = head;     // current는 여기와서 드디어 값이 배정됨(위에까지는 공백)
    while (current != NULL) {
        printf("%d   ", current->num);  // current는 백번지 -> 거기의 next는 200번지
        current = current->next;        // 첫 꼬리(&a)가 나오고 &b -> &c 0 이후엔 NULL
    }
    printf("\n");

    return 0;
}