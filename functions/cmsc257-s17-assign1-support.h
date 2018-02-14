#ifndef CMSC257_A1SUPPORT_INCLUDED
#define CMSC257_A1SUPPORT_INCLUDED

////////////////////////////////////////////////////////////////////////////////
//
//  File          : cmsc257-s17-assign1-support.h
//  Description   : This is a set of general-purpose utility functions we use
//                  for the 257 assignment #1.
//

//
// Functional Prototypes

void float_display_array(float a[], int n);
	// This function prints out the array of floating point values
void integer_display_array(int arr[], int n);
	// This function prints out the array of integer values
int float_evens(float a[], int n);
	// Return the number of even numbers in the array (float version)
int integer_evens(int arr[], int n);
	// Return the number of even numbers in the array (int version)
int countBits(int n);
	// Count the number of '1' bits in the binary representation
	
void most_values(int arr[], int range, int maxVal);
	// Print out the values with the most occurences in array
	
unsigned short reverseBits(unsigned short n);
        // Reverse the binary bit string

void binaryString(void const * const str, unsigned short int size);
        // Print the binary equivalent of the number passed

void integerQuickSort(int arr[], int L,int R);
        // Sort the integer array using QuickSort algorithm
        

#endif // CMSC257_A1SUPPORT_INCLUDED
