#include <stdio.h>

int main(void)
{
    int i, range;
    int select;
    int arr[20];

    printf("This program prints reversed array.\n");

    while(!0){
        printf("1. Enter the number\n");
        printf("2. Exit\n");
        printf("Enter the menu: ");
        scanf("%d", &select);

        if (select == 1) {
            printf("How many numbers(max:20): ");
            scanf("%d", &range);

            printf("Enter the numbers: ");
            for (i = 0; i < range; i++) {
                scanf("%d", (arr+i));
            }
            for (i = range-1; i >=0; i--) {
                printf("%d", *(arr+i));
            }
            printf("\n");
        } else {
            break;
        }
    }
    return 0;
}