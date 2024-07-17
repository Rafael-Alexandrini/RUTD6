#include "raylib.h"

#define LARGURA 1200
#define ALTURA 600
#define N_COLUNAS 60
#define N_LINHAS 30
#define TAM_QUADRADO 20
#define TAM_GRID 20

int main()
{
    char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"W                         W                                W",
"W                         W                                W",
"W                         W                                W",
"W                         W                                W",
"W                         W                                W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"W                                                          W",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};

    int posX = 300;
    int posY = 300;
    int jogadorVivo = 1;

    InitWindow(LARGURA, ALTURA, "Quadrado");
    SetTargetFPS(60);

    while(!WindowShouldClose() && jogadorVivo)
    {
        // Detecta Input
        if (IsKeyPressed(KEY_UP)) posY -= TAM_GRID;
        if (IsKeyPressed(KEY_DOWN)) posY += TAM_GRID;
        if (IsKeyPressed(KEY_LEFT)) posX -= TAM_GRID;
        if (IsKeyPressed(KEY_RIGHT)) posX += TAM_GRID;


        // Checa se saiu da tela
        if (posX >= LARGURA || posX < 0 || posY >= ALTURA|| posY < 0)
        {
            jogadorVivo = 0;
        }


        // Atualiza frame e desenha quadrado
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(posX, posY, TAM_QUADRADO, TAM_QUADRADO, GREEN);
        for (int l = 0; l < N_LINHAS; l++){
            for (int c = 0; c < N_COLUNAS; c++){
                switch(mapa[l][c]){
                    case 'W':
                        DrawRectangle(c * TAM_GRID, l * TAM_GRID, TAM_GRID, TAM_GRID, PURPLE);
                        break;
                    default:
                        break;

                }

            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;


}
