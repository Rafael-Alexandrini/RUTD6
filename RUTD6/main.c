#include "raylib.h"
#include "nossas_funcoes.h"
#include "estruturas.h"
#include "nossas_funcoes.c"
#include <time.h>
#include <stdlib.h>




int main()
{
    int l, c, i, b;
    Color cinzamorto = {176, 176, 176, 200};
    Color caminho = {11, 140, 133, 255};

    char mapa[N_LINHAS + 1][N_COLUNAS + 1] =
    {
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
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    };

    srand(time(NULL));

    int q = 0;
    int t = 0;
    int a = 0;
    int w = 0;

    struct base base = {10, 10, 10};
    struct posicao player = {15, 15};
    struct posicao spawner = {10, 10};
    struct posicao recurso[MAX_RECURSOS] = {{10, 10, 1}, {20, 30, 1}};

    for (l = 0; l < N_LINHAS; l++)
    {
        for (c = 0; c < N_COLUNAS; c++)
        {
            if (mapa[l][c] == 'J')
            {
                player.x = c;
                player.y = l;
            }
            else if (mapa[l][c] == 'M')
            {
                spawner.x = c;
                spawner.y = l;
            }
            else if (mapa[l][c] == 'S')
            {
                base.x = c;
                base.y = l;
            }
            else if (mapa[l][c] == 'R')
            {
                recurso[q].x = c;
                recurso[q].y = l;
                q++;
            }
        }
    }

    struct Inimigo monstros[N_MAX_MONSTROS] = {{3, 2, 1, 0}, {5, 2, 1, 0}, {7, 2, 1, 0}};
    // Os monstros come�am com uma posi��o fora da tela e uma textura aleat�ria
    for (i = 0; i < N_MAX_MONSTROS; i++)
    {
        monstros[i].x = -1;
        monstros[i].y = -1;
        monstros[i].dirx = 0;
        monstros[i].diry = 0;
        monstros[i].idTextura = rand()%4;
        monstros[i].vivo = 1;
    }

    int playerRecursos = 0;
    int podePegarRecursos = 1;
    int playerVidas = PLAYER_VIDAS;
    int podeTomarDano = 1;
    int framesCounter = 0;
    int framesCounter1 = 0;
    int gameover = 1;
    float ultimo_tick = 0;
    int tickCounter = 0;
    int n_monstros_spawnados = 0;
    int monstros_vivos = 0;

    struct bomba bombas[MAX_RECURSOS] = {{-1, -1, 1}, {-1, -1, 1}};


    // incializa as bombas fora da tela em uma posi��o diferente dos monstros
    for (i = 0; i < MAX_RECURSOS; i++)
    {
        bombas[i].x = -5;
        bombas[i].y = -5;
    }

    base.vidas = 3;

    InitWindow(LARGURA, ALTURA, "RUTD6");
    SetTargetFPS(60);

    // load texturas
    Texture2D tijolo = LoadTexture("texturas/tijolo.png");
    Texture2D texturas[4] = {LoadTexture("texturas/estudante 1.png"), LoadTexture("texturas/estudante 2.png"), LoadTexture("texturas/estudante 3.png"), LoadTexture("texturas/estudante 4.png")};
    Texture2D baseF = LoadTexture("texturas/ru.png");
    Texture2D vidas = LoadTexture("texturas/cora��o.png");
    Texture2D obstaculo =  LoadTexture("texturas/prova calc.png");
    Texture2D portal =  LoadTexture("texturas/portal.png");



    while(!WindowShouldClose())
    {
        // Movimento do Jogador  // Remover coisa do shift antes de lan�ar
        if (gameover == 1)
        {
            if (IsKeyDown(KEY_LEFT_SHIFT))
            {
                if (IsKeyDown(KEY_UP)) tenta_mover(&player.x, &player.y, 0, -1, mapa);
                if (IsKeyDown(KEY_DOWN)) tenta_mover(&player.x, &player.y, 0, 1, mapa);
                if (IsKeyDown(KEY_LEFT)) tenta_mover(&player.x, &player.y, -1, 0, mapa);
                if (IsKeyDown(KEY_RIGHT)) tenta_mover(&player.x, &player.y, 1, 0, mapa);
            }
            else
            {
                if (IsKeyPressed(KEY_UP)) tenta_mover(&player.x, &player.y, 0, -1, mapa);
                if (IsKeyPressed(KEY_DOWN)) tenta_mover(&player.x, &player.y, 0, 1, mapa);
                if (IsKeyPressed(KEY_LEFT)) tenta_mover(&player.x, &player.y, -1, 0, mapa);
                if (IsKeyPressed(KEY_RIGHT)) tenta_mover(&player.x, &player.y, 1, 0, mapa);
            }
        }


        // um tick (tudo dentro desse for) ocorre 16 vezes a cada segundo
        if ((GetTime() > ultimo_tick + 1/16.0) && gameover == 1)
        {
            ultimo_tick = GetTime();
            tickCounter++;
            // A cada X ticks: movimento dos inimigos
            if(tickCounter % 8 == 0)
            {
                for (i=0; i<N_MAX_MONSTROS; i++)
                {
                    move_inimigo(&(monstros[i]), mapa);
                }
            }
            if(tickCounter % 24 == 0 && n_monstros_spawnados < N_MAX_MONSTROS)
            {
                monstros[n_monstros_spawnados].x = spawner.x;
                monstros[n_monstros_spawnados].y = spawner.y;
                monstros[n_monstros_spawnados].dirx = 0;
                monstros[n_monstros_spawnados].diry = 1;
                n_monstros_spawnados++;
                monstros_vivos++;
            }
        }


        // V� se player deve tomar dano e tempo de invincibilidade
        for (i = 0; i < N_MAX_MONSTROS; i++)
        {
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

        // v� se player pegou recurso e tempo m�nimo pra pegar mais um recurso
        for (i = 0; i < MAX_RECURSOS; i++)
        {
            if ((recurso[i].x == player.x && recurso[i].y == player.y) && podePegarRecursos == 1)
            {
                playerRecursos++;
                podePegarRecursos = 0;
            }
        }
        if (podePegarRecursos == 0)
        {
            framesCounter1++;
            if (framesCounter1 == 10)
            {
                podePegarRecursos = 1;
                framesCounter1 = 0;
            }
        }

        // base toma dano
        for (i = 0; i < N_MAX_MONSTROS; i++)
        {
            base_toma_dano(&(monstros[i]), &(base));
        }


        if (IsKeyPressed(KEY_G) && playerRecursos > 0)
        {
            bombas[t].x = player.x;
            bombas[t].y = player.y;
            t++;
            playerRecursos--;

        }

        // mata monstro se posi��o for igual e diminui quantidade de monstros
        for (a = 0; a < N_MAX_MONSTROS; a++)
        {
            for (i = 0; i < MAX_RECURSOS; i++)
            {
                if (monstros[a].x == bombas[i].x && monstros[a].y == bombas[i].y)
                {
                    mata_monstro(&(monstros[a]), &(bombas[i]));
                    if (monstros[a].vivo == 0)
                        monstros_vivos--;
                }
            }
        }

            // Atualiza frame e desenha
            BeginDrawing();
            ClearBackground(RAYWHITE);
            desenha_mapa(mapa, caminho, tijolo, baseF, portal);
            DrawRectangle(player.x * TAM_GRID, player.y * TAM_GRID, TAM_GRID, TAM_GRID, GREEN);


            // pega recurso
            for (i = 0; i < MAX_RECURSOS; i++)
            {
                DrawTexture(obstaculo, recurso[i].x * TAM_GRID, recurso[i].y * TAM_GRID, WHITE);
                if (recurso[i].x == player.x && recurso[i].y == player.y)
                {
                    pega_recurso(&(recurso[i]));
                }
            }

            //desenha monstros
            for (i = 0; i < N_MAX_MONSTROS; i++)
                DrawTexture(texturas[monstros[i].idTextura], monstros[i].x * TAM_GRID, monstros[i].y * TAM_GRID, WHITE);

            for (i = 0; i < MAX_RECURSOS; i++)
                DrawTexture(obstaculo, bombas[i].x * TAM_GRID, bombas[i].y * TAM_GRID, GRAY);

            int multiplo = 10;

            DrawText("Vidas: ", 10, 10, 50, RED);
            DrawText("recursos: ", 10, 50, 50, RED);
            DrawText(TextFormat("%i", playerRecursos), 270, 50, 50, RED);
            DrawText(TextFormat("%i", podePegarRecursos), 270, 90, 50, RED);
            DrawText(TextFormat("%i", framesCounter1), 270, 130, 50, RED);
            DrawText("mons vivos: ", 10, 170, 50, RED);
            DrawText(TextFormat("%i", monstros_vivos), 320, 170, 50, RED);

            for (b=0; b<playerVidas; b++)
            {
                multiplo = b * 40;
                DrawTexture(vidas, 170 + multiplo, 18, WHITE);
            }


            if (monstros[1].vivo == 1)
                DrawText("ok!", 360, 10, 50, RED);

            // gameover
            if (playerVidas <= 0 || base.vidas == 0)
            {
                playerVidas = 0;
                DrawRectangle(0, 0, LARGURA, ALTURA, cinzamorto);
                DrawText("GAME OVER", 50, 230, 180, RED);
                gameover = 0;
            }

            if (monstros_vivos == 9 && n_monstros_spawnados == 10){
                DrawRectangle(0, 0, LARGURA, ALTURA, cinzamorto);
                DrawText("VITORIA!", 190, 230, 180, RED);
                DrawText("fazer funcao passa de fase", 190, 390, 50, RED);
                DrawText("= muda o mapa", 190, 430, 50, RED);
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

    mapa 5

    char mapa[N_LINHAS + 1][N_COLUNAS + 1] = {
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    "WWWWWWWW                 WWWWWWW                 WWWWWWWWWWW",
    "WWWWWWWW WWWWWWWWWWWWWWW WWWWWWW WWWWWWWWWWWWWWW WWWWWWWWWWW",
    "WWWWWWWW W             W WWWWWWW W             W WWWWWWWWWWW",
    "WWWWWWWW W        R    W WWWWWWW W             W WWWWWWWWWWW",
    "WWWWWWWW W      J      H WWWWWWW H   R         W WWWWWWWWWWW",
    "WWWWWWWW W             H WWWWWWW H             W WWWWWWWWWWW",
    "WWWWWWWW W             W WWWWWWW W       R     W WWWWWWWWWWW",
    "WWWWWWWW W  R          W WWWWWWW W             W WWWWWWWWWWW",
    "WWWWWWWW WWWWWW  WWWWWWW WWWWWWW WWWWWWW  WWWWWW WWWWWWWWWWW",
    "WWWWWWWW                                                  SW",
    "WWWWWWWWWWWWWWWHHWWWWWWW WWW WWW WWWWWWWHHWWWWWW WWWWWWWWWWW",
    "W                                                WWWWWWWWWWW",
    "WWWWWWWWWWWWWWWHHWWWWWWW WWW WWW WWWWWWWHHWWWWWWWWWWWWWWWWWW",
    "WWWWWWWW                                         WWWWWWWWWWW",
    "WWWWWWWW WWWWWW  WWWWWWW WWWWWWW WWWWWWW  WWWWWW WWWWWWWWWWW",
    "WWWWWWWW W             W WWWWWWW W             W WWWWWWWWWWW",
    "WWWWWWWW W             W WWWWWWW W         R   W WWWWWWWWWWW",
    "WWWWWWWW W     R       W WWWWWWW W             W WWWWWWWWWWW",
    "WWWWWWWW W             W WWWWWWW W             W WWWWWWWWWWW",
    "WWWWWWWW W             H WWWWWWW H     R       W WWWWWWWWWWW",
    "WWWWWWWW W             H WWWWWWW H             W WWWWWWWWWWW",
    "WWWWWWWW W        R    W WWWWWWW W             W WWWWWWWWWWW",
    "WWWWWWWW W             W WWWWWWW W             W WWWWWWWWWWW",
    "WWWWWWWW WWWWWWWWWWWWWWW WWWWWWW WWWWWWWWWWWWWWW WWWWWWWWWWW",
    "WWWWWWWW                 WWWWWWW                 WWWWWWWWWWW",
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};
    */
