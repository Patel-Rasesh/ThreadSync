/*
FLOW - 
1. Client sends the input to be sorted
1a. A different terminal tab would have client.exe running
1b. From where we will send filename (Filename = END suggests closing the connection)
1c. Each Client should be given a CID 
2. Client sends three things (CID, FILENAME and N+1 INTEGERS)
    Why integers when we are sending filename? Our testing environment might not have shared file system - NFS
3. Admin accepts it via socket
4. Admin Communicates it to child using pipe
5. Child is our sorter who sorts it

ACTION STEPS FOR PHASE 2 - 
0. Command line input for Ip address and port number
2. Read the file in client and send it to Sever via socket
    Temporarily have created a different c file (for Admin) which handles IPC

ACTION STEPS FOR PHASE 2B - 
0. Read multiple files - sorting requests (sequencially), give END filename to terminate the connection
1. Send file (array size and array elements) via socket
    a. Send entire array via socket at a time
2. Store it in an array Admin Process
    a. Develop a queue to ensure no loss of information
3. Communicate it via pipe to child process
    a. Sorter Array is File Descriptor in which Admin write to pipe (use Sorter Array as the buffer for the pipe read)
4. Communication between two servers of university

ACTION STEPS FOR PHASE 3 -
1. Create threads

*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 80

typedef struct
{
    char fileName[1024];
    int dataArray[1024];
    int dataSize;
}Buffer;

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

    // 9. Reading file's elements into a buffer
    FILE *file = fopen(clientBuff, "r");
    char element[10];
    fgets(element, MAX_LINE_LENGTH, file);
    
    printf("Length of an array in str %s\n", element);
    
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
    
    
    Buffer tDataToSend;
    memset(&tDataToSend, 0, sizeof(Buffer));

    strcpy(tDataToSend.fileName, clientBuff);
    memcpy(&tDataToSend.dataArray, &inputArray, sizeof(inputArray));

    printf("%s\n", tDataToSend.fileName);

    tDataToSend.dataSize = lengthOfFile;
    int count = 0;
    for(count = 0; count < tDataToSend.dataSize; count++)
    {
        printf("%d ", tDataToSend.dataArray[count]);
    }
    printf("\n");
    ret = send(adminFD, &tDataToSend, sizeof(tDataToSend), 0);

    while(check != 0){

        // 9. Send file name to Admin process
        // TODO - Send file content
        ret = send(adminFD, inputArray, lengthOfFile, 0);
        //ret = send(adminFD, clientBuff, strlen(clientBuff), 0);
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
    printf("Requesting to exit ...");
    close(adminFD);
    
    return 0;
}