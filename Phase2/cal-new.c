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

void test_print(char *argv){
    // 1. Read the argument in a variable
    char *inputTest = argv;
    printf("-----------------------------------------------------------\n");
    printf("Printing from cal!\n");
    printf("-----------------------------------------------------------\n");
    printf("Message has been received and it is - %s \n ", inputTest);

    // 2. Append it to the predetermined sized of array
    // 2a. Instantiate an array, where first element is the size of the array and the rest are elements

}
