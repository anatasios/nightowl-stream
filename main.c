#include "payload.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

void usage(char* fn) {
    printf("Usage: %s <IP> <channel>\nChannel can be 1-4.\n", fn);
    exit (-1);
}


void error(char* er) {
    printf("%s\n", er);
    exit(-1);
}

// Returns int socket number
int connectDVR(char addr[], int port) {
    int sockfd;
    struct sockaddr_in serv_add;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("Failed to create socket");

    memset(&serv_add, '0', sizeof(serv_add));

    serv_add.sin_family = AF_INET;
    serv_add.sin_port = htons(port);

    if(inet_pton(AF_INET, addr, &serv_add.sin_addr)<=0) {
        error("inet_pton error occured");
    }

    if( connect(sockfd, (struct sockaddr *)&serv_add, sizeof(serv_add)) < 0) {
        error("Connection failed");
    }

    return sockfd;
}

void modifyPayloadChannel(char chan) {
    if(chan<49||chan>52) 
        error("Channel must be between 1 and 4");
    chan-=48;
    payload_bin[31] = chan;
}

int main(int argc, char* argv[]) {
    char recvBuff[1024];
    int sockfd = 0, count =0;

    if(argc!=3)
        usage(argv[0]);

    memset(recvBuff, '0', sizeof(recvBuff));

    sockfd = connectDVR(argv[1], 9090);

    // Prepare and send initial payload
    modifyPayloadChannel(argv[2][0]);
    write(sockfd, payload_bin, payload_bin_len);

    do {
        count = read(sockfd, recvBuff, 1024);
        if(count>0) {
            write(STDOUT_FILENO, recvBuff, count);
        }
    } while(count);
}
