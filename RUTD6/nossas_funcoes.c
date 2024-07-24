#include "nossas_funcoes.h"
#include <stdio.h>
#include "raylib.h"

void funcao_exemplo(){
    printf("funcao de exemplo pra testar .h\n");
}


void desenha_mapa(char mapa[31][61], int nLinhas, int nColunas, int tamGrid, Texture2D obstaculo, Texture2D base){
    int l, c;
    for (l = 0; l < nLinhas; l++){
        for (c = 0; c < nColunas; c++){
            switch(mapa[l][c]){
                case 'W':
                    DrawRectangle(c * tamGrid, l * tamGrid, tamGrid, tamGrid, PURPLE);
                    break;
                case 'H':
                    DrawRectangle(c * tamGrid, l * tamGrid, tamGrid, tamGrid, BLUE);
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
                    break;

            }

        }
    }
}

void tentaMover(int *pX, int *pY, int dirX, int dirY, char mapa[31][61]){
    int podeMover = 1;

    switch (mapa[*pY + dirY][*pX + dirX]){
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
