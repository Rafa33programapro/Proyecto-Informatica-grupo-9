#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibreriaProyecto.h"
//Este es el codigo principal
//Recordad usar mas o menos la guia de estilo

int main()
{

	 mostrar_en_pantalla_funciones();           //Imprimimos en pantalla las opciones para el usuario
	 int funcion_escogida = elegir_funcion();   //recogemos la funcion que quiera ejecutar el usuario por medio de la variable 'funcion_escogida'

	switch (funcion_escogida)
	 {
        case 1:
            printf("Calculo de media anual o mensual de una cuenca. \n");
            funcion_1_media_volumen_cuenca();

            break;
        case 2:
            printf("Evolucion del volumen embalsado de una cuenca. \n");
            funcion_2_evolucion_volumen_embalsado();

            break;
        case 3:
            printf("Comparacion de 2 o mas cuencas. \n");
            funcion_3_comparacion_cuencas();

            break;
        case 4:
        	printf("Valores extremos de una cuenca. \n");
            funcion_4_extremos_volumen_embalsado();

        	break;
        case 5:
        	printf("Nivel de agua en una cuenca. \n");
            funcion_5_nivel_agua_cuenca();

        	break;
        case 6:
            printf("Tamaño de la base de datos. \n");
            funcion_6_tamano_base_datos();

            break;
        case 7:
            printf("Probabilidad de desbormiento global por año");
            funcion_7_probabilidad_de_desbordamiento();

            break;
        case 8:
            printf("Salir del programa. \n");
            funcion_8_salir_del_programa();

            break;
        default:
            printf(" Opción no válida \n");
            break;
    }

	return 0;
}
