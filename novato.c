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

  }


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