#include "nossas_funcoes.h"
#include <stdio.h>
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
