#ifndef SOCKETS__H
#define SOCKETS__H
#include <stdio.h>
#include "input.h"
#include "types.h"

#define SOCKET_SUCESS_READING
/*#define SOCKET_FAILED_READING*/

#define RESPONSE_APROBADO
/*#define RESPONSE_NO_APROBADO*/


int socketCreate();
int socketConnect(int handle, const char *ip, unsigned short port);
int socketRead(int handle, unsigned char *data, int maxTimeout);
int socketWrite(int handle, const unsigned char* data);
int socketClose(int handle);

#endif
