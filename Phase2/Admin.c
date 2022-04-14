#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "cal-new.c"
#define MAX_LINE_LENGTH 80

void pipCommunication(Buffer iReceive){

    int parentToChild[2];           // File descriptors for Parent to Child pipe
    int childToParent[2];           // File descriptors for Child to Parent pipe
    char message1[200] = {'\0'};            // Initializing a message for IPC - inter process communication
    pipe(parentToChild);            // Making pipes
    pipe(childToParent);
    int processId , bytes;
    char *supp_ptr = NULL;
    if((processId = fork())== -1){
        printf("error while creating a child process");
    }
    char readBuffer[120];           // This will store message being read and written from the pipe
    Buffer tDataBuffer;
    void *ptr_Receive = NULL;
    int count = 0;

    if(processId == 0){
        close(parentToChild[1]);            // Upon receiving a message (command) from Parent

        // Read from parent into a pointer and copy that pointer to respective variables (i.e. filename, input array, CID)
        memset(&tDataBuffer, 0, sizeof(Buffer));
        ptr_Receive = (Buffer *)malloc(sizeof(Buffer));

        bytes = read(parentToChild[0] , ptr_Receive, sizeof(Buffer));
        memcpy(&tDataBuffer, ptr_Receive, sizeof(Buffer));

        printf("Parent to Child - file name: %s ", tDataBuffer.fileName);
        printf("\n");
        
        printf("Content of the file is - \n");
        for(count = 0; count < tDataBuffer.dataSize; count++){
            printf("%d ", tDataBuffer.dataArray[count]);
            if ((count+1)%10 == 0){
                printf("\n");
            }
        }
        printf("\n");

        printf("--------------------------------------------------------\n");
        printf("Sending to child now \n");
        printf("--------------------------------------------------------\n");
        sortChild(tDataBuffer);             // Reading command from parentToChild pipe and execute it in cal process

        strcat(message1, "OK status for : ");       // Upon successful completion sending the acknowledgment to Parent
        strcat(message1, tDataBuffer.fileName);
        strcat(message1, "\n");
        close(childToParent[0]);
        write(childToParent[1] , message1 , strlen(message1)+1);        // Sending acknowledgment
        int i;
        for(i=0; i<=sizeof(message1); i++){
            message1[i]='\0';           // Clearing the message variable
        }
        memset(&tDataBuffer, 0, sizeof(Buffer));
        memset(ptr_Receive, 0, sizeof(ptr_Receive));
    }

    if(processId !=0 ){
        printf("---------------------------------------------------------------------------------------\n");
        printf("returned-pid is %d and PID is %d\n", processId, getpid());
        printf("---------------------------------------------------------------------------------------\n");

        close(parentToChild[0]);
        write(parentToChild[1] , &iReceive, sizeof(Buffer));

        close(childToParent[1]);
        bytes = read(childToParent[0] , readBuffer , sizeof(readBuffer));

        printf("Child to Parent - acknowledgment : ");
        printf("%s", readBuffer);
        printf("-------------------------------------------------------------------------------------------------\n");
    }
}