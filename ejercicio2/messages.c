#include "messages.h"

string messages[]={
						
						OK_MSG,
						
						ERR_MSG_MEMORIA_NO_DISPONIBLE,
						ERR_MSG_PUNTERO_NULO,
						
						ERR_MSG_MONTO_INVALIDO,
						ERR_MSG_NUMERO_DE_TARJETA_INVALIDA,
						ERR_MSG_NO_SE_PUDO_ABRIR_ARCHIVO_RANGES,
						ERR_MSG_NO_SE_PUDO_ABRIR_ARCHIVO_CARDS,
						ERR_MSG_TARJETA_NO_SE_ENCUENTRA_EN_RANGOS,
						ERR_MSG_TARJETA_NO_SE_ENCUENTRA_DENTRO_DE_TARJETAS_VALIDAS,
						ERR_MSG_CODIGO_DE_SEGURIDAD_INVALIDO,
						
						ERR_MSG_DE_COMUNICACION
};

status_t mostrar_msg_error(status_t st)
{
	fprintf(stderr,"%s\n",messages[st]);
	
	return OK;
}
