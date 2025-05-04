#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LibreriaProyecto.h"

#define MAX_LINE 1024
#define MAX_ENTRIES 6000
#define MAX_NAME 100


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

typedef struct 
{
    char cuenca[MAX_NAME];
    char embalse[MAX_NAME];
    int mes;
    int datos[10]; // de 2012 a 2021
} Entrada;

void funcion_3_comparacion_cuencas(void)
{
	Entrada entradas[MAX_ENTRIES];
    int total_entradas = 0;

    
    FILE *f = fopen("dataset.csv", "r"); //abrimos le CSV y vemos si lo ha hecho correctamente
    if (!f) 
	{
        perror("No se pudo abrir el archivo");
        return;
    }

    char linea[MAX_LINE];
    fgets(linea, MAX_LINE, f); // Saltar descripcion datos

    while (fgets(linea, MAX_LINE, f)) //
	{ 
        Entrada e; //se define una variable de la estructura
        char *token = strtok(linea, ","); //dividimos el texto por sus partes separadas por comas
        strcpy(e.cuenca, token); //se copia la primera columna -> las cuencas

        token = strtok(NULL, ",");
        strcpy(e.embalse, token);

        token = strtok(NULL, ",");
        e.mes = atoi(token); //atoi convierte de char a int

        for (int i = 0; i < 10; i++) 
		{ //se copia en el vector los anos
            token = strtok(NULL, ",");
            e.datos[i] = token ? atoi(token) : 0;
        }

        entradas[total_entradas++] = e;
    }
    fclose(f);

    char seguir;
    do {
        printf("\nCuencas disponibles:\n"); //se ensenan las cuencas unicas que se han encontrado
        char cuencas_unicas[MAX_ENTRIES][MAX_NAME];
        int n_cuencas = 0;
        for (int i = 0; i < total_entradas; i++) 
		{
            int existe = 0;
            for (int j = 0; j < n_cuencas; j++) 
			{
                if (strcmp(entradas[i].cuenca, cuencas_unicas[j]) == 0) 
				{
                    existe = 1;
                    break;
                }
            }
            if (!existe) 
			{
                strcpy(cuencas_unicas[n_cuencas], entradas[i].cuenca);
                printf("%d. %s\n", n_cuencas + 1, cuencas_unicas[n_cuencas]);
                n_cuencas++;
            }
        }

        int opc_cuenca;
        printf("Selecciona cuenca: ");
        scanf("%d", &opc_cuenca);
        if (opc_cuenca < 1 || opc_cuenca > n_cuencas) 
		{
            printf("Selección inválida.\n");
            return;
        }
        char cuenca_sel[MAX_NAME];
        strcpy(cuenca_sel, cuencas_unicas[opc_cuenca - 1]);

        
        char embalses[MAX_ENTRIES][MAX_NAME]; //se ensenan los embalses
        int n_embalses = 0;
        for (int i = 0; i < total_entradas; i++) 
		{
            if (strcmp(entradas[i].cuenca, cuenca_sel) == 0) 
			{
                int existe = 0;
                for (int j = 0; j < n_embalses; j++) 
				{
                    if (strcmp(entradas[i].embalse, embalses[j]) == 0) 
					{
                        existe = 1;
                        break;
                    }
                }
                if (!existe) 
				{
                    strcpy(embalses[n_embalses], entradas[i].embalse);
                    printf("%d. %s\n", n_embalses + 1, embalses[n_embalses]);
                    n_embalses++;
                }
            }
        }

        int opc_embalse;
        printf("Selecciona embalse: ");
        scanf("%d", &opc_embalse);
        if (opc_embalse < 1 || opc_embalse > n_embalses) 
		{
            printf("Selección inválida.\n");
            return;
        }
        char embalse_sel[MAX_NAME];
        strcpy(embalse_sel, embalses[opc_embalse - 1]);

        int mes;
        printf("Selecciona mes (1-12): ");
        scanf("%d", &mes);
        if (mes < 1 || mes > 12) 
		{
            printf("Mes inválido.\n");
            return;
        }

        // Mostrar datos
        int encontrado = 0;
        for (int i = 0; i < total_entradas; i++) 
		{
            if (strcmp(entradas[i].cuenca, cuenca_sel) == 0 && strcmp(entradas[i].embalse, embalse_sel) == 0 && entradas[i].mes == mes) 
				{
                printf("\nDatos para %s - %s, mes %d:\n", cuenca_sel, embalse_sel, mes);
                for (int j = 0; j < 10; j++)
				 {
                    printf("%d: %d\n", 2012 + j, entradas[i].datos[j]);
                }
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) 
		{
            printf("No se encontraron datos para esa combinación.\n");
        }

        printf("\n¿Comparar otra cuenca? (s/n): ");
        scanf(" %c", &seguir);

    } while (seguir == 's' || seguir == 'S');
}