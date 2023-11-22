#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1472 // MTU 1500 - 28 bytes for UDP and IP headers

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <IP:PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    char *ip = strtok(argv[2], ":");
    int port = atoi(strtok(NULL, ":"));

    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUFFER_SIZE];
    FILE *file;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip);

    if ((file = fopen(filename, "rb")) == NULL) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    while (!feof(file)) {
        int bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
        sendto(sockfd, buffer, bytes_read, 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    }

    fclose(file);
    close(sockfd);

    return 0;
}
