#include "raylib.h"
#include "nossas_funcoes.h"

#define LARGURA 1200
#define ALTURA 600
#define N_COLUNAS 60
#define N_LINHAS 30
#define TAM_GRID 20


int main()
{    char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWW                   W         WMW                   W",
"WWWWWWWW WWWWWWWWWWWWWWWWW W         W W                   W",
"WWWWWWWW W               W W         WMW                   W",
"WWWWWWWW H               W W         W W                   W",
"WWWWWWWW W               W W  R      WMW                   W",
"WWWWWWWW W               W W         W W            R      W",
"S        W           R   W W         WMW                   W",
"WWWWWWWWWW               W W         W W                   W",
"W                        W W         W W                   W",
"W                        W W         H H      R            W",
"W                        W W         W W                   W",
"W   R                    W W         W W                   W",
"W                        W W         W WWWWWWWWWWWWHWWWWWWWW",
"W                        H H         W                     W",
"W                        W W         W WWWWWWWWWWWWHWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWW WWWW W         W W             WWWWWWW",
"W             WWWWWWW WWWW W         H H     J       W    WW",
"W          R  H       WWWW W         W W             W WW WW",
"W             WWWWWWW WWWW W         W WWWWWWWWWWWWWWW WW WW",
"W             WWWWWWW WWWW W         W                 WW WW",
"W      R      WWWWWWW WWWW W         WWWWWWWWWWWWWWWWWWWW WW",
"W             WWWWWW  WWWW W                            W WW",
"W        R    WWWWWW WWWWW W                            W WW",
"W             WWWWWWHWWWWW W                            W WW",
"W             W          W W                   R        W WW",
"W   R         W          W WWWWWWHWWWWWWWWWWWWWWWWWWWWWWW WW",
"W             W          H                                WW",
"W             W   R      WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};

    int posX = 300;
    int posY = 300;

    InitWindow(LARGURA, ALTURA, "RUTD6");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // Detecta Input
        if (IsKeyPressed(KEY_UP)) posY -= TAM_GRID;
        if (IsKeyPressed(KEY_DOWN)) posY += TAM_GRID;
        if (IsKeyPressed(KEY_LEFT)) posX -= TAM_GRID;
        if (IsKeyPressed(KEY_RIGHT)) posX += TAM_GRID;


        // Atualiza frame e desenha quadrado
        BeginDrawing();
        ClearBackground(RAYWHITE);
        desenha_mapa(mapa, N_LINHAS, N_COLUNAS, TAM_GRID);
        DrawRectangle(posX, posY, TAM_GRID, TAM_GRID, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;


}
/*
char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWW     WWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW             H     WWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW WWWWWWWWWWWWW     WWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW WWWWWWWWWWWWW     WWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW WWWWWWWWWWWWWWWHWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWW                W              WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWW       R        W WWWWWHWWWWWW WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWW                W W          W WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWW W          W WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW    WWWW W          W WWWWWWWWWWWWWWWWWWWWW",
"S               W    W    W          W   WWWWWWWWWWWWWM M MW",
"WWWWWWWWWWWWWWW W    W WWWW          WWW WWWWWWWWWWWWW WWWWW",
"WWWWWWWWWWWWWWW W    W W               W WWWWWWWWWWWWWMWWWWW",
"WWWWWWWWWWWWWWW W    W H               W WWWWWWWWWWWWW WWWWW",
"WWWWWWWWWWWWWWW W    W W      R        W WWWWWWWWWWWWW WWWWW",
"WWWWWWWWWWWWWWW W    W W               W WWWWWWWWWWWWW WWWWW",
"WWWWWWWWWWWWWWW W  R W W               W WWWWWWWWWWWWW WWWWW",
"WWWWWWWWWWWWWWW W    W W               W               WWWWW",
"WWWWWWWWWWWWWWW W    W W               WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW WWWWWW WWWWWWWW WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW        WWWWWWWW WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWHWWWWWWWWWWWW WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW     R                WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};


char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"W                            W                  W M W      W",
"W                            W                  H   W      W",
"W                            W                  W M W      W",
"W                            H                  W   W      W",
"W                            W           R      W M W      W",
"W                            W                  W   W   R  W",
"W   R                        W                  W M W      W",
"WWWWWWWWWWWWWWWWWWWHWWWWWWWWWWWWWWWWWWWWWWWWWWWWW   W      W",
"W                                                 M H      W",
"WWWWWHWWWWWWWWWWWWWWWWWWWWWWWWWW WWWWWWWWWWHWWWWWWWWW      W",
"W                              W W                  W      W",
"W                              W W              R   W      W",
"W                              W W                  W      W",
"W                              W W                  H      W",
"W                  WWWWWWWWWWWWW W                  W      W",
"W                  W             W                  W R    W",
"W                  W WWWWWWWWWWWWW                  W      W",
"WWWWWWWWWWWHWWWWWWWW W                              W      W",
"W                  W W                              W      W",
"W                  W W                              W      W",
"W     R            W WWWWWWWWWWWWWWWWWWWWWWWHWWWWWWWW      W",
"W                  W W                W             W      W",
"W                  W W                W             W      W",
"WWWWWWWWWWWWWWWWWWWW W                W             W      W",
"S                    W                W             W      W",
"WWWWWWWWWWHWWWWWWWWWWW                W      R      W      W",
"W                                     H             W      W",
"W            R                        W             W      W",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};


char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWW                   W         WMW                   W",
"WWWWWWWW WWWWWWWWWWWWWWWWW W         W W                   W",
"WWWWWWWW W               W W         WMW                   W",
"WWWWWWWW H               W W         W W                   W",
"WWWWWWWW W               W W  R      WMW                   W",
"WWWWWWWW W               W W         W W            R      W",
"S        W           R   W W         WMW                   W",
"WWWWWWWWWW               W W         W W                   W",
"W                        W W         W W                   W",
"W                        W W         H H      R            W",
"W                        W W         W W                   W",
"W   R                    W W         W W                   W",
"W                        W W         W WWWWWWWWWWWWHWWWWWWWW",
"W                        H H         W                     W",
"W                        W W         W WWWWWWWWWWWWHWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWW WWWW W         W W             WWWWWWW",
"W             WWWWWWW WWWW W         H H     J       W    WW",
"W          R  H       WWWW W         W W             W WW WW",
"W             WWWWWWW WWWW W         W WWWWWWWWWWWWWWW WW WW",
"W             WWWWWWW WWWW W         W                 WW WW",
"W      R      WWWWWWW WWWW W         WWWWWWWWWWWWWWWWWWWW WW",
"W             WWWWWW  WWWW W                            W WW",
"W        R    WWWWWW WWWWW W                            W WW",
"W             WWWWWWHWWWWW W                            W WW",
"W             W          W W                   R        W WW",
"W   R         W          W WWWWWWHWWWWWWWWWWWWWWWWWWWWWWW WW",
"W             W          H                                WW",
"W             W   R      WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};

*/
