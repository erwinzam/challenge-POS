#ifndef CARD_UTILS__H
#define CARD_UTILS__H

#include <stdio.h>
#include "types.h"
#include "my_string.h"

#define RANGE_LENGTH_STR 8



typedef struct {
	char rangeLow[8 + 1];
	char rangeHigh[8 + 1];
	unsigned char len;
	int id;
} range_t;

typedef struct {
	char label[12 + 1];
	int id;
} card_t;


bool_t esta_num_tarjeta_en_range(string_t* num_tarjeta,range_t* rango);


bool_t esta_rango_en_card(range_t* rango,card_t* tarjeta);

#endif
