#include <stdio.h>
void float_display_array(float a[], int n){
	int i;
	for(i=0;i<n;i++){
	printf("%.2f\n",  a[i]); //get and print float value in array to 2 decimal places
}}
void integer_display_array(int a[], int n){
	int i;
	for(i=0;i<n;i++){
	printf("%d\n",a[i]);} //print out int values
}
int float_evens(float a[], int n){
	int i;
	int count=0;
	for(i=0;i<n;i++){
	if(((int)a[i] & 1)==0)  //casting float value to int and if array value & 1 comes out to 0 then it is even.
	count+=1;} 			//add to the count of even numbers in the float array
	return count;
}
int integer_evens(int arr[], int n){
	int i;
	int count=0;
	for(i=0;i<n;i++){
	if((arr[i] & 1)==0)	//if array value & 1 come out to 0 then it is even
	count+=1;}			//add to the count of even numbers in the int array
	return count;
}
unsigned int countBits(unsigned int n){
	unsigned int count = 0;
	while(n){			
	count += n & 1;		//add 1 or 0 to count
	n >>=1;				//assign the value of n as n moved 1 bit shift to the right
	}
	return count;
}

void most_values(int arr[], int range,int maxVal){
int i, max, result;
	for(i=0;i<range;i++)		
	arr[arr[i]%maxVal] += maxVal;  //
	max = arr[0];				//
	result = 0;
	for(i=1;i<range;i++){
	if(arr[i] > max){
	max = arr[i];
	result=i;
}
}
	printf("\nThe most occuring value(s):%d \n", result);
}

unsigned short reverseBits(unsigned short int n){
		unsigned short count = sizeof(n) * 8 ;  //multiple the size of n by 8 bits
		unsigned short reverse =0;
		while(n){
		reverse <<=1;      		//bit shift reverse by 1
		reverse |= n & 1;		//returns a 1 if either reverse or n&1 is 1
		n>>=1;					//shift n by 1 to the right
		count--;}
		reverse <<=count;		//reverse is shifted by count to the left
		return reverse;
		
}
/*void binaryString( void const * const str,unsigned short int size){
	int i, j;
	unsigned char *b = (unsigned char*) str;
	unsigned char byte;
	
	for(i=size-1;i>=0;i--){
	for(j=7;j>=0;j--){
	byte = (b[i] >> j) & 1;
	printf("%d", byte);
}
}
puts("");
}*/
void integerQuickSort(int arr[], int L,int R){
int i, j, pivot; //int temp
	if(L < R){  //if Left point is less than Right point
	pivot = L;	//set pivot as L
	i = L;		
	j = R;
	while(i<j){
	while(arr[i] <= arr[pivot] && i < R)
	i++;
	while(arr[j] > arr[pivot])
	j--;
	if(i<j){
	arr[i] = arr[i] ^ arr[j];
	arr[j] = arr[i] ^ arr[j];
	arr[i] = arr[i] ^ arr[j];
	//temp = arr[i];
	//arr[i] = arr[j];
	//arr[j] = temp;
	}
	}
	arr[j] = arr[j] ^ arr[pivot];
	arr[pivot] = arr[j] ^ arr[pivot];
	arr[j] = arr[j] ^ arr[pivot];
	//temp = arr[pivot];
	//arr[pivot] = arr[j];
	//arr[j] = temp;
	integerQuickSort(arr, L, j-1);
	integerQuickSort(arr, j+1, R);
}
}


