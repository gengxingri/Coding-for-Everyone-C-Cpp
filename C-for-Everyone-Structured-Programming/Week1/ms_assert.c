/* Assert.c
   use assert to find errors within program
*/


#include <assert.h>
#include <stdio.h>


int main()
{  
	double x, y;
	while (1)
	{
		printf("Read in 2 floats:\n");
		scanf("%lf %lf", &x, &y);
		assert (y != 0);
		printf("when divided x/y = %lf \n", x/y);
	}
	return 0;
}
