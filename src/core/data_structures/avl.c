#pragma once
#include <cliente.h>
#include <stdlib.h>
#include "avl.h"

int avlAltura(const NodoAvl *no) {
    if (no == NULL) return -1;
    return no->altura;
}

int avlFb(const NodoAvl *no) {
    if (no == NULL) return 0;
    return avlAltura(no->esq) - avlAltura(no->dir);
}

void avlAtualizarAltura(NodoAvl *no) {
    int ae = avlAltura(no->esq);
    int ad = avlAltura(no->dir);
    if (ae > ad)
        no->altura = 1 + ae;
    else
        no->altura = 1 + ad;
}

NodoAvl* avlRotDir(NodoAvl *y) {
    NodoAvl *x = y->esq;
    NodoAvl *B = x->dir;
    x->dir = y;
    y->esq = B;
    avlAtualizarAltura(y);
    avlAtualizarAltura(x);
    return x;
}

NodoAvl* avlRotEsq(NodoAvl *x) {
    NodoAvl *y = x->dir;
    NodoAvl *B = y->esq;
    y->esq = x;
    x->dir = B;
    avlAtualizarAltura(x);
    avlAtualizarAltura(y);
    return y;
}

NodoAvl* avlReequilibrar(NodoAvl *raiz) {
    avlAtualizarAltura(raiz);
    int fb = avlFb(raiz);

    /* LL: pesado à esq, filho esq também pesado à esq ou equilibrado */
    if (fb == +2 && avlFb(raiz->esq) >= 0)
        return avlRotDir(raiz);

    /* RR: pesado à dir, filho dir também pesado à dir ou equilibrado */
    if (fb == -2 && avlFb(raiz->dir) <= 0)
        return avlRotEsq(raiz);

    /* LR: pesado à esq, filho esq pesado à dir → transforma LR em LL */
    if (fb == +2 && avlFb(raiz->esq) < 0) {
        raiz->esq = avlRotEsq(raiz->esq);
        return avlRotDir(raiz);
    }

    /* RL: pesado à dir, filho dir pesado à esq → transforma RL em RR */
    if (fb == -2 && avlFb(raiz->dir) > 0) {
        raiz->dir = avlRotDir(raiz->dir);
        return avlRotEsq(raiz);
    }

    return raiz;   /* sem desequilíbrio */
}

NodoAvl* avlBuscar(NodoAvl *raiz, int cod) {
    if (raiz == NULL)           return NULL;
    if (cod == raiz->dado.cod) return raiz;
    if (cod < raiz->dado.cod)  return avlBuscar(raiz->esq, cod);
    return avlBuscar(raiz->dir, cod);
}

NodoAvl* avlInserir(NodoAvl *raiz, Pedido valor) {
    if (raiz == NULL) {
        NodoAvl *novo = (NodoAvl*) malloc(sizeof(NodoAvl));
        novo->dado   = valor;
        novo->esq    = NULL;
        novo->dir    = NULL;
        novo->altura = 0;
        return novo;
    }
    if (valor.cod < raiz->dado.cod)
        raiz->esq = avlInserir(raiz->esq, valor);
    else if (valor.cod > raiz->dado.cod)
        raiz->dir = avlInserir(raiz->dir, valor);
    else
        return raiz;   /* duplicado: ignora */
    return avlReequilibrar(raiz);
}

NodoAvl* avlMinimo(NodoAvl *raiz) {
    while (raiz->esq != NULL) raiz = raiz->esq;
    return raiz;
}


NodoAvl* avlRemover(NodoAvl *raiz, int cod) {
    if (raiz == NULL) return NULL;

    if (cod < raiz->dado.cod) {
        raiz->esq = avlRemover(raiz->esq, cod);
    } else if (cod > raiz->dado.cod) {
        raiz->dir = avlRemover(raiz->dir, cod);
    } else {
        if (raiz->esq == NULL) {
            NodoAvl *filho = raiz->dir; free(raiz); return filho;
        }
        if (raiz->dir == NULL) {
            NodoAvl *filho = raiz->esq; free(raiz); return filho;
        }
        /* dois filhos: substitui pelo sucessor em-ordem */
        NodoAvl *sucessor = avlMinimo(raiz->dir);
        raiz->dado = sucessor->dado;
        raiz->dir  = avlRemover(raiz->dir, sucessor->dado.cod);
    }
    return avlReequilibrar(raiz);
}

NodoAvl* avlDestruir(NodoAvl *raiz) {
    if (raiz == NULL) return NULL;
    raiz->esq = avlDestruir(raiz->esq);
    raiz->dir = avlDestruir(raiz->dir);
    free(raiz);
    return NULL;
}