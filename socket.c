#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> //socketAPI
#include <unistd.h> //close()

#define BUFSIZE 32 //buffer size

void RaiseError(char *msg) {
    //error message
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {

    int sock; //socketDiscriptor

    //server address
    struct sockaddr_in servAddr;
    char *servIp;
    unsigned short servPort;

    //send server string
    char *sendStr;
    int sendStrLen;

    //receive buffer
    char buf[BUFSIZE];
    int bytesRcvd, totalBytesRcvd;

    //validate arguments
    if((argc < 3) || (4 < argc)) {
        fprintf(stderr, "Usage: %s <Server IP> <Message> [<Server Port>]\n", argv[0]);
        exit(1);
    }
    servIp = argv[1];
    sendStr = argv[2];
    if(argc == 4) {
        servPort = atoi(argv[3]);
    }
    else {
        servPort = 7; //Echo server well-knownPortNumber
    }

    // create tcpStreamSocket
    if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        RaiseError("socket() failed");
    }

    //connect to socket
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(servIp);
    servAddr.sin_port = htons(servPort);
    if(connect(sock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0) {
        RaiseError("connect() failed");
    }

    //send message
    sendStrLen = strlen(sendStr);
    if(send(sock, sendStr, sendStrLen, 0) != sendStrLen) {
        RaiseError("send() sent a different number of bytes than expected");
    }

    //receive message
    totalBytesRcvd = 0;
    printf("Received: ");
    while(totalBytesRcvd < sendStrLen) {
        if((bytesRcvd = recv(sock, buf, BUFSIZE - 1, 0)) <= 0) {
            RaiseError("recv() failed or connection closed prematurely");
        }
        totalBytesRcvd += bytesRcvd;
        buf[bytesRcvd] = '\0';
        printf("%s", buf);
    }
    printf("\n");

    //close
    close(sock);
    return 0;
}
