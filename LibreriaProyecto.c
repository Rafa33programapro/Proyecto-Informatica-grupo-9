#include <stdio.h>
#include "LibreriaProyecto.h"

void mostrar_en_pantalla_funciones(void)
{
	printf("Acciones disponibles: \n \n");
	printf("\t1: Calculo de media anual o mensual de una cuenca. \n");
	printf("\t2: Evolucion del volumen embalsado de una cuenca. \n");
	printf("\t3: Comparacion de 2 o mas cuencas. \n");
	printf("\t4: Valores extremos de una cuenca. \n");
	printf("\t5: Nivel de agua en una cuenca. \n");
	printf("\t6: Exportacion de datos calculados. \n");
}

int elegir_funcion(void)
{
	//Esta funcion le pide al usuario un numero entre 1 y 6, que es el numero de 
	//funcionalidades que tiene el programa.
	int funcion_escogida;
	int comprobacion_entero;
	
	do
	{
		printf("\nAhora, escoja que funcion quiere realizar: \n");
		comprobacion_entero = scanf("%i", &funcion_escogida);
		
		if(	comprobacion_entero != 1)  //comprobamos que se trata de un entero
		{
			printf("Error, introduzca un numero entero valido.");
			int c;
        	while ((c = getchar()) != '\n' && c != EOF);  //limpiamos el buffer para evitar bucles infinitos
		}
		
		if( comprobacion_entero == 1)
		{
			if( funcion_escogida < 1 || funcion_escogida > 6 )
			{
				printf("Error, introduzca un numero entero valido.");
			}
		}
		
	}while (funcion_escogida < 1 || funcion_escogida > 6);
	
	printf("\n Has escogido la accion numero %i:", funcion_escogida);
	
	return(funcion_escogida);
}

void funcion_3_comparacion_cuencas(void)
{
	FILE *p;
	
	p = fopen("dataset.csv","r");
	
	if( p==NULL)
	{
		printf("Error al abrir el archivo");
		return 1;
	}
	
	while(fscanf(p,))
	
	
}