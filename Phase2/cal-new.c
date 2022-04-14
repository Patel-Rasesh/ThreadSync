/*
FLOW - 
1. This is Pipelining sorter with multiple layers of parallel threads
2. Receives N (data size) via pipe from Admin
    a. Receives elements
3. Store those elements in an array (Sorter Array) with size N
4. Uses multiple (log2 M + 2) layers of parallel threads (M - #threads in second layer) (Sorter Array - First layer)
    a. Calculate M based on N.
5. Thread Sync
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 80
typedef struct
{
    char fileName[1024];
    int dataArray[1024];
    int dataSize;
}Buffer;

void test_print(Buffer iReceive){
    // 1. Read the argument in a variable
    //int *inputTest = argv;
    printf("-----------------------------------------------------------\n");
    printf("Printing from cal!\n");
    printf("-----------------------------------------------------------\n");
    printf("Message has been received and it is - %s \n ", iReceive.fileName);

    // 0. Original array before sorting
    int count = 0;
    printf("Original unsorted array is ----------------\n");
    for(count = 0; count < iReceive.dataSize; count++){
        printf("%d ", iReceive.dataArray[count]);
    }
    printf("\n");
    // 2. Append it to the predetermined sized of array
    // 2a. Instantiate an array, where first element is the size of the array and the rest are elements

}
