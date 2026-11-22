#pragma once
#include "data_structures/lista_receita.h"
#include "data_structures/pilha_hamburger.h"
#include "entidade.h"
#include "raylib.h"
/**
  * @brief Representação do pedido de cada cliente
  */

typedef struct {
    int cod; /**< Código da receita a ser preparada */
    ListaReceita receita_pedido; /**< Ingredientes necessários para a receita */
    PilhaHamburger pilha_hamburger; /**< Ingredientes montados para o hambúrguer */
    bool pedido_pronto; /**< Indica se o pedido está pronto */
 } Pedido;

 /**
  * @brief Estado completo de um cliente genérico durante a partida
  */

 typedef struct{
    int paciencia_atual; /**< Paciência restante do cliente */
    Pedido pedido; /**< Pedido atual do cliente */
    Animacao animacao; /**< Animação do cliente */
    Vector2 posicao; /**< Posição do cliente em pixels */
    TileAtual tile_atual; /**< Tile ocupado pelo cliente */
    float velocidade; /**< Velocidade de movimento do cliente na fila */
    TileAtual tile_inicial; /**< Tile inicial do cliente */
    int textura_atual; /**< Índice da textura atual do cliente */
 } Cliente;