/* Assert.c
   use assert to find errors within program
*/

#define NDEBUG // goes before <assert.h>, it turns off the assert
#include <assert.h>
#include <stdio.h>
#include <ctype.h>


int main()
{
	assert(0);
	printf("my program runs\n");
	return 0;
}
