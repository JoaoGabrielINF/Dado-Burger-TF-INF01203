#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

void inserir(TabelaHash *t, int chave, int valor) {
    int i = chave % t->m;
    NoHash *novo_no = (NoHash*) malloc(sizeof(NoHash));
    novo_no->chave = chave;
    novo_no->valor = valor;
    novo_no->prox  = t->tabela[i];   /* insere NoHash início */
    t->tabela[i] = novo_no;
    t->n++;
}

int buscar(TabelaHash *t, int chave) {
    int i = chave % t->m;
    NoHash *p = t->tabela[i];
    while (p != NULL) {
        if (p->chave == chave) return p->valor;
        p = p->prox;
    }
    return false;   /* não encontrado */
}

bool remover(TabelaHash *t, int chave) {
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