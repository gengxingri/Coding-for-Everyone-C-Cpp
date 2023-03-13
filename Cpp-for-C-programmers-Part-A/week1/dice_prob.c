/*
   This is an example shown by Dr. Pohl in class
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define - preprocssor, we donot want to use it
#define SIDES 6
#define R_SIDES (rand()%SIDES +1)    // macros

// Monte Carlo Simulation
int main()
{   
	int i, trials;
	int d, d1, d2, n_dice = 2;
	int outcomes[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Record all cases by rolling two dices
   
   srand(clock());            // seeding function
   printf("\nEnter the number of trials: ");
   scanf("%d", &trials);

    for (i = 0; i < trials; i++){
      d1 = R_SIDES;
      d2 = R_SIDES;
      d = d1 + d2;
    	outcomes[d]++;
    	//printf("d =%d\n", d);
    }

    for (i = 2; i < n_dice * SIDES +1; i++){
    	printf("i = %d, \t p = %f\n", i, (double) (outcomes[i])/trials);
    }
    return 0;

}



