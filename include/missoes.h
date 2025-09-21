#ifndef MISSOES_H
#define MISSOES_H

#include "territorios.h"
#include "jogadores.h"

extern const char *missoes[];
extern const int TOTAL_MISSOES;

int verificarMissaoValida(const char *missao, Territorio *territorios, int totalTerritorio, Jogador *jogador);
void atribuirMissao(char *destino, const char *missoes[], int totalMissoes, Territorio *territorios, int totalTerritorio, Jogador *jogador);
int verificarMissao(char *missao, Territorio *mapa, int tamanho, Jogador *jogador);
void exibirMissao(char missao[]);

#endif