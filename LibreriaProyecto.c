#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LibreriaProyecto.h"

#define MAX_LINEA 1000
#define MAX_FILAS 5000


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
				printf("Error, introduzca un numero entero valido. \n");
			}
		}
		
	}while (funcion_escogida < 1 || funcion_escogida > 6);
	
	printf("\nHas escogido la accion numero %i: ", funcion_escogida);
	
	return(funcion_escogida);
}



void funcion_3_comparacion_cuencas(void)
{
	FILE *archivo = fopen("dataset.csv", "r");
    
    if(archivo == NULL)
	{
		perror("\nError al abrir el archivo");
		return;
	}

    char linea[MAX_LINEA];
    char *campos[20];
    int num_fila = 0;

    // Datos por columnas
    char cuenca[MAX_FILAS][100];
    char embalse[MAX_FILAS][100];
    int mes[MAX_FILAS];
    float datos_anuales[MAX_FILAS][10];  // de 2012 a 2021

    while (fgets(linea, sizeof(linea), archivo)) {
        // Eliminar salto de línea
        linea[strcspn(linea, "\n")] = 0;

        // Separar por comas
        int i = 0;
        char *token = strtok(linea, ",");
        while (token != NULL && i < 20) {
            campos[i++] = token;
            token = strtok(NULL, ",");
        }

        if (num_fila == 0) {
            // Saltar encabezado
            num_fila++;
            continue;
        }

        strcpy(cuenca[num_fila - 1], campos[0]);
        strcpy(embalse[num_fila - 1], campos[1]);
        mes[num_fila - 1] = atoi(campos[2]);

        for (int j = 0; j < 10; j++) {
            datos_anuales[num_fila - 1][j] = atof(campos[3 + j]);
        }

        num_fila++;
    }

    fclose(archivo);

    // ------------------ MENÚ INTERACTIVO ------------------

    char embalse_elegido[100];
    char cuenca_elegida[100];
    int mes_elegido, anio_elegido;

    // Paso 1: Mostrar embalses únicos
    printf("\nEmbalses disponibles:\n");
    for (int i = 0; i < num_fila - 1; i++) {
        int ya_mostrado = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(embalse[i], embalse[j]) == 0) {
                ya_mostrado = 1;
                break;
            }
        }
        if (ya_mostrado == 0) {
            printf("- %s\n", embalse[i]);
        }
    }

    printf("\nElige un embalse: ");
    scanf("%[^\n]", embalse_elegido);

    // Paso 2: Mostrar cuencas asociadas
    printf("\nCuencas disponibles para %s:\n", embalse_elegido);
    for (int i = 0; i < num_fila - 1; i++) {
        if (strcmp(embalse[i], embalse_elegido) == 0) {
            int ya_mostrada = 0;
            for (int j = 0; j < i; j++) {
                if (strcmp(embalse[i], embalse[j]) == 0 &&
                    strcmp(cuenca[i], cuenca[j]) == 0) {
                    ya_mostrada = 1;
                    break;
                }
            }
            if (ya_mostrada == 0) {
                printf("- %s\n", cuenca[i]);
            }
        }
    }

    printf("\nElige una cuenca: ");
    scanf("%s", cuenca_elegida);

    // Paso 3: Mostrar meses
    printf("\nMeses disponibles (número del 1 al 12):\n");
    for (int i = 0; i < num_fila - 1; i++) {
        if (strcmp(embalse[i], embalse_elegido) == 0 &&
            strcmp(cuenca[i], cuenca_elegida) == 0) {
            printf("- %d\n", mes[i]);
        }
    }

    printf("\nElige un mes (1–12): ");
    scanf("%d", &mes_elegido);

    // Paso 4: Año
    printf("\nAños disponibles: 2012 a 2021\n");
    printf("Elige un año: ");
    scanf("%d", &anio_elegido);

    // Paso 5: Mostrar resultado
    int encontrado = 0;
    for (int i = 0; i < num_fila - 1; i++) {
        if (strcmp(embalse[i], embalse_elegido) == 0 &&
            strcmp(cuenca[i], cuenca_elegida) == 0 &&
            mes[i] == mes_elegido) {

            int indice = anio_elegido - 2012;
            if (indice >= 0 && indice < 10) {
                printf("\nResultado para %s (%s), mes %d, año %d: %.2f hm³\n",
                       embalse[i], cuenca[i], mes_elegido, anio_elegido,
                       datos_anuales[i][indice]);
                encontrado = 1;
                break;
            }
        }
    }

    if (encontrado == 0) {
        printf("\nNo se encontró el dato para esa combinación.\n");
    }
	
	
}