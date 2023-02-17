/*  Given the file listing elephant seal weights (elephant_seal_data), 
    read them into an array and compute the average weight 
    for the set of the elephant seals.
*/

//Preprocessing files
#include <stdio.h>


// define function average()
double average(int SIZE, int numberArray[])
{
	int i, sum = 0;
    
    for (i = 0; i < SIZE; i++)
    {
        sum = sum + numberArray[i];
    }
    return sum/SIZE;
}


// main function
int main(void)
{   
    //Decalarations
    FILE *myfile;
    const int SIZE = 1000;
	int i;
    int numberArray[1000];
    

    //Open and read the txt file
    myfile = fopen("elephant_seal_data.txt", "r");
    

    //Read file into array
    for (i = 0; i < 1000; i++)
    {
        fscanf(myfile, "%d", &numberArray[i]);
    }
 
    //Compute and print the average of the array values
    printf("Average of array values is %.3f", average(SIZE, numberArray));

    
    return 0;

}
