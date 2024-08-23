#include "raylib.h"
#include "nossas_funcoes.h"
#include "estruturas.h"
#include "nossas_funcoes.c"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>




int main()
{
    // ----------------------------------------- INICIALIZAÇÕES -----------------------------------------

    // Mapa default
    char mapa[N_LINHAS][N_COLUNAS] =
    {
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "W                                                          W",
        "W                                                          W",
        "W    HHHHH  HHH   HHH    HHH   H                           W",
        "W    H      H  H  H  H  H   H  H                           W",
        "W    HHHHH  HHH   HHH   H   H  H                           W",
        "W    H      H  H  H  H  H   H                              W",
        "W    HHHHH  H  H  H  H   HHH   M                           W",
        "W                                                          W",
        "W                                                          W",
        "W                                                          W",
        "W                                                          W",
        "W    W   W   WW   WWW    WW                                W",
        "W    WW WW  W  W  W  W  W  W                               W",
        "W    W W W  WWWW  WWW   WWWW                               W",
        "W    W   W  W  W  W     W  W                               W",
        "W    W   W  W  W  W     W  W                               W",
        "W                    J                                     W",
        "W                                                          W",
        "W                         R                                W",
        "W                        R                                 W",
        "W    R  R   R  R   R   RR   R     R  RRR    RRR            W",
        "W       RR  R  R   R  R  R  R        R  R  R   R           W",
        "W    R  R R R  R   R  RRRR  R     R  R  R  R   R           W",
        "W    R  R  RR   R R   R  R  R     R  R  R  R   R           W",
        "W    R  R   R    R    R  R  RRRR  R  RRR    RRR            W",
        "W                                                          W",
        "W                                                          W",
        "W                                                         SW",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    };

    srand(time(NULL));

    Color cinzamorto = {176, 176, 176, 200};
    Color caminho = {11, 140, 133, 255};
    Color branco_transparente = {255, 255, 255, 100};

    // inicialização de estruturas
    struct base base = {10, 10, 10};
    struct posicao player = {15, 15};
    struct posicao spawner = {10, 10};
    struct posicao recurso[MAX_RECURSOS] = {{10, 10}, {20, 30}};
    struct Inimigo monstros[N_MAX_MONSTROS] = {};
    struct bomba bombas[MAX_RECURSOS] = {{-1, -1, 1}, {-1, -1, 1}};
    reseta_posicoes(recurso, monstros, bombas); // inicializa as posições

    // inicialização de variáveis
    int l, c, i, b;
    int q = 0;
    int indBombas = 0;
    int a = 0;
    int w = 0;
    int playerRecursos = 0;
    int podePegarRecursos = 1;
    int playerVidas = PLAYER_VIDAS;
    int podeTomarDano = 1;
    int framesCounter = 0;
    int framesCounter1 = 0;
    int framesCounter2 = 0;
    int gameover = 0;
    int pausado = 0;
    float ultimo_tick = 0;
    int tickCounter = 0;
    int n_monstros_spawnados = 0;
    int monstros_vivos = 0;
    int vitoria = 0;
    int nMapa = 0;
    int multiplo = 10;
    base.vidas = 3;
    int deveFechar = 0;
    int finalizouMapas = 0;
    int quantletras = 0;
    char cheats[MAXCARAC + 1] = "\0";
    int contcarac = 0;
    int key;
    int rapidin = 0;
    // Atribui ponteiros à estrutura save
    struct Save salvamento = {};
    salvamento.spawnwer = &spawner;
    salvamento.jogador = &player;
    salvamento.vidasJogador = &playerVidas;
    salvamento.recursosJogador= &playerRecursos;
    salvamento.base = &base;
    salvamento.monstros = monstros;
    salvamento.n_monstros_vivos = &monstros_vivos;
    salvamento.n_monstros_spawnados= &n_monstros_spawnados;
    salvamento.recursos = recurso;
    salvamento.bombas = bombas;
    salvamento.indiceBombas = &indBombas;
    salvamento.nMapa = &nMapa;
    salvamento.tickCounter = &tickCounter;



    typedef enum Tela {TITLE, GAMEPLAY} Tela;

    Tela telaAtual = TITLE;


    // ----------------------------------------- LOOP PRINCIPAL DE GAMEPLAY -----------------------------------------
    InitWindow(LARGURA, ALTURA, "RUTD6");
    SetTargetFPS(60);
    // inicialização de texturas
    Texture2D tijolo = LoadTexture("texturas/tijolo.png");
    Texture2D texturas[4] = {LoadTexture("texturas/estudante 1.png"), LoadTexture("texturas/estudante 2.png"), LoadTexture("texturas/estudante 3.png"), LoadTexture("texturas/estudante 4.png")};
    Texture2D baseF = LoadTexture("texturas/ru.png");
    Texture2D vidas = LoadTexture("texturas/coração.png");
    Texture2D obstaculo =  LoadTexture("texturas/prova calc.png");
    Texture2D portal =  LoadTexture("texturas/portal.png");
    Texture2D titleScreen = LoadTexture("texturas/th.png");
    Texture2D cadeira = LoadTexture("texturas/cadeira.png");

    while(!WindowShouldClose() && !deveFechar)
    {
        switch(telaAtual)
        {
        case TITLE:
        {

            if (IsKeyDown(KEY_Q)) // sair do jogo
                deveFechar = 1;

            if (IsKeyDown(KEY_N)) // novo jogo sem nada salvo
            {
                nMapa = PRIMEIRO_MAPA;
                carrega_mapa(mapa, nMapa);
                reseta_posicoes(recurso, monstros, bombas);
                zera_estado(&vitoria, &gameover, &monstros_vivos, &n_monstros_spawnados);
                acha_no_mapa(mapa, &player, &spawner, &base, recurso, monstros, &n_monstros_spawnados, &monstros_vivos);
                pausado = 0;
                playerRecursos = 0;
                playerVidas = PLAYER_VIDAS;
                finalizouMapas = 0;
                telaAtual = GAMEPLAY;
            }

            if (IsKeyDown(KEY_C)) // carrega jogo anterior
            {
                reseta_posicoes(recurso, monstros, bombas);
                zera_estado(&vitoria, &gameover, &monstros_vivos, &n_monstros_spawnados);
                pausado = 0;
                carrega_save(salvamento);
                carrega_mapa(mapa, nMapa);
                telaAtual = GAMEPLAY;
            }
            break;
        }
        case GAMEPLAY:
        {
            if (!pausado)       //Lógica padrão do jogo não pausado
            {
                // Ações do Jogador
                if (gameover == 0 && vitoria == 0)
                {
                    if (rapidin == 1 && IsKeyDown(KEY_LEFT_SHIFT)) // movimento com cheats
                    {
                        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) tenta_mover(&player.x, &player.y, 0, -1, mapa);
                        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) tenta_mover(&player.x, &player.y, 0, 1, mapa);
                        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) tenta_mover(&player.x, &player.y, -1, 0, mapa);
                        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) tenta_mover(&player.x, &player.y, 1, 0, mapa);
                    }
                    else // movimento do jogador sem cheats
                    {
                        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) tenta_mover(&player.x, &player.y, 0, -1, mapa);
                        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) tenta_mover(&player.x, &player.y, 0, 1, mapa);
                        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) tenta_mover(&player.x, &player.y, -1, 0, mapa);
                        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) tenta_mover(&player.x, &player.y, 1, 0, mapa);
                    }
                    if (IsKeyPressed(KEY_G) && playerRecursos > 0) // G coloca bombas
                    {
                        bombas[indBombas].x = player.x;
                        bombas[indBombas].y = player.y;
                        indBombas++;
                        playerRecursos--;
                        if (indBombas >= MAX_RECURSOS)
                            indBombas = 0;
                    }
                    if(IsKeyPressed(KEY_TAB)) pausado = !pausado;  // tab pausa o jogo
                }


                // CONTADOR DE TICKS (roda 16 vezes por segundo, ficando mais rápido a cada nível)
                if ((GetTime() > ultimo_tick + 1/(16.0 + nMapa * 3)) && gameover == 0)
                {
                    ultimo_tick = GetTime();
                    tickCounter++;
                    // A cada 8 ticks: movimento dos inimigos
                    if(tickCounter % 8 == 0)
                    {
                        for (i=0; i<N_MAX_MONSTROS; i++)
                        {
                            move_inimigo(&(monstros[i]), mapa);
                        }
                    }
                    // A cada 24 ticks: spawn dos inimigos
                    if(tickCounter % 24 == 0 && n_monstros_spawnados < nMapa * 2)
                    {
                        monstros[n_monstros_spawnados].x = spawner.x;
                        monstros[n_monstros_spawnados].y = spawner.y;
                        monstros[n_monstros_spawnados].dirx = 0;
                        monstros[n_monstros_spawnados].diry = 1;
                        n_monstros_spawnados++;
                        monstros_vivos++;
                    }
                }

                // Sistema para ler cheatcodes
                key = tolower(GetCharPressed());
                if (key > 0)
                {
                    if ((key >= 32) && (key<=125) && contcarac < MAXCARAC)
                    {
                        cheats[contcarac] = (char)key;
                        cheats[contcarac+1] = '\0';
                        contcarac++;
                    }
                }
                if(IsKeyPressed(KEY_BACKSPACE))
                {
                    contcarac--;
                    if (contcarac < 0) contcarac = 0;
                    cheats[contcarac] = '\0';
                }
                if (strcmp(cheats, "amor venceu") == 0)
                {
                    playerVidas = playerVidas + 10;
                    strcpy(cheats, "\0");
                    contcarac = 0;
                }
                if (strcmp(cheats, "creeper") == 0)
                {
                    playerRecursos = playerRecursos + 10;
                    strcpy(cheats, "\0");
                    contcarac = 0;
                }
                if (strcmp(cheats, "velocidade") == 0)
                {
                    rapidin = 1;
                    strcpy(cheats, "\0");
                    contcarac = 0;
                }

                // Vê se player deve tomar dano e conta tempo de invincibilidade
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
                // vê se player pegou recurso e tempo mínimo pra pegar mais um recurso
                for (i = 0; i < MAX_RECURSOS; i++)
                {
                    if ((recurso[i].x == player.x && recurso[i].y == player.y) && podePegarRecursos == 1)
                    {
                        playerRecursos++;
                        podePegarRecursos = 0;
                        pega_recurso(&(recurso[i]));
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



                // checa colisão dos monstro com bombas e com base
                for (a = 0; a < N_MAX_MONSTROS; a++)
                {
                    if (monstros[a].x == base.x && monstros[a].y == base.y)
                    {
                        monstros[a].x = -20;
                        monstros[a].y = -20;
                        monstros[a].vivo = 0;
                        base.vidas--;
                        monstros_vivos--;
                    }
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


                // Checa se o player perdeu: DERROTA
                if (playerVidas <= 0 || base.vidas <= 0)
                {
                    playerVidas = 0;
                    gameover = 1;
                    if (IsKeyPressed(KEY_ENTER))
                    {
                        telaAtual = TITLE;
                    }
                }
                // Checa se o player venceu: VITÓRIA
                if (monstros_vivos == 0 && n_monstros_spawnados >= nMapa * 2)
                {
                    vitoria = 1;
                    if (IsKeyPressed(KEY_ENTER))
                    {
                        nMapa++;
                        playerVidas++;
                        if (nMapa <= MAX_MAPAS) // Vai para o próximo mapa
                        {
                            carrega_mapa(mapa, nMapa);
                            indBombas = 0;
                            reseta_posicoes(recurso, monstros, bombas);
                            zera_estado(&vitoria, &gameover, &monstros_vivos, &n_monstros_spawnados);
                            acha_no_mapa(mapa, &player, &spawner, &base, recurso, monstros, &n_monstros_spawnados, &monstros_vivos);
                            base.vidas = 3;
                        }
                        else
                        {   // Vai para a tela final de vitória se acabaram os mapas
                            telaAtual = TITLE;
                            finalizouMapas = 1;
                        }
                    }
                }
            }
            else            // Tela de Pause
            {
                if(IsKeyPressed(KEY_TAB)) pausado = !pausado; // tab despausa
                if(IsKeyPressed(KEY_C)) pausado = !pausado; // C despausa
                if(IsKeyPressed(KEY_L)){                    // L Carrega jogo salvo
                    reseta_posicoes(recurso, monstros, bombas);
                    zera_estado(&vitoria, &gameover, &monstros_vivos, &n_monstros_spawnados);
                    pausado = 0;
                    carrega_save(salvamento);
                    carrega_mapa(mapa, nMapa);
                }
                if(IsKeyPressed(KEY_S)) salva_jogo(salvamento); // S Salva jogo
                if(IsKeyPressed(KEY_V)) telaAtual = TITLE;      // V Volta para tela inicial
                if(IsKeyPressed(KEY_F)) deveFechar = 1;         // F Fecha o jogo
            }
        }
        break;
        }


        // ----------------------------------------- DESENHOS -----------------------------------------
        // Atualiza frame e desenha
        BeginDrawing();
        ClearBackground(RAYWHITE);


        switch(telaAtual)
        {
        case TITLE: // Tela de título
        {
            DrawTexture(titleScreen, 0, 0, WHITE);
            DrawRectangle(0, 0, LARGURA, ALTURA, branco_transparente);
            DrawText("RUTD 6", (LARGURA/2 - MeasureText("RUTD6", 150)/2), 20, 150, RED);
            DrawText("opcoes: ", 50, ALTURA/2, 50, RED);
            DrawText("Q = Sair do Jogo", 50, (ALTURA/2 + 50), 50, RED);
            DrawText("C = Carregar Jogo", 50, (ALTURA/2 + 100), 50, RED);
            DrawText("N = Novo Jogo", 50, (ALTURA/2 + 150), 50, RED);
            // Frases de derrota e vitória
            if (gameover == 1)
                DrawText("Voce morreu.", 10, 170, 50, RED);
            if (finalizouMapas == 1)
                DrawText("Parabens! Completou todos os mapas!", 10, 170, 50, RED);
            break;
        }
        case GAMEPLAY:
        {

            //desenha mapa
            desenha_mapa(mapa, caminho, tijolo, baseF, portal, cadeira);
            //desenha jogador
            DrawRectangle(player.x * TAM_GRID, player.y * TAM_GRID, TAM_GRID, TAM_GRID, GREEN);
            //desenha monstros
            for (i = 0; i < N_MAX_MONSTROS; i++)
                DrawTexture(texturas[monstros[i].idTextura], monstros[i].x * TAM_GRID, monstros[i].y * TAM_GRID, WHITE);
            //desenha bombas
            for (i = 0; i < MAX_RECURSOS; i++)
                DrawTexture(obstaculo, bombas[i].x * TAM_GRID, bombas[i].y * TAM_GRID, GRAY);
            //desenha recursos
            for (i = 0; i < MAX_RECURSOS; i++)
                DrawTexture(obstaculo, recurso[i].x * TAM_GRID, recurso[i].y * TAM_GRID, WHITE);

            //desenha HUD
            DrawText("Vidas: ", 10, 10, 50, RED);
            DrawText("Vidas da base: ", 10, 50, 50, RED);
            DrawText("recursos: ", 10, 90, 35, RED);
            DrawText(TextFormat("%i", playerRecursos), 200, 90, 35, RED);
            DrawText("monstros vivos: ", 10, 115, 35, RED);
            DrawText(TextFormat("%i", monstros_vivos), 285, 115, 35, RED);


            for (b=0; b<playerVidas; b++)
            {
                multiplo = b * 40;
                DrawTexture(vidas, 170 + multiplo, 18, WHITE);
            }
            for (b=0; b<base.vidas; b++)
            {
                multiplo = b * 40;
                DrawTexture(vidas, 380 + multiplo, 58, WHITE);
            }

            //Overlays de derrota, vitória e pause
            if (gameover == 1)
            {
                DrawRectangle(0, 0, LARGURA, ALTURA, cinzamorto);
                DrawText("GAME OVER", 50, 230, 180, RED);
                DrawText("Enter para voltar", 190, 430, 50, RED);
            }
            else if (vitoria == 1)
            {
                DrawRectangle(0, 0, LARGURA, ALTURA, cinzamorto);
                DrawText("VITORIA!", 190, 230, 180, RED);
                DrawText("Enter para continuar", 190, 430, 50, RED);
            }
            else if (pausado == 1)
            {
                DrawRectangle(0, 0, LARGURA, ALTURA, cinzamorto);
                DrawText("Pausado", 190, 130, 180, RED);
                DrawText("C: Continuar\n\n\nL: Carregar ultimo jogo\n\n\nS: Salvar jogo\n\n\nV: Voltar ao menu inicial\n\n\nF: Sair", 190, 330, 50, RED);
            }

        }
        break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
