#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ARVORE
{
    char palavra[20];
    int repeticao;
    struct ARVORE *esq, *dir,*pai;
}Arvore;

typedef struct NODE
{
    char key;
    struct NODE *prox;
    Arvore *noAV;
}Nodo;

Nodo *inicio = NULL;

void insereinicio(char key){
    Nodo *novo;

    novo=(Nodo*)malloc(sizeof(Nodo));
    novo->key=key;
    novo->noAV =NULL;
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

int ehmenor(char a, char b)
{
    if(a < b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



Arvore* buscaNodo(char key,Nodo* aux){
    if(aux==NULL){
        insereordenado(key);
        return buscaNodo(key,inicio);
    }
    if(key = aux->key){
        return aux->noAV;
    }
    else{
        return buscaNodo(key, aux->prox);
    }
}

void inserePalavra(char palavra[20])
{
    char key = palavra[0];
    Arvore *aux = buscaNodo(key,inicio);

}

int main(){

    char palavra[20];
    printf("Insira uma palavra:");
    gets(palavra);
    inserePalavra(palavra);
    
    return 0;
}