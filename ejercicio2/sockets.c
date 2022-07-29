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
	#ifdef RESPONSE_APROBADO
	
	sprintf((string)data,"%s%s",RESPONSE_MSG_TYPE,
							    RESPONSE_MSG_TRANSACCION_APROBADA);
	#endif
	
	#ifdef RESPONSE_NO_APROBADO	
				    
	sprintf((string)data,"%s%s",RESPONSE_MSG_TYPE,"01");
	
	#endif
	
	#ifdef SOCKET_SUCESS_READING
	
	return strlen((string)data);
	
	#endif
	
	#ifdef SOCKET_FAILED_READING
	
	return -1; 
	
	#endif
}

int socketWrite(int handle, const unsigned char* data)
{
	return 0;
}

int socketClose(int handle)
{
	return 0;
}
