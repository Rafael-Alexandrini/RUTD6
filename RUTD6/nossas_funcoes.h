#ifndef NOSSAS_FUNCOES_H_   /* Include guard */
#define NOSSAS_FUNCOES_H_
#include "raylib.h"

<<<<<<< Updated upstream
=======
#define LARGURA 1200
#define ALTURA 600
#define N_COLUNAS 60
#define N_LINHAS 30
#define TAM_GRID 20
#define N_MAX_MONSTROS 10
#define PLAYER_VIDAS 10
#define MAX_RECURSOS 10
#define MAX_BOMBAS 10
>>>>>>> Stashed changes


void funcao_exemplo();

<<<<<<< Updated upstream
void desenha_mapa(char mapa[31][61], int nLinhas, int nColunas, int tamGrid, Color fundo, Texture2D tijolo, Texture2D obstaculo, Texture2D base, Texture2D portal);
=======
void desenha_mapa(char mapa[31][61], Color fundo, Texture2D tijolo, Texture2D base, Texture2D portal);
>>>>>>> Stashed changes

void tenta_mover(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas);

void entra_portal(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas);




#endif // NOSSAS_FUNCOES_H_
