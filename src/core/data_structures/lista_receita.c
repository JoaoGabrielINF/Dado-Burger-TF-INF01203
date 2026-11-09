#include "lista_receita.h"
#include <stdio.h>

void inicializarLista(ListaReceita *lista) {
    lista->ini = NULL;
}

void imprimirLista(const ListaReceita *lista) {
    NodoLista *aux;
    aux = lista->ini;

    while (aux != NULL) {
        printf("[%c]", aux->ingrediente);
        aux = aux->prox;
    }
}


bool buscarLista(const ListaReceita *lista, char ingrediente) {
    NodoLista *aux;
    aux = lista->ini;

    while (aux != NULL) {
        if (aux->ingrediente == ingrediente)
            return true;
    }

    return false; // ingrediente não encontrado
}

bool inserirInicioLista(ListaReceita *lista, char ingrediente) {
    NodoLista *novo = (NodoLista*) malloc(sizeof(NodoLista));
    if (novo == NULL)
        return false; // falha na alocação

    novo->ingrediente = ingrediente;
    novo->prox = lista->ini; // o novo NodoLista aponta para o antigo início
    lista->ini = novo;        // o novo NodoLista passa a ser o início

    return true;
}

bool inserirFimLista(ListaReceita *lista, char ingrediente) {
    NodoLista *novo;
    NodoLista *aux;

    novo = (NodoLista*) malloc(sizeof(NodoLista));
    if (novo == NULL)
        return false;

    novo->ingrediente = ingrediente;
    novo->prox = NULL;

    if (lista->ini == NULL) { // lista vazia: o novo NodoLista é o único (e o início)
        lista->ini = novo;
    } else {
        aux = lista->ini;
        while (aux->prox != NULL) // percorre até o último NodoLista
            aux = aux->prox;
        aux->prox = novo;
    }

    return true;
}

bool removerPorCharLista(ListaReceita *lista, char ingrediente) {
    NodoLista *ant;
    NodoLista *aux;

    ant = NULL;
    aux = lista->ini;

    while (aux != NULL && aux->ingrediente != ingrediente) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) // não encontrado
        return false;

    if (ant == NULL) // removendo o primeiro NodoLista
        lista->ini = aux->prox;
    else             // removendo do meio ou do final
        ant->prox = aux->prox;

    free(aux);
    return true;
}

void destruirLista(ListaReceita *lista) {
    NodoLista *ant;
    NodoLista *aux;
    aux = lista->ini;

    while (aux != NULL) {
        ant = aux;
        aux = aux->prox;
        free(ant);
    }

    lista->ini = NULL;
}

int tamanhoLista(const ListaReceita *lista) {
    NodoLista *aux = lista->ini;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}