#ifndef MESSAGES__H
#define MESSAGES__H

#include "types.h"

#define OK_MSG "Operación exitosa"

#define ERR_MSG_MEMORIA_NO_DISPONIBLE "Error: Memoria no disponible."
#define ERR_MSG_PUNTERO_NULO "Error: Puntero nulo."

#define ERR_MSG_MONTO_INVALIDO "Error: Monto invalido."
#define ERR_MSG_NUMERO_DE_TARJETA_INVALIDA "Error: Numero de tarjeta invalida."
#define ERR_MSG_NO_SE_PUDO_ABRIR_ARCHIVO_RANGES "Error: Base de datos de tarjetas no disponible."
#define ERR_MSG_NO_SE_PUDO_ABRIR_ARCHIVO_CARDS "Error: Base de datos de tarjetas no disponible."
#define ERR_MSG_TARJETA_NO_SE_ENCUENTRA_EN_RANGOS "Error: Tarjeta no soportada."
#define ERR_MSG_TARJETA_NO_SE_ENCUENTRA_DENTRO_DE_TARJETAS_VALIDAS "Error: Tarjeta no soportada."
#define ERR_MSG_CODIGO_DE_SEGURIDAD_INVALIDO "Error: Codigo de seguridad invalido."

status_t mostrar_msg_error(status_t);

#endif
