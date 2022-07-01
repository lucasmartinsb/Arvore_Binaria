#include<bits/stdc++.h>
using namespace std;

struct nodeIndice{
    char info;
    struct nodeIndice *prox;
    struct nodePalavra *primeiro;
};
typedef struct nodeIndice nodeIndice;

struct nodePalavra{
    string palavra;
    int repeticoes;
    struct nodePalavra *esq;
    struct nodePalavra *dir;
    struct nodePalavra *pai;
};
typedef struct nodePalavra nodePalavra;

nodeIndice *raiz;

nodePalavra* inserenodePalavra(string info){
    //nodePalavra *novo = (nodePalavra *) malloc(sizeof(nodePalavra));
    nodePalavra *novo = new nodePalavra;
    //novo = NULL;

    novo->palavra = info;
    novo->repeticoes = 1;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
    
    return novo;
}

nodeIndice* insereNodeIndice(char info){
    nodeIndice *aux, *ant, *novo;

    novo = new nodeIndice;

    novo->info=info;
    novo->prox=NULL;
    novo->primeiro=NULL;

    if(raiz==NULL){
        raiz = novo;
    }

    else if(info <= raiz->info){ //Se é o menor elemento da lista, insere na frente (mesma coisa se colocar só a func insereraiz())
        novo->prox = raiz;
        raiz = novo; 
    }

    else{
        aux = ant = raiz; // No fim
        while ( aux != NULL && (aux->info) < (novo->info) ){ // Se o o novo info é maior que o último, passa para o prox
            ant = aux;
            aux = aux->prox;
        }
        if(aux==NULL){
            ant->prox = novo; // Se não tem prox, insere
        }
        else{ // No meio
            ant->prox = novo;
            novo->prox = aux;
        }
    }
    return raiz;
}

bool verifLetra(char letra){
    nodeIndice *aux = raiz;
    if(raiz == NULL){
        return 0;
    }
    else{
        while(aux != NULL){
            if(aux->info == letra){
                return 1;
            }
            aux = aux->prox;
        }
    }
    return 0;
}

void *insereArvore(nodePalavra *novo, nodePalavra *atual){
    int comparacao = novo->palavra.compare(atual->palavra);
    //strcmp(palavra, inicio->palavra);
    if(comparacao < 0){
        if(atual->esq==NULL){
            atual->esq = novo;
            atual->esq->pai = atual;
        }
        else{
            insereArvore(novo, atual->esq);
        }
    }
    else if(comparacao > 0){
        if(atual->dir==NULL){
            atual->dir = novo;
            atual->dir->pai = atual;
        }
        else{
            insereArvore(novo, atual->dir);
        }
    }
    else if(comparacao == 0){
        atual->repeticoes+=1;
    }
}


nodePalavra * inserePalavra(string palavra){
    char primeira = palavra[0];
    if(raiz == NULL){
        raiz = insereNodeIndice(primeira);
    }
    
    else if(!verifLetra(primeira)){
        raiz = insereNodeIndice(primeira);
    }

    nodeIndice *auxIndice = raiz;
    while(auxIndice!=NULL && auxIndice->info!=primeira){
        auxIndice = auxIndice->prox;
    }

    if(auxIndice->primeiro == NULL){
        auxIndice->primeiro = inserenodePalavra(palavra);
    }
    else{
        insereArvore(inserenodePalavra(palavra), auxIndice->primeiro);
    }
}

int contaOcorrencias(nodePalavra *aresta, int cont){
    if(aresta!=NULL){
        if(aresta->esq != NULL){
            cont = contaOcorrencias(aresta->esq, cont);
        }
        if(aresta->dir != NULL){
            cont = contaOcorrencias(aresta->dir, cont);
        }
        cont = cont + aresta->repeticoes;
    }
    return cont;
}


void quantOcorrencias(){
    nodeIndice *auxIndice = raiz;
    nodePalavra *auxPalavra;
    int cont = 0;

    while(auxIndice != NULL){
        cont = contaOcorrencias(auxIndice->primeiro, cont);
        auxIndice = auxIndice->prox;
    }
    printf("Quantidade de palavras (ocorrencias): %d\n", cont);
}

