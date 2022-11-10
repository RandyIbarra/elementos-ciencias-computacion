#include <stdio.h>
#include <stdlib.h>

// para intercambiar apuntadores usamos apuntador a apuntador
void swap(int **ptr_1,int **ptr_2){
	// guardamos el primer apuntador
	int * aux = *ptr_1;
	// al primero apuntador lo asignamos a lo que tiene el segundo
    *ptr_1 = *ptr_2;
	// aux tiene la informacion inicial de ptr_1, dado que ptr_1 ya contiene la info de ptr_2
    *ptr_2 = aux;
}

int main (void){
	// inicializamos dos variables
	int x = 5;
	int y = 4;
	// apuntamos a ellas
	int *a = &x;
	int *b = &y;
	// observamos valores y direcciones de almacenamiento
    printf("a = %p, *a = %d\n",a, *a);
	printf("b = %p, *b = %d\n",b, *b);
	// hacemos el intercambio de apuntadores
	swap(&a, &b);
	// verificamos que los apuntadores hayan intercambiado la direccion a la que apuntan
    printf("a = %p, *a = %d\n",a, *a);
	printf("b = %p, *b = %d\n",b, *b);
	return 0;
}