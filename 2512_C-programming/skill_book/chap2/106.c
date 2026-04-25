#include <stdio.h>

#define EARNED_INCOME_TAX_RATE 4
#define LOCAL_INCOME_TAX_RATE 10
#define NATIONAL_PENSION_RATE 4.5
#define EMPLOYMENT_INSURANCE_RATE 0.8
#define HEALTH_INSURANCE_RATE 3.38

int main(void)
{
    float salary;
    float eit, lit, np, ei, hi;
    float total;

    printf("This program calculates social insurance tax.\n");
    printf("Please enter your salary(month) : ");
    scanf("%f", &salary);

    eit = salary * (EARNED_INCOME_TAX_RATE / 100.0);
    lit = eit * (LOCAL_INCOME_TAX_RATE / 100.0);
    np = salary * (NATIONAL_PENSION_RATE / 100.0);
    ei = salary * (EMPLOYMENT_INSURANCE_RATE / 100.0);
    hi = salary * (HEALTH_INSURANCE_RATE / 100.0);
    total = eit + lit + np + ei + hi;

    printf("\nEarned Income Tax : %10d Won\n", (int)eit);
    printf("Local Income Tax  : %10d Won\n", (int)lit);
    printf("National Pension  : %10d Won\n", (int)np);
    printf("Employment Insur. : %10d Won\n", (int)ei);
    printf("Health Insurance  : %10d Won\n", (int)hi);
    printf("-----------------------------------\n");
    printf("Total             : %10d Won\n", (int)total);

    return 0;
}