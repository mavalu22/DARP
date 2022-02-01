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
    solucao x, y;
    int i, j;

    srand(time(NULL));
    // lerDados();
    // printMatriz(matrizTempDeslocamento);
    lerSolucao(x);
    // printf("%d %d", x.FO, x.qntdVeiculos);
    // clonarSolucao(x, y);
    // printf("%d %d", y.FO, y.qntdVeiculos);
    // printf("%d ", x.veiculos[2].reqAtendidas);
    // printf("%d ", x.veiculos[2].id);

    for (size_t i = 0; i < x.qntdVeiculos; i++)
    {
        for (size_t j = 0; j < (x.veiculos[i].reqAtendidas * 2) + 2; j++)
        {
            printf("%d ", x.veiculos[i].idLocaisAtendidos[j]);
        }
        printf("\n");
    }

    // printOutroVetor(x.veiculos[0].idLocaisAtendidos);
}

void lerDados()
{

    FILE *f = fopen("darp1.txt", "r");

    fscanf(f, "%d %d %d %d %d", &lixo, &requisicoes, &duracaoMaxRota, &tempMaxViagem, &tempMaxEspera);

    locais = (requisicoes * 2) + 2;

    for (int i = 0; i < VEICULOS; i++)
    {
        fscanf(f, "%d", &capacidadeVeic[i]);
    }

    for (int i = 0; i < locais; i++)
    {
        fscanf(f, "%d", &numAssentosLocal[i]);
    }

    for (int i = 0; i < locais; i++)
    {
        fscanf(f, "%d", &tempServico[i]);
    }

    for (int i = 0; i < locais; i++)
    {
        fscanf(f, "%d", &inicioJanelaTemp[i]);
    }

    for (int i = 0; i < locais; i++)
    {
        fscanf(f, "%d", &fimJanelaTemp[i]);
    }
    for (int i = 0; i < locais; i++)
    {
        for (int j = 0; j < locais; j++)
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

void printOutroVetor(int vet[])
{
    for (int i = 0; i < locais; i++)
    {
        printf("%d \t", vet[i]);
    }
}

void printMatriz(int matriz[MAX_REQ][MAX_REQ])
{
    for (int i = 0; i < locais; i++)
    {
        for (int j = 0; j < locais; j++)
        {
            printf("%d \t", matriz[i][j]);
        }
    }
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
    veiculosUsados[id] = 1; // lembrar de zerar esse vetor na main
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
    int i = 0, j = 0, locaisAt;

    memset(&solucao.veiculos, 0, sizeof(solucao.veiculos));
    memset(&solucao.veiculos->idLocaisAtendidos, 0, sizeof(solucao.veiculos->idLocaisAtendidos));
    FILE *f = fopen("test.txt", "r");
    fscanf(f, "%d %d", &solucao.FO, &solucao.qntdVeiculos);
    // printf("%d %d", solucao.FO, solucao.qntdVeiculos);
    while (j < solucao.qntdVeiculos)
    {
        // printf("teste");

        fscanf(f, "%d", &solucao.veiculos[j].id);
        fscanf(f, "%d", &solucao.veiculos[j].reqAtendidas);
        locaisAt = (solucao.veiculos[j].reqAtendidas * 2) + 2;
        for (i = 0; i < locaisAt; i++)
        {
            // printf("teste");
            fscanf(f, "%d", &solucao.veiculos[j].idLocaisAtendidos[i]);
        }
        j++;
    }
    fclose(f);
}

void clonarSolucao(solucao &original, solucao &nova)
{
    memcpy(&nova, &original, sizeof(original));
}

void calcularFO(solucao &solucao)
{
    int distancia = 0;
    solucao.FO = 10 * solucao.qntdVeiculos;

    for (int i = 0; i < solucao.qntdVeiculos; i++)
    {
        distancia += solucao.veiculos[i].infoVeiculo.durRota;
    }

    solucao.FO = distancia;
}

void verificaPenalidade(solucao &solucao)
{
    for (int i = 0; i < solucao.qntdVeiculos; i++)
    {
        verificaDuracaoRota(solucao);
        verificaDuracaoViagem(solucao);
        verificaTempEspera(solucao);
    }
}

void verificaDuracaoRota(solucao &solucao)
{
    for (int i = 0; i < solucao.qntdVeiculos; i++)
    {
        if (solucao.veiculos[i].infoVeiculo.durRota > duracaoMaxRota)
        {
            totalRestricoes.violDurRota += 1;
            solucao.veiculos[i].infoVeiculo.violDurRota += 1;
        }
    }
}

void verificaDuracaoViagem(solucao &solucao)
{
    for (int i = 0; i < solucao.qntdVeiculos; i++)
    {
        if (solucao.veiculos[i].infoVeiculo.durTotalViagem > tempMaxViagem)
        {
            totalRestricoes.violDurViagem += 1;
            solucao.veiculos[i].infoVeiculo.violDurViagem += 1;
        }
    }
}

void verificaTempEspera(solucao &solucao)
{
    for (int i = 0; i < solucao.qntdVeiculos; i++)
    {
        if (solucao.veiculos[i].infoVeiculo.tempTotalEspera > tempMaxEspera)
        {
            totalRestricoes.violTempEsp += 1;
            solucao.veiculos[i].infoVeiculo.violTempEsp += 1;
        }
    }
}

void verificaHoraChegada(solucao &solucao)
{
    for (int i = 0; i < solucao.qntdVeiculos; i++)
    {
        if (solucao.veiculos[i].infoVeiculo.horario > tempMaxEspera)
        {
            totalRestricoes.violChegada += 1;
            solucao.veiculos[i].infoVeiculo.violChegada += 1;
        }
    }
}

void construtivaAleatoria(solucao &solucao)
{
    int requisicao, idOnibus;
    requisicao = (MAX_REQ - 2) / 2;
    for (int i = 0; i < requisicao; i++)
    {
        idOnibus = rand() % 6;
        requisicaoSolucao[i] = idOnibus;
        requisicaoSolucao[i + 20] = idOnibus;
        solucao.veiculos[idOnibus].reqAtendidas;
    }
}

void solucaoCompleta(solucao &solucao)
{
    int i, j, k;
    // - Número de requisições atendidas.
    // - Função objetivo do veículo.
    // - Sequência de locais que formam a rota do veículo.
    lerSolucao(solucao);
    for (i = 0; i < VEICULOS; i++)
    {
        // solucao.veiculos[i].veiculo.horario = 360;
        //  - Número máximo de assentos utilizados.
        solucao.veiculos[i].infoVeiculo.vaga = capacidadeVeic[i];
        solucao.veiculos[i].infoVeiculo.durRota = 0;
        for (j = 0; j < VEICULOS - 1; j++)
        {
            // - Duração da rota.
            solucao.veiculos[i].infoVeiculo.durRota += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[j]][solucao.veiculos[i].idLocaisAtendidos[j + 1]];
        }
        for (j = 0; j < solucao.veiculos[i].reqAtendidas; j++)
        {
            for (k = j + 1; k < solucao.veiculos[i].reqAtendidas + j + 1; k++)
            {
                // - Tempo de viagem das PPNEs atendidas.
                solucao.veiculos[i].infoVeiculo.passageiros[j].tempoViagem += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[k]][solucao.veiculos[i].idLocaisAtendidos[k + 1]];
            }
        }
    }
}

// - Tempo de espera das PPNEs atendidas e as violações das restrições (texto em itálico, porém de forma individual por veículo).

// void heuConAle(Solucao &s)
// {
//     for(int j = 0; j < numObj; j++)
//         s.vetIdMocObj[j] = (rand()%(numMoc+1)) - 1;
// }