#include <stdio.h>

void print_reversed_binary(int number);
void print_binary(int number);

int main(void)
{
    int number;

    printf("This program converts DEC to reversed BINARY.\n");
    printf("Enter the number : ");
    scanf("%d", &number);

    print_reversed_binary(number);

    printf("Up = Reversed / Down = Normal \n");
    if (number == 0)
        printf("0");
    else
        print_binary(number);

    printf("\n");

    return 0;
}

void print_reversed_binary(int number)
{
    int mod;

    while (!0) {
        mod = number % 2;
        printf("%d", mod);

        if((number / 2) == 0) {
            break;
        }

        number /= 2;
    }
    printf("\n");

    return;
}

void print_binary(int number)
{
    if (number == 0)
        return;

    print_binary(number / 2);
    printf("%d", number % 2);
}