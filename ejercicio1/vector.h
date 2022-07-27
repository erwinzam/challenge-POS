#ifndef VECTOR__H
#define VECTOR__H

#include <stdio.h>
#include "types.h"

#define INIT_CHOP 30
#define CHOP_SIZE 15
			  
typedef struct{
	
	size_t size;
	size_t alloc_size;
	void **items;
	destructor_t p_destructor;
	
				}vector_t;
				 
status_t crear_vector(vector_t **vector);

status_t setear_desctructor_vector(vector_t *vector,destructor_t destructor);
status_t destruir_vector(vector_t**vector);

status_t agregar_item_vector(vector_t *vector,const void *item);

bool_t validar_vector(const vector_t* vector,validator_t validator);

status_t imprimir_vector(const vector_t *vector,FILE *archivo_salida,printer_t printer);


#endif
