#include <stdio.h>  // scanf, printf e fgets
#include <string.h> // manipular strings
#include <stdlib.h> // talvez p exit
#include <time.h>   // srand

// Struct - Território
typedef struct
{
  char nome[30];
  char cor[10];
  int tropas;
} Territorio;

// Função para simular o ataque entre dois territórios
void atacar(Territorio *atacanteIndex, Territorio *defensorIndex)
{
  srand(time(NULL));
  int numeroDadoAtacante = (rand() % 6) + 1;
  int numeroDadoDefensor = (rand() % 6) + 1;

  // se atacante perder = perde uma tropa
  {

    if (numeroDadoAtacante > numeroDadoDefensor)
    {
      printf("%s conquistou %s!\n", atacanteIndex->nome, defensorIndex->nome);
      defensorIndex->tropas = -1; // Defensor perde todas as tropas
    }
    else
    {
      printf("%s defendeu com sucesso contra %s!\n", defensorIndex->nome, atacanteIndex->nome);
      atacanteIndex->tropas = -1; // Atacante perde todas as tropas
    }
  };

  // Função Principal
  int main()
  {

    printf("--- WAR ESTRUTURADO - CADASTRO DE TERRITORIOS ---\n\n");
    printf("Digite a quantidade de Territórios desejada:\n\n");

    int totalTerritorio;
    // Leitura da quantidade de territórios
    scanf("%d", &totalTerritorio);
    // Alocação dinâmica de memória para os territórios
    Territorio *territorios = calloc(totalTerritorio, sizeof(Territorio));
    if (territorios == NULL)
    {
      printf("Erro: Falha na alocação de memória.\n");
      return 1; // Ou exit(1);
    }

    // Laço para interagir com user no terminal
    for (int i = 0; i < totalTerritorio; i++)
    {
      printf("  --- CADASTRANDO TERRITORIO: %d --- \n", i + 1);

      // Leitura do nome do território
      printf("Digite o nome do territorio: ");
      scanf("%s", territorios[i].nome);

      // Leitura da cor do exército
      printf("Digite a cor do exercito: ");
      scanf("%s", territorios[i].cor);

      // Leitura do número de tropas
      printf("Digite o numero de tropas: ");
      scanf("%d", &territorios[i].tropas);

      printf("\n");
    }
    // Exibição dos dados cadastrados
    printf("\n--- MAPA ATUAL DOS TERRITORIOS ---\n");
    printf("%-20s %-15s %s\n", "TERRITORIO", "COR DO EXERCITO", "TROPAS");
    printf("%-20s %-15s %s\n", "----------", "---------------", "------");

    for (int i = 0; i < totalTerritorio; i++)
    {
      printf("%-20s %-15s %d\n",
             territorios[i].nome,
             territorios[i].cor,
             territorios[i].tropas);
    }

    // Escolha um território para atacar outro
    // Liberação da memória alocada
    // Fase de ataque
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio atacante(1 a %d), ou 0 para sair: ", totalTerritorio);
    printf("Escolha o territorio defensor(1 a %d): ", totalTerritorio);
    int atacanteIndex, defensorIndex;
    scanf("%d", &atacanteIndex);
    if (atacanteIndex == 0)
    {
      free(territorios);
      return 0; // Sai do programa
    }
    scanf("%d", &defensorIndex);

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante {nome} rolou um dado e tirou: {numero} ");
    printf("O defensor {nome} rolou um dado e tirou: {numero} ");
    printf("VITORIA DO ATACANTE - O territorio {nome} conquistou o territorio {nome}");
    printf("VITORIA DO DEFENSOR - O territorio {nome} defendeu o territorio {nome}");
    printf("Pressione ENTER para continuar para o próximo turno...");

    printf("\n--- MAPA MUNDO - ESTADO ATUAL ---\n");
    printf("\n--- MAPA ATUAL DOS TERRITORIOS ---\n");
    printf("{numero} - {territorio} {cor} - {tropas} tropas\n");
    free(territorios);
    return 0;
  }