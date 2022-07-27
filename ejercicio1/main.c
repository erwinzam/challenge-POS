#include <stdio.h>
#include "types.h"
#include "input.h"


int main(void)
{
	
	input_t* entrada;
	
	crear_input(&entrada);
	
	puts("Ingrese numeros. Para terminar de agregar numeros ingrese 0.");
	
	if( leer_numeros_input(entrada) != OK)
	{
		fprintf(stderr,"Numeros de entrada invalidos.");
		destruir_input(&entrada);
		return 1;
		
	}
	
	puts("Ingrese nombre de archivo donde va a guardar los numeros");
	
	if( abrir_archivo_salida_input(entrada) != OK)
	{
		fprintf(stderr,"No se pudo abrir archivo.");
		destruir_input(&entrada);
		return 1;
	}
	
	procesar_input(entrada);
	
	destruir_input(&entrada);
	
	return 0;

}
