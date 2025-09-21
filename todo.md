2-5 jogadores cadastrados após territórios
Cores disponíveis: vermelho, azul, verde, preto, amarelo, branco
Continentes: áfrica, europa, oceania, ásia, américa (baseados no nome do território)
Loop contínuo com turnos intercalados entre jogadores
Missões não podem coincidir com território/cor própria do jogador

# Requisitos funcionais

Criação do vetor de missões: declarar um vetor de strings contendo ao menos cinco descrições diferentes de missões estratégicas (ex: Conquistar 3 territórios seguidos, Eliminar todas as tropas da cor vermelha etc.).

Sorteio da missão: implementar a função void atribuirMissao(char* destino, char* missoes[], int totalMissoes) que sorteia uma missão e copia para a variável de missão do jogador usando strcpy.

Armazenamento e acesso: a missão de cada jogador deve ser armazenada dinamicamente utilizando malloc.

Verificação da missão: implementar a função int verificarMissao(char* missao, Territorio* mapa, int tamanho), que avalia se a missão do jogador foi cumprida (crie uma lógica simples inicial para verificação).

Exibição condicional: o sistema deve verificar, ao final de cada turno, se algum jogador cumpriu sua missão e declarar o vencedor.

Use srand(time(NULL)) para gerar números aleatórios.

Missões Disponíveis:
Conquistar o território vermelho
Conquistar o território azul
Conquistar o território verde
conquistar o território preto
conquistar o território amarelo
conquistar o território branco
Conquistar a áfrica
conquistar a europa
conquistar a oceania
conquistar a ásia
conquistar a américa

No sorteio de missões, verificar se os jogadores cadastrados possuem a cor e nome de território

Armazenamento e acesso: a missão de cada jogador deve ser armazenada dinamicamente utilizando malloc (vinculado ao type de território)

Passagem por valor e referência: a missão deve ser passada por valor para exibição e por referência para atribuição e verificação.

Uso de ponteiros: as missões dos jogadores devem ser manipuladas por meio de ponteiros.

Exibição condicional: o sistema deve verificar, ao final de cada turno, se algum jogador cumpriu sua missão e declarar o vencedor.

#

Modularização: o código deve estar dividido em funções específicas, como atribuirMissao, verificarMissao, exibirMissao, atacar, exibirMapa, liberarMemoria, e a main.

Interface intuitiva: o sistema deve exibir a missão ao jogador apenas uma vez (no início) e verificar silenciosamente se ela foi cumprida ao longo da execução.

Bibliotecas necessárias: inclua stdio.h, stdlib.h, string.h e time.h.

Alocação de memória: use calloc ou malloc para alocar os vetores de territórios e armazenar a missão de cada jogador.

Atualização de campos: transfira a cor e metade das tropas para o território defensor se o atacante vencer. Caso contrário, o atacante perde uma tropa.

Função de liberação: implemente void liberarMemoria(...) para liberar toda a memória alocada dinamicamente (territórios e missões).

### ⚙️ Funcionalidades

- Inicialização automática dos territórios
- Menu principal com 3 opções:
  1. Atacar
  2. Verificar Missão
  3. Sair
- Verificação de vitória da missão

### 💡 Conceitos abordados

- Modularização
- `const` correctness
- Estruturação em múltiplas funções
- Passagem por referência

### 📥 Entrada

- Ações do jogador via menu:
  - `1` - Atacar
  - `2` - Verificar Missão
  - `0` - Sair
- Escolha de territórios para ataque

### 📤 Saída

- Mapa atualizado
- Resultados das batalhas
- Verificação da missão
- Mensagem de vitória
