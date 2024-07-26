#include "nossas_funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

void funcao_exemplo(){
    printf("funcao de exemplo pra testar .h\n");
}


void desenha_mapa(char mapa[31][61], int nLinhas, int nColunas, int tamGrid, Color fundo, Texture2D tijolo, Texture2D obstaculo, Texture2D base, Texture2D portal){
    int l, c;
    for (l = 0; l < nLinhas; l++){
        for (c = 0; c < nColunas; c++){
            switch(mapa[l][c]){
                case 'W':
                    DrawTexture(tijolo, c * tamGrid, l * tamGrid, WHITE);
                    break;
                case 'H':
                    DrawTexture(portal, c * tamGrid, l * tamGrid, WHITE);
                    break;
                case 'R':
                    DrawTexture(obstaculo, c * tamGrid, l * tamGrid, WHITE);
                    break;
                case 'S':
                    DrawTexture(base, c * tamGrid, l * tamGrid, WHITE);
                    break;
                case 'M':
                    DrawRectangle(c * tamGrid, l * tamGrid, tamGrid, tamGrid, YELLOW);
                    break;
                default:
                    DrawRectangle(c * tamGrid, l * tamGrid, tamGrid, tamGrid, fundo);
                    break;

            }

        }
    }
}

void tenta_mover(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas){
    int podeMover = 1;

    switch (mapa[*pY + dirY][*pX + dirX]){
        case 'H':
            entra_portal(pX, pY, dirX, dirY, mapa, nLinhas, nColunas);
            break;
        case 'S':
        case 'W':
            podeMover = 0;
            break;
        default:
            break;
    }

    if (podeMover){
        *pX += dirX;
        *pY += dirY;
    }
}

void entra_portal(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas){
    int i;
    int indHole = 0;

    if (dirX == 1){
        for (i = 0; i < nColunas; i++){
            if (mapa[*pY][i] == 'H')
                indHole = i;
        }
        *pX = indHole;
    } else if (dirX == -1){
        for (i = nColunas - 1; i > -1; i--){
            if (mapa[*pY][i] == 'H')
                indHole = i;
        }
        *pX = indHole;
    } else if (dirY == 1){
        for (i = 0; i < nLinhas; i++){
            if (mapa[i][*pX] == 'H')
                indHole = i;
        }
        *pY = indHole;
    } else if (dirY == -1){
        for (i = nLinhas - 1; i > -1; i--){
            if (mapa[i][*pX] == 'H')
                indHole = i;
        }
        *pY = indHole;
    }

}

void move_inimigo(int *pX, int *pY, int *dirX, int *dirY, char mapa[31][61], int nLinhas, int nColunas){
    int dirXog = *dirX;
    int dirYog = *dirY;
    int randomDir = rand() % 2;


    // se não consegue mover na direção original, tenta ir pra uma ou outra. se não consegue, volta. se ainda não, para
    if(pode_mover_inimigo(*pX, *pY, *dirX, *dirY, mapa, nLinhas, nColunas))
    {
        *pX += *dirX;
        *pY += *dirY;
    }
    else
    {
        nova_direcao(dirX, dirY, randomDir);
        if(pode_mover_inimigo(*pX, *pY, *dirX, *dirY, mapa, nLinhas, nColunas))
        {
            *pX += *dirX;
            *pY += *dirY;
        }
        else
        {
            *dirX = dirXog;
            *dirY = dirYog;
            nova_direcao(dirX, dirY, 1 - randomDir);
            if(pode_mover_inimigo(*pX, *pY, *dirX, *dirY, mapa, nLinhas, nColunas))
            {
                *pX += *dirX;
                *pY += *dirY;
            }
            else
            {
                *dirX = -dirXog;
                *dirY = -dirYog;
                if(pode_mover_inimigo(*pX, *pY, *dirX, *dirY, mapa, nLinhas, nColunas))
                {
                    *pX += *dirX;
                    *pY += *dirY;
                }
            }
        }
    }
}

void nova_direcao(int *dirX, int *dirY, int boolDirecao){
    // 1 0 -> 0 1 ou 0 -1
    // -1 0 -> 0 1 ou 0 -1
    // 0 1 -> 1 0 ou -1 0
    // 0 -1 -> 1 0 ou -1 0
    // boolDirecao (0 ou 1) indica uma direcao fixa. deve ser aleatório em outra função
    if (*dirY == 0){
        *dirX = 0;
        *dirY = (boolDirecao * 2) - 1;
    }
    else if (*dirX == 0){
        *dirX = (boolDirecao * 2) - 1;
        *dirY = 0;
    }
}


int pode_mover_inimigo(int pX, int pY, int dirX, int dirY, char mapa[31][61], int nLinhas, int nColunas){
    int podeMover = 1;

    switch (mapa[pY + dirY][pX + dirX]){
        case 'H':
        case 'S':
        case 'W':
            podeMover = 0;
            break;
        default:
            break;
    }
    return podeMover;
}
