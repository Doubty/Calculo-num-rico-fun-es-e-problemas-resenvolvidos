#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int boolean;
#define true 1
#define false 0

boolean verificar_linhas(double **matriz, int dimensao);
boolean verificar_colunas(double **matriz, int dimensao);
double testar_convergencia(double *x_anterior, double *x_proximo, int dimensao);
int main(void)
{
    int j,i;
    int dimA;
    printf("Digite a dimensão da matriz A: ");
    scanf("%d", &dimA);

    //Cria a matriz
    double **matriz_a = (double **)calloc(dimA, sizeof(double *));

    for (i = 0; i < dimA; i++)
    {
        matriz_a[i] = (double *)calloc(dimA, sizeof(double));
    }

    double *matriz_b = (double *)calloc(dimA, sizeof(double));
    double *x0 = (double *)calloc(dimA, sizeof(double));
    //Preenche a matriz A:
    printf("Preenchendo a matriz A:\n\n");
    for ( i = 0; i < dimA; i++)
    {
        printf("Preenchendo a linha %d\n", i + 1);
        for ( j = 0; j < dimA; j++)
        {
            printf("Elemento %d: ", j + 1);
            scanf("%lf", &matriz_a[i][j]);
        }
    }

    //Preenche a matriz B:
    printf("\n\nPreenchendo a matriz B:\n");
    for ( i = 0; i < dimA; i++)
    {
        printf("Elemento %d: ", i + 1);
        scanf("%lf", &matriz_b[i]);
    }

    //Verificar se é diagonal dominante
    //Verificando por linha:
    boolean teste = verificar_linhas(matriz_a, dimA);
    if (teste == false)
    {
        teste = verificar_linhas(matriz_a, dimA);
    }

    int num_ite = 0;
    if (teste == false)
    {
        printf("O método não converge pela verificação da diagonal dominante.\n");
        printf("Digite um número de iterações > 0 para aplicar o método mesmo assim: ");
        scanf("%d", &num_ite);

        if (num_ite <= 0)
        {
            return -1;
        }
    }

    double precisao;
    printf("\nDigite a precisão do método: ");
    scanf("%lf", &precisao);

    //Criando o valor x0 (inicial)
    for ( i = 0; i < dimA; i++)
    {
        x0[i] = matriz_b[i] / matriz_a[i][i];
    }

    //Criando vetor de iterações
    double *xk = (double *)calloc(dimA, sizeof(double));
    double *xt = (double *)calloc(dimA, sizeof(double));

    if (num_ite > 0)
    {

        for(num_ite; num_ite > 0; num_ite--){
            //Calcula os valores de xk
            for ( i = 0; i < dimA; i++)
            {
                double soma = matriz_b[i];
                for ( j = 0; j < dimA; j++)
                {
                    if (j != i)
                    {
                        soma -= x0[j] * matriz_a[i][j];
                    }
                }
                xk[i] = (1.0 / matriz_a[i][i]) * (soma);
            }

            for ( i = 0; i < dimA; i++)
            {
                xt[i] = x0[i];
                x0[i] = xk[i];
            }
        }

    }
    else
    {
        do
        {
            //Calcula os valores de xk
            for ( i = 0; i < dimA; i++)
            {
                double soma = matriz_b[i];
                for ( j = 0; j < dimA; j++)
                {
                    if (j != i)
                    {
                        soma -= x0[j] * matriz_a[i][j];
                    }
                }
                xk[i] = (1.0 / matriz_a[i][i]) * (soma);
            }

            for ( i = 0; i < dimA; i++)
            {
                xt[i] = x0[i];
                x0[i] = xk[i];
            }

        } while (testar_convergencia(xt, xk, dimA) > precisao);
    }

    //Mostra o resultado:
    printf("\n\nResultado: \n");
    for ( i = 0; i < dimA; i++)
    {
        printf("x%d = %lf\n", i, xk[i]);
    }

    //Libera a matriz
    for ( i = 0; i < dimA; i++)
    {
        free(matriz_a[i]);
    }
    free(matriz_a);
    free(matriz_b);
    free(x0);
    free(xk);
    free(xt);
    return 0;
}

boolean verificar_linhas(double **matriz, int dimensao)
{
      int j;
      int i;
    for ( i = 0; i < dimensao; i++)
    {
        int soma = 0;
        for ( j = 0; j < dimensao; j++)
        {
            if(i != j){
                soma += matriz[i][j];
            }
        }
        if (soma > matriz[i][i])
            return false;
    }
    return true;
}

boolean verificar_colunas(double **matriz, int dimensao)
{
       int i;
       int j;
    for ( i = 0; i < dimensao; i++)
    {
        int soma = 0;
        for ( j = 0; j < dimensao; j++)
        {
            if(i != j){
                soma += matriz[i][j];
            }
        }
        if (soma > matriz[i][i])
            return false;
    }
    return true;
}

double testar_convergencia(double *x_anterior, double *x_proximo, int dimensao)
{
    double maior_num = 0, maior_den = 0;
    int i;
    for ( i = 0; i < dimensao; i++)
    {
        if (abs(x_proximo[i] - x_anterior[i]) > maior_num)
        {
            maior_num = abs(x_proximo[i] - x_anterior[i]);
        }

        if (abs(x_proximo[i]) > maior_den)
        {
            maior_den = abs(x_proximo[i]);
        }
    }

    return maior_num / maior_den;
}
