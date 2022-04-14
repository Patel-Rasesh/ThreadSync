#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 80
#define GLOBALLOW 0

typedef struct
{
    char fileName[1024];
    int dataArray[1024];
    int dataSize;
    int CID;
}Buffer;

// Temporary array for intermediate steps
int helperArray[5];
int step = 1;
int Debug;

void print(int array[], int size){
    int iterator;
    for (iterator=0; iterator<=size; iterator++){
        printf("%d ", array[iterator]);
        if ((iterator+1)%10 == 0){
            printf("\n");
        }
    }
    printf("\n");
}

void mergeSort(int inputArray[], int low, int mid, int high) {
   int runner1, runner2, index;

   for(runner1 = low, runner2 = mid + 1, index = low; runner1 <= mid && runner2 <= high; index++) {
      if(inputArray[runner1] <= inputArray[runner2])
         helperArray[index] = inputArray[runner1++];
      else
         helperArray[index] = inputArray[runner2++];
   }
   
   while(runner1 <= mid)    
      helperArray[index++] = inputArray[runner1++];

   while(runner2 <= high)   
      helperArray[index++] = inputArray[runner2++];

   for(index = low; index <= high; index++)
      inputArray[index] = helperArray[index];
    
    if (Debug){
        printf("Intermediate Step %d gives - \n", step);
        step++;
        print(inputArray, sizeof(inputArray));
        printf("\n");
    }
}

void sortHelper(int array[], int low, int high){
    int mid;

    // Base condition for recursive call
    if (low >= high){
        return;
    }
    mid = (low + high)/2;
    mid = low + (high-low)/2;
    sortHelper(array, low, mid);
    sortHelper(array, mid+1, high);
    mergeSort(array, low, mid, high);
}

int sortDriver(Buffer iReceive){

    char *inputFile = iReceive.fileName;
    printf("-------------------------------------------------------------------\n");
    printf("Printing from Sorter ... \n");
    printf("-------------------------------------------------------------------\n");
    printf("Following is the input array read from the file %s - \n", iReceive.fileName);
    print(iReceive.dataArray, iReceive.dataSize);
    printf("\n");

    // TODO - Debug required or not - Ask for user input
    int high = iReceive.dataSize;
    int NCopy = iReceive.dataSize;           // Creating a local variable to preserve any manipulation in variable N (length of the array)

    // 1. Initiating merge now
    printf("Initiating merge operation ...\n");
    printf("NOTE - by default Debug is kept on\n");
    sortHelper(iReceive.dataArray, GLOBALLOW, high);           // Passing universal low 0 and high (length of the array)

    printf("Sorted input array - \n");
    printf("====================================CID=%d, file=%s, N=%d\n", iReceive.CID, iReceive.fileName, iReceive.dataSize);
    print(iReceive.dataArray, NCopy);
    
    return 1;
}