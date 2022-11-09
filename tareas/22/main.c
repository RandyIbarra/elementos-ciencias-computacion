/*
Dado que la imagen es una matriz de numeros usaremos l codigo de la estructura matriz.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct MatrixStruct {
	int nRows;
	int nCols;
	int *data;
} Matrix;

typedef struct PGMStruct {
    char format[128];
    int maxGrayLevel;
    Matrix* image;
} PGM;

int get(Matrix *m, int i, int j) {
    return m->data[m->nCols*i+j];
}

void set(Matrix *m,int i,int j,int val) {
	m->data[m->nCols*i+j]=val;
}

Matrix *createMatrix(int nRows,int nCols) {
	Matrix *mat = NULL;
	if ((mat=(Matrix *)malloc(sizeof(Matrix)))==NULL)
		return NULL;
	mat->nRows = nRows;
	mat->nCols = nCols;
	if ((mat->data=(int *)calloc(nRows*nCols,sizeof(int)))==NULL) {
		free(mat);
		return NULL;
	}
	return mat;
}

PGM *loadPGM(char *fileName) {
	FILE *fp = fopen(fileName,"r");
	if (fp==NULL)
		return NULL;
    PGM *pgm = NULL;
	if ((pgm=(PGM *)malloc(sizeof(PGM)))==NULL){
        fclose(fp);
		return NULL;
    }
    // "The first line specifies the type of encoding: P2 or P5 means PGM"
    // Entonces la primera linea contiene "P2" o "P5"
    fscanf(fp, "%s", (pgm->format));
    // "The two numbers in the second line are the width and height of the image, in pixels."
    int nRows,nCols;
	fscanf(fp,"%d %d\n",&nCols,&nRows);
    pgm->image = createMatrix(nRows,nCols);
    if ((pgm->image)==NULL){
        fclose(fp);
		return NULL;
    }
	// "The third line shows the maximal number of gray levels; in this case, the number of levels is 255."
    int maxGrayLevel;
    fscanf(fp,"%d\n",&(pgm->maxGrayLevel));
    for (int i=0;i<nRows;i++) {
		for (int j=0;j<nCols;j++) {
			int dato;
			fscanf(fp,"%d",&dato);
			set(pgm->image,i,j,dato);
		}
	}
	fclose(fp);
	return pgm;
}

void writePGM(char *fileName, PGM *pgm) {
	FILE *fp = fopen(fileName,"w");
	if (fp==NULL || pgm == NULL)
		return;
    // "The first line specifies the type of encoding: P2 or P5 means PGM"
    fprintf(fp, "P2\n");
    // "The two numbers in the second line are the width and height of the image, in pixels."
    int nRows = pgm->image->nRows;
    int nCols = pgm->image->nCols;
	fprintf(fp,"%d %d\n",nCols, nRows);
	// "The third line shows the maximal number of gray levels; in this case, the number of levels is 255."
    int maxGrayLevel = pgm->maxGrayLevel;
    fprintf(fp,"%d\n",maxGrayLevel);
    // "The other values are the gray levels of pixels, and their total number is (width * height)"
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            int value = get(pgm->image, i, j);
            fprintf(fp, "%d ", value);
        }
        fprintf(fp, "\n");
    }
	fclose(fp);
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

void freePGM(PGM **pgm) {
	if (pgm==NULL)
		return;
	if ((*pgm)==NULL)
		return;
	freeMatrix(&((*pgm)->image));
    free(*pgm);
	*pgm = NULL;
}

int main() {
	PGM *pgm = loadPGM("cat.pgm");
	if (pgm==NULL){
		printf("Error al cargar imagen\n");
		return 0;
	}
    for(int i=0; i<500; i++){
        for(int j=0; j<500; j++){
            set(pgm->image, i,j, pgm->maxGrayLevel);
        }
    }
    writePGM("cat_2.pgm", pgm);
	freePGM(&pgm);
	if(pgm == NULL){
		printf("El apunntador es NULL como se esperaba\n");
	}
}