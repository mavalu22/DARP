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
    solucao x;
    // lerDados();
    // printMatriz(matrizTempDeslocamento);
    lerSolucao(x);
    printf("%d %d", x.FO, x.qntdVeiculos);
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

void clonarSolucao(solucao &original, solucao &clone)
{
    memcpy(&clone, &original, sizeof(original));
}
// https://github.com/eloy-freitas/PRCP/blob/master/main.cpp

void construtivaAleatoria()
{
    for (int i = 0; i < requisicoes; i++)
    {
        requisicaoSolucao[i] = rand() % VEICULOS;
        contaVeiculosUsados(requisicaoSolucao[i]);
    }
}

void contaVeiculosUsados(int id)
{
    veiculosUsados[id] = 1; //lembrar de zerar esse vetor na main
}

int verificaVeiculosUsados()
{
    int total = 0;

    for (int i = 0; i < VEICULOS; i++)
        total += veiculosUsados[i];

    return total;
}

void lerSolucao(solucao &solucao)
{
    int i = 0, j = 0;

    memset(&solucao.veiculos, 0, sizeof(solucao.veiculos));
    memset(&solucao.veiculos->idLocaisAtendidos, 0, sizeof(solucao.veiculos->idLocaisAtendidos));

    FILE *f = fopen("teste.txt", "r");
    fscanf(f, "%d %d", &solucao.FO, &solucao.qntdVeiculos);
    while (not EOF and j < solucao.qntdVeiculos)
    {
        fscanf(f, "%d", &solucao.veiculos[j].id);
        fscanf(f, "%d", &solucao.veiculos[j].reqAtendidas);
        locais = (solucao.veiculos->reqAtendidas) * 2 + 2;
        for (i = 0; i < locais; i++)
        {
            fscanf(f, "%d", &solucao.veiculos->idLocaisAtendidos[i]);
        }
        j++;
    }
    fclose(f);
}

void calcularFO(solucao &solucao)
{
    int distancia;
    solucao.FO = 10 * solucao.qntdVeiculos;

    for (int i = 0; i < solucao.qntdVeiculos; i++)
    {
        distancia = infoVeiculo[i].durRota;
    }

    solucao.FO += distancia;
}
