////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmsc257-s17-assign1.c
//  Description    : This is the main source code for for the first assignment
//                   of CMSC257.  See the related
//                   assignment page for details.
//
//   Author        : Andy Huynh 
//

// Include Files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Project Includes
#include <cmsc257-s17-assign1-support.h>

//
// Functions

////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : The main function for the CMSC257 assignment #1
//
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Outputs      : 0 if successful test, -1 if failure

int main(int argc, char *argv[]) 
{

	// Local variables
	// NOTE: this is where you will want to add some new variables
	float f_array[20];
    int i,x, m_array[20], m_array2[20];
	unsigned short n;
	
	// Step #1 - read in the float numbers to process
	for (i=0; i<20; i++) {
		scanf("%f", &f_array[i]);
	}

    // Step #2 - convert the floating point values to integers
    for(i=0; i<20;i++){
	m_array[i] = (int) f_array[i];
	m_array2[i] = (int) f_array[i];	 
	}
	for(i=0; i<20;i++){
	x = m_array[i]>>31;            // >>31 will result in -1 if negative or 0 if positive
	m_array[i]=(m_array[i] ^ x)-(x); //comparing with XOR,( i ^ 0) - 0 = i, if positive,(i ^ -1) - (-1) = absolute value of i when neg
	}
	for(i=0; i<20;i++){
	m_array[i]= (m_array[i] & (16-1));	
}
    // Step #3 - print out the integer and floating point arrays   
printf("\n float values are: \n"); 	
float_display_array(f_array, 20);
printf("\n Integer values after absolute value and mod: \n");
	integer_display_array(m_array, 20);
printf("\n Integer values before: \n");
	integer_display_array(m_array2, 20);
    // Step #4 - print out the number of '1's in each integer
   for(i=0;i<20;i++){
	unsigned int n=countBits(m_array[i]);
	printf("\n%d has %d '1' bits\n ", m_array[i], n); 	
}
    // Step #5 - Sort the integer array using QuickSort and print the sorted array
   integerQuickSort(m_array, 0, 20);
	printf("\nThe array sorted via Quicksort:\n");
	for(i=0;i<20;i++){
	printf("%d \n", m_array[i]);}

    // Step #6 - figure out number of evens in each array (float and sorted integer arrays)
   int fl = (int) float_evens(f_array,20);
	int in = integer_evens(m_array,20);
	printf("\n There are %d even numbers in the float array and %d even numbers in the integer array \n",fl,in);


    // Step #7 - print the most frequent values from the sorted integer array 
	most_values(m_array,20, 16);
    // Step #8 - print the integers corresponding to the reverse bit string from integer array
	for(i=0;i<20;i++){
	n = reverseBits((unsigned short) m_array[i]);
	printf("\nReverse of %d is %d", m_array[i],n);}
	
	for(i=0;i<20;i++){
	}
	// Return successfully
	return(0);
}
