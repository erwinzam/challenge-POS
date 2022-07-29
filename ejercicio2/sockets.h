#ifndef SOCKETS__H
#define SOCKETS__H
#include <stdio.h>

int socketCreate();
int socketConnect(int handle, const char *ip, unsigned short port);
int socketRead(int handle, unsigned char *data, int maxTimeout);
int socketWrite(int handle, const unsigned char* data);
int socketClose(int handle);

#endif
