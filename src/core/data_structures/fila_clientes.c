#include "fila_clientes.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaFila(FilaClientes *f) {
    f->frente = NULL;
    f->final = NULL;
}

bool estaVaziaFila(const FilaClientes *f) {
    return f->frente == NULL;
}

bool enqueueFila(FilaClientes *f, const Cliente *cliente) {
    NodoFila *novo = (NodoFila*) malloc(sizeof(NodoFila));
    if (novo == NULL)
        return false;

    novo->cliente = *cliente;
    novo->prox = NULL;

    if (f->final != NULL)
        f->final->prox = novo; // o antigo final passa a apontar para o novo NodoFila
    else
        f->frente = novo;      // fila estava vazia: novo NodoFila também é a frente

    f->final = novo;
    return true;
}

bool dequeueFila(FilaClientes *f, Cliente *cliente) {
    NodoFila *removido;

    if (estaVaziaFila(f)) // underflow
        return false;

    removido = f->frente;
    *cliente = removido->cliente;
    f->frente = removido->prox;

    if (f->frente == NULL) // a fila ficou vazia
        f->final = NULL;

    free(removido);
    return true;
}

bool frenteFila(const FilaClientes *f, Cliente *cliente) {
    if (estaVaziaFila(f))
        return false;

    *cliente = f->frente->cliente; // copia o Cliente do primeiro NodoFila sem removê-lo
    return true;
}

int tamanhoFila(const FilaClientes *f) {
    NodoFila *aux = f->frente;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void esvaziaFila(FilaClientes *f){
    NodoFila *aux = f->frente;
    NodoFila *ant;
    for(int i = 0; i < MAX_CLIENTES_FILA; i++){
        ant = aux;
        aux = aux->prox;
        free(ant);
    }
    f->frente = NULL;
    f->final = NULL;
}