#include "raylib.h"
#include "nossas_funcoes.h"
#include "estruturas.h"

#define LARGURA 1200
#define ALTURA 600
#define N_COLUNAS 60
#define N_LINHAS 30
#define TAM_GRID 20
#define N_MAX_MONSTROS 10


int main()
<<<<<<< Updated upstream
{    int l, c, i;
    char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWW                   W         WMW                   W",
"WWWWWWWW WWWWWWWWWWWWWWWWW W         W W                   W",
"WWWWWWWW W               W W         WMW                   W",
"WWWWWWWW H               W W         W W                   W",
"WWWWWWWW W               W W  R      WMW                   W",
"WWWWWWWW W               W W         W W            R      W",
"S        W           R   H H         WMW                   W",
"WWWWWWWWWW               W W         W W                   W",
"W                        H H         W W                   W",
"W                        H H         H H      R            W",
"W                        W W         W W                   W",
"W   R                    W W         W W                   W",
"W                        W W         W WWWWWWWWHWWWHWWWWWWWW",
"W                        H H         W                     W",
"W                        W W         W WWWWWWWWHWWWHWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWW WWWW W         W W             WWWWWWW",
"W             WWWWWWW WWWW W         H H     J       W    WW",
"W          R  H       WWWW W         W W             W WW WW",
"W             WWWWWWW WWWW W         W WWWWWWWWHHWWWWW WW WW",
"W             WWWWWWW WWWW W         W                 WW WW",
"W      R      HWWWWWW WWWH H         WWWWWWWWWWHWWWWWWWWW WW",
"W             WWWWWW  WWWW W                            W WW",
"W        R    WWWWWW WWWWW W                            W WW",
"W             WWWWWWHWWWWW W                            W WW",
"W             W          W W                   R        W WW",
"W   R         W          W WWWWWWHWWWWWWWWWWWWWWWWWWWWWWW WW",
"W             W          H                                WW",
"W             W   R      WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
=======
{   int l, c, i, b;
    Color cinzamorto = {176, 176, 176, 200};
    Color caminho = {11, 140, 133, 255};

char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"W        WWWW  WWWWW   WWWW                                W",
"W    R   WWWW  WWWWW   WWWW                                W",
"W        H         H   WWWW                        R       W",
"W        WWWW  WWWWW   WWWW                                W",
"W  R     WWWW  WWWWW   WWWW                                W",
"W        WWWW  WWWWW   WWWW         R                      W",
"W        WWWW  WWWWW                               J       W",
"W      R WWWW  WWWWW   WWWW                                W",
"W        WWWW  WWWWW   WWWW                                W",
"W        WWWW  WWWWWWWWWWWW                R               W",
"W        WWWW  W          W                                W",
"W     R  WWWW  W WWWWWWWW W                                W",
"W        WWWW  W W      W W                                W",
"W        WWWW  W W      W WWWWWWWWWWWWWWWWW         R      W",
"W   R    WWWW  W W      W                 W                W",
"W        WWWW  W W   R  WWWWWWWWWWWWWWWWW WWW           WWWW",
"W        WWWW                           W WWWW         WWWWW",
"W  R     WWWW  W W                      W WWWWW       WWWWWW",
"W        WWWW  W W                      W WWWWWW     WWWWWWW",
"W      R WWWW  W W              R       W WWWWWWW   WWWWWWWW",
"W        WWWW  W W     R                W WWWWWWWW WWWWWWWWW",
"W        WWWW  W W                      W WWWWWWWW WWWWWWWWW",
"W        WWWWWWW W                      W WWWWWWWW WWWWWWWWW",
"W        WM M    W                      W WWWWWWWWHWWWWWWWWW",
"W        W WWWWWWW          R                              S",
"W   R    WMWWWWWWW                      WWWWWWWWWWWWWWWWWWWW",
"W        W WWWWWWW                                 WWWWWWWWW",
"W        WMWWWWWWW                                 WWWWWWWWW",
>>>>>>> Stashed changes
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};

    struct posicao player = {15, 15};
    for (l = 0; l < N_LINHAS; l++){
        for (c = 0; c < N_COLUNAS; c++){
            if (mapa[l][c] == 'J'){
                player.x = c;
                player.y = l;
            }
        }
    }

    struct posicao monstros[N_MAX_MONSTROS] = {{10, 10}, {16, 16}};

    InitWindow(LARGURA, ALTURA, "RUTD6");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {

<<<<<<< Updated upstream

        // Movimento do Jogador  // Remover coisa do shift antes de lançar
        if (IsKeyDown(KEY_LEFT_SHIFT)){
=======
        if (gameover == 1)
        {
            if (IsKeyDown(KEY_LEFT_SHIFT))
            {
>>>>>>> Stashed changes
            if (IsKeyDown(KEY_UP)) tenta_mover(&player.x, &player.y, 0, -1, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyDown(KEY_DOWN)) tenta_mover(&player.x, &player.y, 0, 1, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyDown(KEY_LEFT)) tenta_mover(&player.x, &player.y, -1, 0, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyDown(KEY_RIGHT)) tenta_mover(&player.x, &player.y, 1, 0, mapa, N_LINHAS, N_COLUNAS);
<<<<<<< Updated upstream
        } else{
            if (IsKeyPressed(KEY_UP)) tenta_mover(&player.x, &player.y, 0, -1, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyPressed(KEY_DOWN)) tenta_mover(&player.x, &player.y, 0, 1, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyPressed(KEY_LEFT)) tenta_mover(&player.x, &player.y, -1, 0, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyPressed(KEY_RIGHT)) tenta_mover(&player.x, &player.y, 1, 0, mapa, N_LINHAS, N_COLUNAS);
=======
            }
            else
            {
                if (IsKeyPressed(KEY_UP)) tenta_mover(&player.x, &player.y, 0, -1, mapa, N_LINHAS, N_COLUNAS);
                if (IsKeyPressed(KEY_DOWN)) tenta_mover(&player.x, &player.y, 0, 1, mapa, N_LINHAS, N_COLUNAS);
                if (IsKeyPressed(KEY_LEFT)) tenta_mover(&player.x, &player.y, -1, 0, mapa, N_LINHAS, N_COLUNAS);
                if (IsKeyPressed(KEY_RIGHT)) tenta_mover(&player.x, &player.y, 1, 0, mapa, N_LINHAS, N_COLUNAS);
            }

>>>>>>> Stashed changes
        }


        // Atualiza frame e desenha quadrado
        BeginDrawing();
        ClearBackground(RAYWHITE);
        desenha_mapa(mapa, N_LINHAS, N_COLUNAS, TAM_GRID);
        DrawRectangle(player.x * TAM_GRID, player.y * TAM_GRID, TAM_GRID, TAM_GRID, GREEN);
        for (i = 0; i < N_MAX_MONSTROS; i++)
            DrawRectangle(monstros[i].x * TAM_GRID, monstros[i].y * TAM_GRID, TAM_GRID, TAM_GRID, ORANGE);
        EndDrawing();
    }

    CloseWindow();
    return 0;


}




/*
mapa 1
char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWW     WWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW                   WWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW WWWWWWWWWWWWW     WWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW WWWWWWWWWWWWW     WWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW WWWWWWWWWWWWWWWHWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWW                W              WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWW       R        W WWWWW WWWWWW WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWW                W W          W WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWW W          W WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW    WWWW W          W WWWWWWWWWWWWWWWWWWWWW",
"S                    W    W          W   WWWWWWWWWWWWWM M MW",
"WWWWWWWWWWWWWWW W    W WWWW          WWW WWWWWWWWWWWWW WWWWW",
"WWWWWWWWWWWWWWW W    W W               W WWWWWWWWWWWWWMWWWWW",
"WWWWWWWWWWWWWWW W    W W               W WWWWWWWWWWWWW WWWWW",
"WWWWWWWWWWWWWWW W    W W      R        W WWWWWWWWWWWWW WWWWW",
"WWWWWWWWWWWWWWW W    W W               W WWWWWWWWWWWWW WWWWW",
"WWWWWWWWWWWWWWW W  R                     WWWWWWWWWWWWW WWWWW",
"WWWWWWWWWWWWWWW W    W W               W               WWWWW",
"WWWWWWWWWWWWWWW W    W W               WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW WWWWWW WWWWWWWW WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWW        WWWWWWWW WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW     R                WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWHWWWWWW WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};

mapa 2
char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"W                            W                  W M W      W",
"W                            W                  W   W      W",
"W                            W                  W M W      W",
"W               J            H                  W   H      W",
"W                            W           R      W M W      W",
"W                            W                  W   W   R  W",
"W   R                        W                  W M W      W",
"WWWWWWWWWWW   WWWWWWWWWWWWWWWWWWWWWWWWWWW WWWHWWW   W      W",
"W                                                 M W      W",
"WWWWWWWWWWW   WWWWWWWWWWWWWWWWWW WWWWWWWW WWWWWWWWWWW      W",
"WWWWWWWWWW    WWWWWWWWWWWWWWWWWW W                  W      W",
"WWWWWWWW     WWWWWWWWWWWWWWWWWWW W              R   W      W",
"WWWWWWW    WWWWWWWWWWWWWWWWWWWWW W                  W      W",
"WWWWWWW   WWWWWWWWWWWWWWWWWWWWWW W                  W      W",
"WWWWWWW   WWWWWWWWWWWWWWWWWWWWWW W                         W",
"WWWWWW   WWWWWWWWWWW             W                    R    W",
"WWWWWW   WWWWWWWWWWW WWWWWWWWWWWWW                         W",
"WWWWWW   WWWWWWWWWWW W                              W      W",
"W                  W W                              W      W",
"W                  W W                              W      W",
"W      R           W WWWWWWWWWWWWWWWWWWWWWWWWHWWWWWWW      W",
"W                  W W                W             W      W",
"W                                     W             W      W",
"WWWWWWWWWWWHWWWWWWWW W                W             W      W",
"S                    W                W             W      W",
"WWWWWWWWWWWHWWWWWWWWWW                       R      W      W",
"W                                     W             W      W",
"W            R                        W             W      W",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};

mapa 3
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

mapa 4
char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"W        WWWW  WWWWW   WWWW                                W",
"W    R   WWWW  WWWWW   WWWW                                W",
"W        H         H   WWWW                        R       W",
"W        WWWW  WWWWW   WWWW                                W",
"W  R     WWWW  WWWWW   WWWW                                W",
"W        WWWW  WWWWW   WWWW         R                      W",
"W        WWWW  WWWWW                               J       W",
"W      R WWWW  WWWWW   WWWW                                W",
"W        WWWW  WWWWW   WWWW                                W",
"W        WWWW  WWWWWWWWWWWW                R               W",
"W        WWWW  W          W                                W",
"W     R  WWWW  W WWWWWWWW W                                W",
"W        WWWW  W W      W W                                W",
"W        WWWW  W W      W WWWWWWWWWWWWWWWWW         R      W",
"W   R    WWWW  W W      W                 W                W",
"W        WWWW  W W   R  WWWWWWWWWWWWWWWWW WWW           WWWW",
"W        WWWW                           W WWWW         WWWWW",
"W  R     WWWW  W W                      W WWWWW       WWWWWW",
"W        WWWW  W W                      W WWWWWW     WWWWWWW",
"W      R WWWW  W W              R       W WWWWWWW   WWWWWWWW",
"W        WWWW  W W     R                W WWWWWWWW WWWWWWWWW",
"W        WWWW  W W                      W WWWWWWWW WWWWWWWWW",
"W        WWWWWWW W                      W WWWWWWWW WWWWWWWWW",
"W        WM M    W                      W WWWWWWWWHWWWWWWWWW",
"W        W WWWWWWW          R                              S",
"W   R    WMWWWWWWW                      WWWWWWWWWWWWWWWWWWWW",
"W        W WWWWWWW                                 WWWWWWWWW",
"W        WMWWWWWWW                                 WWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};
*/
