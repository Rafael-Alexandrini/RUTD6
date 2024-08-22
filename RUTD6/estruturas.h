#ifndef ESTRUTURAS_H_   /* Include guard */
#define ESTRUTURAS_H_
#define MAX_RECURSOS 100
#define N_MAX_MONSTROS 4


struct posicao
{
    int x, y;
};

struct Inimigo
{
    int x, y;
    int dirx, diry;
    int idTextura;
    int vivo;
};

struct bomba
{
    int x, y;
    int ativo;
};

struct base
{
    int x, y;
    int vidas;
};

struct Save
{
    struct posicao *spawnwer;
    struct posicao *jogador;
    int *vidasJogador;
    int *recursosJogardor;
    struct base *base;
    struct Inimigo *monstros; // array de monstros
    int *n_monstros_vivos;
    int *n_monstros_spawnados;
    struct posicao *recursos; // array de recursos
    struct bomba *bombas; // array de bombas
    int *indiceBombas;
    int *nMapa;
    int *tickCounter;
};
#endif // ESTRUTURAS_H_
