/*
FLOW - 
1. Instead of reading from a file, Admin process uses a server socket to receive
    sorting requests from clients
2. Admin process sends three things to Child process - CID, FILENAME and N+1 Integers
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "cal-new.c"
#define MAX_LINE_LENGTH 80

int main(int argc, char **argv) {

    int parentToChild[2];           // File descriptors for Parent to Child pipe
    int childToParent[2];           // File descriptors for Child to Parent pipe

    char message1[200] = {'\0'};            // Initializing a message for IPC - inter process communication
    char readBuffer[120];           // This will store message being read and written from the pipe
    pipe(parentToChild);            // Making pipes
    pipe(childToParent);
    int processId , bytes;
    char *supp_ptr = NULL;
    char inputTest[100];
    char *inputFile = argv[1];          // Reading the file name as a user input
    FILE *file = fopen(inputFile, "r");
    char *lines = fgets(inputTest, MAX_LINE_LENGTH, file);
    int numberOfLines = strtol(lines, &supp_ptr, 10);
    if((processId = fork())== -1){
        printf("error while creating a child process");
    }
    
    if(processId == 0){
        while(numberOfLines != 0){
            
            close(parentToChild[1]);            // Upon receiving a message (command) from Parent
            bytes = read(parentToChild[0] , readBuffer , sizeof(readBuffer));
            printf("Parent to Child - command: %s", readBuffer);
            
            printf("\t\t Sending to child now -------------------------------------\n");
            test_print(readBuffer);             // Reading command from parentToChild pipe and execute it in cal process

            // cal_function(readBuffer);           

            strcat(message1, "OK status : ");       // Upon successful completion sending the acknowledgment to Parent
            strcat(message1, readBuffer);
            strcat(message1, "\n");
            close(childToParent[0]);
            write(childToParent[1] , message1 , strlen(message1)+1);        // Sending acknowledgment
            for(int i=0; i<=sizeof(message1); i++){
                message1[i]='\0';           // Clearing the message variable
            }
            numberOfLines--;
        }
        // exit(1);
    }

    if(processId !=0 ){
        printf("---------------------------------------------------------------------------------------\n");
        printf("returned-pid is %d and PID is %d\n", processId, getpid());
        printf("---------------------------------------------------------------------------------------\n");
        // Number of Lines if the first line from the input file
        while(numberOfLines != 0){

            close(parentToChild[0]);
            fgets(inputTest, MAX_LINE_LENGTH, file);        // Reading the acknowledgment from child
            write(parentToChild[1] , inputTest , strlen(inputTest)+1);

            close(childToParent[1]);
            bytes = read(childToParent[0] , readBuffer , sizeof(readBuffer));

            printf("Child to Parent - acknowledgment : ");
            printf("%s", readBuffer);
            printf("-------------------------------------------------------------------------------------------------\n");
            // exit(1);
            numberOfLines--;
        }
    }

    return 0;
}