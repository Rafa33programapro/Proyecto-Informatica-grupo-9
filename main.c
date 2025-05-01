#include <stdio.h>
#include <stdlib.h>
#include "LibreriaProyecto.h"
//Este es el codigo principal
//Recordad usar mas o menos la guia de estilo

int main() {
	
	 mostrar_en_pantalla_funciones(); //Imprimimos en pantalla las opciones para el usuario
	 int funcion_escogida = elegir_funcion(); //recogemos la funcion que quiera ejecutar el usuario por medio de la variable 'funcion_escogida'

	switch (funcion_escogida)
	 {
        case 1:
            printf(" Calculo de media anual o mensual de una cuenca. \n");
            
            
            break;
        case 2:
            printf(" Evolucion del volumen embalsado de una cuenca. \n");
            
            
            break;
        case 3:
            printf(" Comparacion de 2 o mas cuencas. \n");
            
            
            break;
        case 4:
        	printf(" Valores extremos de una cuenca. \n");
        	
        	
        	break;
        case 5:
        	printf(" Nivel de agua en una cuenca. \n");
        	
        	
        	break;	
        case 6:
        	printf(" Exportacion de datos calculados. \n");
        	
        	
        	break;
        
        default:
            printf(" Opción no válida \n"); 
            break;
    }

	return 0;
}