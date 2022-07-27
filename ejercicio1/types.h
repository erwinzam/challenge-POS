#ifndef TYPES__H
#define TYPES__H

#include <stdio.h>

typedef char* string;


typedef enum{
			OK,
			ERROR_MEMORIA_NO_DISPONIBLE,
			ERROR_PUNTERO_NULO,
			
			ERROR_NUMEROS_INVALIDOS,
			ERROR_NO_SE_PUDO_ABRIR_ARCHIVO_SALIDA
} status_t;

typedef enum{
	FALSE = 0,
	TRUE = 1
} bool_t;

typedef status_t (*destructor_t)(void**);

typedef status_t (*printer_t)(const void*,FILE*);

typedef bool_t (*validator_t)(const void*);

#endif
