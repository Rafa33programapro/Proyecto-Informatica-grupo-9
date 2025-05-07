#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LibreriaProyecto.h"

#define LINEA_MAX 1024
#define ENTRADA_MAX 6000
#define NOMBRES_MAX 100


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
    char cuenca[NOMBRES_MAX];
    char embalse[NOMBRES_MAX];
    int mes;
    int datos[10]; 									// de 2012 a 2021
} Entrada;

void funcion_1_media_volumen_cuenca(void)
{
   Entrada entradas[ENTRADA_MAX];
   int total_entradas = 0;

    FILE *f = fopen("dataset.csv", "r");
    if (!f) 
    {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    char linea[LINEA_MAX];
    fgets(linea, LINEA_MAX, f); // Saltar encabezado

    while (fgets(linea, LINEA_MAX, f))                      //leemos el CSV linea a linea
    {
        Entrada e;
        char *token = strtok(linea, ",");               //guardamos la primera parte de la linea (cuenca)
        strcpy(e.cuenca, token);

        token = strtok(NULL, ",");
        strcpy(e.embalse, token);                       //guardamos la segunda parte de la linea (embalse)    

        token = strtok(NULL, ",");
        e.mes = atoi(token);                            //guardamos la tercera parte de la linea (mes) y lo convertimos a entero

        for (int i = 0; i < 10; i++) 
        {
            token = strtok(NULL, ",");
            e.datos[i] = token ? atoi(token) : 0;           //guardamos el resto de la linea (datos) y los convertimos a enteros, si no hay datos se asigna 0
        }

        entradas[total_entradas++] = e;
    }
    fclose(f);

    char seguir;
    do 
    {
        // Mostrar cuencas únicas
        char cuencas_unicas[ENTRADA_MAX][NOMBRES_MAX];
        int n_cuencas = 0;
        printf("\nCuencas disponibles:\n");
        for (int i = 0; i < total_entradas; i++) 
        {
            int existe = 0;
            for (int j = 0; j < n_cuencas; j++) 
            {
                if (strcmp(entradas[i].cuenca, cuencas_unicas[j]) == 0)             //comparamos para no copiar cuenca/embalse dos veces
                {
                    existe = 1;
                    break;
                }
                {
                    existe = 1;
                    break;
                }
            }
            if (!existe) 
            {
                strcpy(cuencas_unicas[n_cuencas], entradas[i].cuenca);              //se copia la cuenca
                printf("%d. %s\n", n_cuencas + 1, cuencas_unicas[n_cuencas]);
                n_cuencas++;
            }
        }

        int opc_cuenca;
        printf("Selecciona cuenca: ");           //se le pide al usuario que seleccione una cuenca
        scanf("%d", &opc_cuenca);
        if (opc_cuenca < 1 || opc_cuenca > n_cuencas) 
        {
            printf("Selección inválida.\n");
            return 1;
        }
        char cuenca_sel[NOMBRES_MAX];
        strcpy(cuenca_sel, cuencas_unicas[opc_cuenca - 1]);

        int opc_media;               // Opción de media anual o mensual 
        printf("¿Quieres calcular la media anual (1) o mensual (2)?\n");
        scanf("%i", &opc_media);
        if (opc_media == 1)
        {
            printf("Media anual de la cuenca %s:\n", cuenca_sel);               //imprimimos encabezado 
            printf("Año\\Media\n");         
            for(int a=0; a<10; a++) //Recorremos los años
            {
                int suma = 0;
                int num = 0;

                for (int i= 0; i < total_entradas; i++) //Recorremos las entradas y verificamos si coincide con la cuenca seleccionada
                {
                    if(strcmp(entradas[i].cuenca, cuenca_sel) == 0)
                    {
                        suma+= entradas[i].datos[a];
                        num++;
                    }
                }
                if(num>0)
                {
                    printf("%i\\%.2f\n", 2012 + a, suma / num);
                }
                else
                {
                    printf("%i\\Sin Datos\n", 2012 + a);
                }
            }
        }
        else if (opc_media == 2)
        {
            printf("Media mensual de la cuenca %s:\n", cuenca_sel);
            printf("Mes\t Media\n");
            for(int m = 1; m <= 12; m++) //Recorremos los doce meses
            {
                int suma = 0;
                int num = 0;

                for(int i = 0; i < total_entradas; i++)
                {
                    if(strcmp(entradas[i].cuenca, cuenca_sel)==0 && entradas[i].mes == m)
                    {
                        for(int a= 0; a < 10; a++)
                        {
                            suma+= entradas[i].datos[a];
                            num++;
                        }
                    }
                }
                if (num>0)
                {
                    printf("%i\\ %.2f\n", m, suma/num);
                }
                else
                {
                    printf("%i\\ No hay datos\n",m);
                }
            }
        }
        else
        {
            printf("Opcion no valida.\n");
            return 1;
        }
        printf("\n¿Ver otra cuenca/embalse? (s/n): ");
        scanf(" %c", &seguir);

    } while (seguir == 's' || seguir == 'S');

    return 0;
}

void funcion_2_evolucion_volumen_embalsado(void)
{
   Entrada entradas[ENTRADA_MAX];
    int total_entradas = 0;

    FILE *f = fopen("dataset.csv", "r");
    if (!f) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    char linea[LINEA_MAX];
    fgets(linea, LINEA_MAX, f); // Saltar descripcion de datos

    while (fgets(linea, LINEA_MAX, f)) {
        Entrada e;
        char *token = strtok(linea, ",");   //se lee todo entre las comas
        strcpy(e.cuenca, token);

        token = strtok(NULL, ",");
        strcpy(e.embalse, token);

        token = strtok(NULL, ",");
        e.mes = atoi(token);

        for (int i = 0; i < 10; i++) {
            token = strtok(NULL, ",");
            e.datos[i] = token ? atoi(token) : 0; //se leen los datos, si existe se convierte a entero si no se asigna 0
        }

        entradas[total_entradas++] = e;
    }
    fclose(f);

    char seguir;
    do {
        char cuencas_unicas[ENTRADA_MAX][NOMBRES_MAX]; // Mostrar cuencas únicas
        int n_cuencas = 0;
        printf("\nCuencas disponibles:\n");
        for (int i = 0; i < total_entradas; i++) {
            int existe = 0;
            for (int j = 0; j < n_cuencas; j++) {
                if (strcmp(entradas[i].cuenca, cuencas_unicas[j]) == 0) {
                    existe = 1;
                    break;
                }
            }
            if (!existe) {
                strcpy(cuencas_unicas[n_cuencas], entradas[i].cuenca);
                printf("%d. %s\n", n_cuencas + 1, cuencas_unicas[n_cuencas]);
                n_cuencas++;
            }
        }

        int opc_cuenca;
        printf("Selecciona cuenca: ");
        scanf("%d", &opc_cuenca);
        if (opc_cuenca < 1 || opc_cuenca > n_cuencas) {
            printf("Selección inválida.\n");
            return 1;
        }
        char cuenca_sel[NOMBRES_MAX];
        strcpy(cuenca_sel, cuencas_unicas[opc_cuenca - 1]);

        char embalses[ENTRADA_MAX][NOMBRES_MAX]; // Mostrar embalses unicos para esa cuenca
        int n_embalses = 0;
        printf("Embalses disponibles en %s:\n", cuenca_sel);
        for (int i = 0; i < total_entradas; i++) {
            if (strcmp(entradas[i].cuenca, cuenca_sel) == 0) {
                int existe = 0;
                for (int j = 0; j < n_embalses; j++) {
                    if (strcmp(entradas[i].embalse, embalses[j]) == 0) {
                        existe = 1;
                        break;
                    }
                }
                if (!existe) {
                    strcpy(embalses[n_embalses], entradas[i].embalse);
                    printf("%d. %s\n", n_embalses + 1, embalses[n_embalses]);
                    n_embalses++;
                }
            }
        }

        int opc_embalse;
        printf("Selecciona embalse: ");
        scanf("%d", &opc_embalse);
        if (opc_embalse < 1 || opc_embalse > n_embalses) {
            printf("Selección inválida.\n");
            return 1;
        }
        char embalse_sel[NOMBRES_MAX];
        strcpy(embalse_sel, embalses[opc_embalse - 1]);

        printf("\nTabla de datos para %s - %s:\n\n", cuenca_sel, embalse_sel); // Mostrar tabla de datos

        printf("Mes\\Año ");    //imprimimos encabezado
        for (int a = 2012; a <= 2021; a++)
        {
            printf("%6d", a);
        }
        printf("\n");

        for (int m = 1; m <= 12; m++)
        {
            printf("%7d", m);
            for (int a = 0; a < 10; a++)
            {
                int valor = -1;
                for (int i = 0; i < total_entradas; i++)
                {
                    if (strcmp(entradas[i].cuenca, cuenca_sel) == 0 &&strcmp(entradas[i].embalse, embalse_sel)
                        == 0 && entradas[i].mes == m)
                        {
                        valor = entradas[i].datos[a];
                        break;
                    }
                }
                if (valor != -1)    //verificamos si el valor realmente existe
                {
                    printf("%6d", valor);
                } else {
                    printf("%6s", "NA");
                }
            }
            printf("\n");
        }

        printf("\n¿Ver otra cuenca/embalse? (s/n): ");
        scanf(" %c", &seguir);

    } while (seguir == 's' || seguir == 'S');

}

void funcion_3_comparacion_cuencas(void)
{
	Entrada entradas[ENTRADA_MAX];
    int total_entradas = 0;


    FILE *f = fopen("dataset.csv", "r"); 			//abrimos le CSV y vemos si lo ha hecho correctamente
    if (!f)
	{
        perror("No se pudo abrir el archivo");
        return;
    }

    char linea[LINEA_MAX];
    fgets(linea, LINEA_MAX, f); 					// Saltar descripcion datos

    while (fgets(linea, LINEA_MAX, f))
	{
        Entrada e; 									//se define una variable de la estructura
        char *token = strtok(linea, ","); 			//dividimos el texto por sus partes separadas por comas
        strcpy(e.cuenca, token); 					//se copia la primera columna -> las cuencas

        token = strtok(NULL, ",");
        strcpy(e.embalse, token);					//Se copia la segunda columna -> los embalses

        token = strtok(NULL, ",");
        e.mes = atoi(token); 						//Se copia la tercera columna -> meses (atoi convierte de char a int)

        for (int i = 0; i < 10; i++)
		{                                        	//Se leen y copian en el vector de datos los datos por cada ano
            token = strtok(NULL, ",");
            e.datos[i] = token ? atoi(token) : 0;	//verificamos si hay un dato, lo cambiamos a int con atoi y sino le damos valor 0
        }

        entradas[total_entradas++] = e; 			//cada grupo de datos se guarda en una variable e que se reusa, luego esta pasa a ser una parte del vector entradas
    }
    fclose(f);

    char seguir;									//respuesta a si comparar mas cuencas
    do {
        printf("\nCuencas disponibles:\n"); 		//se ensenan las cuencas unicas que se han encontrado
        char cuencas_unicas[ENTRADA_MAX][NOMBRES_MAX];
        int n_cuencas = 0;
        for (int i = 0; i < total_entradas; i++)
		{
            int existe = 0;
            for (int j = 0; j < n_cuencas; j++)
			{
                if (strcmp(entradas[i].cuenca, cuencas_unicas[j]) == 0) //comparamos para no copiar cuenca/embalse dos veces
				{
                    existe = 1;
                    break;
                }
            }
            if (!existe)                                                //si existe ensenamos la cuenca
			{
                strcpy(cuencas_unicas[n_cuencas], entradas[i].cuenca);
                printf("%d. %s\n", n_cuencas + 1, cuencas_unicas[n_cuencas]);
                n_cuencas++;
            }
        }

        int opc_cuenca;
        printf("Selecciona cuenca: ");                                      //el comentario anterior se aplica a esta parte
        scanf("%d", &opc_cuenca);
        if (opc_cuenca < 1 || opc_cuenca > n_cuencas)
		{
            printf("Selección inválida.\n");
            return;
        }
        char cuenca_sel[NOMBRES_MAX];
        strcpy(cuenca_sel, cuencas_unicas[opc_cuenca - 1]);


        char embalses[ENTRADA_MAX][NOMBRES_MAX]; 		//se ensenan los embalses
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
        char embalse_sel[NOMBRES_MAX];
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

