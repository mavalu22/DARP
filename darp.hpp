#ifndef DARP_HPP_INCLUDED
#define DARP_HPP_INCLUDED

#include <string>
#define VEICULOS 6
#define MAX_REQ 50
#define MAX_VIA 1440
#define MAX_ESP 1440

int locais;

typedef struct input
{
    int req;
    int durMaxRot;
    int vetNumAss[VEICULOS];
    // int vetNumAssLoc[locais];
    // int vetTempServ[];
    // int vetIniTemp[];
    // int vetTermTemp[];
    // int matTemp[][];
    int funObj;
} input;

typedef struct passageiro
{
    int horarioEntrada;
    int tempoViagem;
    int tempoEspera;
} passageiro;

typedef struct req
{
    int saida;
    int chegada;
} req;

typedef struct veiculo
{
    int vaga;
    //int requisicoes[];
    int horario;
    int durRota;
    int durTotalViagem;
    int tempTotalEspera;
    int distanciaViagem;
    int violAssentos;
    int violDurRota;
    int violDurViagem;
    int violTempEsp;
    int violChegada;
    passageiro passageiros[MAX_REQ];
} veiculo;

typedef struct solucVeiculos
{
    int id;
    int reqAtendidas;
    int idLocaisAtendidos[MAX_REQ];
    veiculo infoVeiculo;
} solucVeiculos;

typedef struct soluc
{
    int FO;
    int qntdVeiculos;
    solucVeiculos veiculos[VEICULOS];
} solucao;

int requisicoes, duracaoMaxRota, tempMaxViagem, tempMaxEspera, lixo;

int capacidadeVeic[VEICULOS];
int numAssentosLocal[MAX_REQ];
int tempServico[MAX_REQ];
int inicioJanelaTemp[MAX_REQ];
int fimJanelaTemp[MAX_REQ];
int matrizTempDeslocamento[MAX_REQ][MAX_REQ];
int requisicaoSolucao[MAX_REQ];
veiculo totalRestricoes;
int veiculosUsados[VEICULOS];

void contaVeiculosUsados(int id);

int verificaVeiculosUsados();

void lerDados();

void printVetor(int vet[MAX_REQ]);

void printOutroVetor(int vet[VEICULOS]);

void printMatriz(int matriz[MAX_REQ][MAX_REQ]);

void clonarSolucao(solucao &original, solucao &clone);

void construtivaAleatoria();

void lerSolucao(solucao &solucao);

void calcularFO(solucao &solucao);

void verificaDuracaoRota(solucao &solucao);

void verificaDuracaoViagem(solucao &solucao);

void verificaTempEspera(solucao &solucao);

void verificaHoraChegada(solucao &solucao);

void construtivaAleatoria(solucao &solucao);

#endif