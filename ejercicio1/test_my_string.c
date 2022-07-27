#include <stdio.h>
#include "my_string.h"
#include "vector.h"



int main(void)
{
	string_t* str;
	vector_t* vector_str;
	bool_t v_bool;
	
	crear_string(&str);
	
	leer_hasta_chr_string(str,'0',stdin);
	
	imprimir_string(str,stdout);
	
	leer_linea_string(str,stdin);
	
	imprimir_string(str,stdout);
	
	leer_hasta_chr_string(str,'0',stdin);
	split_string(str," \n\t",&vector_str);
	imprimir_vector(vector_str,stdout,(printer_t)imprimir_string);
	
	v_bool = validar_vector(vector_str,(validator_t)es_numero_string);
	
	(v_bool == TRUE)? puts("El vector de strings que contiene numeros ES VALIDO"):puts("El vector de strings que contiene numeros NO ES VALIDO");
	
	leer_linea_string(str,stdin);
	imprimir_10_num_string(str,stdout);
	
	destruir_vector(&vector_str);
	destruir_string(&str);
	
	return 0;
}
