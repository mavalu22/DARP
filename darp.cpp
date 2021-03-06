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
    lerDados();
    // lerSolucao(x);
    durRota(x);
    somaRestricao(x);
    printTela(x);
}

void construtivaGulosa(solucao &solucao)
{
    int i, j, k, l, m, idEncontrado, reqSobra;
    bubble_sort();
    solucao.qntdVeiculos = VEICULOS;
    reqSobra = requisicoes % VEICULOS;
    for (i = 0; i < VEICULOS; i++)
    {
        solucao.veiculos[i].id = i;
        solucao.veiculos[i].reqAtendidas = requisicoes / VEICULOS;
        solucao.veiculos[i].reqAtendidas = (int)solucao.veiculos[i].reqAtendidas;
    }
    for (j = 0; j < reqSobra; j++)
    {
        solucao.veiculos[j].reqAtendidas++;
    }

    k = 0;
    l = 0;

    for (i = 1; i < locais - 1; i++)
    {

        if (buscaVetor(solucao, inicioJanelaTemp[i].id + requisicoes) != -1 || buscaVetor(solucao, inicioJanelaTemp[i].id - requisicoes) != -1)

            solucao.veiculos[k].idLocaisAtendidos[l] = inicioJanelaTemp[i].id;
        if (k == VEICULOS - 1)
        {
            k = 0;
            l++;
        }
        else
            k++;

        if (i >= (locais - 2) - (reqSobra * 2))
        {
            for (j = 0; j < reqSobra; j++)
            {
                solucao.veiculos[j].idLocaisAtendidos[l] = inicioJanelaTemp[i + 1].id;
                i++;
            }

            for (m = 0; m < reqSobra; m++)
            {
                solucao.veiculos[m].idLocaisAtendidos[l + 1] = inicioJanelaTemp[i + 1].id;
                i++;
            }
        }
    }
}

void lerDados()
{

    FILE *f = fopen("darp3.txt", "r");

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
    while (j < solucao.qntdVeiculos)
    {

        fscanf(f, "%d", &solucao.veiculos[j].id);
        fscanf(f, "%d", &solucao.veiculos[j].reqAtendidas);
        locaisAt = (solucao.veiculos[j].reqAtendidas * 2);
        for (i = 0; i < locaisAt; i++)
        {
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

void efetuaSomaRota(solucao &solucao, int i, int j)
{
    durViagem(solucao, i, solucao.veiculos[i].idLocaisAtendidos[j], solucao.veiculos[i].infoVeiculo.horario);
    solucao.veiculos[i].infoVeiculo.durRota += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[j]][solucao.veiculos[i].idLocaisAtendidos[j + 1]] + tempServico[solucao.veiculos[i].idLocaisAtendidos[j + 1]];
    solucao.veiculos[i].infoVeiculo.horario += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[j]][solucao.veiculos[i].idLocaisAtendidos[j + 1]] + tempServico[solucao.veiculos[i].idLocaisAtendidos[j + 1]];
    solucao.veiculos[i].infoVeiculo.distanciaViagem += matrizTempDeslocamento[solucao.veiculos[i].idLocaisAtendidos[j]][solucao.veiculos[i].idLocaisAtendidos[j + 1]];
    int idJanelaTempo = buscaId(solucao.veiculos[i].idLocaisAtendidos[j + 1]);
    if (solucao.veiculos[i].infoVeiculo.horario < inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j + 1]].valor)
    {
        int atraso;
        atraso = inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j + 1]].valor - solucao.veiculos[i].infoVeiculo.horario;
        solucao.veiculos[i].infoVeiculo.horario += atraso;
        solucao.veiculos[i].infoVeiculo.durRota += atraso;
        esperaPPE(solucao, atraso, i);
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
    int idJanelaTempo = buscaId(solucao.veiculos[i].idLocaisAtendidos[j]);
    if (solucao.veiculos[i].infoVeiculo.horario < inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j]].valor)
    {
        int atraso;
        atraso = inicioJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j]].valor - solucao.veiculos[i].infoVeiculo.horario;
        solucao.veiculos[i].infoVeiculo.horario += atraso;
        solucao.veiculos[i].infoVeiculo.durRota += atraso;
        esperaPPE(solucao, atraso, i);
    }
    if (solucao.veiculos[i].infoVeiculo.horario > fimJanelaTemp[solucao.veiculos[i].idLocaisAtendidos[j]])
    {
        solucao.veiculos[i].infoVeiculo.violChegada += 1;
    }
}

