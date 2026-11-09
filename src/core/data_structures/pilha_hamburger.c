#include "pilha_hamburger.h"
#include <stdio.h>

void inicializaPilha(PilhaHamburger *p) {
    p->topo = NULL;
}

bool estaVaziaPilha(const PilhaHamburger *p) {
    return p->topo == NULL;
}

bool pushPilha(PilhaHamburger *p, char ingrediente) {
    NodoPilha *novo = (NodoPilha*) malloc(sizeof(NodoPilha));
    if (novo == NULL)
        return false;

    novo->ingrediente = ingrediente;
    novo->prox = p->topo; // aponta para o antigo topo
    p->topo = novo;        // o novo NodoPilha passa a ser o topo
    return true;
}

bool popPilha(PilhaHamburger *p, char* ingredienteRemovido) {
    NodoPilha *removido;

    if (estaVazia(p)) // underflow
        return false;

    removido = p->topo;
    *ingredienteRemovido = removido->ingrediente;
    p->topo = removido->prox;
    free(removido);
    return true;
}

bool topoPilha(const PilhaHamburger *p, char* ingrediente) {
    if (estaVazia(p))
        return false;

    *ingrediente = p->topo->ingrediente;
    return true;
}

int tamanhoPilha(const PilhaHamburger *p) {
    NodoPilha *aux = p->topo;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}