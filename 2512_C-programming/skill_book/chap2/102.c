#include <stdio.h>

#define PI 3.141592

int main(void)
{
    float r, h ,l;
    float area, volume;

    printf("Enter radius, height, lengt of cone : ");
    scanf("%f %f %f", &r, &h, &l);

    area = PI * r * r + PI * r * l;
    volume = (PI*r*r*h)/3;

    printf("Area of cone = %6.2f\n", area);
    printf("Volume of cone = %6.3f\n", volume);

    return 0;
}