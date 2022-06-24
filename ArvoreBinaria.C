#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}Nodo;

Nodo *inicio;

void insereinicio(char key){
    Nodo *novo;

    novo=(Nodo*)malloc(sizeof(Nodo));
    novo->key=key;
    novo->prox=NULL;

    if(inicio==NULL){
        inicio = novo;
    }
    else{
        novo->prox = inicio;
        inicio = novo;
    }

}

void insereordenado(char key){
    Nodo *aux,*ant,*novo;
    
    novo = (Nodo*)malloc(sizeof(Nodo));
    novo->key = key;
    novo->prox=NULL;
    if(inicio==NULL)   //primeiro e unico
        inicio=novo;
    else if(key <= inicio->key){  //primeiro
            novo->prox=inicio;
            inicio=novo;
         }
         else{
             aux=ant=inicio;   
             while (aux != NULL && (aux->key) < (novo->key) ){
                    ant = aux;
                    aux = aux->prox;
            }
            if(aux==NULL){     //no fim
                ant->prox=novo;
            }
            else {  //no meio
                    ant->prox = novo;
                    novo->prox = aux;
            }
         }
}


int main(){

    insereordenado('b');
    insereordenado('a');
    
    return 0;
}
