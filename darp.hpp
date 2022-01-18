#ifndef DARP_HPP_INCLUDED
#define DARP_HPP_INCLUDED

#define MAX_VIA 1440
#define MAX_ESP 1440
#define CARROS 6

int locais;

typedef struct input
{
    int req;
    int durMaxRot;
    int vetNumAss[CARROS];
    // int vetNumAssLoc[locais];
    // int vetTempServ[];
    // int vetIniTemp[];
    // int vetTermTemp[];
    // int matTemp[][];
    int funObj;
} input;

typedef struct req
{
    int saida;
    int chegada;
} req;

typedef struct veiculo
{
    int id;
    int vaga;
    // int requisicoes[];
    int horario;
    int durRota;
    int durViagem;
    int tempEspera;
    int violAssentos;
    int violDurRota;
    int violDurViagem;
    int violTempEsp;
    int violSaidaChegada;

} veiculo;

typedef struct passageiro
{
    int tempoViagem;
    int tempoEspera;
} passageiro;

#include <string>
#define VEICULOS 6
#define MAX_REQ 50

int requisicoes, duracaoMaxRota, tempMaxViagem, tempMaxEspera, lixo;

int capacidadeVeic[VEICULOS];
int numAssentosLocal[MAX_REQ];
int tempServico[MAX_REQ];
int inicioJanelaTemp[MAX_REQ];
int fimJanelaTemp[MAX_REQ];
int matrizTempDeslocamento[MAX_REQ][MAX_REQ];

void lerDados();

void printVetor(int vet[MAX_REQ]);

void printOutroVetor(int vet[VEICULOS]);

void printMatriz(int matriz[MAX_REQ][MAX_REQ]);

#endif
