#pragma once
#include "../models.h"

typedef struct str_Nodo Nodo;

/**
 * @brief Representação de um nodo da lista, contem um ponteiro para o proximo nodo e um ingrediente
 */
struct str_Nodo {
    Nodo *prox;
    char ingrediente;
};

/**
 * @brief Representação da lista, contem o ponteiro para o primeiro elemento da lista
 * 
 */
typedef struct {
    Nodo *ini;
} ListaReceita;