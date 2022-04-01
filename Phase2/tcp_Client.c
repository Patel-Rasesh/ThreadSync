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
0a. Communication between two different servers of University
 
1. Store the array in the child/Cal process

2. Read the file in client and send it to Sever via socket
3. Make Admin Socket compatible
4. Send filename and elements to cal via pipe from Admin

*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

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
    printf("Enter filename for sorter: ");
    gets(clientBuff);
    
    // 8. Send file name to Admin process
    // TODO - In later phases, I will send filename and elements of the array
    ret = send(adminFD, clientBuff, strlen(clientBuff), 0);
    if(ret < 0){
        printf("Failed to send filename to the Admin process!\n");
        return -1;
    }

    // 9. Receiving acknowledgement from Admin
    ret = recv(adminFD, adminBuff, sizeof(adminBuff), 0);
    if(ret < 0){
        printf("Failed to receive acknowledgement from Admin process\n");
        return -1;
    }
    else{
        printf("Successfully received acknowledgment from Admin process and it is as follows - \n");
        printf("%s\n", adminBuff);
    }
    
    // 10. Closing the connection from this client
    close(adminFD);
    
    return 0;
}