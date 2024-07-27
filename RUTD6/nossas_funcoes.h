#ifndef NOSSAS_FUNCOES_H_   /* Include guard */
#define NOSSAS_FUNCOES_H_
#include "raylib.h"
#include "estruturas.h"

#define LARGURA 1200
#define ALTURA 600
#define N_COLUNAS 60
#define N_LINHAS 30
#define TAM_GRID 20
#define N_MAX_MONSTROS 10
#define PLAYER_VIDAS 10


void funcao_exemplo();

void desenha_mapa(char mapa[31][61], Color fundo, Texture2D tijolo, Texture2D obstaculo, Texture2D base, Texture2D portal);

void tenta_mover(int *pX, int *pY, int dirX, int dirY, char mapa[31][61]);

void entra_portal(int *pX, int *pY, int dirX, int dirY, char mapa[31][61]);

void move_inimigo(struct Inimigo *pInimigo, char mapa[31][61]);

void nova_direcao(int *dirX, int *dirY, int boolDirecao);

int pode_mover_inimigo(int pX, int pY, int dirX, int dirY, char mapa[31][61]);

#endif // NOSSAS_FUNCOES_H_
