#ifndef MY_STRING__H
#define MY_STRING__H

#include "types.h"
#include "vector.h"

#define INIT_STR_CHOP 50
#define CHOP_STR_SIZE 20

#define INPUT_STR_SIZE 10

typedef struct {
	size_t size;
	size_t alloc_size;
	string	str;
} string_t;

status_t crear_string(string_t** str);
status_t leer_hasta_chr_string(string_t* str, const int chr, FILE* archivo_entrada);
status_t leer_linea_string(string_t * str,FILE *archivo_entrada);
status_t cargar_string(string_t* str, const string src);
status_t split_string(const string_t* str,const string del,vector_t** vector_str);
status_t imprimir_string(string_t* str, FILE* archivo_salida);
status_t imprimir_10_num_string(string_t* str,FILE* archivo_salida);
bool_t es_numero_string(const string_t*str);
status_t destruir_string(string_t** str);

#endif
