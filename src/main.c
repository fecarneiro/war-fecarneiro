#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/territorios.h"
#include "../include/jogadores.h"
#include "../include/missoes.h"
#include "../include/batalha.h"
#include "../include/utils.h"

/**
 * Função principal do jogo WAR
 * Gerencia o fluxo completo do jogo: cadastro de territórios,
 * criação de jogadores, atribuição de missões e loop principal do jogo
 */
int main()
{
    printf("--- WAR ESTRUTURADO - CADASTRO DE TERRITORIOS ---\n\n");
    printf("Digite a quantidade de Territórios desejada:\n\n");

    int totalTerritorio;
    do
    {
        scanf("%d", &totalTerritorio);
        if (totalTerritorio <= 1)
        {
            printf("Erro: A quantidade de territorios deve ser maior que 1. Tente novamente:\n");
        }
    } while (totalTerritorio <= 1);

    Territorio *territorios = calloc(totalTerritorio, sizeof(Territorio));
    if (territorios == NULL)
    {
        printf("Erro: Falha na alocação de memória.\n");
        return 1;
    }

    cadastrarTerritorios(territorios, totalTerritorio);
    exibirMapa(territorios, totalTerritorio);

    int totalJogadores = totalTerritorio;

    Jogador *jogadores = malloc(totalJogadores * sizeof(Jogador));
    if (jogadores == NULL)
    {
        printf("Erro: Falha na alocação de memória para jogadores.\n");
        free(territorios);
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < totalJogadores; i++)
    {
        printf("\n--- CADASTRANDO JOGADOR %d ---\n", i + 1);
        printf("Digite o nome do jogador dono do território %s: ", territorios[i].nome);
        scanf("%s", jogadores[i].nome);

        jogadores[i].capacidadeTerritorios = 2;
        jogadores[i].territorios = malloc(jogadores[i].capacidadeTerritorios * sizeof(int));
        jogadores[i].numTerritorios = 0;

        adicionarTerritorio(&jogadores[i], i);

        jogadores[i].missao = malloc(100 * sizeof(char));
        atribuirMissao(jogadores[i].missao, missoes, TOTAL_MISSOES,
                       territorios, totalTerritorio, &jogadores[i]);

        jogadores[i].cumprida = 0;

        printf("Jogador %s, ", jogadores[i].nome);
        exibirMissao(jogadores[i].missao);
    }

    int jogadorAtual = 0;
    while (1)
    {
        int tentativas = 0;
        while (jogadores[jogadorAtual].cumprida == -1 && tentativas < totalJogadores)
        {
            jogadorAtual = (jogadorAtual + 1) % totalJogadores;
            tentativas++;
        }

        if (tentativas >= totalJogadores)
        {
            printf("Jogo acabou! Apenas um jogador restante.\n");
            break;
        }

        printf("\n--- TURNO DO JOGADOR: %s ---\n", jogadores[jogadorAtual].nome);
        printf("Seus territórios: ");
        for (int i = 0; i < jogadores[jogadorAtual].numTerritorios; i++)
        {
            int idx = jogadores[jogadorAtual].territorios[i];
            printf("%s ", territorios[idx].nome);
        }
        printf("\n");

        int opcao = exibirMenu(jogadores[jogadorAtual].nome);

        if (opcao == 3)
        {
            break;
        }
        else if (opcao == 2)
        {
            printf("\n");
            exibirMissao(jogadores[jogadorAtual].missao);
            if (verificarMissao(jogadores[jogadorAtual].missao, territorios, totalTerritorio,
                                &jogadores[jogadorAtual]))
            {
                printf("PARABÉNS! Você cumpriu sua missão!\n");
                printf("VITÓRIA POR MISSÃO! Jogador %s venceu!\n", jogadores[jogadorAtual].nome);
                break;
            }
            else
            {
                printf("Missão ainda não foi cumprida. Continue jogando!\n");
            }
            printf("Pressione ENTER para continuar...");
            getchar();
            continue;
        }
        else if (opcao == 1)
        {
            exibirMapa(territorios, totalTerritorio);
            printf("Escolha o territorio atacante (1 a %d), ou 0 para cancelar: ", totalTerritorio);
            int atacanteIndex;
            scanf("%d", &atacanteIndex);
            limparBufferEntrada();
            if (atacanteIndex == 0)
            {
                continue;
            }
            printf("Escolha o territorio defensor (1 a %d): ", totalTerritorio);
            int defensorIndex;
            scanf("%d", &defensorIndex);
            limparBufferEntrada();

            atacanteIndex--;
            defensorIndex--;

            if (atacanteIndex < 0 || atacanteIndex >= totalTerritorio ||
                defensorIndex < 0 || defensorIndex >= totalTerritorio ||
                atacanteIndex == defensorIndex)
            {
                printf("Selecao invalida. Tente novamente.\n");
                continue;
            }

            int possuiAtacante = 0;
            for (int i = 0; i < jogadores[jogadorAtual].numTerritorios; i++)
            {
                if (jogadores[jogadorAtual].territorios[i] == atacanteIndex)
                {
                    possuiAtacante = 1;
                    break;
                }
            }
            if (!possuiAtacante)
            {
                printf("Erro: Você só pode atacar com seus próprios territórios.\n");
                continue;
            }

            if (strcmp(territorios[atacanteIndex].cor, territorios[defensorIndex].cor) == 0)
            {
                printf("Erro: Nao pode atacar um territorio da mesma cor (mesmo dono).\n");
                continue;
            }

            atacar(&territorios[atacanteIndex], &territorios[defensorIndex], jogadores,
                   totalJogadores, atacanteIndex, defensorIndex);

            printf("\n--- MAPA MUNDO - ESTADO ATUAL ---\n");
            exibirMapa(territorios, totalTerritorio);

            if (verificarMissao(jogadores[jogadorAtual].missao, territorios, totalTerritorio,
                                &jogadores[jogadorAtual]))
            {
                printf("VITÓRIA POR MISSÃO! Jogador %s cumpriu: %s\n",
                       jogadores[jogadorAtual].nome, jogadores[jogadorAtual].missao);
                break;
            }

            if (allSameColor(territorios, totalTerritorio))
            {
                char *corVencedora = territorios[0].cor;
                for (int i = 0; i < totalJogadores; i++)
                {
                    if (jogadores[i].cumprida != -1)
                    {
                        for (int j = 0; j < jogadores[i].numTerritorios; j++)
                        {
                            int idx = jogadores[i].territorios[j];
                            if (strcmp(territorios[idx].cor, corVencedora) == 0)
                            {
                                printf("VITÓRIA POR DOMINAÇÃO! Jogador %s conquistou todos os territórios!\n",
                                       jogadores[i].nome);
                                goto fim_jogo;
                            }
                        }
                    }
                }
            fim_jogo:
                break;
            }

            jogadorAtual = (jogadorAtual + 1) % totalJogadores;
            printf("Pressione ENTER para continuar para o proximo turno...");
            getchar();
        }
        else
        {
            printf("Opção inválida! Escolha 1, 2 ou 3.\n");
            printf("Pressione ENTER para continuar...");
            getchar();
            continue;
        }
    }

    for (int i = 0; i < totalJogadores; i++)
    {
        if (jogadores[i].missao != NULL)
        {
            free(jogadores[i].missao);
        }
        if (jogadores[i].territorios != NULL)
        {
            free(jogadores[i].territorios);
        }
    }
    free(jogadores);
    free(territorios);
    return 0;
}