int contaUnicas(nodePalavra *aresta, int cont){
    if(aresta!=NULL){
        if(aresta->esq != NULL){
            cont = contaUnicas(aresta->esq, cont);
        }
        if(aresta->dir != NULL){
            cont = contaUnicas(aresta->dir, cont);
        }
        cont = cont + 1;
    }
    return cont;
}

nodePalavra* buscaRecuriva (nodePalavra * no, string palavra){
    int comparacao = no->palavra.compare(palavra);
    while (no != NULL){
        if(no->palavra == palavra){
            return no;
        }
        else{
            if(comparacao > 0){
                return buscaRecuriva(no->esq, palavra);
            }
            else{ 
                return buscaRecuriva(no->dir, palavra);
            }
        }
    }
    return NULL;
}

nodePalavra * buscaPalavra(string palavra){
    nodeIndice *auxIndice = raiz;
    nodePalavra *auxPalavra;
    while(auxIndice != NULL && auxIndice->info != palavra[0]){
        auxIndice = auxIndice->prox;
    }

    auxPalavra = buscaRecuriva(auxIndice->primeiro, palavra);

    return auxPalavra;
}

void quantPalavrasUnicas(){
    nodeIndice *auxIndice = raiz;
    nodePalavra *auxPalavra;
    int cont = 0;

    while(auxIndice != NULL){
        cont = contaUnicas(auxIndice->primeiro, cont);
        auxIndice = auxIndice->prox;
    }
    printf("Quantidade de palavras unicas: %d\n", cont);
}

void preFix(nodePalavra *aresta){
    if(aresta!=NULL){
        cout << aresta->palavra;
        printf("\n");
        preFix(aresta->esq);
        preFix(aresta->dir);
    }
}

void preFixMenor(nodePalavra *aresta){
    if(aresta!=NULL){
        int comparacao = aresta->palavra.compare(aresta->esq->palavra);
        if(comparacao > 0){
            cout << aresta->esq->palavra;
            printf("\n");
            cout << aresta->palavra;
            printf("\n");
        }
        preFixMenor(aresta->esq);
        preFixMenor(aresta->dir);
    }
}

void exibePalavrasTotal(){
    nodeIndice *auxIndice = raiz;

    while(auxIndice != NULL){
        preFixMenor(auxIndice->primeiro);
        auxIndice = auxIndice->prox;
    }
}

void exibePalavrasIndice(char letra){
    nodeIndice *auxIndice = raiz;

    while(auxIndice != NULL && auxIndice->info != letra){
        auxIndice = auxIndice->prox;
    }
    preFix(auxIndice->primeiro);
}

nodePalavra* maiorOcorrenciasIndice(nodePalavra *aresta, nodePalavra *maior){
    nodePalavra *palavraMaisRepetida, *palavraEsq, *palavraDir;

    if(aresta->esq != NULL){
        palavraEsq = maiorOcorrenciasIndice(aresta->esq, maior);
        if(palavraEsq != NULL){
            maior = palavraEsq;
        }
    }
    if(aresta->dir != NULL){
        palavraDir = maiorOcorrenciasIndice(aresta->dir, maior);
        if(palavraDir != NULL){
            maior = palavraDir;
        }
    }
    if(maior == NULL){
        return aresta;
    }
    if(aresta->repeticoes > maior->repeticoes){
        return aresta;
    }
    else{
        return maior;
    }
}

void maiorOcorrencias(){
    nodeIndice *auxIndice = raiz;
    int maior = 0;
    nodePalavra *nodeMaisRepetido, *nodeMaisRepetidoIndice = NULL;

    while(auxIndice != NULL){
        nodeMaisRepetidoIndice = maiorOcorrenciasIndice(auxIndice->primeiro, nodeMaisRepetidoIndice);
        int teste = nodeMaisRepetidoIndice->repeticoes;
        if(teste > maior){
            nodeMaisRepetido = nodeMaisRepetidoIndice;
        }
        auxIndice = auxIndice->prox;
    }

    cout << nodeMaisRepetido->palavra;
    printf(" - %d ocorrencias", nodeMaisRepetido->repeticoes);
}

