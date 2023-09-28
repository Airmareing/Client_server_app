#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define CLIENT_PORT 35
#define SERVER_PORT 50
#define SERVER_IP "192.168.1.10"
//#define SERVER_LOCAL_IP "127.0.0.1"
#define MAX_BUFFER_SIZE 1024

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        printf("inet_pton failed: src does not contain a character"
            " string representing a valid network address in the specified"
            " address family\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(CLIENT_PORT);
    adr.sin_addr.s_addr = INADDR_ANY;

    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);
    
    FILE *logfile = fopen("test1.log", "a");
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
