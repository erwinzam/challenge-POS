#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef char* string;


typedef enum{
			OK,

			ERROR_MEMORIA_NO_DISPONIBLE,
			ERROR_PUNTERO_NULO,
			
			ERROR_MONTO_INVALIDO,
			ERROR_NUMERO_DE_TARJETA_INVALIDA,
			ERROR_NO_SE_PUDO_ABRIR_ARCHIVO_RANGES,
			ERROR_NO_SE_PUDO_ABRIR_ARCHIVO_CARDS,
			ERROR_TARJETA_NO_SE_ENCUENTRA_EN_RANGOS,
			ERROR_TARJETA_NO_SE_ENCUENTRA_DENTRO_DE_TARJETAS_VALIDAS,
			ERROR_CODIGO_DE_SEGURIDAD_INVALIDO
} status_t;

typedef enum{
	FALSE = 0,
	TRUE = 1
} bool_t;

typedef status_t (*destructor_t)(void**);

typedef status_t (*printer_t)(const void*,FILE*);

typedef bool_t (*validator_t)(const void*);

#endif
