#include <stdio.h>
#include <stdlib.h>

int main(void){

    //Quantidade de pontos
    int n;
    printf("Digite a quantidade de pontos de entrada: ");
    scanf("%d", &n);

    //Valores de X, Y e L
    double * x = (double *) calloc(n, sizeof(double));
    double * y = (double *) calloc(n, sizeof(double));
    double * L = (double *) calloc(n, sizeof(double));

    //Preenche os valores de entrada
    printf("Digite o valor de x e y, respectivamente: \n");
    for(int i = 0; i < n; i++){
        printf("x%d e y%d\n", i, i);
        scanf("%lf %lf", &x[i], &y[i]);
    }

    double xi, yi = 0;
    //O valor à ser interpolado
    printf("Digite o valor de X a ser interpolado: ");
    scanf("%lf", &xi);
    
    for(int i=0; i<n;i++){
        L[i]=1;
        for(int j=0;j<n;j++){
            if(j!=i){
                L[i]=L[i]*((xi-x[j])/(x[i]-x[j]));
            }

        }
        yi=yi + L[i]*y[i];

    }

    printf("O valor de para %lf interpolado é: %lf", xi, yi);

    free(x);
    free(y);
    free(L);
    return 0;
}