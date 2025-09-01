#include <stdio.h>  // scanf, printf e fgets
#include <string.h> // manipular strings
#include <stdlib.h> // talvez p exit

// Struct - Território
struct Terrotorio
{
  char nome[30];
  char cor[10];
  int tropas;
};

// Função para limpar buffer
void limparBufferEntrada()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}

int main()
{
  // Vetor Estático de Território com 5 elementos
  struct Territorio territorio[5];

  // Variável para armazenamento de territórios e opção do user
  int totalTerritorios = 0;
  int opcao;

  // Laço para interagir com user no terminal
  do
  {
    printf(" --- MENU PARA CADASTRAR TERRITORIO --- ");
    printf("1 - Cadastrar novo territorio\n");
    printf("2 - Listar todos territorios\n");
    printf("0 - Sair\n");
    printf(" ---------------------------------------- ");
    printf(" Escolha uma opção: ");

    scanf("%d", &opcao);
    limparBufferEntrada();
  }

  switch (opcao)
  {
  case 1:
    printf("  --- CADASTRO DE NOVO TERRITORIO --- \n\n");

    if (totalTerritorios < MAX_TERRITORIOS)
    {
      printf("Nome do Territorio: ");
      fgets(territorio[totalTerritorios].nome, TAM_STRING, stdin);

      printf("Cor do Território: ");
      fgets(territorio[totalTerritorios].cor, TAM_STRING, stdin);

      printf("Número de Tropas: ");
      fgets(territorio[totalTerritorios].tropas, TAM_STRING, stdin);
      limparBufferEntrada();
    }
    break;

  default:
    break;
  }
  else
  {
  }

  return 0
}

//  **Nome**, **Cor do Exército**, e **Número de Tropas**.
// - Exibir o estado atual do mapa.

// ### ⚙️ Funcionalidades

// - Leitura de dados pelo terminal (`fgets` e `scanf`)
// - Impressão organizada dos dados de todos os territórios

// ### 💡 Conceitos abordados

// - `struct`
// - Vetor estático
// - Entrada/saída com `scanf`, `fgets`, e `printf`

// ### 📥 Entrada

// O usuário digita o nome do território, a cor do exército dominante e o número de tropas para **cada um dos 5 territórios**.

// ### 📤 Saída