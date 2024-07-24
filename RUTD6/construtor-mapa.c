#include <stdio.h>

int main()
{
    char mapa[31][61];
    printf("Manda la: \n");
    for(int i = 0; i<31; i++)
        gets(mapa[i]);
    for(int l = 0; l< 30; l++)
    {
        printf("\"");
        for (int c = 0; c < 60; c++ )
        {
            printf("%c", mapa[l][c]);
        }
        printf("\"");
        printf(",");
        printf("\n");
    }




    return 0;
}
