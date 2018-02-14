#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//Project Includes
#include <proj2header.h>


int main(){
int bytes = 0;
void * start = sbrk(0);

printf("Start Heap address is: %p\n", start);

	char * ptr1 = (char *)malloc(289);
	bytes += 289;
	printf("Memory Leak after malloc: %d\n", memLeaks(start, sbrk(0),bytes));
char * ptr2 = (char *)malloc(47);
      bytes += 47;
      printf("Memory Leak after malloc: %d\n", memLeaks(start, sbrk(0),bytes));
  char * ptr3 = (char *)malloc(192);
      bytes += 192;
      printf("Memory Leak after malloc: %d\n", memLeaks(start, sbrk(0),bytes));
   char * ptr4 = (char *)malloc(14);
      bytes += 14;
      printf("Memory Leak after malloc: %d\n", memLeaks(start, sbrk(0),bytes));
   char * ptr5 = (char *)malloc(2);
      bytes += 2;
      printf("Memory Leak after malloc: %d\n", memLeaks(start, sbrk(0),bytes));
   char * ptr6 = (char *)malloc(29);
      bytes += 29;
      printf("Memory Leak after malloc: %d\n", memLeaks(start, sbrk(0),bytes));
 
  char * ptr7 = (char *)malloc(89);
      bytes += 89;
      printf("Memory Leak after malloc: %d\n", memLeaks(start, sbrk(0),bytes));
 
  char * ptr8 = (char *)malloc(19);
      bytes += 19;
      printf("Memory Leak after malloc: %d\n", memLeaks(start, sbrk(0),bytes));
 
  char * ptr9 = (char *)malloc(10);
      bytes += 10;
      printf("Memory Leak after malloc: %d\n", memLeaks(start, sbrk(0),bytes));
 
  char * ptr10 = (char *)malloc(25);
      bytes += 25;
      printf("Memory Leak after malloc: %d\n", memLeaks(start, sbrk(0),bytes));
 
printf("\n");


	ptr1 = (char*)realloc(ptr1,233);
	bytes +=233;
	bytes -=289;
	printf("Memory Leak after realloc: %d\n\n", memLeaks(start,sbrk(0), bytes));
 ptr2 = (char*)realloc(ptr2,14);
      bytes +=14;
      bytes -=47;
      printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
 ptr3 = (char*)realloc(ptr3,230);
      bytes +=230;
      bytes -=192;
     printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
 ptr4 = (char*)realloc(ptr4,9);
      bytes +=9;
      bytes -=14;
      printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
 ptr5 = (char*)realloc(ptr5,87);
      bytes +=87;
      bytes -=2;
      printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
 ptr6 = (char*)realloc(ptr6,3);
      bytes +=3;
      bytes -=29;
      printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
 ptr7 = (char*)realloc(ptr7,13);
      bytes +=13;
      bytes -=89;
      printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
 ptr8 = (char*)realloc(ptr8,223);
    bytes +=223;
      bytes -=19;
      printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
 ptr9 = (char*)realloc(ptr9,33);
      bytes +=33;
      bytes -=10;
     printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
 ptr10 = (char*)realloc(ptr10,100);
      bytes +=100;
      bytes -=25;
      printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));

printf("\n");

(char*)calloc(102,1);
bytes += 102;
printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
(char*)calloc(74,1);
bytes += 74;
printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
(char*)calloc(10,1);
bytes += 10;
printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
(char*)calloc(79,1);
bytes += 79;
printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
(char*)calloc(15,1);
bytes += 15;
printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
(char*)calloc(85,1);
bytes += 85;
printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
(char*)calloc(5,1);
bytes += 5;
printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
(char*)calloc(90,1);
bytes += 90;
printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
(char*)calloc(70,1);
bytes += 70;
printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
(char*)calloc(120,1);
bytes += 120;
printf("Memory Leak after calloc: %d\n\n", memLeaks(start,sbrk(0), bytes));

free(ptr1);
ptr1 = NULL;
bytes -= 102;
printf("Memory Leak after free: %d\n\n", memLeaks(start,sbrk(0), bytes));

free(ptr2);
ptr2 = NULL;
bytes -= 74;
printf("Memory Leak after free: %d\n\n", memLeaks(start,sbrk(0), bytes));

free(ptr3);
ptr3 = NULL;
bytes -= 10;
printf("Memory Leak after free: %d\n\n", memLeaks(start,sbrk(0), bytes));

free(ptr4);
ptr4 = NULL;
bytes -= 79;
printf("Memory Leak after free: %d\n\n", memLeaks(start,sbrk(0), bytes));

free(ptr5);
ptr5 = NULL;
bytes -= 15;
printf("Memory Leak after free: %d\n\n", memLeaks(start,sbrk(0), bytes));


