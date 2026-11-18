#pragma once
/** Tamanho da tabela hash usada pelo projeto */
#define TAM_HASH 51
#include <stdbool.h>
#include "cliente.h"

// Pelo mesmo motivo didático, será usado o hash por divisão, garantindo uma chance um pouco maior que as outras funções de ocorrência de colisões.
// Adotaremos o tratamento de colisões com o encadeamento separado (chaining)

typedef struct NoHash {
    int chave; /**< Chave usada para localizar o nó */
    int valor; /**< Valor armazenado no nó */
    struct NoHash *prox; /**< Próximo nó da cadeia de colisões */
} NoHash;

/**
 * @brief Tabela hash com tratamento de colisões por encadeamento separado.
 */
typedef struct {
    NoHash **tabela; /**< Vetor de listas de colisões */
    int m; /**< Capacidade da tabela */
    int n; /**< Quantidade de elementos armazenados */
} TabelaHash;

/**
 * @brief Inicializa a tabela hash com o tamanho TAM_HASH
 * @param[out] t Ponteiro para a tabela que será inicializada
 */
void inicializarHash(TabelaHash *t);

/**
 * @brief Insere um par chave-valor na tabela hash.
 * @param[in,out] t Tabela hash que receberá o elemento
 * @param[in] chave Chave do elemento
 * @param[in] valor Valor associado à chave
 */
void inserirHash(TabelaHash *t, int chave, int valor); 

/**
 * @brief Busca o valor associado a uma chave.
 * @param[in] t Tabela hash consultada
 * @param[in] chave Chave procurada
 * @return Valor associado à chave, ou 0 se ela não for encontrada
 */
int buscarHash(TabelaHash *t, int chave);

/**
 * @brief Remove da tabela hash o elemento associado à chave.
 * @param[in,out] t Tabela hash a ser atualizada
 * @param[in] chave Chave do elemento a remover
 * @return true se o elemento foi removido
 * @return false se a chave não estiver na tabela
 */
bool removerHash(TabelaHash *t, int chave);