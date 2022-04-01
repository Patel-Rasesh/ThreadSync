#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 80
#define GLOBALLOW 0

// Temporary array for intermediate steps
int helperArray[5];
int step = 1;
int Debug;

void print(int array[], int size){
    int iterator;
    for (iterator=0; iterator<size; iterator++){
        printf("%d ", array[iterator]);
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

int main(int argc, char **argv){

    char *inputFile = argv[1];           // Reading filename as a user input
    FILE *file = fopen(inputFile, "r");          // Opening the file
    char inputTest[100];         // This will store one line from the file at a time
    char *supp_ptr = NULL;       // Supplimentary pointer
    char *lines = fgets(inputTest, MAX_LINE_LENGTH, file);           // Reading the first line from the file - number of lines
    int NFromFile = strtol(lines, &supp_ptr, 10);            // Converting number of lines to an integer
    printf("%d ", NFromFile);
    supp_ptr = NULL;

    int *inputArrayFile = (int *) malloc(NFromFile*sizeof(int *));          // Initializing input Array pointer
    int index = 0;

    int numberOfElements = NFromFile;
    while(numberOfElements != 0){           // Lopping until EOF
       char *elementStr = (char *) malloc(sizeof(char *));            // Initializing the element
       if(NULL == elementStr){
           return 0;
        }
       fgets(inputTest, MAX_LINE_LENGTH, file);         // Reading the next element
       strcpy(elementStr, inputTest);
       int element = strtol(elementStr, &supp_ptr, 10);       // Converting elementStr to integer
       supp_ptr = NULL;
       //printf("%d ", element);            // Printing for debug

       inputArrayFile[index] = element;         // Append to the input array pointer
       index++;

       free(elementStr);
       elementStr = NULL;
       numberOfElements--;
    }
    printf("\n");
    printf("-------------------------------------------------------------------\n");
    printf("Following is the input array read from the file %s - \n", inputFile);
    printf("-------------------------------------------------------------------\n");
    print(inputArrayFile, NFromFile);
    printf("\n");

    // TODO - Debug required or not - Ask for user input
    int high = NFromFile;
    int NCopy = NFromFile;           // Creating a local variable to preserve any manipulation in variable N (length of the array)
    sortHelper(inputArrayFile, GLOBALLOW, high);           // Passing universal low 0 and high (length of the array)

    printf("Sorted input array - \n");
    print(inputArrayFile, NCopy);
    
    return 1;
}