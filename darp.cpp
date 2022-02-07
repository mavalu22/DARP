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
    int i, j, requisicoes=0;

    srand(time(NULL));
    lerDados();
    // printMatriz(matrizTempDeslocamento);
    lerDados();
    requisicoes = (locais - 2)/2;
    //lerSolucao(x);
    //bubble_sort();
    construtivaGulosa(x);
    x.veiculos[0].infoVeiculo.distanciaViagem = 0;
    x.veiculos[1].infoVeiculo.distanciaViagem = 0;
    x.veiculos[2].infoVeiculo.distanciaViagem = 0;
    // durRota(x);
    // clonarSolucao(x, y);
    // calcularFO(x);
    // printf("FO = %d", x.FO);


    // for (int i = 0; i < VEICULOS; i++)
    // {
    //     printf("Veiculo: %d\n", i);
    //     printf("Violacao assento: %d\n", x.veiculos[i].infoVeiculo.violAssentos);
    //     printf("Violacao Chegada: %d\n", x.veiculos[i].infoVeiculo.violChegada);
    //     printf("Violacao Duração da rota: %d\n", x.veiculos[i].infoVeiculo.violDurRota);
    //     printf("Violacao Duração da viagem: %d\n", x.veiculos[i].infoVeiculo.violDurViagem);
    //     // printf("%d--", inicioJanelaTemp[i].id);
    //     // printf("%d \t", inicioJanelaTemp[i].valor);
    //     printf("\n");
    // }

    
    for (int i = 0; i < VEICULOS; i++)
    {
        for(int j = 0; j < x.veiculos[i].reqAtendidas*2; j++) {
           printf("%d \t", x.veiculos[i].idLocaisAtendidos[j]);
        }
        printf("\n");
    }

    // impressão do tempo de viagem de cada passageiro
    // for (int i = 0; i < VEICULOS; i++)
    // {
    //     printf("Veiculo %d:\n", i);
    //     for(int j = 0; j < x.veiculos[i].reqAtendidas*2; j++){
    //         if(x.veiculos[i].idLocaisAtendidos[j] < requisicoes)
    //             printf("id:%d --- %d\n", x.veiculos[i].idLocaisAtendidos[j], x.veiculos[i].infoVeiculo.passageiros[x.veiculos[i].idLocaisAtendidos[j]].tempoViagem);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
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
        inicioJanelaTemp[i].id = i;
        fscanf(f, "%d", &inicioJanelaTemp[i].valor);
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
        locaisAt = (solucao.veiculos[j].reqAtendidas * 2);
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

void efetuaSomaRota(solucao &solucao, int i, int j)
{
    durViagem(solucao, i, solucao.veiculos[i].idLocaisAtendidos[j], solucao.veiculos[i].infoVeiculo.horario);
    solucao.veiculos[i].infoVeiculo.durRota += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[j]][solucao.veiculos[i].idLocaisAtendidos[j + 1]] + tempServico[solucao.veiculos[i].idLocaisAtendidos[j + 1]];
    solucao.veiculos[i].infoVeiculo.horario += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[j]][solucao.veiculos[i].idLocaisAtendidos[j + 1]] + tempServico[solucao.veiculos[i].idLocaisAtendidos[j + 1]];
    solucao.veiculos[i].infoVeiculo.distanciaViagem += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[j]][solucao.veiculos[i].idLocaisAtendidos[j + 1]];
    if (solucao.veiculos[i].infoVeiculo.horario < inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j + 1]].valor)
    {
        solucao.veiculos[i].infoVeiculo.horario += (inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j + 1]].valor - solucao.veiculos[i].infoVeiculo.horario);
        solucao.veiculos[i].infoVeiculo.durRota += (inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j + 1]].valor - solucao.veiculos[i].infoVeiculo.horario);
    }
    if (solucao.veiculos[i].infoVeiculo.horario > fimJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j + 1]])
    {
        solucao.veiculos[i].infoVeiculo.violChegada += 1;
    }    
}

void efetuaSomaGaragemSaida(solucao &solucao, int i, int j)
{
    solucao.veiculos[i].infoVeiculo.durRota += matrizTempDeslocamento[0][solucao.veiculos[i].idLocaisAtendidos[j]] + tempServico[solucao.veiculos[i].idLocaisAtendidos[j]];
    solucao.veiculos[i].infoVeiculo.horario += matrizTempDeslocamento[0][solucao.veiculos[i].idLocaisAtendidos[j]] + tempServico[solucao.veiculos[i].idLocaisAtendidos[j]];
    solucao.veiculos[i].infoVeiculo.distanciaViagem += matrizTempDeslocamento[0][solucao.veiculos[i].idLocaisAtendidos[j]];
    if (solucao.veiculos[i].infoVeiculo.horario < inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j]].valor)
    {
        solucao.veiculos[i].infoVeiculo.horario += (inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j]].valor - solucao.veiculos[i].infoVeiculo.horario);
        solucao.veiculos[i].infoVeiculo.durRota += (inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j]].valor - solucao.veiculos[i].infoVeiculo.horario);
    }
    if (solucao.veiculos[i].infoVeiculo.horario > fimJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j]])
    {
        solucao.veiculos[i].infoVeiculo.violChegada += 1;
    }  
}

