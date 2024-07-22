#ifndef NOSSAS_FUNCOES_H_   /* Include guard */
#define NOSSAS_FUNCOES_H_


void funcao_exemplo();

void desenha_mapa(char mapa[31][61], int nLinhas, int nColunas, int tamGrid);

void tentaMover(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int tamGrid);

#endif // NOSSAS_FUNCOES_H_
