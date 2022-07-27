#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"

status_t crear_input(input_t** entrada)
{
	if(entrada == NULL) return ERROR_PUNTERO_NULO;
	
	if( ( *entrada = (input_t *) malloc( sizeof(input_t) ) ) == NULL)
		return ERROR_MEMORIA_NO_DISPONIBLE;
	
	(*entrada)->archivo_entrada = stdin;
	(*entrada)->archivo_salida = NULL;
	(*entrada)->numeros_entrada = NULL;
		
	return OK;
}

status_t leer_numeros_input(input_t* entrada)
{
	string_t* str;
	vector_t* vector_str;
	bool_t v_bool;
		
	crear_string(&str);
	
	leer_hasta_chr_string(str,'0',entrada->archivo_entrada);
	
	split_string(str," \n\t",&vector_str);
	
	v_bool = validar_vector(vector_str,(validator_t)es_numero_string);
	
	if(v_bool == FALSE)
	{
		destruir_vector(&vector_str);
		destruir_string(&str);
		return ERROR_NUMEROS_INVALIDOS;	
	}
	
	entrada->numeros_entrada = vector_str;
	
	destruir_string(&str);
	
	return OK;
}

status_t abrir_archivo_salida_input(input_t* entrada)
{
	string_t* archivo_str;
	FILE* fo;
		
	crear_string(&archivo_str);
	
	leer_linea_string(archivo_str,stdin);
	
	
	if((fo=fopen(archivo_str->str,"wt"))==NULL)
	{
		destruir_string(&archivo_str);
		return ERROR_NO_SE_PUDO_ABRIR_ARCHIVO_SALIDA;
	}
	
	entrada->archivo_salida = fo;
	
	destruir_string(&archivo_str);
	
	return OK;
}

status_t procesar_input(const input_t* input)
{
	imprimir_vector(input->numeros_entrada,input->archivo_salida,(printer_t)imprimir_10_num_string);
	
	return OK;
}


status_t destruir_input(input_t** entrada)
{
	if( (*entrada)->archivo_salida != NULL)
		fclose((*entrada)->archivo_salida);
	
	(*entrada)->archivo_salida = NULL;
	
	if( (*entrada)->numeros_entrada != NULL)
		destruir_vector( &( (*entrada)->numeros_entrada ) );
		
	(*entrada)->numeros_entrada = NULL;
		
	(*entrada)->archivo_entrada = NULL;
	
	if(*entrada != NULL)
		free(*entrada);
	
	*entrada = NULL;	
	
	return OK;
}
