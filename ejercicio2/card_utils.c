#include <string.h>
#include <stdlib.h>
#include "card_utils.h"

bool_t esta_num_tarjeta_en_range(string_t* num_tarjeta,range_t* rango)
{
	char range_str[RANGE_LENGTH_STR+1];
	
	size_t rango_inf;
	size_t rango_sup;
	
	size_t rango_tarjeta;
	
	char* temp;
	
	
	rango_inf = (size_t)strtoul(rango->rangeLow,&temp,10);
	rango_sup = (size_t)strtoul(rango->rangeHigh,&temp,10);
	
	
	memset(range_str, '\0', sizeof(range_str));
	strncpy(range_str, num_tarjeta->str,RANGE_LENGTH_STR);
	
	rango_tarjeta = (size_t)strtoul(range_str,&temp,10);
	
	if(rango_tarjeta < rango_inf || rango_tarjeta > rango_sup)
		return FALSE;
		
	if(num_tarjeta->size != rango->len)
		return FALSE;
		
	return TRUE;
	
}


bool_t esta_rango_en_card(range_t* rango,card_t* tarjeta)
{
	
	if(rango->id != tarjeta->id)
		return FALSE;
	
	return TRUE;
}
