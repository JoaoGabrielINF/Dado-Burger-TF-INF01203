#pragma once
#include <stdbool.h>
#include "constants.h"
#include "data_structures/fila_clientes.h"
#include "data_structures/heap_estoque.h"
#include "data_structures/lista_receita.h"
#include "data_structures/pilha_hamburger.h"
#include "data_structures/hash.h"
#include "raylib.h"

/**
  * @brief Representação do pedido de cada cliente
  */

typedef struct {
    int cod; /**< Código da receita a ser preparada */
    ListaReceita receita_pedido; /**< Ingredientes necessários para a receita */
    PilhaHamburger pilha_hamburger; /**< Ingredientes montados para o hambúrguer */
    bool pedido_pronto; /**< Indica se o pedido está pronto */
    bool pedido_entregue; /**< Indica se o pedido foi entregue */
    char adicionar_pilha; /**< Caractere à ser adicionado na pilha */
    OpcoesPilha opcao; /**< Verifica se o jogador quer adicionar ou remover item da pilha, true se adiciona, false se remove */
    int quantidade_ingredientes_adicionados;/**< Numero de ingredientes adicionados na pilha */
    
 } Pedido;

 /**
 * @brief Estoque de alimentos perenes
 */

typedef struct {
    char alimento; /**< Simbolo do alimento do estoque */
    int quantidade; /**< Quantidade do alimento do simbolo */
} EstoquePerenes;

 /**
 * @brief Estado completo do jogador durante a partida 
 */

typedef struct {
    Vector2 posicao; /**< Posição atual do jogador em pixel */
    HeapEstoque heap_estoque[QUANTIDADE_ALIMENTOS_PERECIVEIS]; /**< Estoque de perecíveis armazenado em heap */
    EstoquePerenes estoque_perenes[MAXIMO_PERENES];
    float velocidade; /**< Velocidade do jogador */
    TileAtual tile_atual; /**< Tile ocupado pelo jogador */
    Pedido pedido_atual; /**< Pedido feito pelo cliente */
    Animacao animacao; /**< Animacao do jogador */
    TabelaHash hash; /**< Tabela hash dos pedidos já realizados */
    TileAtual tile_inicial; /**< Tile que o jogador vai spawnar */
    Rectangle hitbox; /**< Hitbox do jogador utilizada para teste de colisões */
    bool andando; /**< Indica se o jogador está se movendo */
} Jogador;


/**
 * @brief Estado completo dos equipamentos de cozinha disponíveis para o uso do jogador
 */

typedef struct {
    MateriaisCozinha materiais; /**< Tipo do equipamento */
    Vector2 posicao_pixels; /**< Posição do equipamento em pixels */
    TileAtual tile_atual; /**< Posição do equipamento no mapa */
    Rectangle hitbox;
    char alimento_preparado;
    bool em_uso; /**< Indica se o equipamento está em uso */
    bool foi_utilizado; /**< Indica se o equipamento foi utilizado uma vez */
    int turno_pronto; /**< Tempo restante no preparo de um alimento */
} EquipamentoCozinha;

/**
 * @brief Matriz de tiles do mapa
 */
typedef struct {
    char tiles[MAPA_LINHAS][MAPA_COLUNAS]; /**< Matriz de caracteres do mapa */
} Mapa;

 /**
 * @brief Estado completo do jogo durante a partida
 */

typedef struct {
    DificuldadeJogo dificuldade; /**< Dificuldade do jogo selecionada */
    Jogador jogador; /**< Personagem do jogador */
    EquipamentoCozinha equipamentos[NUMERO_EQUIPAMENTOS]; /**< Equipamentos da cozinha */
    int turno_atual; /**< Turno atual em que o jogo se encontra */
    bool aumentou_turno; /**< Indica se o turno aumentou */
    FilaClientes fila_clientes; /**< Fila de clientes */
    int pontuacao; /**< Pontuacao obtida pelo jogador - numero de clientes atendidos até o momento */
    TelaAtual tela_atual; /**< Tela atual que o jogo está apresentando */
    bool jogando; /**< Indica se uma partida está em andamento */
    float tempo; /**< Tempo decorrido na partida */
    Mapa mapa[NUMERO_MAPAS]; /**< Mapas da partida: recepcao e cozinha */
    bool proximo_cliente; /**< Indica se é para a fila andar/viro proximo cliente */
} Jogo;
