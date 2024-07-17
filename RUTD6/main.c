#include "raylib.h"

#define LARGURA 600
#define ALTURA 600
#define TAM_QUADRADO 20
#define TAM_GRID 20

int main()
{
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
        EndDrawing();
    }

    CloseWindow();
    return 0;


}
