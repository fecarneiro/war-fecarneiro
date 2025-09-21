#include <stdio.h>
#include <stdlib.h>
#include "../include/jogadores.h"

/**
 * Adiciona um território à lista de territórios de um jogador
 * Expande automaticamente a capacidade se necessário
 * @param jogador Ponteiro para o jogador que receberá o território
 * @param indiceTerritorio Índice do território a ser adicionado
 */
void adicionarTerritorio(Jogador *jogador, int indiceTerritorio)
{
    if (jogador->numTerritorios >= jogador->capacidadeTerritorios)
    {
        jogador->capacidadeTerritorios *= 2;
        jogador->territorios = realloc(jogador->territorios,
                                       jogador->capacidadeTerritorios * sizeof(int));
    }

    jogador->territorios[jogador->numTerritorios] = indiceTerritorio;
    jogador->numTerritorios++;
}

/**
 * Remove um território da lista de territórios de um jogador
 * @param jogador Ponteiro para o jogador que perderá o território
 * @param indiceTerritorio Índice do território a ser removido
 */
void removerTerritorio(Jogador *jogador, int indiceTerritorio)
{
    for (int i = 0; i < jogador->numTerritorios; i++)
    {
        if (jogador->territorios[i] == indiceTerritorio)
        {
            for (int j = i; j < jogador->numTerritorios - 1; j++)
            {
                jogador->territorios[j] = jogador->territorios[j + 1];
            }
            jogador->numTerritorios--;
            break;
        }
    }
}

/**
 * Encontra qual jogador é o dono de um território específico
 * @param jogadores Array de todos os jogadores do jogo
 * @param totalJogadores Número total de jogadores
 * @param indiceTerritorio Índice do território cujo dono se busca
 * @return Índice do jogador dono do território, ou -1 se não encontrado
 */
int encontrarDonoTerritorio(Jogador *jogadores, int totalJogadores, int indiceTerritorio)
{
    for (int i = 0; i < totalJogadores; i++)
    {
        for (int j = 0; j < jogadores[i].numTerritorios; j++)
        {
            if (jogadores[i].territorios[j] == indiceTerritorio)
            {
                return i;
            }
        }
    }
    return -1;
}