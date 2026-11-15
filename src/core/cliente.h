#include "data_structures/lista_receita.h"
#include "data_structures/pilha_hamburger.h"
#include "entidade.h"
#include "raylib.h"
/**
  * @brief Representação do pedido de cada cliente
  */

typedef struct {
    int cod; /**< Codigo da receita à ser preparada */
    ListaReceita receitaPedido; /**< Lista de ingredientes necessários - receita */
    PilhaHamburger pilhaHamburger; /**< Pilha para a montagem do hamburger */
    bool pedidoPronto; /**< Booleano para saber se o pedido está pronto */
 } Pedido;

 /**
  * @brief Estado completo do cliente durante a partida
  */

 typedef struct{
    int pacienciaAtual; /**< Paciência maxima do cliente atual */
    Pedido pedido; /**< Codigo do pedido atual - à ser selecionado aleatoriamente entre os codigos dos char*s da AVL */
    Animacao animacao;/**< Animacao do cliente */
    Vector2 posicao; /**< Posicao em pixel do cliente */
    TileAtual tileAtual; /**< Tile ocupado pelo cliente */
    float velocidade; /**< Velocidade do cliente ao andar na fila */
    TileAtual tile_inicial; /**< Tile que o cliente vai spawnar */
 } Cliente;