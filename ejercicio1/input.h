#ifndef INPUT__H
#define INPUT__H

#include "types.h"
#include "vector.h"

typedef struct{
	
	FILE* archivo_salida;
	FILE* archivo_entrada;
	vector_t* numeros_entrada;
	
} input_t;

status_t crear_input(input_t** entrada);
status_t procesar_input(const input_t* entrada);
status_t leer_numeros_input(input_t* entrada);
status_t abrir_archivo_salida_input(input_t* entrada);
status_t destruir_input(input_t** entrada);


#endif