printf("End of Heap address is: %p\n\n", sbrk(0));


      char * ptrA = (char *)malloc2(289);
      bytes += 289;
      printf("Memory Leak after malloc with best fit: %d\n", memLeaks(start, sbrk(0),bytes));
  char * ptrB = (char *)malloc2(47);
        bytes += 47;
        printf("Memory Leak after malloc with best fit: %d\n", memLeaks(start, sbrk(0),bytes));
    char * ptrC = (char *)malloc2(192);
        bytes += 192;
        printf("Memory Leak after malloc with best fit: %d\n", memLeaks(start, sbrk(0),bytes));
     char * ptrD = (char *)malloc2(14);
        bytes += 14;
        printf("Memory Leak after malloc with best fit: %d\n", memLeaks(start, sbrk(0),bytes));
     char * ptrE = (char *)malloc2(2);
        bytes += 2;
        printf("Memory Leak after malloc with best fit: %d\n", memLeaks(start, sbrk(0),bytes));
     char * ptrF = (char *)malloc2(29);
        bytes += 29;
        printf("Memory Leak after malloc with best fit: %d\n", memLeaks(start, sbrk(0),bytes));
 
    char * ptrG = (char *)malloc2(89);
        bytes += 89;
        printf("Memory Leak after malloc with best fit: %d\n", memLeaks(start, sbrk(0),bytes));
 
    char * ptrH = (char *)malloc2(19);
        bytes += 19;
        printf("Memory Leak after malloc with best fit: %d\n", memLeaks(start, sbrk(0),bytes));
 
    char * ptrI = (char *)malloc2(10);
        bytes += 10;
      printf("Memory Leak after malloc with best fit: %d\n", memLeaks(start, sbrk(0),bytes));
 
    char * ptrJ = (char *)malloc2(25);
        bytes += 25;
        printf("Memory Leak after malloc with best fit: %d\n", memLeaks(start, sbrk(0),bytes));
 
  printf("\n");

ptrA = (char*)realloc2(ptrA,233);
     bytes +=233;
      bytes -=289;
      printf("Memory Leak after realloc: %d\n\n", memLeaks(start,sbrk(0), bytes));
   ptrB = (char*)realloc2(ptrB,14);
        bytes +=14;
        bytes -=47;
        printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
   ptrC = (char*)realloc2(ptrC,230);
        bytes +=230;
        bytes -=192;
       printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
   ptrD = (char*)realloc2(ptrD,9);
        bytes +=9;
        bytes -=14;
        printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
   ptrE = (char*)realloc2(ptrE,87);
        bytes +=87;
        bytes -=2;
        printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
   ptrF = (char*)realloc2(ptrF,3);
        bytes +=3;
        bytes -=29;
        printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
   ptrG = (char*)realloc2(ptrG,13);
        bytes +=13;
        bytes -=89;
        printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
   ptrH = (char*)realloc2(ptrH,223);
      bytes +=223;
        bytes -=19;
        printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
   ptrI = (char*)realloc2(ptrI,33);
        bytes +=33;
        bytes -=10;
       printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
   ptrJ = (char*)realloc2(ptrJ,100);
        bytes +=100;
        bytes -=25;
        printf("Memory Leak after realloc:: %d\n\n", memLeaks(start,sbrk(0), bytes    ));
 
  printf("\n");
(char*)calloc2(102,1);
  bytes += 102;
  printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
 (char*)calloc2(74,1);
 bytes += 74;
 printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
 (char*)calloc2(10,1);
 bytes += 10;
 printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
 (char*)calloc2(79,1);
 bytes += 79;
 printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
 (char*)calloc2(15,1);
 bytes += 15;
 printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
 (char*)calloc2(85,1);
 bytes += 85;
 printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
 (char*)calloc2(5,1);
 bytes += 5;
 printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
 (char*)calloc2(90,1);
 bytes += 90;
 printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
 (char*)calloc2(70,1);
 bytes += 70;
 printf("Memory Leak after calloc: %d\n", memLeaks(start,sbrk(0), bytes));
 (char*)calloc2(120,1);
 bytes += 120;
 printf("Memory Leak after calloc: %d\n\n", memLeaks(start,sbrk(0), bytes));


 free(ptrA);
 ptrA = NULL;
 bytes -= 102;
 printf("Memory Leak after free: %d\n\n", memLeaks(start,sbrk(0), bytes));

 free(ptrB);
 ptrB = NULL;
 bytes -= 74;
 printf("Memory Leak after free: %d\n\n", memLeaks(start,sbrk(0), bytes));

 free(ptrC);
 ptrC = NULL;
 bytes -= 10;
 printf("Memory Leak after free: %d\n\n", memLeaks(start,sbrk(0), bytes));

 free(ptrD);
 ptrD = NULL;
 bytes -= 79;
 printf("Memory Leak after free: %d\n\n", memLeaks(start,sbrk(0), bytes));

 free(ptrE);
 ptrE = NULL;
 bytes -= 15;
 printf("Memory Leak after free: %d\n\n", memLeaks(start,sbrk(0), bytes));


return 0;

}




