#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1460 // MTU 1500 - 40 bytes for TCP and IP headers

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <IP:PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    char *ip = strtok(argv[2], ":");
    int port = atoi(strtok(NULL, ":"));

    int sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    FILE *file;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    if ((file = fopen(filename, "rb")) == NULL) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    while (!feof(file)) {
        int bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
        send(sock, buffer, bytes_read, 0);
    }

    fclose(file);
    close(sock);

    return 0;
}
