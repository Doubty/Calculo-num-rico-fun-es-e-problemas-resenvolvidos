#include <stdio.h>
#include <stdlib.h>

double f(double x, double y);
double k1(double xk, double yk);
double k2(double xk, double yk, double h);

int main(void){
    int n;
    double h;    

    printf("Digite a quantidade de pontos: ");
    scanf("%d", &n);

    double * x = (double *) calloc(n, sizeof(double));
    double * y = (double *) calloc(n, sizeof(double));

    while(n<=0){
    printf("Digite a quantidade de pontos: ");
    scanf("%d", &n);
    }

    printf("Digite o valor inicial de x: ");
    scanf("%lf", &x[0]);
    printf("Digite o valor final de x: ");
    scanf("%lf", &x[n]);
    printf("Digite o valor inicial de y: ");
    scanf("%lf", &y[0]);

    h = (x[n]-x[0])/n;

    for(int i=0; i<n-1;i++){

        y[i+1] = y[i] + (h/2)*(k1(x[i], y[i]) + k2(x[i], y[i], h));

        x[i+1] = x[i] + h;
    }

    FILE * arquivo;

    arquivo = fopen("funcao.tsv", "w");

    if(arquivo == NULL){
        printf("ERRO: Não foi possível abrir o arquivo\n");
        return 1;
    }
    
    printf("X\tY\n");
    fprintf(arquivo,"X\tY\n");
    for(int i=0;i<n;i++){
        fprintf(arquivo,"%lf\t%lf\n", x[i], y[i]);
        printf("%lf\t%lf\n", x[i], y[i]);
    }
    printf("Arquivo salvo com sucesso!");
    free(x);
    free(y);

    //system("pause");
    return 0;
}

double f(double x, double y){
    return x;
}

double k1(double xk, double yk){
    return f(xk, yk);
}

double k2(double xk, double yk, double h){
    return f(xk + h, yk + h*k1(xk, yk));
}
