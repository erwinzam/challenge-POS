#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"
#include "input.h"
#include "card_utils.h"


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


status_t leer_cod_seguridad_input(input_t* entrada)
{
	leer_linea_string(entrada->cod_seguridad,stdin);
	
	if(es_monto_string(entrada->monto) == FALSE)
	{
		return ERROR_CODIGO_DE_SEGURIDAD_INVALIDO;
	}
	
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
