#pragma once

#include "data_structures/lista_receita.h"
#include "data_structures/pilha_hamburger.h"
#include "entidade.h"
#include "raylib.h"

 /**
  * @brief Estado completo de um cliente genérico durante a partida
  */

 typedef struct{
    int paciencia_atual; /**< Paciência restante do cliente */
    int codigo_pedido; /**< Pedido atual do cliente */
    Animacao animacao; /**< Animação do cliente */
    Vector2 posicao; /**< Posição do cliente em pixels */
    TileAtual tile_atual; /**< Tile ocupado pelo cliente */
    TileAtual tile_inicial; /**< Tile inicial do cliente */
    int textura_atual; /**< Índice da textura atual do cliente */
 } Cliente;