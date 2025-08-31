#include <stdio.h> // scanf, printf e fgets
#include <string.h>  // manipular strings
#include <stdlib.h> // talvez p exit

// Struc - Território
struct Terrotorio {
  char nome[50];
  char cor [10];
  int tropas;
};

// Função para limpar buffer
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {}
}

int main () { 
  // Vetor Estático de Território com 5 elementos 
  struct Terrotorio territorio[5];

  // Variável para armazenamento de territórios e opção do user
  int totalTerritorios = 0;
  int opcao;

  // Laço para interagir com user no terminal
  do {
    printf(" --- MENU PARA CADASTRAR TERRITORIO( --- ")
    printf(" ")
    printf(" ")
    printf(" ")
    printf(" ")
  }

  return 0
}



// - Terminal: Cadastrar os dados de cada território: **Nome**, **Cor do Exército**, e **Número de Tropas**.
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