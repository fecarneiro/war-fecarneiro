#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/batalha.h"
#include "../include/jogadores.h"

/**
 * Executa uma batalha entre dois territórios através de dados
 * Gerencia a transferência de tropas, mudança de propriedade e eliminação de jogadores
 * @param atacante Ponteiro para o território atacante
 * @param defensor Ponteiro para o território defensor
 * @param jogadores Array de todos os jogadores do jogo
 * @param totalJogadores Número total de jogadores
 * @param indiceAtacante Índice do território atacante no array de territórios
 * @param indiceDefensor Índice do território defensor no array de territórios
 */
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

  perdedor->tropas -= 1;

  if (perdedor->tropas == 0)
  {
    int donoAtacante = encontrarDonoTerritorio(jogadores, totalJogadores, indiceAtacante);
    int donoDefensor = encontrarDonoTerritorio(jogadores, totalJogadores, indiceDefensor);

    if (vencedor == atacante)
    {
      int tropasOriginaisDefensor = defensor->tropas + 1;
      int metadeDefensor = (tropasOriginaisDefensor + 1) / 2;

      atacante->tropas += metadeDefensor;
      defensor->tropas = tropasOriginaisDefensor - metadeDefensor;

      printf("Atacante %s ganhou %d tropas do defensor!\n", atacante->nome, metadeDefensor);
    }
    else
    {
      int tropasOriginaisAtacante = atacante->tropas + 1;
      int metadeAtacante = (tropasOriginaisAtacante + 1) / 2;

      defensor->tropas += metadeAtacante;
      atacante->tropas = tropasOriginaisAtacante - metadeAtacante;

      printf("Defensor %s ganhou %d tropas do atacante!\n", defensor->nome, metadeAtacante);
    }

    strcpy(perdedor->cor, vencedor->cor);

    if (vencedor == atacante)
    {
      removerTerritorio(&jogadores[donoDefensor], indiceDefensor);
      adicionarTerritorio(&jogadores[donoAtacante], indiceDefensor);

      if (jogadores[donoDefensor].numTerritorios == 0)
      {
        printf("Jogador %s foi eliminado! Missão descartada.\n",
               jogadores[donoDefensor].nome);
        jogadores[donoDefensor].cumprida = -1;
      }
    }
    else
    {
      removerTerritorio(&jogadores[donoAtacante], indiceAtacante);
      adicionarTerritorio(&jogadores[donoDefensor], indiceAtacante);

      if (jogadores[donoAtacante].numTerritorios == 0)
      {
        printf("Jogador %s foi eliminado! Missão descartada.\n",
               jogadores[donoAtacante].nome);
        jogadores[donoAtacante].cumprida = -1;
      }
    }

    printf("CONQUISTA ESPECIAL: %s conquistou %s, transferindo cor e redistribuindo tropas (%d para %s, %d para %s).\n",
           vencedor->nome, perdedor->nome, perdedor->tropas, perdedor->nome, vencedor->tropas, vencedor->nome);
  }
  else
  {
    printf("O territorio %s perdeu 1 tropa.\n", perdedor->nome);
  }
}