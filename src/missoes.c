#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/missoes.h"

const char *missoes[] = {
    "conquistar território vermelho",
    "conquistar território azul",
    "conquistar território verde",
    "conquistar território preto",
    "conquistar território amarelo",
    "conquistar território branco",
    "conquistar áfrica",
    "conquistar europa",
    "conquistar oceania",
    "conquistar ásia",
    "conquistar américa"};
const int TOTAL_MISSOES = 11;

/**
 * Verifica se uma missão é válida para um jogador específico
 * Uma missão é inválida se o jogador já possui o que a missão pede para conquistar
 * @param missao String com a missão a ser verificada
 * @param territorios Array de territórios do jogo
 * @param totalTerritorio Número total de territórios
 * @param jogador Ponteiro para o jogador que receberá a missão
 * @return 1 se a missão é válida, 0 caso contrário
 */
int verificarMissaoValida(const char *missao, Territorio *territorios,
                          int totalTerritorio, Jogador *jogador)
{
    if (strstr(missao, "território") != NULL)
    {
        char corMissao[10];
        sscanf(missao, "conquistar território %s", corMissao);

        if (!corExiste(corMissao, territorios, totalTerritorio))
        {
            return 0;
        }

        for (int i = 0; i < jogador->numTerritorios; i++)
        {
            int indiceTerritorio = jogador->territorios[i];
            if (strcmp(territorios[indiceTerritorio].cor, corMissao) == 0)
            {
                return 0;
            }
        }
    }

    if (strstr(missao, "conquistar ") != NULL && strstr(missao, "território") == NULL)
    {
        char continenteMissao[30];
        sscanf(missao, "conquistar %s", continenteMissao);

        if (!territorioExiste(continenteMissao, territorios, totalTerritorio))
        {
            return 0;
        }

        for (int i = 0; i < jogador->numTerritorios; i++)
        {
            int indiceTerritorio = jogador->territorios[i];
            if (strcmp(territorios[indiceTerritorio].nome, continenteMissao) == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}

/**
 * Atribui uma missão aleatória e válida para um jogador
 * @param destino String onde a missão será armazenada
 * @param missoes Array com todas as missões possíveis
 * @param totalMissoes Número total de missões disponíveis
 * @param territorios Array de territórios do jogo
 * @param totalTerritorio Número total de territórios
 * @param jogador Ponteiro para o jogador que receberá a missão
 */
void atribuirMissao(char *destino, const char *missoes[], int totalMissoes,
                    Territorio *territorios, int totalTerritorio, Jogador *jogador)
{
    int missaoValida = 0;
    int indiceMissao;

    do
    {
        indiceMissao = rand() % totalMissoes;
        missaoValida = verificarMissaoValida(missoes[indiceMissao], territorios,
                                             totalTerritorio, jogador);
    } while (!missaoValida);

    strcpy(destino, missoes[indiceMissao]);
}

/**
 * Verifica se um jogador cumpriu sua missão
 * @param missao String com a missão do jogador
 * @param mapa Array de territórios do jogo
 * @param tamanho Número total de territórios
 * @param jogador Ponteiro para o jogador cuja missão será verificada
 * @return 1 se a missão foi cumprida, 0 caso contrário
 */
int verificarMissao(char *missao, Territorio *mapa, int tamanho, Jogador *jogador)
{
    if (strstr(missao, "território") != NULL)
    {
        char corMissao[10];
        sscanf(missao, "conquistar território %s", corMissao);

        for (int i = 0; i < jogador->numTerritorios; i++)
        {
            int indiceTerritorio = jogador->territorios[i];
            if (strcmp(mapa[indiceTerritorio].cor, corMissao) == 0)
            {
                return 1;
            }
        }
    }

    if (strstr(missao, "conquistar ") != NULL && strstr(missao, "território") == NULL)
    {
        char continenteMissao[30];
        sscanf(missao, "conquistar %s", continenteMissao);

        for (int i = 0; i < jogador->numTerritorios; i++)
        {
            int indiceTerritorio = jogador->territorios[i];
            if (strcmp(mapa[indiceTerritorio].nome, continenteMissao) == 0)
            {
                return 1;
            }
        }
    }

    return 0;
}

/**
 * Exibe a missão de um jogador na tela
 * @param missao String com a missão a ser exibida
 */
void exibirMissao(char missao[])
{
    printf("Sua missão: %s\n", missao);
}