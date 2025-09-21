#include <stdio.h>  // scanf, printf e fgets
#include <string.h> // manipular strings
#include <stdlib.h> // talvez p exit
#include <time.h>   // srand
#include <ctype.h>  // tolower

// Vetor de missões disponíveis
const char *missoes[] = {
    "conquistar território vermelho",
    "conquistar território azul",
    "conquistar território verde",
    "conquistar território preto",
    "conquistar território amarelo",
    "conquistar território branco",
    "conquistar áfrica",
    "conquistar europa",
    "conquistar oceania",
    "conquistar ásia",
    "conquistar américa"};
const int TOTAL_MISSOES = 11;

// Struct - Território
typedef struct
{
  char nome[30];
  char cor[10];
  int tropas;
} Territorio;

// Struct - Jogador
typedef struct
{
  char nome[30];
  char *missao;              // Missão alocada dinamicamente
  int cumprida;              // 0 = não, 1 = sim, -1 = eliminado
  int *territorios;          // Array de índices dos territórios que possui
  int numTerritorios;        // Quantidade de territórios que possui
  int capacidadeTerritorios; // Capacidade máxima do array (para realloc)
} Jogador;

// Função para limpar o buffer de entrada
void limparBufferEntrada()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Função para normalizar nomes de territórios
void normalizarNomeTerritorio(char *nome)
{
  // Converter para minúsculas primeiro
  for (int i = 0; nome[i]; i++)
  {
    nome[i] = tolower(nome[i]);
  }

  // Adicionar acentos conforme necessário
  if (strcmp(nome, "africa") == 0)
  {
    strcpy(nome, "áfrica");
  }
  else if (strcmp(nome, "america") == 0)
  {
    strcpy(nome, "américa");
  }
  else if (strcmp(nome, "asia") == 0)
  {
    strcpy(nome, "ásia");
  }
}

// Função para adicionar território a um jogador
void adicionarTerritorio(Jogador *jogador, int indiceTerritorio)
{
  // Se precisa expandir o array
  if (jogador->numTerritorios >= jogador->capacidadeTerritorios)
  {
    jogador->capacidadeTerritorios *= 2;
    jogador->territorios = realloc(jogador->territorios,
                                   jogador->capacidadeTerritorios * sizeof(int));
  }

  jogador->territorios[jogador->numTerritorios] = indiceTerritorio;
  jogador->numTerritorios++;
}

// Função para remover território de um jogador
void removerTerritorio(Jogador *jogador, int indiceTerritorio)
{
  // Encontrar e remover território do array
  for (int i = 0; i < jogador->numTerritorios; i++)
  {
    if (jogador->territorios[i] == indiceTerritorio)
    {
      // Mover todos os elementos seguintes uma posição para trás
      for (int j = i; j < jogador->numTerritorios - 1; j++)
      {
        jogador->territorios[j] = jogador->territorios[j + 1];
      }
      jogador->numTerritorios--;
      break;
    }
  }
}

// Função para encontrar o dono de um território
int encontrarDonoTerritorio(Jogador *jogadores, int totalJogadores, int indiceTerritorio)
{
  for (int i = 0; i < totalJogadores; i++)
  {
    for (int j = 0; j < jogadores[i].numTerritorios; j++)
    {
      if (jogadores[i].territorios[j] == indiceTerritorio)
      {
        return i; // Retorna índice do jogador dono
      }
    }
  }
  return -1; // Território sem dono (erro)
}

// Função para verificar se um território existe no jogo
int territorioExiste(const char *nomeTerritorio, Territorio *territorios, int totalTerritorio)
{
  for (int i = 0; i < totalTerritorio; i++)
  {
    if (strcmp(territorios[i].nome, nomeTerritorio) == 0)
    {
      return 1; // Território existe
    }
  }
  return 0; // Território não existe
}

// Função para verificar se uma cor existe no jogo
int corExiste(const char *cor, Territorio *territorios, int totalTerritorio)
{
  for (int i = 0; i < totalTerritorio; i++)
  {
    if (strcmp(territorios[i].cor, cor) == 0)
    {
      return 1; // Cor existe
    }
  }
  return 0; // Cor não existe
}

