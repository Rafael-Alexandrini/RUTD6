#ifndef ESTRUTURAS_H_   /* Include guard */
#define ESTRUTURAS_H_


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
#endif // ESTRUTURAS_H_
