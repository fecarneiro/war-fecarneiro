#include <stdio.h>  // scanf, printf e fgets
#include <string.h> // manipular strings
#include <stdlib.h> // talvez p exit
#include <time.h>   // srand

// Função para limpar o buffer de entrada
void limparBufferEntrada()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Struct - Território
typedef struct
{
  char nome[30];
  char cor[10];
  int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *territorios, int totalTerritorio)
{
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
}

// Função para exibir o mapa dos territórios
void exibirMapa(Territorio *territorios, int totalTerritorio)
{
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
}

// Função para simular o ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor, int *dadoAtac, int *dadoDef)
{
  srand(time(NULL));
  *dadoAtac = (rand() % 6) + 1;
  *dadoDef = (rand() % 6) + 1;

  if (*dadoAtac > *dadoDef)
  {
    if (defensor->tropas == 1)
    {
      printf("VITORIA DO ATACANTE - O territorio %s conquistou o territorio %s!\n", atacante->nome, defensor->nome);
      strcpy(defensor->cor, atacante->cor); // Corrigido: defensor assume a cor do atacante
      defensor->tropas = 1;                 // Conquistado com 1 tropa
      atacante->tropas -= 1;                // Atacante perde 1
      return;
    }
    defensor->tropas -= 1; // Defensor perde 1
    printf("VITORIA DO ATACANTE - O territorio %s conquistou uma tropa de %s!\n", atacante->nome, defensor->nome);
  }
  else
  {
    if (atacante->tropas == 1)
    {
      printf("VITORIA DO DEFENSOR - O territorio %s conquistou o territorio %s!\n", defensor->nome, atacante->nome);
      strcpy(atacante->cor, defensor->cor); // Corrigido: atacante assume a cor do defensor
      atacante->tropas = 1;                 // Conquistado com 1 tropa
      defensor->tropas -= 1;                // Defensor perde 1
      return;
    }
    atacante->tropas -= 1; // Atacante perde 1
    printf("VITORIA DO DEFENSOR - O territorio %s defendeu com sucesso contra %s!\n", defensor->nome, atacante->nome);
  }
}

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

  // Chama a função de cadastro
  cadastrarTerritorios(territorios, totalTerritorio);

  // Exibe o mapa inicial
  exibirMapa(territorios, totalTerritorio);

  // Fase de ataque em loop
  while (1)
  {
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio atacante (1 a %d), ou 0 para sair: ", totalTerritorio);
    int atacanteIndex;
    scanf("%d", &atacanteIndex);
    limparBufferEntrada(); // Limpa o buffer após scanf
    if (atacanteIndex == 0)
    {
      break; // Sai do loop
    }
    printf("Escolha o territorio defensor (1 a %d): ", totalTerritorio);
    int defensorIndex;
    scanf("%d", &defensorIndex);
    limparBufferEntrada(); // Limpa o buffer após scanf

    // Consideramos: 0-based
    atacanteIndex--;
    defensorIndex--;

    if (atacanteIndex < 0 || atacanteIndex >= totalTerritorio ||
        defensorIndex < 0 || defensorIndex >= totalTerritorio ||
        atacanteIndex == defensorIndex)
    {
      printf("Selecao invalida. Tente novamente.\n");
      continue;
    }

    int dadoAtac, dadoDef;
    atacar(&territorios[atacanteIndex], &territorios[defensorIndex], &dadoAtac, &dadoDef);

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", territorios[atacanteIndex].nome, dadoAtac);
    printf("O defensor %s rolou um dado e tirou: %d\n", territorios[defensorIndex].nome, dadoDef);

    // Imprimir mapa atualizado
    printf("\n--- MAPA MUNDO - ESTADO ATUAL ---\n");
    printf("\n--- MAPA ATUAL DOS TERRITORIOS ---\n");
    for (int i = 0; i < totalTerritorio; i++)
    {
      printf("%d - %s %s - %d tropas\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }

    printf("Pressione ENTER para continuar para o proximo turno...");
    getchar(); // Buffer já limpo
  }

  free(territorios);
  return 0;
}