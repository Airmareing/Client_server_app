#ifndef ERRPROCESS_H
#define ERRPROCESS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

#endif // ERRPROCESS_H