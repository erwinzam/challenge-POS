#include <stdio.h>
#include "my_string.h"



int main(void)
{
	string_t* str;
	
	crear_string(&str);
	
	puts("Ingrese monto:");
	leer_linea_string(str,stdin);
	
	( es_monto_string(str) == TRUE )?
		puts("Es un monto valido"):
		puts("NO es un monto valido");
		
	puts("Ingrese un numero de tarjeta:");
	leer_linea_string(str,stdin);
	
	( es_num_tarjeta_string(str) == TRUE )?
		puts("Es un numero de tarjeta valido"):
		puts("NO es un numero de tarjeta valido");
		
	puts("Ingrese un codigo de seguridad:");
	leer_linea_string(str,stdin);
	
	( es_cod_seguridad_string(str) == TRUE )?
		puts("Es un codigo de seguridad valido"):
		puts("NO es un codigo de seguridad valido");
	
	destruir_string(&str);
	
	return 0;
}
