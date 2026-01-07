#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    printf("HTTP server running on port 8080\n");

    while (1) {
        client_fd = accept(server_fd, NULL, NULL);
        read(client_fd, buffer, sizeof(buffer));

        const char *response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n\r\n"
            "Hello from simple HTTP server";

        write(client_fd, response, strlen(response));
        close(client_fd);
    }

    return 0;
}
