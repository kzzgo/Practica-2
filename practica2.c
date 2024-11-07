//practica 2
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 512


float Mat[N][N];
float MatDD[N][N];
float V1[N], V2[N], V3[N], V4[N];


void InitData(){
int i,j;
srand(334411);
for( i = 0; i < N; i++ )
 for( j = 0; j < N; j++ ){
 Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
 if ( (abs(i - j) <= 3) && (i != j))
 MatDD[i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX));
 else if ( i == j )
 MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX)));
 else MatDD[i][j] = 0.0;
 }
for( i = 0; i < N; i++ ){
 V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
 V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
 V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
}
}

//PRIMERA FUNCIO
void PrintVect(float vect[N], int from, int numel){
    int i;
    if (from < 0 || from >= N){
        printf("Error: aquest valor no és valid.\n");
        return;
    }
    
    if (numel <= 0){
        printf("Error: aquest valor no és valid.\n");
        return;
    }

    for (i = from; i < from + numel && i < N; i++){
        printf("%f ", vect[i]);
    }

    printf("\n");
}


//SEGONA FUNCIO
void PrintRow(float mat[N][N], int row, int from, int numel){
    int i;
    if (row < 0 || row >= N) {
        printf("Error: fila fora de límits.\n");
        return;
    }

    if (from < 0 || from >= N) {
        printf("Error: Posició inicial fora de límits.\n");
        return;
    }

    if (numel <= 0) {
        printf("Error: aquest valor no és valid.\n");
        return;    
    }
    
    for (i = from; i < from + numel && i < N; i++) {
        printf("%f ", mat[row][i]);
    }
    printf("\n");
}

//TERCERA FUNCIO
void MultEscalar(float vect[N], float vectres[N], float alfa){
    for (int i = 0; i < N; i++) {
        vectres[i] = alfa * vect[i];
    }
}

//QUARTA FUNCIO
float Scalar( float vect1[N], float vect2[N] ){
    float resultat = 0.0 ;
    for (int i = 0; i < N; i++) {
        resultat += vect1[i] * vect2[i];
        return resultat;
    }       
}

//QUINTA FUNCIO
float Magnitude( float vect[N] ){
    float resultat;
    resultat = sqrt(Scalar(vect,vect));
    return resultat;
}

//SISENA FUNCIO
int Ortogonal( float vect1[N], float vect2[N] ){
    float resultat;
    resultat = Scalar(vect1,vect2);
    if (resultat != 0)
        return  0;
    else
        return 1;
}

//SETENA FUNCIO
void Projection( float vect1[N], float vect2[N], float vectres[N] ){
MultEscalar(vect1,  vectres, ((Scalar(vect1,vect2)/(Magnitude(vect2)))));
}


//VUITENA FUNCIO
float Infininorm( float M[N][N] ){
        float suma_max = 0;
    for (int i = 0; i < N; i++){
        float suma_fila = 0;
        for (int j = 0; j < N; i++){
            suma_fila += fabs(M[i][j]);
        } 
        if (suma_fila > suma_max){
            suma_fila = suma_max;
        }
    }
    return suma_max
}

//NOVENA FUNCIO
float Onenorm( float M[N][N] ){
    float suma_max = 0;
    for (int i = 0; i < N; i++){
        float suma_columna = 0;
        for (int j = 0; j < N; i++){
            suma_columna += fabs(M[j][i]);
        } 
        if (suma_columna > suma_max){
            suma_columna = suma_max;
        }
    }
    return suma_max
}
//DESENA FUNCIO
float NormFrobenius( float M[N][N]){
    float frob = 0.0
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++)
            frob += abs((M[i][j])*M[i][j])
    frob = sqrt(frob)
}
//ONZENA FUNCIO
int DiagonalDom(float M[N][N])
float element_diagonal
float sum_altres
    for (int i = 0; i < N; i++)
        element_diagonal = abs(M[i][i])
        for (int j = 0; j < N; j++)
            if (j != i);{
                sum_altres += abs(M[i][j])
            }
    if (element_diagonal < sum_altres){
    return 0
return 1
}


//DOTZENA FUNCIO
void Matriu_x_Vector( float M[N][N], float vect[N], float vectres[N] ){
    int i, j;
    for (i = 0; i < N; i++) {
        vectres[i] = 0;
        for (j = 0; j < N; j++) {
            vectres[i] += M[i][j] * vect[j];
        }
    }
}


//TRETZENA FUNCIO
int Jacobi( float M[N][N] , float vect[N], float vectres[N], unsigned iter ){
    if (!DiagonalDom(M)) {
        return 0;
    }

    float x[N] = {0};
    float temp[N];
    int k, i, j;

    for (k = 0; k < iter; k++) {
        for (i = 0; i < N; i++) {
            temp[i] = vect[i];
            for (j = 0; j < N; j++) {
                if (j != i) temp[i] -= M[i][j] * x[j];
            }
            temp[i] /= M[i][i];
        }
        for (i = 0; i < N; i++) {
            x[i] = temp[i];
        }
    }
    
    for (i = 0; i < N; i++) {
        vectres[i] = x[i];
    }
    return 1;
}


//FUNCIÓ PRINCIPAL MAIN
int main(){

InitData();

//PRINT FUNCIO 1
printf("  ___ ___  ___  ___ _    ___ __  __   _     _ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   / |\n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\  | |\n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\ |_|\n");
printf("                                             \n");

printf("A. Els elements 0 al 9 i 256 al 265 dels vectors V1, V2 i V3.\n\n");
printf("V1 del 0 al 9 i del 256 al 265:\n");
PrintVect(V1, 0, 10);
PrintVect(V1, 256, 266);
printf("\n");
printf("\n");

printf("V2 del 0 al 9 i del 256 al 265:\n");
PrintVect(V2, 0, 10);
PrintVect(V2, 256, 266);
printf("\n");
printf("\n");

printf("V3 del 0 al 9 i del 256 al 265:\n");
PrintVect(V3, 0, 10);
PrintVect(V3, 256, 266);
printf("\n");
printf("\n");


//PRINT FUNCIO 2
printf("  ___ ___  ___  ___ _    ___ __  __   _     ___ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   |_  )\n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\   / / \n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\ /___|\n");
printf("                                               \n");

printf("Elements de la fila 0 de la matriu (índexs 0 al 9):\n");
PrintRow(Mat, 0, 0, 10);
printf("\n");

printf("Elements de la fila 100 de la matriu (índexs 0 al 9):\n");
PrintRow(Mat, 100, 0, 10);
printf("\n");


//PRINT FUNCIO 3
printf("  ___ ___  ___  ___ _    ___ __  __   _     ____ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   |__ / \n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\   |_ \\ \n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\ |___/ \n");
printf("                                               \n");

}
