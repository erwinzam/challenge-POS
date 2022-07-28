#ifndef INPUT__H
#define INPUT__H

#include "types.h"
#include "my_string.h"

typedef struct{
	
	string_t* monto;
	string_t* num_tarjeta;
	string_t* cod_seguridad;
	string_t* label;
	
} input_t;

status_t crear_input(input_t** entrada);

status_t leer_monto_input(input_t* entrada);
status_t leer_num_tarjeta_input(input_t* entrada);
status_t reconocer_num_tarjeta_input(const input_t* entrada,string ranges_file_name,string cards_file_name);
status_t imprimir_label_input(input_t* entrada,FILE* archivo_salida);
status_t leer_cod_seguridad_input(input_t* entrada);
status_t procesar_input(const input_t* entrada);

status_t destruir_input(input_t** entrada);


#endif
