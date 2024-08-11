#include "nossas_funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

void desenha_mapa(char mapa[N_LINHAS][N_COLUNAS], Color fundo, Texture2D tijolo, Texture2D base, Texture2D portal){
    int l, c;
    for (l = 0; l < N_LINHAS; l++){
        for (c = 0; c < N_COLUNAS; c++){
            switch(mapa[l][c]){
                case 'W':
                    DrawTexture(tijolo, c * TAM_GRID, l * TAM_GRID, WHITE);
                    break;
                case 'H':
                    DrawTexture(portal, c * TAM_GRID, l * TAM_GRID, WHITE);
                    break;
                case 'S':
                    DrawTexture(base, c * TAM_GRID, l * TAM_GRID, WHITE);
                    break;
                case 'M':
                    DrawRectangle(c * TAM_GRID, l * TAM_GRID, TAM_GRID, TAM_GRID, YELLOW);
                    break;
                default:
                    DrawRectangle(c * TAM_GRID, l * TAM_GRID, TAM_GRID, TAM_GRID, fundo);
                    break;

            }

        }
    }
}

void tenta_mover(int *pX, int *pY, int dirX, int dirY, char mapa[N_LINHAS][N_COLUNAS]){
    int podeMover = 1;

    if ((*pX + dirX) < 0 || (*pX + dirX) >= N_COLUNAS || (*pY + dirY) < 0 || (*pY + dirY) >= N_LINHAS){
        podeMover = 0;
    }
    else{
        switch (mapa[*pY + dirY][*pX + dirX]){
            case 'H':
                entra_portal(pX, pY, dirX, dirY, mapa);
                break;
            case 'S':
            case 'W':
                podeMover = 0;
                break;
            default:
                break;
        }
    }

    if (podeMover){
        *pX += dirX;
        *pY += dirY;
    }
}

void entra_portal(int *pX, int *pY, int dirX, int dirY, char mapa[N_LINHAS][N_COLUNAS]){
    int i;
    int indHole = 0;

    if (dirX == 1){
        for (i = 0; i < N_COLUNAS; i++){
            if (mapa[*pY][i] == 'H')
                indHole = i;
        }
        *pX = indHole;
    } else if (dirX == -1){
        for (i = N_COLUNAS - 1; i > -1; i--){
            if (mapa[*pY][i] == 'H')
                indHole = i;
        }
        *pX = indHole;
    } else if (dirY == 1){
        for (i = 0; i < N_LINHAS; i++){
            if (mapa[i][*pX] == 'H')
                indHole = i;
        }
        *pY = indHole;
    } else if (dirY == -1){
        for (i = N_LINHAS - 1; i > -1; i--){
            if (mapa[i][*pX] == 'H')
                indHole = i;
        }
        *pY = indHole;
    }

}

void move_inimigo(struct Inimigo *pInimigo, char mapa[N_LINHAS][N_COLUNAS]){
    int dirXog = pInimigo->dirx; // guarda temporariamente direções originais dos inimigos
    int dirYog = pInimigo->diry;


    // se não consegue mover na direção original, tenta ir pra uma ou outra. se não consegue, volta. se ainda não, para
    if(pode_mover_inimigo(pInimigo->x, pInimigo->y, pInimigo->dirx, pInimigo->diry, mapa)){   // anda reto
        pInimigo->x += pInimigo->dirx;
        pInimigo->y += pInimigo->diry;
    }
    else{
        nova_direcao(&(pInimigo->dirx), &(pInimigo->diry));
        if(pode_mover_inimigo(pInimigo->x, pInimigo->y, pInimigo->dirx, pInimigo->diry, mapa)){ // anda esquerda/direita
            pInimigo->x += pInimigo->dirx;
            pInimigo->y += pInimigo->diry;
        }
        else{
            pInimigo->dirx = - pInimigo->dirx;
            pInimigo->diry = - pInimigo->diry;
            if(pode_mover_inimigo(pInimigo->x, pInimigo->y, pInimigo->dirx, pInimigo->diry, mapa)){ // anda contrário, direita/esquerda
                pInimigo->x += pInimigo->dirx;
                pInimigo->y += pInimigo->diry;
            }
            else{
                pInimigo->dirx = -dirXog;
                pInimigo->diry = -dirYog;
                if(pode_mover_inimigo(pInimigo->x, pInimigo->y, pInimigo->dirx, pInimigo->diry, mapa)){ // em último caso, anda pra trás
                    pInimigo->x += pInimigo->dirx;
                    pInimigo->y += pInimigo->diry;
                }
            }
        }
    }
}

