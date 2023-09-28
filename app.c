#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "errprocess.h"

#define CLIENT_PORT 35
#define SERVER_PORT 50
#define SERVER_IP "127.0.0.1"
#define MAX_BUFFER_SIZE 1024

int main() {
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(CLIENT_PORT);
    adr.sin_addr.s_addr = INADDR_ANY;

    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);
    
    FILE *logfile = fopen("app.log", "a");
    if (!logfile) {
        perror("log file open failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        socklen_t adrlen = sizeof adr;
        int client = Accept(server, (struct sockaddr *) &adr, &adrlen);

        char buffer[MAX_BUFFER_SIZE];
        ssize_t nread;
        
        int dest = Socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in d_server = {0};
        d_server.sin_family = AF_INET;
        d_server.sin_port = htons(SERVER_PORT);
        Inet_pton(AF_INET, SERVER_IP, &d_server.sin_addr);
        Connect(dest, (struct sockaddr *) &d_server, sizeof(d_server));

        while ((nread = read(client, buffer, MAX_BUFFER_SIZE)) > 0) {
            // модификация и вывод данных
            char modified_buffer[MAX_BUFFER_SIZE * 2] = {0};
            sprintf(modified_buffer, "Received [%zd]: <", nread);
            strcat(modified_buffer, buffer);
            strcat(modified_buffer, ">");
            write(STDOUT_FILENO, modified_buffer, strlen(modified_buffer));
            printf("\n");
            write(dest, modified_buffer, strlen(modified_buffer));

            // запись лога
            fprintf(logfile, "%s\n", modified_buffer);
            fflush(logfile); 

            //очистка массива
            memset(buffer, 0, sizeof(buffer));
        }

        close(client);
    }

    close(server);
    fclose(logfile);
    return 0;
}
