# WAR Game - Estruturado

Um jogo de estratégia baseado no clássico WAR, implementado em C com arquitetura modular.

## Estrutura do Projeto

```
war-game/
├── include/                  # Headers (.h) com assinaturas e structs
│   ├── territorios.h        # Gerenciamento de territórios
│   ├── jogadores.h          # Gerenciamento de jogadores
│   ├── missoes.h            # Sistema de missões
│   ├── batalha.h            # Sistema de combate
│   └── utils.h              # Funções utilitárias
├── src/                     # Implementações (.c)
│   ├── territorios.c        # Implementação de territórios
│   ├── jogadores.c          # Implementação de jogadores
│   ├── missoes.c            # Implementação de missões
│   ├── batalha.c            # Implementação de combate
│   ├── utils.c              # Implementação de utilitários
│   └── main.c               # Programa principal
├── Makefile                 # Automatiza compilação
└── README.md               # Este arquivo
```

## Como Compilar

### Usando o Makefile

Para compilar o projeto:

```bash
make
```

Para compilar e executar:

```bash
make run
```

Para limpar arquivos compilados:

```bash
make clean
```

### Compilação Manual

```bash
gcc -Wall -Wextra -std=c99 -g -Iinclude src/*.c -o war
```

## Como Jogar

1. Execute o programa compilado:

   ```bash
   ./war
   ```

2. Configure o jogo:

   - Digite a quantidade de territórios desejada (mínimo 2)
   - Para cada território, informe:
     - Nome do território
     - Cor do exército
     - Número de tropas
   - Para cada jogador, informe o nome

3. O jogo funcionará em turnos:
   - **Atacar**: Escolha um território seu para atacar um território inimigo
   - **Verificar Missão**: Veja sua missão atual e se foi cumprida
   - **Sair**: Encerrar o jogo

## Regras do Jogo

### Missões

Cada jogador recebe uma missão aleatória:

- Conquistar território de cor específica
- Conquistar continente específico

### Combate

- Atacante e defensor rolam dados (1-6)
- Maior valor vence
- Perdedor perde 1 tropa
- Se perdedor fica com 0 tropas:
  - Vencedor ganha metade das tropas originais do perdedor
  - Território muda de cor para a do vencedor
  - Transferência de propriedade

### Condições de Vitória

1. **Missão**: Cumprindo sua missão específica
2. **Dominação**: Conquistando todos os territórios (mesma cor)
3. **Eliminação**: Sendo o último jogador com territórios

## Módulos

### territorios.h/c

- Estrutura `Territorio`
- Cadastro e exibição de territórios
- Validação de territórios e cores

### jogadores.h/c

- Estrutura `Jogador`
- Gerenciamento de propriedade de territórios
- Adição/remoção de territórios

### missoes.h/c

- Array de missões disponíveis
- Atribuição e validação de missões
- Verificação de cumprimento

### batalha.h/c

- Sistema de combate entre territórios
- Resolução de ataques
- Transferência de territórios

### utils.h/c

- Limpeza de buffer de entrada
- Normalização de nomes
- Interface de menu

## Requisitos

- Compilador GCC
- Sistema Unix/Linux (para Makefile)
- Make (opcional, para usar Makefile)

## Autor

Projeto desenvolvido como exercício de programação em C com arquitetura modular.

# 🗺️ Desafio WAR Estruturado – Conquista de Territórios

Bem-vindo ao **Desafio WAR Estruturado!** Inspirado no famoso jogo de estratégia, este desafio convida você a programar diferentes versões do jogo WAR, evoluindo seus conhecimentos em **C** à medida que avança pelos níveis **Novato**, **Aventureiro** e **Mestre**.

A empresa **MateCheck** contratou você para criar uma versão estruturada do WAR. Cada nível propõe novas funcionalidades, conceitos e desafios de programação. **Você escolhe por onde começar!**

---

## 🧩 Nível Novato: Cadastro Inicial dos Territórios

### 🎯 Objetivo

- Criar uma `struct` chamada `Territorio`.
- Usar um **vetor estático de 5 elementos** para armazenar os territórios.
- Cadastrar os dados de cada território: **Nome**, **Cor do Exército**, e **Número de Tropas**.
- Exibir o estado atual do mapa.

### ⚙️ Funcionalidades

- Leitura de dados pelo terminal (`fgets` e `scanf`)
- Impressão organizada dos dados de todos os territórios

### 💡 Conceitos abordados

- `struct`
- Vetor estático
- Entrada/saída com `scanf`, `fgets`, e `printf`

### 📥 Entrada

O usuário digita o nome do território, a cor do exército dominante e o número de tropas para **cada um dos 5 territórios**.

### 📤 Saída

## 🧗‍♂️ Nível Aventureiro: Batalhas Estratégicas

### 🎯 Objetivo

- Substituir o vetor estático por **alocação dinâmica com `calloc`**
- Criar uma função para **simular ataques entre dois territórios**
- Utilizar números aleatórios para representar dados de batalha

### 🆕 Novidades em relação ao Nível Novato

- Alocação dinâmica de memória com `calloc`
- Uso de **ponteiros**
- Laço interativo para o jogador escolher **territórios para atacar e defender**
- Simulação de dados de ataque e defesa com `rand()`

### ⚙️ Funcionalidades

- Cadastro dos territórios (como no Nível Novato)
- Fase de ataque com:
  - Escolha de atacante e defensor
  - Dados de ataque/defesa
  - Lógica:
    - Se atacante vence → defensor perde 1 tropa
    - Se defensor perde todas → território é conquistado
    - Empates favorecem o atacante

### 💡 Conceitos abordados

- Ponteiros
- `calloc` / `free`
- Aleatoriedade com `rand()` / `srand()`
- Funções para modularização

### 📥 Entrada

- Território **atacante** (1 a 5)
- Território **defensor** (1 a 5)

### 📤 Saída

Exibição do resultado da batalha, dados sorteados e mudanças no mapa.

## 🧠 Nível Mestre: Missões e Modularização Total

### 🎯 Objetivo

- Dividir o código em funções bem definidas
- Implementar um **sistema de missões**
- Verificar cumprimento da missão
- Aplicar **boas práticas** (uso de `const`, modularização, etc.)

### 🆕 Diferenças em relação ao Nível Aventureiro

- Modularização total em funções
- Missões aleatórias atribuídas:
  1. Destruir o exército **Verde**
  2. Conquistar **3 territórios**
- Menu interativo com opções

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

## 🏁 Conclusão

Com este **Desafio WAR Estruturado**, você praticará fundamentos essenciais da linguagem **C** de forma **divertida e progressiva**.

Cada nível foca em um conjunto de habilidades:

- 🟢 **Novato**: `struct`, vetor, entrada/saída
- 🔵 **Aventureiro**: ponteiros, memória dinâmica, lógica de jogo
- 🟣 **Mestre**: modularização, design limpo, sistema de missões

🚀 **Boa sorte! Avance nos níveis e torne-se um mestre da programação estratégica!**

> Equipe de Ensino – MateCheck
