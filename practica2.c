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
    }
    return resultat;
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
        for (int j = 0; j < N; j++){
            suma_fila += fabs(M[i][j]);
        } 
        if (suma_fila > suma_max){
            suma_max = suma_fila;
        }
    }
    return suma_max;
}

//NOVENA FUNCIO
float Onenorm( float M[N][N] ){
    float suma_max = 0;
    for (int i = 0; i < N; i++){
        float suma_columna = 0;
        for (int j = 0; j < N; j++){
            suma_columna += fabs(M[j][i]);
        } 
        if (suma_columna > suma_max){
            suma_max = suma_columna;
        }
    }
    return suma_max;
}
//DESENA FUNCIO
float NormFrobenius( float M[N][N] ) {
    float frob = 0.0;
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++)
            frob += fabsf((M[i][j]) * M[i][j]);
    return sqrt(frob);
}

//ONZENA FUNCIO
int DiagonalDom(float M[N][N]){
int i, j;
float element_diagonal;
float sum_altres;
    for (int i = 0; i < N; i++)
        element_diagonal = fabsf(M[i][i]);
        for (int j = 0; j < N; j++)
            if (j != i){
                sum_altres += fabsf(M[i][j]);
            }
    if (element_diagonal < sum_altres){
    return 0;
return 1;
}
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

//PRINT EXERCICI 1
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


//PRINT EXERCICI 2
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
printf("\n");


//PRINT EXERCICI 3
printf("  ___ ___  ___  ___ _    ___ __  __   _     ____ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   |__ / \n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\   |_ \\ \n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\ |___/ \n");
printf("                                               \n");

printf("MatDD fila 0 del 0 al 9 i fila 100 del 95 al 104:\n");
PrintRow(MatDD, 0, 0, 10);
PrintRow(MatDD, 100, 90, 10);
printf("\n");
printf("\n");

//PRINT EXERCICI 4
printf("  ___ ___  ___  ___ _    ___ __  __   _     _ _  \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   | | | \n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\  |_  _|\n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\   |_| \n");
printf("                                               \n");

float inf_norm_Mat = Infininorm(Mat);
float one_norm_Mat = Onenorm(Mat);
float frobenius_Mat = NormFrobenius(Mat);
int is_diag_dominant_Mat = DiagonalDom(Mat);

float inf_norm_MatDD = Infininorm(MatDD);
float one_norm_MatDD = Onenorm(MatDD);
float frobenius_MatDD = NormFrobenius(MatDD);
int is_diag_dominant_MatDD = DiagonalDom(MatDD);

printf("Infininorma de Mat = %f\n", inf_norm_Mat);
printf("Norma ú de Mat = %f\n", one_norm_Mat);
printf("Norma de Frobenius de Mat = %f\n", frobenius_Mat);
printf("La matriu Mat %s diagonal dominant\n", is_diag_dominant_Mat ? "és" : "no és");

printf("Infininorma de MatDD = %f\n", inf_norm_MatDD);
printf("Norma ú de MatDD = %f\n", one_norm_MatDD);
printf("Norma de Frobenius de MatDD = %f\n", frobenius_MatDD);
printf("La matriu MatDD %s diagonal dominant\n", is_diag_dominant_MatDD ? "és" : "és");
printf("\n");
printf("\n");

//PRINT EXERCICI 5
printf("  ___ ___  ___  ___ _    ___ __  __   _     ___ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   | __|\n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\  |__ \\\n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\ |___/\n");
printf("                                                \n");

float prod_V1_V2 = Scalar(V1, V2);
float prod_V1_V3 = Scalar(V1, V3);
float prod_V2_V3 = Scalar(V2, V3);

printf("Escalar <V1, V2> = %f\n", prod_V1_V2);
printf("Escalar <V1, V3> = %f\n", prod_V1_V3);
printf("Escalar <V2, V3> = %f\n", prod_V2_V3);
printf("\n");
printf("\n");

//PRINT EXERCICI 6
printf("  ___ ___  ___  ___ _    ___ __  __   _      __ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\    / / \n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\  / _ \\\n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\ \\___/\n");
printf("                                                \n");

printf("Magnitud V1 = %f\n", Magnitude(V1));
printf("Magnitud V2 = %f\n", Magnitude(V2));
printf("Magnitud V3 = %f\n", Magnitude(V3));

printf("\n");
printf("\n");

//PRINT EXERCICI 7
printf("  ___ ___  ___  ___ _    ___ __  __   _     ____ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   |__  |\n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\    / / \n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\  /_/  \n");
printf("                                                 \n");

if (Ortogonal(V1, V2)) {
    printf("V1 i V2 són ortogonals\n");
} else {
    printf("V1 i V2 no són ortogonals\n");
}

if (Ortogonal(V1, V3)) {
    printf("V1 i V3 són ortogonals\n");
} else {
    printf("V1 i V3 no són ortogonals\n");
}

if (Ortogonal(V2, V3)) {
    printf("V2 i V3 són ortogonals\n");
} else {
    printf("V2 i V3 no són ortogonals\n");
}

printf("\n");
printf("\n");

//PRINT EXERCICI 8
printf("  ___ ___  ___  ___ _    ___ __  __   _     ___ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   ( _ )\n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\  / _ \\\n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\ \\___/\n");
printf("                                                \n");

float V3_res[N];
MultEscalar(V3, V3_res, 2.0);

printf("Els elements 0 al 9 i 256 al 265 del resultat de multiplicar V3 per 2.0 són:\n");
PrintVect(V3_res, 0, 10);
PrintVect(V3_res, 256, 10);

printf("\n");
printf("\n");

//PRINT EXERCICI 9
printf("  ___ ___  ___  ___ _    ___ __  __   _     ___ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   / _ \\\n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\  \\_, /\n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\  /_/ \n");
printf("                                                \n");

float V2_projection_V3[N], V1_projection_V2[N];

Projection(V2, V3, V2_projection_V3);
Projection(V1, V2, V1_projection_V2);

printf("Els elements 0 a 9 del resultat de la projecció de V2 sobre V3 són:\n");
PrintVect(V2_projection_V3, 0, 10);

printf("Els elements 0 a 9 del resultat de la projecció de V1 sobre V2 són:\n");
PrintVect(V1_projection_V2, 0, 10);


printf("\n");
printf("\n");

//PRINT EXERCICI 10
printf("  ___ ___  ___  ___ _    ___ __  __   _     _  __  \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   / |/  \\ \n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\  | | () |\n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\ |_|\__/ \n");
printf("                                                    \n");

float Mat_V2_res[N];
Matriu_x_Vector(Mat, V2, Mat_V2_res);

printf("Els elements 0 a 9 del resultat de la multiplicació de Mat per V2 són:\n");
PrintVect(Mat_V2_res, 0, 10);


//PRINT EXERCICI 11
printf("  ___ ___  ___  ___ _    ___ __  __   _     _ _ \n");
printf(" | _ \\ _ \\/ _ \\| _ ) |  | __|  \\/  | /_\\   / / |\n");
printf(" |  _/   / (_) | _ \\ |__| _|| |\\/| |/ _ \\  | | |\n");
printf(" |_| |_|_\\\\___/|___/____|___|_|  |_/_/ \\_\\ |_|_|\n");
printf("                                                 \n");

float X_1_iter[N], X_1000_iter[N];
if (Jacobi(MatDD, V3, X_1_iter, 1)) {
    printf("Els elements 0 a 9 de la solució (1 iter) del sistema d'equacions són:\n");
    PrintVect(X_1_iter, 0, 10);
}
if (Jacobi(MatDD, V3, X_1000_iter, 1000)) {
    printf("Els elements 0 a 9 de la solució (1000 iters) del sistema d'equacions són:\n");
    PrintVect(X_1000_iter, 0, 10);
}
if (!DiagonalDom(MatDD)) {
    printf("La matriu MatDD no és diagonal dominant, no es pot aplicar Jacobi\n");
}

printf("\n");
printf("\n");

printf("  ___ ___   ___  ___ _      ___ ___  ___   ___ ___    _   __  __   _   \n");
printf(" | __|_ _| |   \\| __| |    | _ \\ _ \\/ _ \\ / __| _ \\  /_\\ |  \\/  | /_\\  \n");
printf(" | _| | |  | |) | _|| |__  |  _/   / (_) | (_ |   / / _ \\| |\\/| |/ _ \\ \n");
printf(" |_| |___| |___/|___|____| |_| |_|_\\\\___/ \\___|_|_\\/_/ \\_\\_|  |_/_/ \\_\\ \n");


}
