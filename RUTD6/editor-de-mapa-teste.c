#include "raylib.h"
#include "nossas_funcoes.h"
#include "nossas_funcoes.c"
#include "estruturas.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_TILES 7

void escreve(char mapa[31][61], FILE *arq_mapa);

void carrega(char mapa[31][61], FILE *arq_mapa);


int main(){
    Color caminho = {11, 140, 133, 255};

char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWW                   W         WMWWWWWW              W",
"WWWWWWWW WWWWWWWWHWWWWWWWW W         W WWWWWWHWWWWWWWW   WWW",
"WWWWWWWW W               W W         W W                   W",
"WWWWWWWW W               W W         W W                   W",
"WWWWWWWW W               W W  R      W W                   W",
"WWWWWWWW W               W W         W W            R      W",
"S        W           R   W W         W W                   W",
"WWWWW   WW               W W         W W                   W",
"W                        W W         W W                   W",
"W                        W W                  R            W",
"W                        W W                               W",
"W   R                    H H         W W                   W",
"W                                    W WWWWWWWWWWWWWWWWWWWWW",
"W                        H H         W                     W",
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
"W             W          WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};
    FILE *arq_mapa;

    // carrega mapa
    arq_mapa = fopen("./mapas/testemapa1.txt", "r+");
    if (arq_mapa == NULL) {
        printf("Erro na abertura do arquivo, criando novo\n");
        arq_mapa = fopen("./mapas/testemapa1.txt", "w+");
        carrega(mapa, arq_mapa);
    }
    else carrega(mapa, arq_mapa);

    InitWindow(LARGURA, ALTURA, "RUTD6");
    SetTargetFPS(60);

    Texture2D tijolo = LoadTexture("texturas/tijolo.png");
    Texture2D texturas[4] = {LoadTexture("texturas/estudante 1.png"), LoadTexture("texturas/estudante 2.png"), LoadTexture("texturas/estudante 3.png"), LoadTexture("texturas/estudante 4.png")};
    Texture2D base = LoadTexture("texturas/ru.png");
    Texture2D vidas = LoadTexture("texturas/coração.png");
    Texture2D obstaculo =  LoadTexture("texturas/prova calc.png");
    Texture2D portal =  LoadTexture("texturas/portal.png");


    struct posicao mouse = {};
    int indTileSelecionada = 0;
    char tilePossiveis[MAX_TILES] = {'W', 'H', 'S', 'M', 'R', 'T', 'J'};
    Texture2D textTilePossiveis[MAX_TILES] = {tijolo, portal, base, texturas[2], obstaculo, texturas[3], texturas[1]};


    while(!WindowShouldClose())
    {

        // mouse
        mouse.x = ((int)(GetMouseX() / TAM_GRID) + N_COLUNAS)%N_COLUNAS;
        mouse.y = ((int)(GetMouseY() / TAM_GRID) + N_LINHAS)%N_LINHAS;

        if (IsKeyPressed(KEY_S)){ // escreve mudanças e salva no arquivo
            escreve(mapa, arq_mapa);
            fflush(arq_mapa);
            printf("Acho que salvou!\n");
        }

        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) mapa[mouse.y][mouse.x] = ' ';

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))  mapa[mouse.y][mouse.x] = tilePossiveis[indTileSelecionada];

        if(GetMouseWheelMove() != 0)
            indTileSelecionada = (indTileSelecionada + (int)GetMouseWheelMove() + MAX_TILES) % MAX_TILES;



        // Atualiza frame e desenha
        BeginDrawing();
        ClearBackground(RAYWHITE);
        desenha_mapa(mapa, caminho, tijolo, base, portal, obstaculo);
        DrawTexture(textTilePossiveis[indTileSelecionada], mouse.x * TAM_GRID, mouse.y * TAM_GRID, WHITE);
        DrawText(TextFormat("%i", indTileSelecionada), 270, 50, 50, RED);
        EndDrawing();


    }
    escreve(mapa, arq_mapa);

    fclose(arq_mapa);

    CloseWindow();
    return 0;

}

void escreve(char mapa[31][61], FILE *arq_mapa){
    rewind(arq_mapa);
    for (int i = 0; i < N_LINHAS; i++){
        printf("%d - %s\n", i, mapa[i]);
        fputs(mapa[i], arq_mapa);
        fputc('\n', arq_mapa);
    }
}

void carrega(char mapa[31][61], FILE *arq_mapa){
    for (int i = 0; i < N_LINHAS; i++){
            mapa[i][60] = '\0';
            if(!feof(arq_mapa)){
                    // Não sei pq é  COLUNAS + 2, mas tá funcionando. Investigar dps pq tem algo errado
                if (fgets(mapa[i], N_COLUNAS + 2, arq_mapa) != NULL);
                 mapa[i][60] = '\0';
                 printf("%d - %s", i, mapa[i]);
                 printf("%d - %d\n", i, (mapa[i][60] == '\n'));
            }
    }
}