void umaOcorrenciaIndice(nodePalavra *aresta){
    if(aresta!=NULL){
        if(aresta->repeticoes == 1){
            cout << aresta->palavra;
            printf("\n");
        }
        umaOcorrenciaIndice(aresta->esq);
        umaOcorrenciaIndice(aresta->dir);
    }
}

void umaOcorrencia(){
    nodeIndice *auxIndice = raiz;

    while(auxIndice != NULL){
        umaOcorrenciaIndice(auxIndice->primeiro);
        auxIndice = auxIndice->prox;
    }
}

int quantosFilhos(nodePalavra *aresta){
    if(aresta->esq == NULL && aresta->dir == NULL){
        return 0;
    }
    else if((aresta->esq != NULL && aresta->dir == NULL) || (aresta->esq == NULL && aresta->dir != NULL)){
        return 1;
    }
    else{
        return 2;
    }
}

int removeFolha(nodePalavra *aresta){
    nodePalavra *pai = aresta->pai;
    if(pai==NULL){
        return 0;
    }
    else{
        if(pai->esq == aresta){
            pai->esq = NULL;
            return 1;
        }
        else{
            pai->dir = NULL;
            return 1;
        }
    }
    free(aresta);
}

void removeUmFilho(nodePalavra *aresta, nodePalavra *raiz){
    nodePalavra *pai = aresta->pai;
    if(pai = NULL){ //nodo excluido e a raiz da arvore
        if(aresta->esq != NULL){
            raiz = aresta->esq;
        }
        else{
            raiz = aresta->dir;
        }
    }
    else{
        if(aresta->esq == NULL){
            if(pai->dir == aresta){
                pai->dir = aresta->dir;
            }
            else{ //pai->esq==aresta
				pai->esq=aresta->dir;
			}
			aresta->dir->pai = pai;
        }
			else{ //aresta->dir==null
				if(pai->dir==aresta){
					pai->dir=aresta->esq;
				}
				else{ //pai.getEsq()==aresta
					pai->esq=aresta->esq;
				}
				aresta->esq->pai = pai;
			}
            free(aresta);	
    }
}

void removeDoisFilhos( struct nodePalavra *aresta, nodePalavra *raiz){
	//Remove um nodo que possui dois filhos
    nodePalavra *aux=aresta->esq;
    nodePalavra *pai = NULL;
            
    while(aux->dir!= NULL){//Busca o elemento mais da direita (desce a esq. e depois a direita)
        aux = aux->dir;
    }
    aresta->palavra = aux->palavra; //atribui o novo valor
    
    //Nodo Folha
    if((aux->esq == NULL) && (aux->dir == NULL)){
        removeFolha(aux);
    }
    else{
        removeUmFilho(aux, raiz);
    }				
}

void removePalavra(string palavra){
    nodePalavra *nodeExcluido = buscaPalavra(palavra);
    nodeIndice *auxIndice = raiz;

    while(auxIndice != NULL && auxIndice->info != palavra[0]){
        auxIndice = auxIndice->prox;
    }

    
    if(quantosFilhos(nodeExcluido) == 0){
        removeFolha(nodeExcluido);
    }
    else if(quantosFilhos(nodeExcluido) == 1){
        removeUmFilho(nodeExcluido, auxIndice->primeiro);
    }
    else if(quantosFilhos(nodeExcluido) == 2){
        removeDoisFilhos(nodeExcluido, auxIndice->primeiro);
    }
}

int main(){
    raiz = NULL;

    inserePalavra("abelha");
    inserePalavra("crocodiloilho");
    inserePalavra("bala");
    inserePalavra("caralho");
    inserePalavra("jesus");
    inserePalavra("ambulancia");
    inserePalavra("trator");
    inserePalavra("aa");

    /*printf("\n");
    quantOcorrencias();
    printf("\n");
    quantPalavrasUnicas();
    printf("\n");
    buscaPalavra("abacate");
    printf("\n");
    exibePalavrasTotal();
    printf("\n");
    maiorOcorrencias();
    printf("\n");
    umaOcorrencia();
    printf("\n");*/

    exibePalavrasTotal();
    printf("\n");

    /*removePalavra("abelha");

    exibePalavrasTotal();
    printf("\n");

    exibePalavrasIndice('a');
    printf("\n");*/

    return 0;
}