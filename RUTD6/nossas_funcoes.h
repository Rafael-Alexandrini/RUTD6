#ifndef NOSSAS_FUNCOES_H_   /* Include guard */
#define NOSSAS_FUNCOES_H_
#include "raylib.h"
#include "estruturas.h"

#define LARGURA 1200
#define ALTURA 600
#define N_COLUNAS 60
#define N_LINHAS 30
#define TAM_GRID 20
#define N_MAX_MONSTROS 50
#define MAXCARAC 15
#define PLAYER_VIDAS 1
#define MAX_RECURSOS 50
#define MAX_FONTES 5
#define MAX_MAPAS 6
#define PRIMEIRO_MAPA 1
#define LOCAL_SAVE "./mapas/meusave.bin"


void desenha_mapa(char mapa[N_LINHAS][N_COLUNAS], Color fundo, Texture2D tijolo, Texture2D base, Texture2D portal, Texture2D cadeira);

void tenta_mover(int *pX, int *pY, int dirX, int dirY, char mapa[N_LINHAS][N_COLUNAS]);

void entra_portal(int *pX, int *pY, int dirX, int dirY, char mapa[N_LINHAS][N_COLUNAS]);

void move_inimigo(struct Inimigo *pInimigo, char mapa[N_LINHAS][N_COLUNAS]);

void nova_direcao(int *dirX, int *dirY);

int pode_mover_inimigo(int pX, int pY, int dirX, int dirY, char mapa[N_LINHAS][N_COLUNAS]);

void pega_recurso (struct posicao *recurso);

void mata_monstro (struct Inimigo *inimigo, struct bomba *bomba);

void acha_no_mapa (char mapa[N_LINHAS][N_COLUNAS], struct posicao *player, struct posicao *spawner, struct base *base, struct posicao recurso[MAX_RECURSOS], struct Inimigo monstros[N_MAX_MONSTROS], int *n_monstros_spawnados, int *monstros_vivos);

void zera_estado(int *vitoria, int *gameover, int *monstros_vivos, int *n_monstros_spawnados);

int carrega_mapa(char mapa[N_LINHAS][N_COLUNAS], int nMapa);

void reseta_posicoes(struct posicao recurso[MAX_RECURSOS], struct Inimigo monstros[N_MAX_MONSTROS], struct bomba bombas[MAX_RECURSOS]);

void salva_jogo(struct Save save);

void carrega_save(struct Save save);

#endif // NOSSAS_FUNCOES_H_

