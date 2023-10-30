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

void lerAresta(Vertice **cabecas)
{
    int v1, v2, peso;

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
    criaCabecas(4);
}
