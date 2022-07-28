#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"





status_t crear_string(string_t** str)
{
	if(str == NULL) return ERROR_PUNTERO_NULO;
	
	if( ( *str = (string_t *) malloc( sizeof(string_t) ) ) == NULL)
		return ERROR_MEMORIA_NO_DISPONIBLE;
	
	(*str)->alloc_size = INIT_STR_CHOP;
		
	if( ( (*str)->str = (string) malloc( (*str)->alloc_size * sizeof(char) ) ) == NULL){
		free(*str);
		*str = NULL;
		return ERROR_MEMORIA_NO_DISPONIBLE;
	}
	
	(*str)->size = 0;
	
	(*str)->str[0] = '\0';
		
	return OK;
}

status_t leer_hasta_chr_string(string_t* str, const int chr, FILE* archivo_entrada)
{
	char aux_str[INPUT_STR_SIZE + 1];
	
	string aux;
	
	char* pch;
	
	bool_t caracter_encontrado = FALSE;
	
	char* pstr;
	str->str[0] = '\0';
	while(1)
	{	
		
		fgets(aux_str, INPUT_STR_SIZE + 1, archivo_entrada);
		
		if(str->alloc_size <= str->size + 1 + INPUT_STR_SIZE + 1)
		{
			if( ( aux = (string)realloc( str->str, (str->alloc_size + CHOP_STR_SIZE) ) ) == NULL)
				return ERROR_MEMORIA_NO_DISPONIBLE;
			str->alloc_size+=CHOP_STR_SIZE;
			str->str = aux;
			
		}
		
			
		strcat(str->str,aux_str);
		str->size = strlen(str->str);
		
		pch = strchr(aux_str,'\n');
		
		if( ( pch != NULL ) && ( *pch == '\n' ) )
		{	
			
			pstr = str->str;
			while( ( pch = strchr(pstr,chr) ) != NULL )
			{	
				
				if( ( (str->str == pch)? 1: isspace( (int)*(pch-1) ) ) 
					&&  (  isspace( (int)*(pch+1) ) || *(pch+1) == '\0' ) )
				{
					*pch = '\0';
					str->size = strlen(str->str);
					caracter_encontrado = TRUE;
					break;
				}
				pstr = pch + 1;
			}
			
			if(caracter_encontrado == TRUE) break;
		}
			
		
	}
	
	
	return OK;
}

status_t leer_linea_string(string_t * str,FILE *archivo_entrada)
{
	char aux_str[INPUT_STR_SIZE + 1];
	
	string aux;
	
	char* pch;
	
	str->str[0] = '\0';
	
	while(1)
	{	
		
		fgets(aux_str, INPUT_STR_SIZE + 1, archivo_entrada);
		
		if(str->alloc_size <= str->size + 1 + INPUT_STR_SIZE + 1)
		{
			if( ( aux = (string)realloc( str->str, (str->alloc_size + CHOP_STR_SIZE) ) ) == NULL)
				return ERROR_MEMORIA_NO_DISPONIBLE;
			str->alloc_size+=CHOP_STR_SIZE;
			str->str = aux;
			
		}
		
			
		strcat(str->str,aux_str);
		str->size = strlen(str->str);
		
		pch = strchr(aux_str,'\n');
		
		if( ( pch != NULL ) && ( *pch == '\n' ) )
		{	
			pch = strchr(str->str,'\n');
			*pch = '\0';
			str->size = strlen(str->str);
			break;
		}
				
	}
	
	
	return OK;
}

status_t imprimir_string(string_t* str,FILE* archivo_salida)
{
	fprintf(archivo_salida,"%s\n",str->str);
	return OK;
}



bool_t es_numero_string(const string_t* str)
{
	char *temp;
	
	strtod(str->str,&temp);
	if(*temp) return FALSE;
	
	return TRUE;
}

bool_t es_monto_string(const string_t*str)
{
	
	char *temp;
	
	/*Valido si hay 1 coma*/
	temp = strchr(str->str,',');
	if(temp == NULL)
		return FALSE;
	
	/*Me aseguro que no haya mas de 1 coma*/	
	temp = strchr(temp + 1,',');
	if(temp != NULL)
		return FALSE;
	
	/*Me aseguro que el string sea un monto donde la parte decimal*/
	/*esta separada por una coma*/
	strtod(str->str,&temp);
	
	if(*temp != '\0' && *temp != ',') 
		return FALSE;
	
	/*Si aparece un punto en el monto entonces no valido. */
	if( strchr(str->str,'.') != NULL)
		return FALSE;
		
	temp = strchr(str->str,',');
	if(strlen(temp+1) != CANTIDAD_DECIMALES_MONTO)
		return FALSE;
	
	
	return TRUE;
}

bool_t es_num_tarjeta_string(const string_t* str)
{
	char *temp;
	
	strtoul(str->str,&temp,10);
	
	if(*temp != '\0') 
		return FALSE;
	
	if(str->size < CANTIDAD_MINIMA_NUM_TARJETA)
		return FALSE;
	
	return TRUE;		
	
}

bool_t es_cod_seguridad_string(const string_t* str)
{
	char *temp;
	
	strtoul(str->str,&temp,10);
	
	if(*temp != '\0') 
		return FALSE;
	
	if(str->size != COD_SEGURIDAD_STR_LEN)
		return FALSE;
	
	return TRUE;
}

status_t cargar_string(string_t* str, const string src)
{
	string aux;
	
	if(str == NULL)
		return ERROR_PUNTERO_NULO;
		
	if(str->alloc_size <= strlen(src) + 1)
	{
		if( ( aux = (string)realloc( str->str, (strlen(src) + 1) ) ) == NULL)
			return ERROR_MEMORIA_NO_DISPONIBLE;
			
		str->alloc_size = strlen(src) + 1;
		str->str = aux;
			
	}
	
	strcpy(str->str,src);
	str->size = strlen(str->str);
	
	return OK;
}

status_t imprimir_10_num_string(string_t* str,FILE* archivo_salida)
{
	char aux_str[10 + 1];
	size_t offset;
	
	strcpy(aux_str,"0000000000");
	
	if(str->size < strlen(aux_str))
	{
		offset = strlen(aux_str) - str->size;
		strcpy(aux_str + offset,str->str);
	}
	
	fprintf(archivo_salida,"%s\n",aux_str);
	
	return OK;
	
}

status_t destruir_string(string_t** str)
{
	if(str==NULL) return ERROR_PUNTERO_NULO;
	
	free((*str)->str);
	(*str)->str=NULL;
	
	free(*str);
	*str=NULL;
	return OK;
}
