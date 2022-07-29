#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"
#include "input.h"
#include "card_utils.h"
#include "sockets.h"


status_t crear_input(input_t** entrada)
{
	if(entrada == NULL) return ERROR_PUNTERO_NULO;
	
	if( ( *entrada = (input_t *) malloc( sizeof(input_t) ) ) == NULL)
		return ERROR_MEMORIA_NO_DISPONIBLE;
		
	(*entrada)->monto  = NULL;
	(*entrada)->num_tarjeta  = NULL;
	(*entrada)->cod_seguridad = NULL;
	(*entrada)->label = NULL;
	
	crear_string( &( (*entrada)->monto ) );
	
	crear_string( &( (*entrada)->num_tarjeta ) );
	
	crear_string( &( (*entrada)->cod_seguridad ) );
	
	crear_string( &( (*entrada)->label ) );
	
		
	return OK;
}

status_t leer_monto_input(input_t* entrada)
{
	leer_linea_string(entrada->monto,stdin);
	
	if(es_monto_string(entrada->monto) == FALSE)
	{
		return ERROR_MONTO_INVALIDO;
	}
		
	return OK;
	
}

status_t leer_num_tarjeta_input(input_t* entrada)
{
	leer_linea_string(entrada->num_tarjeta,stdin);
	
	if(es_num_tarjeta_string(entrada->num_tarjeta) == FALSE)
		return ERROR_NUMERO_DE_TARJETA_INVALIDA;
		
	return OK;
}

status_t reconocer_num_tarjeta_input(const input_t* entrada,
									 string ranges_file_name,
									 string cards_file_name)
{
	FILE* f_ranges;
	FILE* f_cards;
	
	range_t rango;
	card_t tarjeta;
	
	bool_t esta_tarjeta_en_ranges = FALSE;
	bool_t esta_tarjeta_en_cards = FALSE;
	
	string_t* aux_str;
	
	crear_string(&aux_str);
	
	if( (f_ranges = fopen(ranges_file_name, "rb")) == NULL)
	{
		destruir_string(&aux_str);
		return ERROR_NO_SE_PUDO_ABRIR_ARCHIVO_RANGES;
	}
		
	if( (f_cards = fopen(cards_file_name, "rb")) == NULL)
	{
		fclose(f_ranges);
		destruir_string(&aux_str);
		return ERROR_NO_SE_PUDO_ABRIR_ARCHIVO_CARDS;
	}
	
	while(1)
	{
		fread(&(rango),sizeof(range_t),1,f_ranges);
		
		if(feof(f_ranges))
			break;
		
		if( esta_num_tarjeta_en_range(entrada->num_tarjeta,&rango) == TRUE )
		{
			esta_tarjeta_en_ranges = TRUE;
			break;
		}
		
	}
	
	if(esta_tarjeta_en_ranges == FALSE)	
	{	
		fclose(f_cards);
		fclose(f_ranges);
		destruir_string(&aux_str);
		
		return ERROR_TARJETA_NO_SE_ENCUENTRA_EN_RANGOS;
	}
	
	
	
	while(1)
	{
		fread(&(tarjeta),sizeof(card_t),1,f_cards);
		
		if(feof(f_cards))
			break;
		
		if( esta_rango_en_card(&rango,&tarjeta) == TRUE )
		{
			esta_tarjeta_en_cards = TRUE;
			break;
		}
		
	}
	
	if(esta_tarjeta_en_cards == FALSE)	
	{	
		fclose(f_cards);
		fclose(f_ranges);
		destruir_string(&aux_str);
		
		return ERROR_TARJETA_NO_SE_ENCUENTRA_DENTRO_DE_TARJETAS_VALIDAS;
	}
	
	cargar_string(entrada->label,tarjeta.label);
	
	
	return OK;
}

status_t imprimir_label_input(input_t* entrada,FILE* archivo_salida)
{
	imprimir_string(entrada->label,archivo_salida);
	
	return OK;
}