// Função para verificar se uma missão é válida para um jogador
int verificarMissaoValida(const char *missao, Territorio *territorios,
                          int totalTerritorio, Jogador *jogador)
{
  // Se missão é sobre cor
  if (strstr(missao, "território") != NULL)
  {
    char corMissao[10];
    sscanf(missao, "conquistar território %s", corMissao);

    // NOVA VERIFICAÇÃO: Verificar se a cor existe no jogo
    if (!corExiste(corMissao, territorios, totalTerritorio))
    {
      return 0; // Missão inválida - cor não existe no jogo
    }

    // Verificar se jogador já possui território dessa cor
    for (int i = 0; i < jogador->numTerritorios; i++)
    {
      int indiceTerritorio = jogador->territorios[i];
      if (strcmp(territorios[indiceTerritorio].cor, corMissao) == 0)
      {
        return 0; // Missão inválida
      }
    }
  }

  // Se missão é sobre continente
  if (strstr(missao, "conquistar ") != NULL && strstr(missao, "território") == NULL)
  {
    char continenteMissao[30];
    sscanf(missao, "conquistar %s", continenteMissao);

    // NOVA VERIFICAÇÃO: Verificar se o território existe no jogo
    if (!territorioExiste(continenteMissao, territorios, totalTerritorio))
    {
      return 0; // Missão inválida - território não existe no jogo
    }

    // Verificar se jogador já possui território desse continente
    for (int i = 0; i < jogador->numTerritorios; i++)
    {
      int indiceTerritorio = jogador->territorios[i];
      if (strcmp(territorios[indiceTerritorio].nome, continenteMissao) == 0)
      {
        return 0; // Missão inválida
      }
    }
  }

  return 1; // Missão válida
}

// Função para atribuir missão aleatória a um jogador
void atribuirMissao(char *destino, const char *missoes[], int totalMissoes,
                    Territorio *territorios, int totalTerritorio, Jogador *jogador)
{
  int missaoValida = 0;
  int indiceMissao;

  do
  {
    indiceMissao = rand() % totalMissoes;
    missaoValida = verificarMissaoValida(missoes[indiceMissao], territorios,
                                         totalTerritorio, jogador);
  } while (!missaoValida);

  strcpy(destino, missoes[indiceMissao]);
}

// Função para verificar se um jogador cumpriu sua missão
int verificarMissao(char *missao, Territorio *mapa, int tamanho, Jogador *jogador)
{
  // Se missão é sobre cor específica
  if (strstr(missao, "território") != NULL)
  {
    char corMissao[10];
    sscanf(missao, "conquistar território %s", corMissao);

    // Verificar se jogador possui algum território dessa cor
    for (int i = 0; i < jogador->numTerritorios; i++)
    {
      int indiceTerritorio = jogador->territorios[i];
      if (strcmp(mapa[indiceTerritorio].cor, corMissao) == 0)
      {
        return 1; // Missão cumprida
      }
    }
  }

  // Se missão é sobre continente
  if (strstr(missao, "conquistar ") != NULL && strstr(missao, "território") == NULL)
  {
    char continenteMissao[30];
    sscanf(missao, "conquistar %s", continenteMissao);

    // Verificar se jogador possui território desse continente
    for (int i = 0; i < jogador->numTerritorios; i++)
    {
      int indiceTerritorio = jogador->territorios[i];
      if (strcmp(mapa[indiceTerritorio].nome, continenteMissao) == 0)
      {
        return 1; // Missão cumprida
      }
    }
  }

  return 0; // Missão não cumprida
}

// Função para exibir missão do jogador
void exibirMissao(char missao[])
{
  printf("Sua missão: %s\n", missao);
}

