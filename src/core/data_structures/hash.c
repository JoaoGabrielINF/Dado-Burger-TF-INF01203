#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarHash(TabelaHash *t){
    t->m =  TAMANHO_HASH;
    t->n = 0;
    t->tabela = malloc(t->m * sizeof(NoHash*));
    for(int i = 0; i < t->m; i++){
        t->tabela[i] = NULL;
    }
    
}

bool inserirHash(TabelaHash *t, int chave, const ListaReceita *lista) {
    int i = chave % t->m;
    NoHash *novo_no = (NoHash*) malloc(sizeof(NoHash));
    bool colisao = true;
    novo_no->chave = chave;
    novo_no->valor.ini = lista->ini;
    if(t->tabela[i] == NULL) colisao = false;
    novo_no->prox  = t->tabela[i];   /* insere NoHash início */
    t->tabela[i] = novo_no;
    t->n++;
    return colisao;
}

NodoLista* buscarHash(TabelaHash *t, int chave) {
    int i = chave % t->m;
    NoHash *p = t->tabela[i];
    while (p != NULL) {
        if (p->chave == chave) return p->valor.ini;
        p = p->prox;
    }
    return NULL;   /* não encontrado */
}

bool removerHash(TabelaHash *t, int chave) {
    int i = chave % t->m;
    NoHash *p = t->tabela[i];
    NoHash *ant = NULL;
    while (p != NULL) {
        if (p->chave == chave) {
            if (ant == NULL)
                t->tabela[i] = p->prox;   /* era o primeiro */
            else
                ant->prox = p->prox;
            free(p);
            t->n--;
            return 1;   /* removido */
        }
        ant = p;
        p   = p->prox;
    }
    return 0;   /* não encontrado */
}

void reiniciaHash(TabelaHash *t){
    if (t == NULL) {
        return;
    }

    NoHash *aux;

    for(int i = 0; i < t->m; i++){
        aux = t->tabela[i];
        NoHash *ant;
        while(aux != NULL){
            ant = aux;
            aux = aux->prox;
            free(ant);
        }
        t->tabela[i] = NULL;
    }
    t->n = 0;
}