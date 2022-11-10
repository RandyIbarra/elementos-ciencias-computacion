#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct Complex{
	double r; //parte real
	double i; //parte imaginaria
} Complex;

int main (void){
    printf("Numero de bytes usados por un Complex: %ld\n", sizeof(Complex));
    printf("Entonces si a un apuntador a Complex se le suma 1, ahora debe de moverse %ld bytes\n", sizeof(Complex));
    // declaramos un arreglo de tipo Complex y lo llenamos a nuestro antojo
	Complex array[SIZE];
    for(int i = 0; i<SIZE; i++){
        array[i].r = (double)( i);
        array[i].i = (double)(-i);
    }
	// apuntamos al primer elemento con un apuntador a Complex
    Complex* ptr = &array[0];
    // recorremos todas las posiciones con este apuntador e imprimimos direcciones de memoria
    for(int i=0; i<SIZE; i++){
        printf("Memoria en hexadecimal: %p ---contiene---> (%.02lf, %.02lf)\n", ptr, array[i].r, array[i].i);
        ptr+=1;
    }
    printf("Observemos que se va sumando 1 en el segundo digito de la direccion de memoria.\n");
    printf("Como estos numeros estan en hexadecimal significa que esta avanzando de 16 en 16 bytes.\n");
	return 0;
}