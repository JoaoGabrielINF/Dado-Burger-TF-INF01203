#pragma once
#include <stdbool.h>
#include "constants.h"
#include "data_structures/fila_clientes.h"
#include "data_structures/heap_estoque.h"
#include "data_structures/lista_receita.h"
#include "data_structures/pilha_hamburger.h"
#include "raylib.h"

/**
 * @brief Estado completo do jogador durante a partida 
 */

typedef struct {
    Vector2 posicao; /**< Posição atual do jogador em pixel */
    HeapEstoque heapEstoque; /**< Estoque de perecíveis armazenado em Heap */
    float velocidade; /**< Velocidade do jogador */
    TileAtual tile_atual; /**< Tile ocupado pelo jogador */
    Animacao animacao; /**< Animacao do jogador */
    TileAtual tileInicial; /**< Tile que o jogador vai spawnar */
} Jogador;

 /**
 * @brief Estado completo do jogo durante a partida
 */

typedef struct {
    DificuldadeJogo dificuldade; /**< Dificuldade do jogo selecionada */
    Jogador jogador; /**< Personagem do jogador */
    int turnoAtual; /**< Turno atual em que o jogo se encontra */
    FilaClientes filaClientes; /**< Fila de clientes */
    int pontuacao; /**< Pontuacao obtida pelo jogador */
    TelaAtual telaAtual; /**< Tela atual que o jogo está apresentando */
    bool jogando; /**<B ooleano para saber se o usuario está em uma partida ou não */
    float tempo;
} Jogo;

/**
 * @brief Estado completo dos equipamentos de cozinha disponíveis para o uso do jogador
 */

typedef struct {
    MateriaisCozinha equipamentos; /**< ENUM que representa fogão, bancada e tábua */
    bool emUso; /**< Booleano para saber se o equipamento está em uso */
    float tempoPreparoRestante; /**< Tempo restante no preparo de algum alimento */
} EquipamentoCozinha;

/**
 * @brief Matriz de tiles do mapa
 */
typedef struct {
    char tiles[MAPA_LINHAS] [MAPA_COLUNAS]; /**< Matriz de tiles */
} Mapa;
