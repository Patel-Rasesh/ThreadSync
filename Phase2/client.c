/*
FLOW -
Same ip address will go in both the places - 
Admin will run from the ip address user enters (./admin.exe)
Client will connect from any ip address (./client.exe)

ACTION STEPS- 
1. Command line input of DEBUG for EACH file
5. IP, port, CID, debug
2. Reread through the document

*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LENGTH 80

// 0. The following structure is used in socket send/receive
typedef struct
{
    char fileName[1024];
    int dataArray[1024];
    int dataSize;
    int CID;
}Buffer;

Buffer readFile(char* iFileName){
    srand(time(NULL));
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

    printf("Length of this input array is N = %d\n", lengthOfFile);
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
    printf("Elements of the array are - \n");
    for(iterator=0; iterator<lengthOfFile; iterator++){
        printf("%d ", inputArray[iterator]);
        if ((iterator+1)%10 == 0){
            printf("\n");
        }
    }
    printf("\n");
    
    // 10. Preparing structure to send filename and input array
    Buffer oDataToSend;
    memset(&oDataToSend, 0, sizeof(Buffer));

    strcpy(oDataToSend.fileName, iFileName);
    memcpy(&oDataToSend.dataArray, &inputArray, sizeof(inputArray));

    oDataToSend.dataSize = lengthOfFile;

    //CID and assign them to input array
    // int CIDInput;
    // printf("Enter CID for this client = ");
    // scanf("%d", &CIDInput);
    // oDataToSend.CID = CIDInput;

    // int debugLocal;
    // printf("Detailed execution of sorting, turn Debug on by entering 1 (otherwise enter 0) : ");
    // scanf("%d", &debugLocal);
    // oDataToSend.debug = debugLocal;
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

    char ipaddrInput[100];
    int portInput;
    // printf("Enter the IP address and port of the server\n");
    // printf("1. IP address = ");
    // fgets(ipaddrInput, 100, stdin);

    // printf("2. Port = ");
    // scanf("%d", &portInput);

    // printf("The following IP address and port are entered ...\n");
    // printf("%s ", ipaddrInput);
    //printf("%d\n", portInput);

    // char clientBuff[200];
    // memset(clientBuff, '\0', sizeof(clientBuff));
    // printf("Sequentially enter file names and enter END (without quotes) to exit : \n");
    // gets(clientBuff);
    // printf("Entered in file number 1 : %s\n", clientBuff);

    //adminAddress.sin_addr.s_addr = inet_addr(ipaddrInput);
    //adminAddress.sin_port = htons(portInput);
    // adminAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // adminAddress.sin_port = htons(2000);
    adminAddress.sin_addr.s_addr = inet_addr("10.176.92.16");
    adminAddress.sin_port = htons(3490);
    
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
    printf("Sequentially enter file names and enter END (without quotes) to exit\n");
    gets(clientBuff);
    printf("Entered in file number 1 : %s\n", clientBuff);

    // 8. Check if filename is END
    char endRequest[] = "End";
    int fileIterator = 1;

    int check = strcmp(clientBuff, endRequest);

    // 11. Send input arrays from files until filename = END
    while(check != 0){

        // Getting Buffer from ReadFile function
        printf("Entered file is not END\n");
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
        memset(clientBuff, '\0', sizeof(clientBuff));
        gets(clientBuff);
        printf("Entered in file number %d : %s\n", fileIterator+1, clientBuff);
        fileIterator++;
        check = strcmp(clientBuff, endRequest);
    }

    // 11. Closing the connection from this client
    printf("Requesting to exit ...\n");
    close(adminFD);
    
    return 0;
}