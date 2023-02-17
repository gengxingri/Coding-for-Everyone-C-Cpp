/*
Simple iteration VS simple recursion
Fibonacci F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1
*/

#include <stdio.h>

long fibonacci(int n)
{
	long f2 = 1, f1 = 0, f_old;
	int i;

	for (i = 0; i < n; i++){
		f_old = f2;
	    f2 = f2 + f1;
	    f1 = f_old;	
	    };    
	return f2;
}


long recursion_fibonacci(int n)
{
	if (n <= 1)
		return n;
	else
		return(recursion_fibonacci(n-1) + recursion_fibonacci(n-2));

}

int main(void)
{
	int how_many = 0, i;
	printf("I want tabnle of fractorial of n:\n");

	scanf("%d", &how_many);
	printf("\n fibonacci \n");

	for (i=1;i<= how_many;i++)
		printf("\n%d\t %ld %ld\n", i, fibonacci(i), recursion_fibonacci(i));
	printf("\n \n");
	return 0;
}
