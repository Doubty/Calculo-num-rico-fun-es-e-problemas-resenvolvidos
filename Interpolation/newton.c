#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{

    int num;
    printf("Digite a quantidade de pontos para interpolar: ");
    scanf("%d", &num);

    //Instancia um vetor de vetores com o número de iterações ou ordens
    double ** y = (double **)calloc(num, sizeof(double *));
    for (int i = 0; i < num; i++)
    {
        //Inicializa cada iteração com o número de valores que serão calculados
        y[i] = (double *)calloc(num - i, sizeof(double));
    }
    //Instancia um vetor para armazenar os valores de x
    double * x = (double *)calloc(num, sizeof(double));

    //Preenche os valores de x e os valores de y iniciais
    for (int i = 0; i < num; i++)
    {
        printf("Digite o valor de x%d e y%d, respectivamente: ", i, i);
        scanf("%lf %lf", &x[i], &y[0][i]);
    }

    //Calcula os valores das funções F[]
    
    //È importante inicializar da iteração 1, pois os valores de y[0] são os valores iniciais
    for (int i = 1; i < num; i++)
    {   
        //Percorre o número de funções dentro das iterações
        for (int j = 0; j < num - i; j++)
        {
            //A cada iteração, há um deslocamento no valor de x, por isso, j + i
            y[i][j] = (y[i - 1][j + 1] - y[i - 1][j])/(x[j + i] - x[j]);
        }
    }

    //Mostra o polinômio interpolador:
    printf("O polinômio interpolador é: \nP(x) = ");
    for (int i = 0; i < num; i++)
    {

        //Se o valor for positivo mostra sem parênteses
        if (y[i][0] > 0)
        {
            printf("%.2lf", y[i][0]);
        }
        else
        {
            printf("(%.2lf)", y[i][0]);
        }

        //Mostra os valores das diferenças de x - xn
        for (int j = 0; j < i; j++)
        {   
            //Se o valor for negativo, mostra o +
            if(x[j] < 0){
                //Utiliza o abs apenas para mostrar o número
                printf("(x+%.2lf)", abs(x[j]));
            }else if(x[j] == 0){
                //Se o valor de xn for 0, não precisa mostrá-lo
                printf("(x)");
            }else{
                //Mostra valores positivos normalmente
                printf("(x-%.2lf)", x[j]);
            }
        }

        //Enquanto não for a última iteração, realiza a soma de dn
        if (i < num - 1)
        {
            printf(" + ");
        }
    }

    //Limpa o buffer do teclado
    setbuf(stdin, NULL);
    int opt;

    //O usuário pode realizar a interpolação de um ponto ou finalizar o programa
    do
    {
        printf("\n\nSelecione uma opção: \n");
        printf("1- Interpolar um ponto\n");
        printf("2- Finalizar programa\n");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:
        {
            double pontoX;
            printf("\n\nDigite um ponto x: ");
            scanf("%lf", &pontoX);

            double resultado = 0;
            for (int i = 0; i < num; i++)
            {
                //Armazena o produto das diferenças
                double produtoDiferenca = 1;
                //Realiza a soma dos valores das diferenças (x-xn)
                for (int j = 0; j < i; j++)
                {
                    produtoDiferenca *= (pontoX - x[j]);
                }
                //Multiplica o produto da diferença pelo valor de dn: Ex d0, d1
                resultado += produtoDiferenca * y[i][0];
            }
            //Mostra o resultado da interpolação
            printf("P(%lf) = %lf\n\n", pontoX, resultado);
            break;
        }
        case 2:
            //Libera a memória alocada e finaliza o programa
            for (int i = 0; i < num; i++)
            {
                free(y[i]);
            }
            free(y);
            return 0;
        default:
            printf("Opção inválida\n");
            break;
        }
    } while (opt != '2');
}