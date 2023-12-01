#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Vertice
{
    int vertice;
    int peso;
    struct Vertice *conexao;
} Vertice;

typedef struct Antecedente
{
    int vertice;
    int anterior;
    int distancia;
    bool aberto;
} Antecedente;

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
    int v1 = -1, v2 = -1, peso;
    do
    {
        printf("\nInsira os vértices: ");
        scanf("%d %d", &v1, &v2);
        printf("Insira o peso: ");
        scanf("%d", &peso);

        if (v1 < 0 || v1 > n - 1 || v2 < 0 || v2 > n - 1)
        {
            printf("Valores inválidos!\n");
        }
    } while (v1 < 0 || v1 > n - 1 || v2 < 0 || v2 > n - 1);

    Vertice *novoVertice = (Vertice *)malloc(sizeof(Vertice));
    novoVertice->peso = peso;
    novoVertice->vertice = v2;
    novoVertice->conexao = NULL;

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
        if (cabecas[i] != NULL)
        {
            imprimir = cabecas[i];
            printf("\n |%d|", i);

            while (imprimir->conexao != NULL)
            {
                imprimir = imprimir->conexao;
                printf("-> |%d|%d|", imprimir->vertice, imprimir->peso);
            }

            printf("\n");
        }
    }
}

void sair(Vertice **cabecas, int n)
{
    for (int i = 0; i < n; i++)
    {
        Vertice *atual = cabecas[i];
        while (atual != NULL)
        {
            Vertice *prox = atual->conexao;
            free(atual);
            atual = prox;
        }
        cabecas[i] = NULL;
    }

    free(cabecas);
    exit(0);
}

Antecedente *iniDijkstra(Vertice **cabecas, int n, int partida)
{
    Antecedente *antecedente = (Antecedente *)malloc(sizeof(Antecedente) * n);

    for (int i = 0; i < n; i++)
    {
        antecedente[i].distancia = INT_MAX / 2;
        antecedente[i].anterior = -1;
        antecedente[i].aberto = true;
    }

    antecedente[partida].distancia = 0;

    return antecedente;
}

bool aberto(Antecedente *antecedente, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (antecedente[i].aberto == true && antecedente[i].distancia < INT_MAX / 2)
        {
            return true;
        }
    }

    return false;
}

int menorDist(Antecedente *antecedente, int n)
{
    int index, menorDist = INT_MAX / 2;

    for (int i = 0; i < n; i++)
    {
        if (antecedente[i].aberto == true && antecedente[i].distancia < menorDist)
        {
            menorDist = antecedente[i].distancia;
            index = i;
        }
    }

    return index;
}

void imprimirCaminho(Antecedente *antecedente, int destino)
{
    if (antecedente[destino].anterior != -1)
    {
        imprimirCaminho(antecedente, antecedente[destino].anterior);
        printf("-> ");
    }
    printf("%d ", destino);
}

void dijkstra(Vertice **cabecas, int n)
{
    int partida;

    do
    {
        printf("\nInsira o vértice de partida: ");
        scanf("%d", &partida);
    } while (partida < 0 || partida >= n);

    Antecedente *antecedente = iniDijkstra(cabecas, n, partida);

    Vertice *vertice;
    int menorEst;

    while (aberto(antecedente, n))
    {
        menorEst = menorDist(antecedente, n);
        antecedente[menorEst].aberto = false;

        vertice = cabecas[menorEst]->conexao;

        while (vertice != NULL)
        {
            int v = vertice->vertice;

            if (antecedente[v].aberto && antecedente[menorEst].distancia + vertice->peso < antecedente[v].distancia)
            {
                antecedente[v].anterior = menorEst;
                antecedente[v].distancia = antecedente[menorEst].distancia + vertice->peso;
            }

            vertice = vertice->conexao;
        }
    }

    for (int i = 0; i < n; i++)
    {

        printf("\n%d %d %d \t Caminho: ", antecedente[i].vertice,
               antecedente[i].distancia,
               antecedente[i].anterior);

        if (antecedente[i].distancia < INT_MAX / 2)
        {
            imprimirCaminho(antecedente, i);
        }
        else
        {
            printf("Sem caminho");
        }

        printf("\n");
    }

    free(antecedente);
    return;
}

int main()
{
    int menu = 0, n = -1;

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
            printf("3. Algoritmo de Dijkstra\n");
            printf("4. Limpar e Sair\n");
            scanf("%d", &menu);
        } while (menu < 1 || menu > 4);

        switch (menu)
        {
        case 1:
            lerAresta(cabecas, n);
            break;
        case 2:
            imprimirGrafo(cabecas, n);
            break;
        case 3:
            dijkstra(cabecas, n);
            break;
        case 4:
            sair(cabecas, n);
            break;
        }
    }

    return 0;
}