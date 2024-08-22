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

struct jogo
{
    struct base base;
    struct posicao spawnwer;
    struct posicao jogador;
    struct posicao recursos[MAX_RECURSOS];
    struct bomba bombas[MAX_RECURSOS];
    struct Inimigo monstros[N_MAX_MONSTROS];



};
#endif // ESTRUTURAS_H_
