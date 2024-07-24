#ifndef NOSSAS_FUNCOES_H_   /* Include guard */
#define NOSSAS_FUNCOES_H_
#include "raylib.h"



void funcao_exemplo();

void desenha_mapa(char mapa[31][61], int nLinhas, int nColunas, int tamGrid, Color fundo, Texture2D tijolo, Texture2D obstaculo, Texture2D base, Texture2D portal);

void tentaMover(int *pX, int *pY, int dirX, int dirY, char mapa[31][61]);


#endif // NOSSAS_FUNCOES_H_
