#include <stdio.h>
#include <stdlib.h>

typedef struct MatrixStruct {
	int nRows;
	int nCols;
	// apuntador simple
	double *data;
} Matrix;

double get(Matrix *m, int i, int j) {
    return m->data[m->nCols*i+j];
}

void set(Matrix *m,int i,int j,double val) {
	m->data[m->nCols*i+j]=val;
}

Matrix *createMatrix(int nRows,int nCols) {
	Matrix *mat = NULL;
	if ((mat=(Matrix *)malloc(sizeof(Matrix)))==NULL)
		return NULL;
    /// Las dos lineas anteriores (26 y 27) son una forma corta de escribir:
    //mat = (Matrix *) malloc(sizeof(Matrix));
    //if(mat == NULL) 
    //    return NULL;
	mat->nRows = nRows;
	mat->nCols = nCols;
	if ((mat->data=(double *)calloc(nRows*nCols,sizeof(double)))==NULL) {
		free(mat);
		return NULL;
	}
    /// Las cuatro lineas anteriores (34 a 37) son una forma corta de escribir:
    //mat->data = (double *) calloc(nRows*nCols, sizeof(double));
    //if (mat->data == NULL) {
	//	free(mat);
	//	return NULL;
	//}
	for(int i = 0; i<nRows*nCols; i++)
		mat->data[i] = 0.0;
	return mat;
}

void printMatrix(Matrix *m) {
	if (m==NULL)
		return;
	printf("%d %d\n",m->nRows,m->nCols);
	for (int i=0;i<m->nRows;i++) {
		for (int j=0;j<m->nCols;j++)
            // %2.6f indica que se imprimen 2 cifras con 6 decimales
			printf("%2.6f ",get(m,i,j));
		printf("\n");
	}
}

void saveMatrix(Matrix *m, char *fileName) {
	if (m==NULL)
		return;
	FILE *fp = fopen(fileName,"w");
	if (fp==NULL)
		return;
	fprintf(fp,"%d %d\n",m->nRows,m->nCols);
	for (int i=0;i<m->nRows;i++) {
		for (int j=0;j<m->nCols;j++)
            // %2.6f indica que se imprimen 2 cifras con 6 decimales
			fprintf(fp,"%2.6f ",get(m,i,j));
		fprintf(fp,"\n");
	}
	fclose(fp);
}

Matrix *loadMatrix(char *fileName) {
	FILE *fp = fopen(fileName,"r");
	if (fp==NULL)
		return NULL;
	int nRows,nCols;
	fscanf(fp,"%d %d\n",&nRows,&nCols);
	Matrix *m = createMatrix(nRows,nCols);
	for (int i=0;i<m->nRows;i++) {
		for (int j=0;j<m->nCols;j++) {
			double dato;
			fscanf(fp,"%lf ",&dato);
			set(m,i,j,dato);
		}
	}
	fclose(fp);
	return m;
}

void freeMatrix(Matrix **m) {
	if (m==NULL)
		return;
	if ((*m)==NULL)
		return;
	// Primero: liberamos memoria de la variable de los datos de la matriz
	free((*m)->data);
	// ahora podemos liberar la memoria de la variable de la matriz
	free(*m);
	// nos aseguramos de que la variable que nos mandan ahora sea NULL
	*m = NULL;
}

void fillRand(Matrix *m) {
	if (m==NULL)
		return;
	for (int i=0;i<m->nRows;i++)
		for (int j=0;j<m->nCols;j++)
			set(m,i,j,(double)rand()/RAND_MAX);
}


int main() {
	Matrix *m = createMatrix(10,10);
	if (m==NULL){
		printf("Error al crear Matrix\n");
		return 0;
	}
	fillRand(m);
	saveMatrix(m,"toto.mat");
	//Matrix *m = loadMatrix("toto.mat");
	printMatrix(m);
	freeMatrix(&m);
	if(m == NULL){
		printf("El apunntador es NULL como se esperaba\n");
	}
}