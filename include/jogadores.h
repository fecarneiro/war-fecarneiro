#ifndef JOGADORES_H
#define JOGADORES_H

#include "territorios.h"

typedef struct
{
    char nome[30];
    char *missao;
    int cumprida;
    int *territorios;
    int numTerritorios;
    int capacidadeTerritorios;
} Jogador;

void adicionarTerritorio(Jogador *jogador, int indiceTerritorio);
void removerTerritorio(Jogador *jogador, int indiceTerritorio);
int encontrarDonoTerritorio(Jogador *jogadores, int totalJogadores, int indiceTerritorio);

#endif