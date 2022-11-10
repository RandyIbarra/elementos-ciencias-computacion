/*
Programar una función que recibe un apuntador a double y un número de elementos n, 
y que calcula la varianza de los n elementos consecutivos ubicados a partir de la 
dirección indicada por el apuntador. 

En la función main, declarar un arreglo de tamaño 10000, llenarlo de números 
aleatorios, y usar la función anterior 3 veces para calcular la varianza de: 

-los primeros 2000 elementos
-los últimos 5000
-los 3000 de en medio
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// tamanio de arreglo a generar
#define SIZE 10000
// se suelen declarar constantes importantes de esta forma
// asi, si es necesario cambiarla, solo lo hacemos aqui
// y no buscamos todas las ocurrencias en el codigo.

// Calcular como: https://es.wikipedia.org/wiki/Media_(matem%C3%A1ticas)#Media_aritm%C3%A9tica
double getMean(double* array, int size){
    // inicializamos variable en 0
    double mean = 0.0;
    // sumamos valores y dividimos suma entre cantidad de elementos
    for(int i = 0; i<size; i++) 
		mean += array[i];
	mean /= size;
    return mean;
}

// Calcular como: https://es.wikipedia.org/wiki/Varianza#Varianza_muestral
double getVariance(double* array, int size){
    // inicializamos variable en 0
    double variance = 0.0;
    // calculamos media de los datos (necesario para calcular varianza)
    double mean = getMean(array, size);
    // sumamos "errores" al cuadrado y dividimos suma entre cantidad de elementos
    for(int i = 0; i<size; i++) 
		variance += (array[i] - mean)*(array[i] - mean);
	variance /= size;
    return variance;
}

void fillArray(double* array, int size){
    // damos semilla para reproducir generacion de numeros aleatorios con rand()
    //srand(1);
    // no se definio el rango de los numeros aleatorios a generar
    // entonces nosotros definimos el rango entre 0 y 1
    for(int i = 0; i<size; i++){
        // rand() regresa un int por lo que lo transformamos a double primero
        double val = (double) rand();
        // rand() regresa un int entre 0 y RAND_MAX, 
        // pero nos interesa generar numeros entre 0 y 1.
        array[i] = (double) (val / RAND_MAX);
    }
}

void printArray(double* array, int size){
    printf("Valores\n");
    for(int i = 0; i<size; i++){
        printf("%lf ", array[i]);
    }
    printf("\n");
}

int main(){

	double A[SIZE];
	
    fillArray(A, SIZE);
    
    //printArray(A, SIZE);
	
	printf("Varianza de los primeros 2000 elementos");
	printf("\n%lf", getVariance(A, 2000)); // printf("\n%lf", getVariance(&A[0], 2000));
	printf("\n\nVarianza de los ultimos 5000");
	printf("\n%lf", getVariance(A + 5000, 5000)  ); // printf("\n%lf", getVariance(&A[5000], 5000));
	printf("\n\nVarianza de los 3000 elementos de en medio ");
	printf("\n%lf\n", getVariance(A + 3500, 3000)  ); // printf("\n%lf", getVariance(&A[3500], 3000));

	return 0;
}