status_t leer_cod_seguridad_input(input_t* entrada)
{
	leer_linea_string(entrada->cod_seguridad,stdin);
	
	if(es_monto_string(entrada->monto) == FALSE)
	{
		return ERROR_CODIGO_DE_SEGURIDAD_INVALIDO;
	}
	
	return OK;
}

status_t crear_request_msg(const input_t* entrada,string* request_msg)
{
	char monto_str[MONTO_STR_LEN + 2];
	
	char* p_str_src;
	char* p_str_dest;
	char* temp;
	
	size_t monto;
	
	size_t msg_str_len = MENSAJE_STR_LEN +
				         (entrada->num_tarjeta)->size +
						 MONTO_STR_LEN +
						 (entrada->cod_seguridad)->size;
				     
	if( ( *request_msg = (string) malloc( (msg_str_len + 1) * sizeof(char) ) ) == NULL )
		return ERROR_MEMORIA_NO_DISPONIBLE;
		
	memset(*request_msg,'\0',msg_str_len + 1 );
	
	strcpy(monto_str, (entrada->monto)->str);
	p_str_src = strchr( (entrada->monto)->str , ',');
	p_str_dest = strchr( monto_str , ',');
	strcpy(p_str_dest,p_str_src + 1);
	
	
	monto = strtoul(monto_str,&temp,10);
	
	sprintf(*request_msg,"%s%s%02u%012u%s", REQUEST_MSG,
											(entrada->num_tarjeta)->str,
											(unsigned int) (entrada->num_tarjeta)->size,
											(unsigned int) monto,
											(entrada->cod_seguridad)->str);
	
	
	return OK;
}

bool_t es_response_aprobada(string response)
{
							   
	char response_esperado[20];
	
	sprintf(response_esperado,"%s%s",RESPONSE_MSG_TYPE,
									 RESPONSE_MSG_TRANSACCION_APROBADA);	
	
	if(strcmp(response,response_esperado))
		return FALSE;
	
	return TRUE;
}

status_t procesar_input(const input_t* entrada)
{
	int socket_h;
	string request_msg;
	
	char ip[] = IP_ADRRES;
	unsigned short port = PORT_NUMBER;
	
	unsigned char response[50];
	
	int socket_status;
	
	
	socket_h = socketCreate();
	
	socketConnect(socket_h,ip,port);
	
	crear_request_msg(entrada,&request_msg);
	
	socketWrite(socket_h,(unsigned char*)request_msg);
	
	socket_status=socketRead(socket_h,response,MAX_TIMEOUT_MILLISECONDS);
	
	if(socket_status == -1 || socket_status != strlen((string)response) )
	{
		socketClose(socket_h);
		free(request_msg);
		return ERROR_DE_COMUNICACION;
	}
	
	if(es_response_aprobada((string)response) == FALSE)
		puts("NO APROBADA");
	else
		puts("APROBADA");
	
	socketClose(socket_h);
	
	free(request_msg);
	return OK;
}



status_t destruir_input(input_t** entrada)
{
	if( (*entrada)->monto != NULL)
		destruir_string( &( (*entrada)->monto ) );
	
	(*entrada)->monto = NULL;
	
	if( (*entrada)->num_tarjeta != NULL)
		destruir_string( &( (*entrada)->num_tarjeta ) );
		
	(*entrada)->num_tarjeta = NULL;
	
	if( (*entrada)->cod_seguridad != NULL)
		destruir_string( &( (*entrada)->cod_seguridad ) );
		
	(*entrada)->cod_seguridad = NULL;
	
	if( (*entrada)->label != NULL)
		destruir_string( &( (*entrada)->label ) );
		
	(*entrada)->label = NULL;
	
	if(*entrada != NULL)
		free(*entrada);
	
	*entrada = NULL;	
	
	return OK;
}


