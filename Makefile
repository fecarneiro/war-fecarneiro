# Makefile para o jogo WAR

# Configurações do compilador
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Nome do executável
TARGET = war

# Arquivos fonte
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Regra principal
all: $(OBJDIR) $(TARGET)

# Criar diretório de objetos
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compilar o executável
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compilar arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Regras que não criam arquivos
.PHONY: all clean run

# Dependências específicas
$(OBJDIR)/main.o: $(INCDIR)/territorios.h $(INCDIR)/jogadores.h $(INCDIR)/missoes.h $(INCDIR)/batalha.h $(INCDIR)/utils.h
$(OBJDIR)/territorios.o: $(INCDIR)/territorios.h $(INCDIR)/utils.h
$(OBJDIR)/jogadores.o: $(INCDIR)/jogadores.h $(INCDIR)/territorios.h
$(OBJDIR)/missoes.o: $(INCDIR)/missoes.h $(INCDIR)/territorios.h $(INCDIR)/jogadores.h
$(OBJDIR)/batalha.o: $(INCDIR)/batalha.h $(INCDIR)/territorios.h $(INCDIR)/jogadores.h
$(OBJDIR)/utils.o: $(INCDIR)/utils.h