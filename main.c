#include "payload.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void usage(char* fn) {
    printf("Usage:\n\n%s <IP> <channel>\nChannel can be 1-4.", fn);
    exit (-1);
}

void main(int argc, char* argv[]) {
    if(argc!=3)
        usage(argv[0]);


}