void nova_direcao(int *dirX, int *dirY){
    // dada ponteiros para uma direção, muda esta para 90 graus à direita ou esquerda, aleatóriamente
    // Exemplos:
    // 1 0 (direita) -> 0 1 ou 0 -1 (cima ou baixo)
    // -1 0 (esquerda) -> 0 1 ou 0 -1 (cima ou baixo)
    // 0 1 (baixo) -> 1 0 ou -1 0 (esquerda ou direita)
    // 0 -1 (cima) -> 1 0 ou -1 0 (esquerda ou direita)
    int randomDir = rand() % 2; // escolhe direita/esquerda aleatóriamente

    if (*dirY == 0){
        *dirX = 0;
        *dirY = (randomDir * 2) - 1;
    }
    else if (*dirX == 0){
        *dirX = (randomDir * 2) - 1;
        *dirY = 0;
    }
}


int pode_mover_inimigo(int pX, int pY, int dirX, int dirY, char mapa[N_LINHAS][N_COLUNAS]){
    int podeMover = 1;

    // se está dentro do mapa
    if ((pX + dirX) < 0 || (pX + dirX) >= N_COLUNAS || (pY + dirY) < 0 || (pY + dirY) >= N_LINHAS){
        podeMover = 0;
    }
    else{
        switch (mapa[pY + dirY][pX + dirX]){
            case 'H':
            case 'W':
                podeMover = 0;
                break;
            default:
                break;
        }
    }
    return podeMover;
}

void pega_recurso (struct posicao *recurso)
{

    recurso->x = -20;
    recurso->y = -20;

}

void base_toma_dano (struct Inimigo *inimigo, struct base *base)
{
    if (inimigo->x == base->x && inimigo->y == base->y){

        inimigo->x = -20;
        inimigo->y = -20;
        base->vidas--;
    }
}

void mata_monstro (struct Inimigo *inimigo, struct bomba *bomba)
{
        inimigo->x = -20;
        inimigo->y = -20;
        bomba->x = -10;
        bomba->y = -10;
        inimigo->vivo = 0;
}

void acha_no_mapa (char mapa[N_LINHAS][N_COLUNAS], struct posicao *player, struct posicao *spawner, struct base *base, struct posicao recurso[MAX_RECURSOS])
{
    int l, c;
    int i = 0;

    for (l = 0; l < N_LINHAS; l++)
    {
        for (c = 0; c < N_COLUNAS; c++)
        {
            if (mapa[l][c] == 'J')
            {
                player->x = c; // pega a posição inicial do jogador no mapa
                player->y = l;
            }
            else if (mapa[l][c] == 'M')
            {
                spawner->x = c; // pega a posição inicial do spawner de monstros no mapa
                spawner->y = l;
            }
            else if (mapa[l][c] == 'S')
            {
                base->x = c; // pega a posição da base no mapa
                base->y = l;
            }
            else if (mapa[l][c] == 'R')
            {
                recurso[i].x = c; // pega a posição do q ésimo recurso
                recurso[i].y = l;
                i++;
            }
        }
    }

}

void zera_estado(int *vitoria, int *gameover, int *monstros_vivos, int *n_monstros_spawnados)
{
    *vitoria = 0;
    *gameover = 0;
    *monstros_vivos = 0;
    *n_monstros_spawnados = 0;
}

int carrega_mapa(char mapa[N_LINHAS][N_COLUNAS], int nMapa){
    int conseguiuAbrir = 1;
    char nomeArquivoText[30];
    sprintf(nomeArquivoText, "mapas/mapa%02d.txt", nMapa);
    FILE *arquivoText;
    arquivoText = fopen(nomeArquivoText, "r");

    if (arquivoText == NULL)
        conseguiuAbrir = 0;  // Erro na abertura do arquivo
    else{
        for (int l = 0; l < N_LINHAS; l++){
            for (int c = 0; c < N_COLUNAS; c++){
                mapa[l][c] = getc(arquivoText);
            }
            getc(arquivoText);
        }
        fclose(arquivoText);
    }

    return conseguiuAbrir;
}

void reseta_posicoes(struct posicao recurso[MAX_RECURSOS], struct Inimigo monstros[N_MAX_MONSTROS], struct bomba bombas[MAX_RECURSOS]){
    int i;
    // Os monstros começam com uma posição fora da tela e uma textura aleatória
    for (i = 0; i < N_MAX_MONSTROS; i++)
    {
        monstros[i].x = -1;
        monstros[i].y = -1;
        monstros[i].dirx = 0;
        monstros[i].diry = 0;
        monstros[i].idTextura = rand()%4;
        monstros[i].vivo = 1;
    }



    // incializa as bombas e os recursos fora da tela em uma posição diferente dos monstros
    for (i = 0; i < MAX_RECURSOS; i++)
    {
        bombas[i].x = -5;
        bombas[i].y = -5;
        recurso[i].x = -6;
        recurso[i].y = -6;
    }
}
