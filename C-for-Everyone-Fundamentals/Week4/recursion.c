/*
Simple iteration VS simple recursion
*/

#include <stdio.h>

long int factorial( int n)
{
	long f =1;
	int i;

	for (i =1; i<=n;i++)
	    f = f*i;
	return f;
}

long int recursion_factorial(int n)
{
	if (n == 1)
		return 1;
	else
		return(recursion_factorial(n-1)*n);

}

int main(void)
{
	int how_many = 0, i;
	printf("I want tabnle of fractorial of n:\n");

	scanf("%d", &how_many);
	printf("\n factorials \n");

	for (i=1;i<= how_many;i++)
		printf("\n%d\t %ld\n", i, factorial(i));
	printf("\n\n");

	for (i=1;i<= how_many;i++)
		printf("\n%d\t %ld\n", i, recursion_factorial(i));
	printf("\n\n");
	return 0;
}


