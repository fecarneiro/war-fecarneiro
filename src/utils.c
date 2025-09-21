#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/utils.h"

/**
 * Limpa o buffer de entrada para evitar problemas com leitura de dados
 * Remove todos os caracteres restantes no buffer até encontrar quebra de linha ou EOF
 */
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * Normaliza o nome de território convertendo para minúsculas e
 * aplicando correções específicas para nomes com acentos
 * @param nome String com o nome do território a ser normalizado
 */
void normalizarNomeTerritorio(char *nome)
{
    for (int i = 0; nome[i]; i++)
    {
        nome[i] = tolower(nome[i]);
    }

    if (strcmp(nome, "africa") == 0)
    {
        strcpy(nome, "áfrica");
    }
    else if (strcmp(nome, "america") == 0)
    {
        strcpy(nome, "américa");
    }
    else if (strcmp(nome, "asia") == 0)
    {
        strcpy(nome, "ásia");
    }
}

/**
 * Exibe o menu principal do jogo para o jogador atual
 * @param nomeJogador Nome do jogador que está no turno atual
 * @return Opção escolhida pelo jogador (1-Atacar, 2-Verificar Missão, 3-Sair)
 */
int exibirMenu(char *nomeJogador)
{
    int opcao;
    printf("\n=== MENU DO JOGADOR: %s ===\n", nomeJogador);
    printf("1. Atacar\n");
    printf("2. Verificar Missão\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    limparBufferEntrada();
    return opcao;
}