void efetuaSomaGaragemChegada(solucao &solucao, int i, int j)
{
    durViagem(solucao, i, j, solucao.veiculos[i].infoVeiculo.horario);
    solucao.veiculos[i].infoVeiculo.durRota += matrizTempDeslocamento[j][locais - 1];
    solucao.veiculos[i].infoVeiculo.horario += matrizTempDeslocamento[j][locais - 1];
    solucao.veiculos[i].infoVeiculo.distanciaViagem += matrizTempDeslocamento[j][locais - 1];
    if (solucao.veiculos[i].infoVeiculo.horario > fimJanelaTemp[locais - 1])
    {
        solucao.veiculos[i].infoVeiculo.violChegada += 1;
    }
}

void durRota(solucao &solucao)
{
    int i, j, k, numMaximoAssentos = 0, numAtualAssentos = 0, locaisVeiculo = 0;
    for (i = 0; i < solucao.qntdVeiculos; i++)
    {
        locaisVeiculo = solucao.veiculos[i].reqAtendidas * 2;

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
        efetuaSomaGaragemChegada(solucao, i, solucao.veiculos[i].idLocaisAtendidos[locaisVeiculo - 1]);

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
        solucao.veiculos[i].infoVeiculo.passageiros[idLocal - requisicoes].tempoViagem = horario - solucao.veiculos[i].infoVeiculo.passageiros[idLocal - requisicoes].horarioEntrada;
        if (solucao.veiculos[i].infoVeiculo.passageiros[idLocal - requisicoes].tempoViagem > tempMaxViagem)
        {
            solucao.veiculos[i].infoVeiculo.violDurViagem += 1;
        }
    }
}

void solucaoCompleta(solucao &solucao)
{
    int i, j, k;
    lerSolucao(solucao);
    durRota(solucao);
}

void bubble_sort()
{
    vetor temp;
    int i, j, tam = (locais - 1);

    for (i = 1; i < tam; i++)
    {
        for (j = 1; j < tam; j++)
        {
            if (inicioJanelaTemp[i].valor < inicioJanelaTemp[j].valor)
            {
                temp = inicioJanelaTemp[i];
                inicioJanelaTemp[i] = inicioJanelaTemp[j];
                inicioJanelaTemp[j] = temp;
            }
        }
    }
}

int buscaVetor(solucao &solucao, int chave)
{
    for (int i = 0; i < VEICULOS; i++)
    {
        for (int j = 0; j < solucao.veiculos[i].reqAtendidas * 2; j++)
        {
            if (solucao.veiculos[i].idLocaisAtendidos[j] == chave)
                return i;
        }
    }
    return -1;
}

void esperaPPE(solucao &solucao, int atraso, int idVeiculo)
{
    int i, j, maxLocais, id;

    maxLocais = solucao.veiculos[idVeiculo].reqAtendidas * 2;
    for (i = 0; i < maxLocais; i++)
    {
        if (solucao.veiculos[idVeiculo].idLocaisAtendidos[i] <= requisicoes)
        {
            id = solucao.veiculos[idVeiculo].idLocaisAtendidos[i];
            if ((solucao.veiculos[idVeiculo].infoVeiculo.passageiros[id].horarioEntrada != 0) && (solucao.veiculos[i].infoVeiculo.passageiros[id].tempoViagem == 0))
            {
                solucao.veiculos[idVeiculo].infoVeiculo.passageiros[id].tempoEspera += atraso;
            }
        }
    }
}

void construtivaGulosa(solucao &solucao)
{
    int i, j = 0, req, idInsercao, posicaoEntrada, posicaoInsercaoChegada;
    req = (locais - 2) / 2;
    unsigned int posicaoInsercao[VEICULOS];
    memset(posicaoInsercao, 0, sizeof(posicaoInsercao));
    for (int i = 0; i < req; i++)
    {
        idInsercao = posicaoInsercao[j];
        solucao.veiculos[j].idLocaisAtendidos[idInsercao] = inicioJanelaTemp[i].id;
        solucao.veiculos[j].reqAtendidas += 1;
        posicaoInsercao[j] += 1;

        if ((solucao.veiculos[j].reqAtendidas % capacidadeVeic[j]) == 0)
        {
            posicaoEntrada = posicaoInsercao[j] - (capacidadeVeic[j] - 1);
            for (int i = 0; i < capacidadeVeic[j]; i++)
            {
                idInsercao = solucao.veiculos[j].idLocaisAtendidos[posicaoEntrada] * req;
                solucao.veiculos[j].idLocaisAtendidos[posicaoInsercao[j]] = idInsercao;
                posicaoInsercao[j] += 1;
                posicaoEntrada += 1;
            }
        }

        if (j == 5)
        {
            j = 0;
        }
        else
        {
            j++;
        }
    }
}

