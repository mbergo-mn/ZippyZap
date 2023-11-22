#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IP:PORT>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ip = strtok(argv[1], ":");
    int port = atoi(strtok(NULL, ":"));

    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("TCP Server listening on %s:%d\n", ip, port);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&address)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while(1) {
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        printf("%s\n", buffer);
    }

    close(new_socket);
    close(server_fd);

    return 0;
}
