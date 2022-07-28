#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "card_utils.h"


#define RANGES_FILE_NAME "ranges.dat"
#define CARDS_FILE_NAME "cards.dat"

#define RANGO_INF_STR "18000000"
#define RANGO_SUP_STR "19000000"

#define RANGO_LEN 17
#define RANGO_ID 14


#define TARJETA_LABEL "Visa"
#define TARJETA_ID 14

int main(void)
{
	FILE* ranges_f;
	FILE* cards_f;
	
	range_t rango;
	card_t tarjeta;
	
	ranges_f = fopen(RANGES_FILE_NAME,"wb");
	cards_f = fopen(CARDS_FILE_NAME,"wb");
	
	/* Cargo valores para rango que lo guardare en ranges.dat*/
	strcpy(rango.rangeLow,RANGO_INF_STR);
	strcpy(rango.rangeHigh,RANGO_SUP_STR);
	rango.len = RANGO_LEN;
	rango.id = RANGO_ID;
	
	fwrite(&rango,sizeof(range_t),1,ranges_f);
	
	/* Cargo valores para tarjeta que lo guardare en cards.dat*/
	strcpy(tarjeta.label,TARJETA_LABEL);
	tarjeta.id = TARJETA_ID;
	
	fwrite(&tarjeta,sizeof(card_t),1,cards_f);
	
	fclose(cards_f);
	fclose(ranges_f);
	
	return 0;
	
}
