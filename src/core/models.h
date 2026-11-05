#include <stdbool.h>
#include "constants.h"
#include "data_structures/fila.h"
#include "data_structures/heap.h"
#include "data_structures/listaenc.h"
#include "data_structures/pilha.h"
#include "raylib.h"

/**
 * @brief Representação e categorização individual de cada alimento
 */
typedef struct {
    char alimento; /**< Caractere do alimento */
    bool preparo; /**<Queijos, Cebola, Tomate, Carne, Ovo, Bacon */
    bool perecivel; /**<carne, ovo frito, bacon - frituras */
 } Alimentos;

 /**
  * @brief Posicao discreta no mapa baseada em lihna e coluna
  */

 typedef struct {
    int linha; /**<Indice da linha no grid do mapa */
    int coluna; /**<Indice da coluna no grid do mapa */
 } TileAtual;

 /**
  * @brief Estado completo do cliente durante a partida
  */
 typedef struct{
    int pacienciaAtual; /**Paciencia maxima do cliente atual */
    Pedido pedido; /**<Codigo do pedido atual - à ser selecionado aleatoriamente entre os codigos dos produtos da AVL */
    Animacao animacao;/**<Animacao do cliente */
    Vector2 posicao; /**<Posicao em pixel do cliente */
    TileAtual tileAtual; /**<Tile ocupado pelo cliente */
    float velocidade; /**<Velocidade do cliente ao andar na fila */
    TileAtual tile_inicial; /**< Tile que o cliente vai spawnar */
    Pedido pedido_cliente;
 } Cliente;

 /**
  * @brief Representação do pedido de cada cliente
  */

 typedef struct {
    int cod; /**<Codigo da receita à ser preparada */
    ListaReceita receitaPedido; /**<Lista de ingredientes necessários - receita */
    PilhaHamburger pilhaHamburger; /**<Pilha para a montagem do hamburger */
    bool pedidoPronto; /**<Booleano para saber se o pedido está pronto */
 } Pedido;

/**
 * @brief Elementos necessários para realizar a animação das entidades
 */
 typedef struct  {
    int primeiro; /**<Primeiro frame */
    int ultimo; /**<Ultimo frame*/
    int atual; /**<Frame atual*/
    float velocidade; /**<Velocidade de mudança do frame */
    float duracaoRestante; /**<Duração restante do frame atual */
    TipoAnimacao tipo; /** <Ação e direção atual da animação */
    int passo; /**<Numero de frames que são pulados por iteração */
} Animacao;

/**
 * @brief Estado completo do jogo durante a partida
 */

typedef struct {
    DificuldadeJogo dificuldade; /**<Dificuldade do jogo selecionada */
    Jogador jogador; /**<Personagem do jogador */
    FilaClientes filaClientes; /**<Fila de clientes */
    int pontuacao; /**<Pontuacao obtida pelo jogador */
    TelaAtual telaAual; /**<Tela atual que o jogo está apresentando */
    bool jogando; /**<Booleano para saber se o usuario está em uma partida ou não */
    float tempo;
} Jogo;

/**
 * @brief Estado completo do jogador durante a partida 
 */

typedef struct {
    Vector2 posicao; /**<Posição atual do jogador em pixel */
    int turnoAtual; /**<Turno atual em que o jogo se encontra */
    HeapEstoque heapEstoque; /**<Estoque armazenado em Heap */
    float velocidade; /**<Velocidade do jogador */
    TileAtual tile_atual; /**<Tile ocupado pelo jogador */
    Animacao animacao; /**<Animacao do jogador */
    TileAtual tileInicial; /**<Tile que o jogador vai spawnar */
} Jogador;

/**
 * @brief Estado completo dos equipamentos de cozinha disponíveis para o uso do jogador
 */

typedef struct {
    MateriaisCozinha equipamentos; /**<ENUM que representa fogão, bancada e tábua */
    bool emUso; /**<Booleano para saber se o equipamento está em uso */
    float tempoPreparoRestante; /**<Tempo restante no preparo de algum alimento */
} EquipamentoCozinha;

/**
 * @brief Matriz de tiles do mapa
 */
typedef struct {
    char tiles[MAPA_LINHAS] [MAPA_COLUNAS];
} Mapa;
