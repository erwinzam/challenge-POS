#include <stdio.h>
#include "types.h"
#include "input.h"
#include "messages.h"


int main(void)
{
	
	input_t* entrada;
	status_t st;
	
	string f_name_ranges = "ranges.dat"; 
	string f_name_cards = "cards.dat"; 
	
	FILE *archivo_salida = stdout;
	
	crear_input(&entrada);
	puts("Ingrese monto:");
	
	if( ( st = leer_monto_input(entrada) ) != OK )
	{
		mostrar_msg_error(st);
		destruir_input(&entrada);
		return 1;
	}
	
	puts("Ingrese numero de tarjeta");
	
	if( ( st = leer_num_tarjeta_input(entrada) ) != OK )
	{
		mostrar_msg_error(st);
		destruir_input(&entrada);
		return 1;
	}
	
	puts("Ingrese codigo de segurida");
	if( ( st = leer_cod_seguridad_input(entrada) ) != OK )
	{
		mostrar_msg_error(st);
		destruir_input(&entrada);
		return 1;
	}
	
	if( ( st = reconocer_num_tarjeta_input(entrada,f_name_ranges,f_name_cards) ) != OK )
	{
		mostrar_msg_error(st);
		destruir_input(&entrada);
		return 1;
	}
	
	imprimir_label_input(entrada,archivo_salida);
	
	if( ( st = procesar_input(entrada) ) != OK)
	{
		mostrar_msg_error(st);
		destruir_input(&entrada);
		return 1;
	}
	
	
	destruir_input(&entrada);
	
	return 0;

}
