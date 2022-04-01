/*
FLOW - 
1. This is Pipelining sorter with multiple layers of parallel threads
2. Receives N (data size) via pipe from Admin
2a. Receives elements
5. Thread Sync
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 80

void test_print(char *argv){
    // 1. Read the argument in a variable
    char *inputTest = argv;
    printf("Printing from cal ---------------------------------------\n");
    printf("Message has been received and it is - %s \n ", inputTest);

    // 2. Append it to the predetermined sized of array
}