void somaRestricao(solucao &solucao)
{
    totalRestricoes;
    for (int i = 0; i < solucao.qntdVeiculos; i++)
    {
        totalRestricoes.distanciaViagem += solucao.veiculos[i].infoVeiculo.distanciaViagem;
        totalRestricoes.durRota += solucao.veiculos[i].infoVeiculo.durRota;
        totalRestricoes.violAssentos += solucao.veiculos[i].infoVeiculo.violAssentos;
        totalRestricoes.violChegada += solucao.veiculos[i].infoVeiculo.violChegada;
        totalRestricoes.violDurRota += solucao.veiculos[i].infoVeiculo.violDurRota;
        totalRestricoes.violDurViagem += solucao.veiculos[i].infoVeiculo.violDurViagem;
        totalRestricoes.violChegadaLocal += solucao.veiculos[i].infoVeiculo.violChegadaLocal;
    }
    somaEsperaPPNE(solucao);
}

void somaEsperaPPNE(solucao &solucao)
{
    int id;
    for (int i = 0; i < solucao.qntdVeiculos; i++)
    {
        for (int j = 0; j < solucao.veiculos[i].reqAtendidas; j++)
        {
            id = solucao.veiculos[i].idLocaisAtendidos[j];
            totalRestricoes.tempTotalEspera += solucao.veiculos[i].infoVeiculo.passageiros[id].tempoEspera;
        }
    }
    if (totalRestricoes.tempTotalEspera > tempMaxEspera)
    {
        totalRestricoes.violTempEsp += 1;
    }
}

int buscaId(int chave)
{
    for (int i = 0; i < locais; i++)
    {
        if (chave == inicioJanelaTemp[i].id)
        {
            return i;
        }
    }
    return -1;
}

void printTela(solucao &solucao)
{

    printf("N??mero de ve??culos usados: %d\n", solucao.qntdVeiculos);
    printf("Valor da Fun????o objetivo da solucao: %d\n", solucao.FO);
    printf("Dist??ncia percorrida por todos os ve??culos: %d\n", totalRestricoes.distanciaViagem);
    printf("Somatorio da dura????o das rotas dos veiculos: %d\n", totalRestricoes.durRota);
    printf("Tempo total de viagem de todas as PPNEs: %d\n", totalRestricoes.durTotalViagem); // falta somar
    printf("Tempo total de espera de todas as PPNEs: %d\n", totalRestricoes.tempTotalEspera);
    printf("N??mero de viola????es no n??mero de assentos dos ve??culos: %d\n", totalRestricoes.violAssentos);
    printf("N??mero de viola????es na dura????o m??xima das rotas: %d\n", totalRestricoes.violDurRota);
    printf("N??mero de viola????es no tempo m??ximo de viagem de todas as PPNEs: %d\n", totalRestricoes.violDurViagem);
    printf("N??mero de viola????es no tempo m??ximo de espera de todas as PPNEs: %d\n", totalRestricoes.violTempEsp);
    printf("N??mero de viola????es nos hor??rios de chegada nos locais: %d\n", totalRestricoes.violChegadaLocal);
    printf("N??mero de viola????es nos hor??rios de chegada: %d\n", totalRestricoes.violChegada);
    printf("\n");
    printf("\n");

    printf("Viola????es por veiculos usados na solu????o\n");
    printf("Numero de veiculos usados: %d\n", solucao.qntdVeiculos);
    for (int i = 0; i < solucao.qntdVeiculos; i++)
    {
        printf("Numero de requisi????es atendidas: %d\n", solucao.veiculos[i].reqAtendidas);
        printf("Dura????o da rota: %d\n", solucao.veiculos[i].infoVeiculo.durRota);
        for (int j = 0; j < solucao.veiculos[i].reqAtendidas * 2; j++)
        {
            int id;
            id = solucao.veiculos[i].idLocaisAtendidos[j];
            if (id < requisicoes)
            {
                printf("Tempo de viagem da PPNE de id=%d: %d\n", id, solucao.veiculos[i].infoVeiculo.passageiros[id].tempoViagem);
                printf("Tempo de espera da PPNE de id=%d: %d\n", id, solucao.veiculos[i].infoVeiculo.passageiros[id].tempoEspera);
            }
        }
        printf("Violacao assento: %d\n", solucao.veiculos[i].infoVeiculo.violAssentos);
        printf("Violacao Chegada: %d\n", solucao.veiculos[i].infoVeiculo.violChegada);
        printf("Violacao Dura????o da rota: %d\n", solucao.veiculos[i].infoVeiculo.violDurRota);
        printf("Violacao Dura????o da viagem: %d\n", solucao.veiculos[i].infoVeiculo.violDurViagem);
        printf("Sequ??ncia de locais que formam a rota do ve??culo %d\n", i);
        for (int j = 0; j < solucao.veiculos[i].reqAtendidas * 2; j++)
        {
            printf("%d\t", solucao.veiculos[i].idLocaisAtendidos[j]);
        }
        printf("\n");
        printf("\n");
        printf("\n");
    }

    printf("\n");
}
