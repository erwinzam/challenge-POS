#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "vector.h"


status_t crear_vector(vector_t **vector)
{
	if(vector==NULL) return ERROR_PUNTERO_NULO;
	
	
	if((*vector=(vector_t*)malloc(sizeof(vector_t)))==NULL)
		return ERROR_MEMORIA_NO_DISPONIBLE;
		
	if(((*vector)->items=(void**)malloc(INIT_CHOP*sizeof(void*)))==NULL)
	{
		free(*vector);
		*vector=NULL;
		return ERROR_MEMORIA_NO_DISPONIBLE;
	}
	
	(*vector)->alloc_size=INIT_CHOP;
	(*vector)->size=0;
	
	return OK;
}


status_t setear_desctructor_vector(vector_t *vector,destructor_t destructor)
{
	
	if(vector==NULL) return ERROR_PUNTERO_NULO;
	
	vector->p_destructor=destructor;
	
	return OK;
}

status_t destruir_vector(vector_t**vector)
{
	size_t i;
	status_t s;
	
	if(vector==NULL) return ERROR_PUNTERO_NULO;
	
	for(i=0;i<(*vector)->size;i++)
		if( ( s = (*( (*vector)->p_destructor) )( &( (*vector)->items[i] ) ) )!=OK) 
			return s;
		
	free((*vector)->items);
	(*vector)->items=NULL;
	free(*vector);
	*vector=NULL;
	return OK;
}

status_t agregar_item_vector(vector_t *vector,const void *item)
{
	void **aux;
	
	if(vector==NULL || item==NULL) return ERROR_PUNTERO_NULO;
	
	
	if(vector->items==NULL)
	{
		if((vector->items=(void**)malloc(INIT_CHOP*sizeof(void*)))==NULL)
			return ERROR_MEMORIA_NO_DISPONIBLE;
		vector->alloc_size=INIT_CHOP;
		vector->size=0;
	}
	vector->items[vector->size++]=(void*)item;
	
	
	if(vector->alloc_size==vector->size)
	{
		
		if((aux=(void**)realloc(vector->items,(vector->alloc_size+CHOP_SIZE)))==NULL)
			return ERROR_MEMORIA_NO_DISPONIBLE;
		vector->alloc_size+=CHOP_SIZE;
		vector->items=aux;
	}
	
	return OK;
}



status_t imprimir_vector(const vector_t *vector,FILE *archivo_salida,printer_t printer)
{
	status_t s;
	size_t i;
	
	if(vector==NULL || archivo_salida==NULL)
		return ERROR_PUNTERO_NULO;
		
	for(i=0;i<vector->size;i++)
		if( (s=(*printer)(vector->items[i],archivo_salida) )!=OK)
			return s;
			
	return OK;
}
	

bool_t validar_vector(const vector_t* vector,validator_t validator)
{
	size_t i;
	
	if(vector==NULL)
		return ERROR_PUNTERO_NULO;
		
	for(i=0;i<vector->size;i++)
		if( (*validator)(vector->items[i])  == FALSE)
			return FALSE;
			
	return TRUE;
}
		
