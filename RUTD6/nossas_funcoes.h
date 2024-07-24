#ifndef NOSSAS_FUNCOES_H_   /* Include guard */
#define NOSSAS_FUNCOES_H_



void funcao_exemplo();

void desenha_mapa(char mapa[31][61], int nLinhas, int nColunas, int tamGrid);

void tenta_mover(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas);
<<<<<<< Updated upstream

void entra_portal(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas);
=======
>>>>>>> Stashed changes

void entra_portal(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas);

#endif // NOSSAS_FUNCOES_H_
