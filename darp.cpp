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

// void construtivaAleatoria()
// {
//     for (int i = 0; i < requisicoes; i++)
//     {
//         requisicaoSolucao[i] = rand() % VEICULOS;
//         contaVeiculosUsados(requisicaoSolucao[i]);
//     }
// }

// void contaVeiculosUsados(int id)
// {
//     veiculosUsados[id] = 1; // lembrar de zerar esse vetor na main
// }

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
    int idOnibus;

    for (int i = 0; i < requisicoes; i++)
    {
        idOnibus = rand() % 6;
        solucao.veiculos[idOnibus].reqAtendidas += 1;
        solucao.veiculos[idOnibus].idLocaisAtendidos[solucao.veiculos[idOnibus].reqAtendidas - 1] = i;
        solucao.veiculos[idOnibus].reqAtendidas += 1;
        solucao.veiculos[idOnibus].idLocaisAtendidos[solucao.veiculos[idOnibus].reqAtendidas - 1] = requisicoes + i;
    }
}

// - Duração da rota.
// - Número máximo de assentos utilizados.
// - Número de violações no número de assentos dos veículos.

void durRota(solucao &solucao)
{
    int i, j, k, numMaximoAssentos = 0, numAtualAssentos = 0;
    for (i = 0; i < solucao.qntdVeiculos; i++)
    {
        for (j = 0; j < ((solucao.veiculos[i].reqAtendidas) * 2) + 1; j++)
        {
            numAtualAssentos = numAssentosLocal[j];
            numMaximoAssentos = MAX(numAtualAssentos, numMaximoAssentos);
            if (numAtualAssentos > capacidadeVeic[i])
            {
                solucao.veiculos[i].infoVeiculo.violAssentos += 1;
            }
            durViagem(solucao, i, solucao.veiculos[i].idLocaisAtendidos[j], solucao.veiculos[i].infoVeiculo.horario);
            solucao.veiculos[i].infoVeiculo.durRota += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[j]][solucao.veiculos[i].idLocaisAtendidos[j + 1]] + tempServico[solucao.veiculos[i].idLocaisAtendidos[j + 1]];
            solucao.veiculos[i].infoVeiculo.horario += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[j]][solucao.veiculos[i].idLocaisAtendidos[j + 1]] + tempServico[solucao.veiculos[i].idLocaisAtendidos[j + 1]];
            solucao.veiculos[i].infoVeiculo.distanciaViagem += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[j]][solucao.veiculos[i].idLocaisAtendidos[j + 1]] + tempServico[solucao.veiculos[i].idLocaisAtendidos[j + 1]];
            if (solucao.veiculos[i].infoVeiculo.horario < inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j + 1]])
            {
                solucao.veiculos[i].infoVeiculo.horario += (inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j + 1]] - solucao.veiculos[i].infoVeiculo.horario);
                solucao.veiculos[i].infoVeiculo.durRota += (inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j + 1]] - solucao.veiculos[i].infoVeiculo.horario);
            }
            if (solucao.veiculos[i].infoVeiculo.horario > fimJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j + 1]])
            {
                solucao.veiculos[i].infoVeiculo.violChegada += 1;
            }
        }
        if (solucao.veiculos[i].infoVeiculo.horario > fimJanelaTemp[0])
        {
            solucao.veiculos[i].infoVeiculo.violChegada += 1;
        }
        if (solucao.veiculos[i].infoVeiculo.durRota > duracaoMaxRota)
        {
            solucao.veiculos[i].infoVeiculo.violDurRota += 1;
        }
    }
}

void durViagem(solucao &solucao, int i, int idLocal, int horario)
{
    if (idLocal <= requisicoes)
    {
        solucao.veiculos[i].infoVeiculo.passageiros[idLocal].horarioEntrada = horario;
    }
    else
    {
        solucao.veiculos[i].infoVeiculo.passageiros[idLocal - requisicoes].tempoViagem = horario - solucao.veiculos[i].infoVeiculo.passageiros[idLocal].horarioEntrada;
        if (solucao.veiculos[i].infoVeiculo.passageiros[idLocal - requisicoes].tempoViagem > tempMaxViagem)
        {
            solucao.veiculos[i].infoVeiculo.violDurViagem += 1;
        }
    }

    // int k, j;
    // for (i = 0; i < solucao.qntdVeiculos; i++)
    // {
    //     solucao.veiculos[i].infoVeiculo.horario = inicioJanelaTemp[0];
    //     // - Número de violações na duração máxima das rotas

    //     for (j = 0; j < solucao.veiculos[i].reqAtendidas; j++)
    //     {
    //         for (k = j + 1; k < solucao.veiculos[i].reqAtendidas + j + 1; k++)
    //         {
    //             // - Tempo de viagem das PPNEs atendidas.
    //             solucao.veiculos[i].infoVeiculo.passageiros[j].tempoViagem += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[k]][solucao.veiculos[i].idLocaisAtendidos[k + 1]];
    //         }
    //         if (solucao.veiculos[i].infoVeiculo.passageiros[j].tempoViagem > tempMaxViagem)
    //         {
    //             // -Número de violações no tempo máximo de viagem de todas as PPNEs
    //             solucao.veiculos[i].infoVeiculo.violDurViagem += 1;
    //         }
    //     }
    // }
}
// void()
// {
//     int i, j, k;
// }
// void()
// {
//     int i, j, k;
// }

void solucaoCompleta(solucao &solucao)
{
    int i, j, k;
    // - Número de requisições atendidas.
    // - Função objetivo do veículo.
    // - Sequência de locais que formam a rota do veículo.
    // - Número de veículos usados.
    // - Valor da função objetivo da
    // solução.
    lerSolucao(solucao);
    durRota(solucao);
    //durViagem(solucao);
}

// Lembrar de zerar todos os vetores na main
// - Número de veículos usados. OK
// - Valor da função objetivo da
// solução. OK
// - Distância percorrida por todos os veículos. (Falta somar)
// - Duração das rotas de todos os veículos. (Falta somar)
// - Tempo total de viagem de todas as PPNEs. (Falta somar)
// - Tempo total de espera de todas as PPNEs.
// - Número de violações no número de assentos dos veículos. OK
// - Número de violações na duração máxima das rotas. OK
// - Número de violações no tempo máximo de viagem de todas as PPNEs. OK
// - Número de violações no tempo máximo de espera de todas as PPNEs.
// - Número de violações nos horários de saída e chegada dos veículos nas garagens.

// Para cada Veículo:

//     - Número de requisições atendidas. OK
//     - Número máximo de assentos utilizados. OK
//     - Duração da rota. OK
//     - Tempo de viagem das PPNEs atendidas. OK
//     - Tempo de espera das PPNEs atendidas e as violações das restrições (texto em itálico, porém de forma individual por veículo).
//     - Função objetivo do veículo. OK
//     - Sequência de locais que formam a rota do veículo. OK
