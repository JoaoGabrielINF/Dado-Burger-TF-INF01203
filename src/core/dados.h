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

/**
 * @brief Inicializa as 3 variáveis da AVL de pedidos, histórico de partidas e cache de pedidos.
 */
void dados_inicializar(void);
