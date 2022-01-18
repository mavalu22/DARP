#include <iostream>
#include <time.h>
#include <cstring>
#include <memory.h>
#include <math.h>
#include "darp.hpp"

using namespace std;

#define MAX(X, Y) ((X > Y) ? X : Y)

int main(int argc, const char *argv[])
{

    string instancia = "";

    lerDados();
    printMatriz(matrizTempDeslocamento);
}

void lerDados()
{

    FILE *f = fopen("darp1.txt", "r");

    fscanf(f, "%d %d %d %d %d", &lixo, &requisicoes, &duracaoMaxRota, &tempMaxViagem, &tempMaxEspera);

    requisicoes = (requisicoes * 2) + 2;

    for (int i = 0; i < VEICULOS; i++)
    {
        fscanf(f, "%d", &capacidadeVeic[i]);
    }

    for (int i = 0; i < requisicoes; i++)
    {
        fscanf(f, "%d", &numAssentosLocal[i]);
    }

    for (int i = 0; i < requisicoes; i++)
    {
        fscanf(f, "%d", &tempServico[i]);
    }

    for (int i = 0; i < requisicoes; i++)
    {
        fscanf(f, "%d", &inicioJanelaTemp[i]);
    }

    for (int i = 0; i < requisicoes; i++)
    {
        fscanf(f, "%d", &fimJanelaTemp[i]);
    }
    for (int i = 0; i < requisicoes; i++)
    {
        for (int j = 0; j < requisicoes; j++)
        {
            fscanf(f, "%d", &matrizTempDeslocamento[i][j]);
            // printf("%d %d\n", i, j);
        }
    }
    fclose(f);
}

void printVetor(int vet[VEICULOS])
{
    for (int i = 0; i < VEICULOS; i++)
    {
        printf("%d \t", vet[i]);
    }
}

void printOutroVetor(int vet[MAX_REQ])
{
    for (int i = 0; i < requisicoes; i++)
    {
        printf("%d \t", vet[i]);
    }
}

void printMatriz(int matriz[MAX_REQ][MAX_REQ])
{
    for (int i = 0; i < requisicoes; i++)
    {
        for (int j = 0; j < requisicoes; j++)
        {
            printf("%d \t", matriz[i][j]);
        }
    }
}