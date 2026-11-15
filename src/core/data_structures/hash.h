#pragma once
#define TAM_HASH 51 /*Para uma chance de colisão  de 50%, para fins didáticos, adotaremos o numero primo seguinte ao quadrado do numero de clientes por partida para tamanho da tabela hash*/
#include <stdbool.h>
#include "cliente.h"

// Pelo mesmo motivo didático, será usado o hash por divisão, garantindo uma chance um pouco maior que as outras funções de ocorrência de colisões.
// Adotaremos o tratamento de colisões com o encadeamento separado (chaining)

typedef struct NoHash {
    int chave; /**< */
    int valor; /**< */
    struct NoHash *prox; /**< */
} NoHash;

typedef struct {
    NoHash **tabela;   /**< */
    int m;         /** */ 
    int n;         /**< */
} TabelaHash;

/**
 * @brief Inicializa a tabela hash com o tamanho TAM_HASH
 * @param t ponteiro para a tabela hash
 */
void inicializarHash(TabelaHash *t);

/**
 * @brief Inserir um nó na tabela hash
 * @param t ponteiro para a tabela hash
 * @param chave parâmetro da função hash
 * @param valor valor do nó a ser inserido
 */
void inserirHash(TabelaHash *t, int chave, int valor); 

/**
 * @brief Busca  
 * @param t 
 * @param chave 
 * @return int 
 */
int buscarHash(TabelaHash *t, int chave);


bool removerHash(TabelaHash *t, int chave);