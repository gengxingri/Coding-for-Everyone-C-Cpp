#include <stdio.h>
#include <math.h>

int main(void)
{
double x;
double result;
printf("Enter x between (0,1):");
scanf("%lf", &x);
result = sin(x);
printf("sin(%.2lf)=%.2lf\n", x, result);
return 0;
}