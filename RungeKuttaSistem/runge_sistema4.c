#include <stdio.h>
#include <stdlib.h>

double f1(double x, double y);
double f2(double x, double y);
double k1(double xk, double yk, int funcao);
double k2(double xk, double yk, double h, int funcao);
double k3(double xk, double yk, double h, int funcao);
double k4(double xk, double yk, double h, int funcao);

int main(void){
    int n;
    double h;    

    printf("Digite a quantidade de pontos: ");
    scanf("%d", &n);

    double * x = (double *) calloc(n, sizeof(double));
    double * y1 = (double *) calloc(n, sizeof(double));
    double * y2 = (double *) calloc(n, sizeof(double));

    while(n <= 0){
        printf("Digite a quantidade de pontos: ");
        scanf("%d", &n);
    }

    printf("Digite o valor inicial de x: ");
    scanf("%lf", &x[0]);
    printf("Digite o valor final de x: ");
    scanf("%lf", &x[n-1]);
    printf("Digite o valor inicial de y1: ");
    scanf("%lf", &y1[0]);
    printf("Digite o valor inicial de y2: ");
    scanf("%lf", &y2[0]);

    h = (x[n-1]-x[0])/n;

    for(int i=0; i<n-1;i++){

        y1[i+1] = y1[i] + (h/6)*(k1(x[i], y1[i], 1) + 2*k2(x[i], y1[i], h, 1) + 2*k3(x[i], y1[i], h, 1) + k4(x[i], y1[i], h, 1));
        y2[i+1] = y2[i] + (h/6)*(k1(x[i], y2[i], 2) + 2*k2(x[i], y2[i], h, 2) + 2*k3(x[i], y2[i], h, 2) + k4(x[i], y2[i], h, 2));
        x[i+1] = x[i] + h;
    }

    FILE * arquivo;

    arquivo = fopen("funcao.tsv", "w");

    if(arquivo == NULL){
        printf("ERRO: Não foi possível abrir o arquivo\n");
        return 1;
    }
    
    printf("X\tY1\tY2\n");
    fprintf(arquivo,"X\tY1\tY2\n");
    for(int i=0;i<n;i++){
        fprintf(arquivo,"%lf\t%lf\t%lf\n", x[i], y1[i], y2[i]);
        printf("%lf\t%lf\t%lf\n", x[i], y1[i],y2[i]);
    }
    printf("Arquivo salvo com sucesso!");
    free(x);
    free(y1);
    free(y2);

    //system("pause");
    return 0;
}

double f1(double x, double y){
    return y;
}

double f2(double x, double y){
    return 2*y;
}

double k1(double xk, double yk, int funcao){
    if(funcao == 1){
        return f1(xk, yk);
    }else{
        return f2(xk, yk);
    }
}   

double k2(double xk, double yk, double h, int funcao){
    if(funcao == 1){
        return f1(xk + (h/2), yk + k1(xk, yk, 1)*(h/2));
    }else{
        return f2(xk + (h/2), yk + k1(xk, yk, 2)*(h/2));
    }
}

double k3(double xk, double yk, double h, int funcao){
    if(funcao == 1){
        return f1(xk + (h/2), yk + k2(xk, yk, h,1)*(h/2));
    }else{
        return f2(xk + (h/2), yk + k2(xk, yk, h,2)*(h/2));
    }
}

double k4(double xk, double yk, double h, int funcao){
    if(funcao == 1){
        return f1(xk + h, yk + k3(xk, yk, h, 1)*h);
    }else{
        return f2(xk + h, yk + k3(xk, yk, h, 2)*h);
    }
}