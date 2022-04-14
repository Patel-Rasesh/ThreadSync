/*
ACTION STEPS- 
0. Pass Buffer structure in pipe communication to Cal
1. Print merge sort output on each step
2. Call merge sort from cal
3. Include CID in the buffer structure
4. Bring output of the merge sort in the required format

5. Command line input for IP address and port number
6. Develop a queue in Admin to ensure no loss of information
7. Communicate it via pipe to child process
    a. Sorter Array is File Descriptor in which Admin write to pipe (use Sorter Array as the buffer for the pipe read)
8. Communication between two servers of university
9. 

*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 80

// 0. The following structure is used in socket send/receive
typedef struct
{
    char fileName[1024];
    int dataArray[1024];
    int dataSize;
}Buffer;

Buffer readFile(char* iFileName){
    /*
    Takes filename as an argument and returns the required structure 
    (filename, input array, and size of the input array) for that input file
    */
    FILE *file = fopen(iFileName, "r");
    char element[10];
    fgets(element, MAX_LINE_LENGTH, file);
    
    char *supp_ptr = NULL;
    int lengthOfFile = strtol(element, &supp_ptr, 10);
    supp_ptr = NULL;

    printf("Length of this input array is %d\n", lengthOfFile);
    int iterator;
    int inputArray[lengthOfFile];

    memset(&element, 0, sizeof(element));

    for(iterator=0; iterator<lengthOfFile; iterator++){
        fgets(element, MAX_LINE_LENGTH, file);

        int elementInt = strtol(element, &supp_ptr, 10);
        supp_ptr = NULL;
    
        inputArray[iterator] = elementInt;
        memset(&element, 0, sizeof(element));
    }
    printf("Elements of the input file are - \n");
    for(iterator=0; iterator<lengthOfFile; iterator++){
        printf("%d ", inputArray[iterator]);
    }
    printf("\n");
    
    // 10. Preparing structure to send filename and input array
    Buffer oDataToSend;
    memset(&oDataToSend, 0, sizeof(Buffer));

    strcpy(oDataToSend.fileName, iFileName);
    memcpy(&oDataToSend.dataArray, &inputArray, sizeof(inputArray));

    printf("%s\n", oDataToSend.fileName);

    oDataToSend.dataSize = lengthOfFile;
    int count = 0;
    for(count = 0; count < oDataToSend.dataSize; count++)
    {
        printf("%d ", oDataToSend.dataArray[count]);
    }
    printf("\n");
    return oDataToSend;
}

int main(void)
{
    // 1. Defining file descriptor for Admin process
    int adminFD;
    
    // 2. Defining Socket address for later configuration of port and IP address
    struct sockaddr_in adminAddress;
    //struct sockaddr_in server_addr, client_addr;
    
    // 3. Defining and initializing Admin side message buffer
    char adminBuff[200];
    memset(adminBuff, '\0', sizeof(adminBuff));
    
    // 4. Socket creation with pre-configured parameters
    printf("Creating socket now ... \n");
    adminFD = socket(AF_INET, SOCK_STREAM, 0);
    
    if(adminFD < 0){
        printf("ERROR - Could not create socket!\n");
        return -1;
    }
    else{
        printf("Socket is created successfully!\n");
    }
    
    // 5. Setting PORT and IP address
    // TODO - set them same as tcp_Admin
    adminAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    adminAddress.sin_port = htons(2000);
    adminAddress.sin_family = AF_INET;
    
    // 6. Sending connection request to Admin
    int ret = connect(adminFD, (struct sockaddr*)&adminAddress, sizeof(adminAddress));
    if(ret < 0){
        printf("Failed to connect to the Admin process!\n");
        return -1;
    }
    else{
        printf("Successfully connected to Admin process!\n");
    }
    
    // 7. Fetch file name from user as command line input
    char clientBuff[200];
    memset(clientBuff, '\0', sizeof(clientBuff));
    printf("Enter file names sequentially and enter END (without quotes) to exit\n");
    gets(clientBuff);
    printf("Entered in 1 : %s\n", clientBuff);

    // 8. Check if filename is END
    char endRequest[] = "END";
    int fileIterator = 1;

    int check = strcmp(clientBuff, endRequest);

    // 11. Send input arrays from files until filename = END
    while(check != 0){

        // Getting Buffer from ReadFile function
        Buffer tDataToSend = readFile(clientBuff);
        ret = send(adminFD, &tDataToSend, sizeof(tDataToSend), 0);

        if(ret < 0){
            printf("Failed to send filename to the Admin process!\n");
            return -1;
        }

        // 10. Receiving acknowledgement from Admin
        ret = recv(adminFD, adminBuff, sizeof(adminBuff), 0);
        if(ret < 0){
            printf("Failed to receive acknowledgement from Admin process\n");
            return -1;
        }
        else{
            printf("Successfully received acknowledgment from Admin process and it is as follows - \n");
            printf("%s\n", adminBuff);
        }
        printf("Enter next file --- \n");
        gets(clientBuff);
        printf("Entered in %d : %s\n", fileIterator+1, clientBuff);
        fileIterator++;
        check = strcmp(clientBuff, endRequest);
    }

    // 11. Closing the connection from this client
    printf("Requesting to exit ...\n");
    close(adminFD);
    
    return 0;
}