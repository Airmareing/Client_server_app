#include <sys/types.h>
#include <sys/socket.h>
#include "errprocess.h"

#define SERVER_PORT 50
#define SERVER_IP "127.0.0.1"
#define MAX_BUFFER_SIZE 1024

int main() {
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(SERVER_PORT);
    adr.sin_addr.s_addr = inet_addr(SERVER_IP); 
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);

    while (1) {
        socklen_t adrlen = sizeof adr;
        int my_server = Accept(server, (struct sockaddr *) &adr, &adrlen);
        ssize_t nread;
        char buf[MAX_BUFFER_SIZE * 2] = {0};

        while ((nread = read(my_server, buf, sizeof(buf))) > 0) {
            write(STDOUT_FILENO, buf, nread);
            printf("\n");
        }

        if (nread == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }

        close(my_server);
    }
    
    close(server);
    return 0;
}
