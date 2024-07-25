#include "raylib.h"
#include "nossas_funcoes.h"
#include "estruturas.h"
#include "nossas_funcoes.c"
#include <time.h>
#include <stdlib.h>

#define LARGURA 1200
#define ALTURA 600
#define N_COLUNAS 60
#define N_LINHAS 30
#define TAM_GRID 20
#define N_MAX_MONSTROS 20
#define PLAYER_VIDAS 10


int main()
{   int l, c, i, b;
    Color cinzamorto = {176, 176, 176, 200};
    Color caminho = {11, 140, 133, 255};

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

    struct posicao player = {15, 15};
    for (l = 0; l < N_LINHAS; l++){
        for (c = 0; c < N_COLUNAS; c++){
            if (mapa[l][c] == 'J'){
                player.x = c;
                player.y = l;
            }
        }
    }
    struct posicao monstros[N_MAX_MONSTROS] = {{10, 10}, {16, 16}, {43, 18}};

    int playerVidas = PLAYER_VIDAS;
    int podeTomarDano = 1;
    int framesCounter = 0;
    int gameover = 1;
    int numeroAleatorio;

    srand(time(NULL));

    numeroAleatorio = rand()%4;

    InitWindow(LARGURA, ALTURA, "RUTD6");
    SetTargetFPS(60);

    Texture2D tijolo = LoadTexture("texturas/tijolo.png");
    Texture2D e[4] = {LoadTexture("texturas/estudante 1.png"), LoadTexture("texturas/estudante 2.png"), LoadTexture("texturas/estudante 3.png"), LoadTexture("texturas/estudante 4.png")};
    Texture2D base = LoadTexture("texturas/ru.png");
    Texture2D vidas = LoadTexture("texturas/cora��o.png");
    Texture2D obstaculo =  LoadTexture("texturas/prova calc.png");
    Texture2D portal =  LoadTexture("texturas/portal.png");
    /*
    Texture2D e[1] = LoadTexture("texturas/estudante 1.png");
    Texture2D e[2] = LoadTexture("texturas/estudante 2.png");
    Texture2D e[3] = LoadTexture("texturas/estudante 3.png");
    Texture2D e[4] = LoadTexture("texturas/estudante 4.png");
    */


    while(!WindowShouldClose())
    {
        // Movimento do Jogador  // Remover coisa do shift antes de lan�ar

        if (gameover == 1)
        {
            if (IsKeyDown(KEY_LEFT_SHIFT)){
            if (IsKeyDown(KEY_UP)) tenta_mover(&player.x, &player.y, 0, -1, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyDown(KEY_DOWN)) tenta_mover(&player.x, &player.y, 0, 1, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyDown(KEY_LEFT)) tenta_mover(&player.x, &player.y, -1, 0, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyDown(KEY_RIGHT)) tenta_mover(&player.x, &player.y, 1, 0, mapa, N_LINHAS, N_COLUNAS);
        } else{
            if (IsKeyPressed(KEY_UP)) tenta_mover(&player.x, &player.y, 0, -1, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyPressed(KEY_DOWN)) tenta_mover(&player.x, &player.y, 0, 1, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyPressed(KEY_LEFT)) tenta_mover(&player.x, &player.y, -1, 0, mapa, N_LINHAS, N_COLUNAS);
            if (IsKeyPressed(KEY_RIGHT)) tenta_mover(&player.x, &player.y, 1, 0, mapa, N_LINHAS, N_COLUNAS);
        }
        }


        // Atualiza frame e desenha quadrado
        BeginDrawing();
        ClearBackground(RAYWHITE);
        desenha_mapa(mapa, N_LINHAS, N_COLUNAS, TAM_GRID, caminho, tijolo, obstaculo, base, portal);
        DrawRectangle(player.x * TAM_GRID, player.y * TAM_GRID, TAM_GRID, TAM_GRID, GREEN);

        int multiplo = 10;

        for (b=0; b<playerVidas; b++)
        {
            multiplo = b * 40;
            DrawTexture(vidas, 170 + multiplo, 18, WHITE);
        }

        /*
        switch (playerVidas)
        {
            case 3:
            DrawTexture(vidas, 250, 18, WHITE);
            case 2:
            DrawTexture(vidas, 210, 18, WHITE);
            case 1:
            DrawTexture(vidas, 170, 18, WHITE);
            break;
            default:
        }
        */

        DrawText("Vidas: ", 10, 10, 50, RED);
        DrawText((TextFormat("%i", framesCounter)), 10, 100, 70, RED);
        DrawText((TextFormat("%i", podeTomarDano)), 10, 200, 70, RED);

        for (i = 0; i < N_MAX_MONSTROS; i++)
            {
                DrawTexture(e[numeroAleatorio], monstros[i].x * TAM_GRID, monstros[i].y * TAM_GRID, WHITE);
            if ((monstros[i].x == player.x && monstros[i].y == player.y) && podeTomarDano == 1)
                {
                    podeTomarDano = 0;
                    playerVidas--;
                }
            }
        if (podeTomarDano == 0)
            {
            framesCounter++;
            if (framesCounter == 60)
                {
                    podeTomarDano = 1;
                    framesCounter = 0;
                }
            }

        if (playerVidas <= 0 )
        {
            playerVidas = 0;
            DrawRectangle(0, 0, LARGURA, ALTURA, cinzamorto);
            DrawText("GAME OVER", 50, 230, 180, RED);
            gameover = 0;
        }

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
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWW                      WWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWHWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};

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
"WWWWWWWW                   W         WMWWWWWW              W",
"WWWWWWWW WWWWWWWWHWWWWWWWW W         W WWWWWWHWWWWWWWW   WWW",
"WWWWWWWW W               W W         WMW                   W",
"WWWWWWWW W               W W         W W                   W",
"WWWWWWWW W               W W  R      WMW                   W",
"WWWWWWWW W               W W         W W            R      W",
"S        W           R   W W         WMW                   W",
"WWWWW   WW               W W         W W                   W",
"W                        W W         W W                   W",
"W                        W W                  R            W",
"W                        W W                               W",
"W   R                                W W                   W",
"W                                    W WWWWWWWWWWWWWWWWWWWWW",
"W                                    W                     W",
"W                        W W         W WWWWWWHWWWWWWWWWWWWWW",
"WWWWWWHWWWWWWWWWWWWWWWWWWW W         W W             WWWWWWW",
"W             WWWWWWWWWWWW W         W W     J       W    WW",
"W          R          WWWW W         W W             W WW WW",
"W             WWWWWWW WWWW W         W WWWWWWWWWWWWWWW WW WW",
"W             WWWWWWW WWWW W         W                 WW WW",
"W      R      WWWWWWW WWWW W         WWWWWWWWWWWWWWWWWWWW WW",
"W             WWWWWW  WWWW W                            W WW",
"W        R    WWWWWW WWWWW W                            W WW",
"W             WWWWWWWWWWWW W                            W WW",
"W             W          W W                   R        W WW",
"W   R         W          W WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW WW",
"W             H          W                                WW",
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
