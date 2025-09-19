#include <stdio.h>  // scanf, printf e fgets
#include <string.h> // manipular strings
#include <stdlib.h> // talvez p exit

// Struct - Território
typedef struct {
  char nome[30];
  char cor[10];
  int tropas;
} Territorio;

// Função para limpar buffer
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
};

int main()
{
  // Vetor Estático de Território com 5 elementos
  Territorio territorios[5];

  printf("=== DESAFIO WAR ESTRUTURADO - CADASTRO DE TERRITORIOS ===\n\n");
  printf("Vamos cadastrar 5 territórios para o jogo WAR!\n\n");

  // Laço para interagir com user no terminal
  for (int i = 1; i < 5; i ++) {
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
  printf("\n=== MAPA ATUAL DOS TERRITORIOS ===\n");
  printf("%-20s %-15s %s\n", "TERRITORIO", "COR DO EXERCITO", "TROPAS");
  printf("%-20s %-15s %s\n", "----------", "---------------", "------");

  for (int i = 0; i < 5; i++) {
      printf("%-20s %-15s %d\n", 
            territorios[i].nome, 
            territorios[i].cor, 
            territorios[i].tropas);
  }

  // Estatísticas básicas
  int totalTropas = 0;
  for (int i = 0; i < 5; i++) {
      totalTropas += territorios[i].tropas;
  }

  printf("\n=== ESTATISTICAS ===\n");
  printf("Total de territorios: 5\n");
  printf("Total de tropas no mapa: %d\n", totalTropas);
  printf("Media de tropas por territorio: %.1f\n", (float)totalTropas / 5);

  return 0;

}