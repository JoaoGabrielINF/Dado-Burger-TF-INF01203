#pragma once
#include "data_structures/avl.h"
#include "data_structures/lista_contigua_historico.h"
#include "data_structures/hash.h"

// Raiz da AVL de pedidos.
extern NodoAvl *pedidos_avl;

// Histórico de partidas (lista contígua).
extern ListaContHistorico historico_partidas;

// Cache de pedidos indexado por código (4.3 no PDF da atv). durante a partida, entra no fluxo sorteio -> hash -> miss -> AVL.
extern TabelaHash cache_pedidos;

extern int maior_codigo_avl;

/**
 * @brief Inicializa as estruturas globais e zera o maior código de pedido da AVL.
 */
void dados_inicializar(void);
