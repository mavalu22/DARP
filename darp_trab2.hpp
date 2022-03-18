#ifndef DARP_HPP_INCLUDED
#define DARP_HPP_INCLUDED

#define MAX_VEI 10
#define MAX_REQ 60
#define MAX_LOC MAX_REQ * 2 + 2

#include <string>
#include <tuple>

// Estruturas de dados
typedef struct tsolucao
{
    int matAteVei[MAX_VEI][MAX_LOC];
    int vetQtdLocAte[MAX_VEI];
    int funObj;
    //--- dados da FO
    int numVeiUsa;
    int dstTotal;
    int durTotal;
    int tViTotal;
    int tEsTotal;
    //--- dados dos veículos
    int vetDstPerVei[MAX_VEI];
    int vetDurRotVei[MAX_VEI];
    int vetHorSaiVei[MAX_VEI];
    int vetHorCheVei[MAX_VEI];
    //--- dados dos locais
    int vetHorCheLoc[MAX_LOC];
    int vetHorIniAte[MAX_LOC];
    int vetHorSaiLoc[MAX_LOC];
    int vetCarVeiLoc[MAX_LOC];
    int vetTemEspLoc[MAX_LOC];
    //--- dados das requisições (PPNEs)
    int vetTemViaReq[MAX_REQ];
    int vetTemEspReq[MAX_REQ];
    //--- violações não tratadas na modelagem
    int vioCapVei;
    int vioDurRot;
    int vioJanTem;
    int vioTemVia;
    int vioTemEsp;
    int vetVioCapVei[MAX_VEI];
    int vetVioDurRot[MAX_VEI];
} solucao;

// Dados de entrada
int numVei;
int numReq;
int durMaxRot;
int temMaxVia;
int temMaxEsp;
int vetCapVei[MAX_VEI];
int vetQtdAssLoc[MAX_LOC];
int vetTemSerLoc[MAX_LOC];
int vetIniJTLoc[MAX_LOC];
int vetFinJTLoc[MAX_LOC];
int matTemDesLoc[MAX_LOC][MAX_LOC];

// Variáveis auxiliares
int numLoc;
int vetLocOrd[MAX_LOC];

// Métodos
void calcFO(solucao &s);
void heuConGul(solucao &s);
void escSolucao(solucao &s, std::string arq);
void escRequisicao(solucao &s, const int req, FILE *f);
void escVeiculo(solucao &s, const int vei, FILE *f);
void escProblema(std::string arq);
void escArquivo(solucao &s, std::string arq);
int idVeiEmbLoc(solucao &s, const int locDes);
void ordenarLocais();
void testarDados(std::string arq);
void lerDados(std::string arq);
void gerar_vizinha(solucao &s);
std::tuple<int, int> buscaMatriz(int requisicao, solucao &s);
void excluirMatriz(int requisicao, solucao &s);
void insereMatriz(int requisicao, int carro, solucao &s);
void ils(const double tempo_max, solucao &s, double &tempo_melhor, double &tempo_total);
void heuBLMM(solucao &s);
#endif