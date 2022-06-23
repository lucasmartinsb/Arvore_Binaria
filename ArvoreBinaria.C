#include <stdio.h>

typedef struct ARVORE
{
    char palavra[20];
    int repeticao;
    struct ARVORE *left, *right;
}Arvore;

typedef struct NODE
{
    char key;
    struct NODE *prox;
}Node;

int main(){

    int teste = 10;    
    printf("Fala Rafa");

    teste+=teste;

    return 0;
}
