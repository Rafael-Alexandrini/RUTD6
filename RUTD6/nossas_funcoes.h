#ifndef NOSSAS_FUNCOES_H_   /* Include guard */
#define NOSSAS_FUNCOES_H_
#include "raylib.h"
#include "estruturas.h"

#define LARGURA 1200
#define ALTURA 600
#define N_COLUNAS 60
#define N_LINHAS 30
#define TAM_GRID 20
#define N_MAX_MONSTROS 2
#define PLAYER_VIDAS 10
#define MAX_RECURSOS 100
#define MAX_FONTES 5
#define MAX_MAPAS 6
#define PRIMEIRO_MAPA 1


void desenha_mapa(char mapa[N_LINHAS][N_COLUNAS], Color fundo, Texture2D tijolo, Texture2D base, Texture2D portal);

void tenta_mover(int *pX, int *pY, int dirX, int dirY, char mapa[N_LINHAS][N_COLUNAS]);

void entra_portal(int *pX, int *pY, int dirX, int dirY, char mapa[N_LINHAS][N_COLUNAS]);

void move_inimigo(struct Inimigo *pInimigo, char mapa[N_LINHAS][N_COLUNAS]);

void nova_direcao(int *dirX, int *dirY);

int pode_mover_inimigo(int pX, int pY, int dirX, int dirY, char mapa[N_LINHAS][N_COLUNAS]);

void pega_recurso (struct posicao *recurso);

void base_toma_dano (struct Inimigo *inimigo, struct base *base);

void mata_monstro (struct Inimigo *inimigo, struct bomba *bomba);

void acha_no_mapa (char mapa[N_LINHAS][N_COLUNAS], struct posicao *player, struct posicao *spawner, struct base *base, struct posicao recurso[MAX_RECURSOS]);

void zera_estado(int *vitoria, int *gameover, int *monstros_vivos, int *n_monstros_spawnados);

int carrega_mapa(char mapa[N_LINHAS][N_COLUNAS], int nMapa);

#endif // NOSSAS_FUNCOES_H_

