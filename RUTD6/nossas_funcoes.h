#ifndef NOSSAS_FUNCOES_H_   /* Include guard */
#define NOSSAS_FUNCOES_H_
#include "raylib.h"



void funcao_exemplo();

void desenha_mapa(char mapa[31][61], int nLinhas, int nColunas, int tamGrid, Color fundo, Texture2D tijolo, Texture2D obstaculo, Texture2D base, Texture2D portal);

void tenta_mover(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas);

void entra_portal(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas);

void move_inimigo(int *pX, int *pY, int *dirX, int *dirY, char mapa[31][61], int nLinhas, int nColunas);

void nova_direcao(int *dirX, int *dirY, int boolDirecao);

int pode_mover_inimigo(int pX, int pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas);

#endif // NOSSAS_FUNCOES_H_
