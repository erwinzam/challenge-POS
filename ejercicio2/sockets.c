#include "sockets.h"
#include "input.h"
#include "types.h"
#include <string.h>
#include <stdio.h>


int socketCreate()
{
	return 0;
}

int socketConnect(int handle, const char *ip, unsigned short port)
{
	return 0;
}

int socketRead(int handle, unsigned char *data, int maxTimeout)
{
	sprintf((string)data,"%s%s",RESPONSE_MSG_TYPE,
							    RESPONSE_MSG_TRANSACCION_APROBADA);
							    
	/*sprintf((string)data,"%s%s",RESPONSE_MSG_TYPE,"01");*/
	
	return strlen((string)data);
	/*return -1; */
}

int socketWrite(int handle, const unsigned char* data)
{
	return 0;
}

int socketClose(int handle)
{
	return 0;
}
