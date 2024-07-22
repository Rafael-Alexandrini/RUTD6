#include "nossas_funcoes.h"
#include <stdio.h>
#include "raylib.h"

void funcao_exemplo(){
    printf("funcao de exemplo pra testar .h\n");
}


void desenha_mapa(char mapa[31][61], int nLinhas, int nColunas, int tamGrid){
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
                    DrawRectangle(c * tamGrid, l * tamGrid, tamGrid, tamGrid, RED);
                    break;
                case 'S':
                    DrawRectangle(c * tamGrid, l * tamGrid, tamGrid, tamGrid, BLACK);
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

void tentaMover(int *pX, int *pY, int dirX, int dirY, char mapa[31][61], int tamGrid){
    int podeMover = 1;
    int pMapaX = *pX / tamGrid;
    int pMapaY = *pY / tamGrid;

    if (mapa[pMapaY + dirY][pMapaX + dirX] == 'W') podeMover = 0;

    if (podeMover){
    *pX += dirX * tamGrid;
    *pY += dirY * tamGrid;
    }
}
