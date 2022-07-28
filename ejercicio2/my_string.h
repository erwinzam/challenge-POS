#ifndef MY_STRING__H
#define MY_STRING__H

#include "types.h"

#define INIT_STR_CHOP 50
#define CHOP_STR_SIZE 20

#define INPUT_STR_SIZE 10

#define CANTIDAD_DECIMALES_MONTO 2
#define CANTIDAD_MINIMA_NUM_TARJETA 13

#define COD_SEGURIDAD_STR_LEN 3

typedef struct {
	size_t size;
	size_t alloc_size;
	string	str;
} string_t;

status_t crear_string(string_t** str);
status_t leer_hasta_chr_string(string_t* str, const int chr, FILE* archivo_entrada);
status_t leer_linea_string(string_t * str,FILE *archivo_entrada);
status_t cargar_string(string_t* str, const string src);
status_t imprimir_string(string_t* str, FILE* archivo_salida);
status_t imprimir_10_num_string(string_t* str,FILE* archivo_salida);
bool_t es_numero_string(const string_t*str);
bool_t es_monto_string(const string_t*str);
bool_t es_num_tarjeta_string(const string_t* str);
bool_t es_cod_seguridad_string(const string_t* str);
status_t destruir_string(string_t** str);

#endif
