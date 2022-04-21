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
#include "MergeSort.c"

#define MAX_LINE_LENGTH 80

void sortChild(Buffer iReceive){
    
    // 1. Read the argument in a variable
    printf("-----------------------------------------------------------\n");
    printf("Printing from cal process!\n");
    printf("-----------------------------------------------------------\n");
    printf("Message has been received from file - %s \n", iReceive.fileName);

    // 2. Original array before sorting
    int count = 0;
    printf("Child - Original unsorted array is ----------------\n");
    for(count = 0; count < iReceive.dataSize; count++){
        printf("%d ", iReceive.dataArray[count]);
        if ((count+1)%10 == 0){
            printf("\n");
        }
    }
    printf("\n");
    sortDriver(iReceive);
    // 2a. Instantiate an array, where first element is the size of the array and the rest are elements

}
