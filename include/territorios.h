#ifndef TERRITORIOS_H
#define TERRITORIOS_H

typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void cadastrarTerritorios(Territorio *territorios, int totalTerritorio);
void exibirMapa(Territorio *territorios, int totalTerritorio);
int territorioExiste(const char *nomeTerritorio, Territorio *territorios, int totalTerritorio);
int corExiste(const char *cor, Territorio *territorios, int totalTerritorio);
int allSameColor(Territorio *territorios, int totalTerritorio);

#endif