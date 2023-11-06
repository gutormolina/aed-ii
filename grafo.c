#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice
{
    int vertice;
    int peso;
    struct Vertice *conexao;
} Vertice;

Vertice **criaCabecas(int n) 
{
    Vertice **cabecas = (Vertice **)malloc(sizeof(Vertice *) * n);

    for (int i = 0; i < n; i++)
    {
        cabecas[i] = (Vertice *)malloc(sizeof(Vertice));
        cabecas[i]->vertice = i;
        cabecas[i]->peso = 0;
        cabecas[i]->conexao = NULL;
    }
    
    return cabecas;
}

void lerAresta(Vertice **cabecas, int n)
{
    int v1, v2, peso;

    do
    {
        printf("Insira os vértices: ");
        scanf("%d %d", &v1, &v2);
        printf("Insira o peso: ");
        scanf("%d", &peso);

        if (v1 < 0 || v1 > n || v2 < 0 || v2 > n)
        {
            printf("Valores inválidos!\n");
        }
    } while (v1 < 0 || v1 > n || v2 < 0 || v2 > n);

    Vertice *novoVertice = (Vertice *)malloc(sizeof(Vertice));
    novoVertice->peso = peso;
    novoVertice->vertice = v2;

    Vertice *aux = cabecas[v1];
    
    while (aux->conexao != NULL)
    {
        aux = aux->conexao;
    }

    aux->conexao = novoVertice;
}

void imprimirGrafo(Vertice **cabecas, int n)
{
    Vertice *imprimir;

    for (int i = 0; i < n; i++)
    {
        imprimir = cabecas[i];
        printf("\n |%d|->", i);

        while (imprimir->conexao != NULL)
        {
            imprimir = imprimir->conexao;
            printf(" |%d|%d|->", imprimir->vertice, imprimir->peso);
        }
        
        printf("\n");
    }
    
}

int main()
{
    int menu, n;
    
    do
    {
        printf("Insira o número de vértices do grafo: ");
        scanf("%d", &n);
    } while (n < 0 || n > 19);
    
    Vertice **cabecas = criaCabecas(n);

    for (;;)
    {
        do
        {
            printf("\n -- Menu -- \n");
            printf("1. Ler Aresta\n");
            printf("2. Imprimir Grafo\n");
            printf("3. Limpar e Sair\n");
            scanf("%d", &menu);
        } while (menu < 1 || menu > 3);

        switch (menu)
        {
            case 1:
                lerAresta(cabecas, n);
                break;
            case 2:
                imprimirGrafo(cabecas, n);
                break;
            case 3:
                //sair(cabecas, n);
                break;
        }
    }
    
    return 0;
}