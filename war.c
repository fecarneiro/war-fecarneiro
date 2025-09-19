#include <stdio.h>  // scanf, printf e fgets
#include <string.h> // manipular strings
#include <stdlib.h> // talvez p exit

// Struct - Território
typedef struct
{
  char nome[30];
  char cor[10];
  int tropas;
} Territorio;

int main()
{
  // // Vetor Estático de Território com 5 elementos
  // Territorio territorios[5];

  printf("--- WAR ESTRUTURADO - CADASTRO DE TERRITORIOS ---\n\n");
  printf("Digite a quantidade de Territórios:\n\n");
  // Leitura da quantidade de territórios
  int quantidade;
  scanf("%d", &quantidade);

  // Laço para interagir com user no terminal
  for (int i = 0; i < quantidade; i++)
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

  for (int i = 0; i < 5; i++)
  {
    printf("%-20s %-15s %d\n",
           territorios[i].nome,
           territorios[i].cor,
           territorios[i].tropas);
  }
  return 0;
}