// Função para exibir menu principal
int exibirMenu(char *nomeJogador)
{
  int opcao;
  printf("\n=== MENU DO JOGADOR: %s ===\n", nomeJogador);
  printf("1. Atacar\n");
  printf("2. Verificar Missão\n");
  printf("3. Sair\n");
  printf("Escolha uma opção: ");
  scanf("%d", &opcao);
  limparBufferEntrada();
  return opcao;
}

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
    normalizarNomeTerritorio(territorios[i].nome); // Normalizar nome

    // Leitura da cor do exército
    printf("Digite a cor do exercito: ");
    scanf("%s", territorios[i].cor);
    // Converter cor para minúsculas para consistência
    for (int j = 0; territorios[i].cor[j]; j++)
    {
      territorios[i].cor[j] = tolower(territorios[i].cor[j]);
    }

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
void atacar(Territorio *atacante, Territorio *defensor, Jogador *jogadores,
            int totalJogadores, int indiceAtacante, int indiceDefensor)
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
    // Encontrar donos dos territórios
    int donoAtacante = encontrarDonoTerritorio(jogadores, totalJogadores, indiceAtacante);
    int donoDefensor = encontrarDonoTerritorio(jogadores, totalJogadores, indiceDefensor);

    // Se atacante venceu, ele ganha metade das tropas do defensor (arredondado para cima)
    if (vencedor == atacante)
    {
      // Atacante ganha metade das tropas do defensor original (antes de perder 1)
      int tropasOriginaisDefensor = defensor->tropas + 1;     // +1 porque já perdeu 1 tropa
      int metadeDefensor = (tropasOriginaisDefensor + 1) / 2; // Arredonda para cima

      // Atacante ganha as tropas
      atacante->tropas += metadeDefensor;

      // Defensor fica com o resto (pode ficar com 0 ou mais)
      defensor->tropas = tropasOriginaisDefensor - metadeDefensor;

      printf("Atacante %s ganhou %d tropas do defensor!\n", atacante->nome, metadeDefensor);
    }
    else
    {
      // Defensor venceu, mas atacante chegou a 0 tropas
      // Defensor ganha metade das tropas do atacante original
      int tropasOriginaisAtacante = atacante->tropas + 1;     // +1 porque já perdeu 1 tropa
      int metadeAtacante = (tropasOriginaisAtacante + 1) / 2; // Arredonda para cima

      // Defensor ganha as tropas
      defensor->tropas += metadeAtacante;

      // Atacante fica com o resto
      atacante->tropas = tropasOriginaisAtacante - metadeAtacante;

      printf("Defensor %s ganhou %d tropas do atacante!\n", defensor->nome, metadeAtacante);
    }

    // Transferir cor para o vencedor
    strcpy(perdedor->cor, vencedor->cor);

    // Transferir propriedade do território
    if (vencedor == atacante)
    {
      // Atacante venceu, pega território do defensor
      removerTerritorio(&jogadores[donoDefensor], indiceDefensor);
      adicionarTerritorio(&jogadores[donoAtacante], indiceDefensor);

      // Verificar se defensor perdeu todos os territórios
      if (jogadores[donoDefensor].numTerritorios == 0)
      {
        printf("Jogador %s foi eliminado! Missão descartada.\n",
               jogadores[donoDefensor].nome);
        jogadores[donoDefensor].cumprida = -1; // Marca como eliminado
      }
    }
    else
    {
      // Defensor venceu, pega território do atacante
      removerTerritorio(&jogadores[donoAtacante], indiceAtacante);
      adicionarTerritorio(&jogadores[donoDefensor], indiceAtacante);

      // Verificar se atacante perdeu todos os territórios
      if (jogadores[donoAtacante].numTerritorios == 0)
      {
        printf("Jogador %s foi eliminado! Missão descartada.\n",
               jogadores[donoAtacante].nome);
        jogadores[donoAtacante].cumprida = -1; // Marca como eliminado
      }
    }

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

  // Cada território representa um jogador
  int totalJogadores = totalTerritorio;

  // Alocar jogadores dinamicamente
  Jogador *jogadores = malloc(totalJogadores * sizeof(Jogador));
  if (jogadores == NULL)
  {
    printf("Erro: Falha na alocação de memória para jogadores.\n");
    free(territorios);
    return 1;
  }

  // Inicializar gerador de números aleatórios
  srand(time(NULL));

  // Cadastrar cada jogador e associar automaticamente com seu território
  for (int i = 0; i < totalJogadores; i++)
  {
    printf("\n--- CADASTRANDO JOGADOR %d ---\n", i + 1);
    printf("Digite o nome do jogador dono do território %s: ", territorios[i].nome);
    scanf("%s", jogadores[i].nome);

    // Inicializar array de territórios
    jogadores[i].capacidadeTerritorios = 2; // Começa com capacidade para 2
    jogadores[i].territorios = malloc(jogadores[i].capacidadeTerritorios * sizeof(int));
    jogadores[i].numTerritorios = 0;

    // Adicionar território automaticamente (cada jogador começa com o território i)
    adicionarTerritorio(&jogadores[i], i);

    // Alocar e atribuir missão
    jogadores[i].missao = malloc(100 * sizeof(char));
    atribuirMissao(jogadores[i].missao, missoes, TOTAL_MISSOES,
                   territorios, totalTerritorio, &jogadores[i]);

    jogadores[i].cumprida = 0;

    printf("Jogador %s, ", jogadores[i].nome);
    exibirMissao(jogadores[i].missao);
  }

  // Fase de ataque em loop com turnos por jogador
  int jogadorAtual = 0;
  while (1)
  {
    // Pular jogadores eliminados
    int tentativas = 0;
    while (jogadores[jogadorAtual].cumprida == -1 && tentativas < totalJogadores)
    {
      jogadorAtual = (jogadorAtual + 1) % totalJogadores;
      tentativas++;
    }

    // Se todos os jogadores foram eliminados exceto um
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

    // Exibir menu e processar opção
    int opcao = exibirMenu(jogadores[jogadorAtual].nome);

    if (opcao == 3)
    {
      break; // Sair do jogo
    }
    else if (opcao == 2)
    {
      // Verificar missão
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
      continue; // Volta para o menu sem mudar de jogador
    }
    else if (opcao == 1)
    {
      // Atacar
      exibirMapa(territorios, totalTerritorio); // Mostra mapa para facilitar seleção
      printf("Escolha o territorio atacante (1 a %d), ou 0 para cancelar: ", totalTerritorio);
      int atacanteIndex;
      scanf("%d", &atacanteIndex);
      limparBufferEntrada(); // Limpa o buffer após scanf
      if (atacanteIndex == 0)
      {
        continue; // Volta para o menu sem mudar de jogador
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

      // Verificar se o jogador atual possui o território atacante
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

      // Imprimir mapa atualizado
      printf("\n--- MAPA MUNDO - ESTADO ATUAL ---\n");
      exibirMapa(territorios, totalTerritorio);

      // Verificar se jogador atual cumpriu sua missão
      if (verificarMissao(jogadores[jogadorAtual].missao, territorios, totalTerritorio,
                          &jogadores[jogadorAtual]))
      {
        printf("VITÓRIA POR MISSÃO! Jogador %s cumpriu: %s\n",
               jogadores[jogadorAtual].nome, jogadores[jogadorAtual].missao);
        break;
      }

      // Verificar se todos territórios têm a mesma cor (vitória por dominação)
      if (allSameColor(territorios, totalTerritorio))
      {
        // Encontrar vencedor pela cor dominante
        char *corVencedora = territorios[0].cor;
        for (int i = 0; i < totalJogadores; i++)
        {
          if (jogadores[i].cumprida != -1)
          { // Jogador não eliminado
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

      // Fim da lógica de ataque - próximo jogador
      jogadorAtual = (jogadorAtual + 1) % totalJogadores;
      printf("Pressione ENTER para continuar para o proximo turno...");
      getchar(); // Buffer já limpo
    }
    else
    {
      // Opção inválida
      printf("Opção inválida! Escolha 1, 2 ou 3.\n");
      printf("Pressione ENTER para continuar...");
      getchar();
      continue; // Volta para o menu sem mudar de jogador
    }
  }

  // Liberar memória
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