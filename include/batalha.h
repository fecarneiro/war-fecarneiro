#ifndef BATALHA_H
#define BATALHA_H

#include "territorios.h"
#include "jogadores.h"

void atacar(Territorio *atacante, Territorio *defensor, Jogador *jogadores, int totalJogadores, int indiceAtacante, int indiceDefensor);

#endif