void efetuaSomaGaragemChegada(solucao &solucao, int i, int j)
{
    printf("na saida %d\n", solucao.veiculos[i].idLocaisAtendidos[j]);
    durViagem(solucao, i, j, solucao.veiculos[i].infoVeiculo.horario);
    solucao.veiculos[i].infoVeiculo.durRota += matrizTempDeslocamento[j][locais-1];
    solucao.veiculos[i].infoVeiculo.horario += matrizTempDeslocamento[j][locais-1];
    solucao.veiculos[i].infoVeiculo.distanciaViagem += matrizTempDeslocamento[j][locais-1];
    if (solucao.veiculos[i].infoVeiculo.horario > fimJanelaTemp[locais-1])
    {
        solucao.veiculos[i].infoVeiculo.violChegada += 1;
    }   
}

void durRota(solucao &solucao)
{
    int i, j, k, numMaximoAssentos = 0, numAtualAssentos = 0, locaisVeiculo = 0;
    for (i = 0; i < solucao.qntdVeiculos; i++)
    {
        locaisVeiculo = solucao.veiculos[i].reqAtendidas * 2; // acho que não precisa do +1

        efetuaSomaGaragemSaida(solucao, i, 0);
        for (j = 0; j < locaisVeiculo - 1; j++)
        {
            numAtualAssentos = numAssentosLocal[j];
            numMaximoAssentos = MAX(numAtualAssentos, numMaximoAssentos);
            if (numAtualAssentos > capacidadeVeic[i])
            {
                solucao.veiculos[i].infoVeiculo.violAssentos += 1;
            }
            efetuaSomaRota(solucao, i, j);
            
        }
        printf("teste demais %d\n", solucao.veiculos[i].idLocaisAtendidos[locaisVeiculo-1]);
        efetuaSomaGaragemChegada(solucao, i, solucao.veiculos[i].idLocaisAtendidos[locaisVeiculo-1]);

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
        printf("entrou %d\n", idLocal);       
        solucao.veiculos[i].infoVeiculo.passageiros[idLocal].horarioEntrada = horario;
    }
    else
    {
        printf("id: %d ---- entrou seh %d\n", idLocal - requisicoes,horario - solucao.veiculos[i].infoVeiculo.passageiros[idLocal - requisicoes].horarioEntrada);       
        solucao.veiculos[i].infoVeiculo.passageiros[idLocal - requisicoes].tempoViagem = horario - solucao.veiculos[i].infoVeiculo.passageiros[idLocal - requisicoes].horarioEntrada;
        if (solucao.veiculos[i].infoVeiculo.passageiros[idLocal - requisicoes].tempoViagem > tempMaxViagem)
        {
            solucao.veiculos[i].infoVeiculo.violDurViagem += 1;
        }
    }
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

void bubble_sort()
{
  vetor temp;
  int i, j, tam = (locais-2)/2;
  
  for(i = 1; i < tam; i++){
    for(j = 1; j < tam; j++){
      if(inicioJanelaTemp[i].valor < inicioJanelaTemp[j].valor){
        temp = inicioJanelaTemp[i];
        inicioJanelaTemp[i] = inicioJanelaTemp[j];
        inicioJanelaTemp[j] = temp;
      }
    }
  }
}

int buscaVetor(solucao &solucao, int chave)
{
    for(int i = 0; i < VEICULOS; i++){
        for(int j =0; j < solucao.veiculos[i].reqAtendidas; j++){
            if(solucao.veiculos[i].idLocaisAtendidos[j] == chave)
                return i;
        }
    }
    return -1;
}

void construtivaGulosa(solucao &solucao)
{
    int i, j=0, req, idInsercao, posicaoEntrada, posicaoInsercaoChegada;
    req = (locais - 2) / 2;
    unsigned int posicaoInsercao[VEICULOS];
    memset(posicaoInsercao, 0, sizeof(posicaoInsercao));
    for(int i = 0; i < req; i++)
    {
        idInsercao = posicaoInsercao[j];
        solucao.veiculos[j].idLocaisAtendidos[idInsercao] = inicioJanelaTemp[i].id;
        solucao.veiculos[j].reqAtendidas += 1;
        posicaoInsercao[j] += 1;

        if((solucao.veiculos[j].reqAtendidas % capacidadeVeic[j]) == 0 )
        {
            posicaoEntrada = posicaoInsercao[j] - (capacidadeVeic[j]-1);
            //printf("Entrada ---- %d\n", posicaoEntrada);
            for(int i = 0; i < capacidadeVeic[j]; i++)
            {
                idInsercao = solucao.veiculos[j].idLocaisAtendidos[posicaoEntrada] * req;
                printf("j=%d ---- id --- %d\n", j, solucao.veiculos[j].idLocaisAtendidos[posicaoEntrada]);
                solucao.veiculos[j].idLocaisAtendidos[posicaoInsercao[j]] = idInsercao;
                posicaoInsercao[j] += 1;
                posicaoEntrada += 1;
            }
        }

        if(j == 5)
        {
            j = 0;
        } else {
            j++;
        } 
    }
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
