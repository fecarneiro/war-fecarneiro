#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/territorios.h"
#include "../include/utils.h"

/**
 * Cadastra todos os territórios do jogo solicitando dados do usuário
 * @param territorios Array de territórios a ser preenchido
 * @param totalTerritorio Número total de territórios a cadastrar
 */
void cadastrarTerritorios(Territorio *territorios, int totalTerritorio)
{
    for (int i = 0; i < totalTerritorio; i++)
    {
        printf("  --- CADASTRANDO TERRITORIO: %d --- \n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);
        normalizarNomeTerritorio(territorios[i].nome);

        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);
        for (int j = 0; territorios[i].cor[j]; j++)
        {
            territorios[i].cor[j] = tolower(territorios[i].cor[j]);
        }

        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }
}

/**
 * Exibe o mapa atual com todos os territórios, suas cores e tropas
 * @param territorios Array de territórios a ser exibido
 * @param totalTerritorio Número total de territórios
 */
void exibirMapa(Territorio *territorios, int totalTerritorio)
{
    printf("\n===== MAPA ATUAL DOS TERRITORIOS ========\n");
    printf("%-20s %-15s %s\n", "TERRITORIO", "COR DO EXERCITO", "TROPAS");
    printf("%-20s %-15s %s\n", "----------", "---------------", "------");

    for (int i = 0; i < totalTerritorio; i++)
    {
        printf("%-20s %-15s %d\n",
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas);
    }
}

/**
 * Verifica se um território com o nome especificado existe no jogo
 * @param nomeTerritorio Nome do território a ser procurado
 * @param territorios Array de territórios onde buscar
 * @param totalTerritorio Número total de territórios
 * @return 1 se o território existe, 0 caso contrário
 */
int territorioExiste(const char *nomeTerritorio, Territorio *territorios, int totalTerritorio)
{
    for (int i = 0; i < totalTerritorio; i++)
    {
        if (strcmp(territorios[i].nome, nomeTerritorio) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * Verifica se existe algum território com a cor especificada
 * @param cor Cor a ser procurada
 * @param territorios Array de territórios onde buscar
 * @param totalTerritorio Número total de territórios
 * @return 1 se a cor existe, 0 caso contrário
 */
int corExiste(const char *cor, Territorio *territorios, int totalTerritorio)
{
    for (int i = 0; i < totalTerritorio; i++)
    {
        if (strcmp(territorios[i].cor, cor) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * Verifica se todos os territórios possuem a mesma cor (condição de vitória)
 * @param territorios Array de territórios a ser verificado
 * @param totalTerritorio Número total de territórios
 * @return 1 se todos têm a mesma cor, 0 caso contrário
 */
int allSameColor(Territorio *territorios, int totalTerritorio)
{
    for (int i = 1; i < totalTerritorio; i++)
    {
        if (strcmp(territorios[0].cor, territorios[i].cor) != 0)
        {
            return 0;
        }
    }
    return 1;
}