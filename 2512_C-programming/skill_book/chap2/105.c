#include <stdio.h>

int main(void)
{
    int select;
    double celcius, kelvin, fahrenheit;

    printf("This program calculates temperature. \n");

    while (!0){
        printf("1. Celcius to Fahrenhiet.\n");
        printf("2. Celcius to Kelvin.\n");
        printf("3. Fahrenheit to Celcius.\n");
        printf("4. Fahrenheit to Kelvin.\n");
        printf("5. Exit.\n");
        printf("Enter the menu: ");
        scanf("%d", &select);

        if (select == 1 || select == 2) {
            printf("\nPlease enter the Celcius: ");
            scanf("%lf", &celcius);
            if (select == 1) {
                fahrenheit = celcius * 9 / 5 + 32;
                printf("Fahrenheit : %.2f\n", fahrenheit);
            } else {
                kelvin = celcius + 273.15;
                printf("Kelvin: %.2f\n", kelvin);
            }
        } else if (select == 3 || select ==4) {
            printf("\nPlease enter the Fahrenheit: ");
            scanf("%lf", &fahrenheit);
            if (select == 3) {
                celcius = (fahrenheit-32) * 5 / 9;
                printf("Celcius: %.2f\n", celcius);
            } else {
                kelvin = (fahrenheit-32) * 5 / 9 + 273.15;
                printf("Kelvin: %.2f\n", kelvin);
            }
        } else if (select == 5) {
            break;
        } else {
            printf("Wrong menu, Try again.\n");
        }
        printf("\n");
    }
    
    return 0;
}