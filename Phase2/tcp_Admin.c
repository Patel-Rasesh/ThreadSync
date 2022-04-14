#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "Admin.c"

int main(void)
{
    // 1. Defining file descriptor for Admin process
    int adminFD;
    
    // 2. Defining Socket address for later configuration of port and IP address
    struct sockaddr_in adminAddress;
    
    // 3. Defining and initializing Admin side message buffer
    char adminBuff[200];
    memset(adminBuff, '\0', sizeof(adminBuff));
    
    // 4. Socket creation with pre-configured parameters
    printf("Creating socket now ... \n");
    adminFD = socket(AF_INET, SOCK_STREAM, 0);
    
    if(adminFD < 0){
        // TODO - Can we use pError here?
        printf("ERROR - Could not create socket!\n");
        return -1;
    }
    else{
        printf("Socket is created successfully!\n");
    }    
    
    // 5. Setting PORT and IP address
    // TODO - set them as user inputs
    adminAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    adminAddress.sin_port = htons(2000);
    adminAddress.sin_family = AF_INET;
    
    // 6. Binding the created socket to given IP and PORT
    int ret;
    ret = bind(adminFD, (struct sockaddr*)&adminAddress, sizeof(adminAddress));
    if(ret<0){
        printf("FAILURE while binding!\n");
        return -1;
    }
    else{
        printf("Binding established!\n");
    }
    
    // 7. Start listening to incoming client connection requests
    ret = listen(adminFD, 1);
    if(ret < 0){
        printf("FAILURE while listening!\n");
        return -1;
    }
    else{
        printf("Listening established!\n");
    }
    
    // 8. Start accepting connection requests
    struct sockaddr_in clientAddress;
    int clientBuffSize = sizeof(clientAddress);
    int clientFD;
    clientFD = accept(adminFD, (struct sockaddr*)&clientAddress, &clientBuffSize);
    
    // Handling if something goes wrong
    if (clientFD < 0){
        printf("Client could not establish connection!\n");
        return -1;
    }
    else{
        // Using clientAddress to fetch what PORT and IP it is connected to
        printf("Client is successfully connected to IP :%s at PORT: %i \n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
    }
    
    // 9. Start receiving messages from clients
    Buffer tReceive;    
    void *ptr_Receive = NULL;
    char endRequest[] = "END";

    memset(&tReceive, 0, sizeof(Buffer));
    ptr_Receive = (Buffer *)malloc(sizeof(Buffer));
    
    ret = recv(clientFD, ptr_Receive, sizeof(Buffer), 0);

    memcpy(&tReceive, ptr_Receive, sizeof(Buffer));
    
    int check = strcmp(tReceive.fileName, endRequest);

    while(check != 0){
        if (ret < 0){
            printf("FAILURE in receiving message from client!\n");
            return -1;
        }
        else{
            printf("Sucessfully received message from the client and it is as follows - : \n");
            printf("Filename - %s\n", tReceive.fileName);

            printf("Elements in the file are - \n");
            int count = 0;
            for(count = 0; count < tReceive.dataSize; count++)
            {
                printf("%d ", tReceive.dataArray[count]);
                if ((count+1)%10 == 0){
                    printf("\n");
                }
            }
            printf("\n");
        }    
        
        // 10. Acknowledging that message has been received
        strcpy(adminBuff, "Admin acknowledges!\n");
        ret = send(clientFD, adminBuff, strlen(adminBuff), 0);
        if (ret < 0){
            printf("Admin failed to acknowledge!\n");
            return -1;
        }
        
        // TODO - 11. Send the client's message to child process - cal process
        printf("Sending client's message (via Admin) to the child process - cal\n"); 
        pipCommunication(tReceive);
        
        memset(&tReceive, 0, sizeof(Buffer));
        memset(ptr_Receive, 0, sizeof(ptr_Receive));
        
        ret = recv(clientFD, ptr_Receive, sizeof(Buffer), 0);
        memcpy(&tReceive, ptr_Receive, sizeof(Buffer));
        
        check = strcmp(tReceive.fileName, endRequest);
    }
    // 12. Close socket and file descriptors
    printf("Closing the connection from Admin server now ... \n");
    close(clientFD);
    close(adminFD);
    
    return 0;
}