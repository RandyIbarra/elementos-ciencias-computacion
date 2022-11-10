#include <stdio.h>
#include <stdlib.h>

int sumBytes(unsigned long long n){
	// usamos un apuntador a char (1 byte)
    char *ptr = (char*)(&n);
    // calculamos el numero de bytes de un unsigned long long int
    int n_bytes = sizeof(n);
    // variable que guardara la suma
	int sum = 0, current;
	for(int i = 0; i<n_bytes; i++){
		// guardamos en una variabole tipo int el valor del byte actual
        current = (int)(*ptr);
        // imprimimos para verificar que numero representa cada byte
		printf("numero[%d] = %d\n", i, current);
		// sumamos valor asociado al byte
		sum += current;
		//apuntamos al siguiente byte
		ptr++;
	}
	return sum;
}

int main (void){
	unsigned long long n;
    
    n = 258;
	printf("Resultado de sumar los numeros asociados a cada byte: %d\n", sumBytes(n));

    n = 255;
	printf("Resultado de sumar los numeros asociados a cada byte: %d\n", sumBytes(n));

    n = 100000;
	printf("Resultado de sumar los numeros asociados a cada byte: %d\n", sumBytes(n));
	
    return 0;
}