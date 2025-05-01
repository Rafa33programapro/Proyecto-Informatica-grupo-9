#include <stdio.h>
#include "LibreriaProyecto.h"

void mostrar_en_pantalla_funciones(void)
{
	printf("Acciones disponibles: \n \n");
	printf("\t1: Calculo de media anual o mensual de una cuenca. \n");
	printf("\t2: Evolucion del volumen embalsado de una cuenca. \n");
	printf("\t3: Comaparacion de 2 o mas cuencas. \n");
	printf("\t4: Valores extremos de una cuenca. \n");
	printf("\t5: Nivel de agua en una cuenca. \n");
	printf("\t6: Exportacion de datos calculados. \n");
}

int elegir_funcion(void)
{
	//Esta funcion le pide al usuario un numero entre 1 y 6, que es el numero de 
	//funcionalidades que tiene el programa.
	int funcion_escogida;
	
	do
	{
		printf("Ahora, escoja que funcion quiere realizar: \n");
		scanf("%i", &funcion_escogida);
		
		if (funcion_escogida < 1 || funcion_escogida > 6) 
		{	
            printf("Numero invalido, por favor ingrese un numero entre 1 y 6. \n");
        }
		
	}while (funcion_escogida < 1 || funcion_escogida > 6);
	
	printf("Has escogido la accion numero %i.", funcion_escogida);
	
	return(funcion_escogida);
}