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

// Função para verificar se todos os territórios têm a mesma cor
int allSameColor(Territorio *territorios, int totalTerritorio)
{
  for (int i = 1; i < totalTerritorio; i++)
  {
    if (strcmp(territorios[0].cor, territorios[i].cor) != 0)
    {
      return 0; // Falso
    }
  }
  return 1; // Verdadeiro
}

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

// Função para simular o ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor)
{
  srand(time(NULL));
  int dadoAtac = (rand() % 6) + 1;
  int dadoDef = (rand() % 6) + 1;

  printf("\n--- RESULTADO DA BATALHA ---\n");
  printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtac);
  printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDef);

  Territorio *vencedor = NULL;
  Territorio *perdedor = NULL;

  if (dadoAtac > dadoDef)
  {
    vencedor = atacante;
    perdedor = defensor;
    printf("VITORIA DO ATACANTE - O territorio %s venceu contra %s!\n", atacante->nome, defensor->nome);
  }
  else
  {
    vencedor = defensor;
    perdedor = atacante;
    printf("VITORIA DO DEFENSOR - O territorio %s defendeu com sucesso contra %s!\n", defensor->nome, atacante->nome);
  }

  // Subtrair 1 tropa do perdedor
  perdedor->tropas -= 1;

  // Se o perdedor ficou com 0 tropas, aplicar regras especiais
  if (perdedor->tropas == 0)
  {
    // Transferir cor para o vencedor
    strcpy(perdedor->cor, vencedor->cor);
    // Passar a tropa (1) para o vencedor
    int totalTropasVencedor = vencedor->tropas + 1;
    // Dividir por 2
    int metade = totalTropasVencedor / 2;
    // Perdedor (agora dominado) fica com metade
    perdedor->tropas = metade;
    // Vencedor fica com a outra metade
    vencedor->tropas = totalTropasVencedor - metade;
    printf("CONQUISTA ESPECIAL: %s conquistou %s, transferindo cor e redistribuindo tropas (%d para %s, %d para %s).\n",
           vencedor->nome, perdedor->nome, perdedor->tropas, perdedor->nome, vencedor->tropas, vencedor->nome);
  }
  else
  {
    // Se perdedor tinha mais de 1, apenas perdeu 1 tropa
    printf("O territorio %s perdeu 1 tropa.\n", perdedor->nome);
  }
}

// Função Principal
int main()
{
  printf("--- WAR ESTRUTURADO - CADASTRO DE TERRITORIOS ---\n\n");
  printf("Digite a quantidade de Territórios desejada:\n\n");

  int totalTerritorio;
  // Leitura da quantidade de territórios com validação
  do
  {
    scanf("%d", &totalTerritorio);
    if (totalTerritorio <= 1)
    {
      printf("Erro: A quantidade de territorios deve ser maior que 1. Tente novamente:\n");
    }
  } while (totalTerritorio <= 1);

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
    exibirMapa(territorios, totalTerritorio); // Mostra mapa para facilitar seleção
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

    // Validações adicionais
    if (atacanteIndex < 0 || atacanteIndex >= totalTerritorio ||
        defensorIndex < 0 || defensorIndex >= totalTerritorio ||
        atacanteIndex == defensorIndex)
    {
      printf("Selecao invalida. Tente novamente.\n");
      continue;
    }
    if (strcmp(territorios[atacanteIndex].cor, territorios[defensorIndex].cor) == 0)
    {
      printf("Erro: Nao pode atacar um territorio da mesma cor (mesmo dono).\n");
      continue;
    }

    atacar(&territorios[atacanteIndex], &territorios[defensorIndex]);

    // Imprimir mapa atualizado
    printf("\n--- MAPA MUNDO - ESTADO ATUAL ---\n");
    exibirMapa(territorios, totalTerritorio);

    // Verificar se o jogo acabou
    if (allSameColor(territorios, totalTerritorio))
    {
      printf("Jogo acabou! Todos os territorios possuem a mesma cor.\n");
      break;
    }

    printf("Pressione ENTER para continuar para o proximo turno...");
    getchar(); // Buffer já limpo
  }

  free(territorios);
  return 0;
}