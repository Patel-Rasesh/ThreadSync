#include <stdio.h>

void main(){
    char ipaddrInput[20];
    int portInput;
    // printf("Enter the IP address and port of the server\n");
    // printf("1. IP address = ");
    // fgets(ipaddrInput, 20, stdin);

    printf("2. Port = ");
    scanf("%d", &portInput);

    if (portInput == 2){
        printf("Yes");
    }
    // printf("The following IP address and port are entered ...\n");
    // printf("%s\n", ipaddrInput);
    // printf("%d\n", portInput);
}