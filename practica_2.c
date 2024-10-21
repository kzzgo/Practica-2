//practica 2
#include <stdio.h>
#include <stdlib.h>
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

//PRIMER PROBLEMA
void PrintVect( float vect[N], int from, int numel ){
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


//SEGON PROBLEMA
void PrintRow( float mat[N][N], int row, int from, int numel ){
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


//FUNCIÓ PRINCIPAL MAIN
int main(){

InitData();

//PRINT PROBLEMA 1
printf("  ___ ___  ___  ___ _    ___ __  __   _     _ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   / |\n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\  | |\n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\ |_|\n");
printf("                                             \n");

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


//PRINT PROBLEMA 2
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

}