#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

/* cabecera de las llamadas a MPI */
#include <mpi.h>

//Kevin Daniel Gatica Oportus
//19.034.012-0

/**
 * Manda un mensaje desde todos los procesos con
 * rango distinto de 0 al proceso 0. El proceso 0
 * los saca por pantalla.
 * Entrada: ninguna
 * Salida: contenido de los mensajes recibidos por
 * el proceso 0, que los imprime
 */

// Funcion que retorna fecha y hora
char* horayfecha(char mensaje2[100]){
	{
    time_t tH; // Definimos tH (hora y fecha) como tipo de dato time_t
    struct tm *tm; // tm es la estructura de la hora
    char fechaHora[80]; // Cadena de fecha y hora

    tH=time(NULL);
    tm=localtime(&tH); // Guarda hora local en tm
    strftime(fechaHora, 80, " %Y-%m-%d %H:%M:%S", tm);
    sprintf (mensaje2,"%s", fechaHora); // Imprime fecha y hora
    return mensaje2;
	}
}

int main(int argc, char** argv) {
    int mi_rango; /* rango del proceso    */
    int p; /* numero de procesos   */
    int fuente; /* rango del que envia  */
    int dest; /* rango del que recibe */
    int tag = 0; /* etiqueta del mensaje */
    char mensaje[100]; // Mensaje
    char mensaje2[100]; // Guarda fecha y hora en la funcion
    char mensaje3[100]; // Guarda mensaje2 como texto

    struct utsname nombreHost;// Estructura de utsname
    MPI_Status estado; /* devuelve estado al recibir*/

    /* Comienza las llamadas a MPI */
    MPI_Init(&argc, &argv);

    /* Averiguamos el rango de nuestro proceso */
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);

    /* Averiguamos el número de procesos que estan
     * ejecutando nuestro porgrama
     */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (mi_rango != 0) {
        /* Crea mensaje */
    if(uname(&nombreHost) < 0) {// En caso que falle, imprima error
        printf("Error al leer nombre");
    } else{
	sprintf(mensaje, "%s", nombreHost.nodename); // Guarda el nombre en mensaje
	sprintf(mensaje3, "%s" , horayfecha(mensaje2)); // Guarda fecha y hora en mensaje3
	strcat(mensaje, mensaje3); // Concatena mensaje3 a mensaje

    }
        dest = 0;



        /* Usa strlen+1 para que la marca /0 se transmita */
        MPI_Send(mensaje, strlen(mensaje) + 1, MPI_CHAR,
                dest, tag, MPI_COMM_WORLD);
    } else { /* mi_rango == 0 */
        for (fuente = 1; fuente < p; fuente++) {
            MPI_Recv(mensaje, 100, MPI_CHAR, fuente,
                    tag, MPI_COMM_WORLD, &estado);
            printf("%s\n", mensaje);
        }
    }

    /* Termina con MPI. Recordemos que después de
     * esta llamada no podemos llamar a funciones
     * MPI, ni siquiera de nuevo a MPI_Init
     */
    MPI_Finalize();
    return EXIT_SUCCESS;
}
