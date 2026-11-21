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
    HeapEstoque heap_estoque; /**< Estoque de perecíveis armazenado em heap */
    float velocidade; /**< Velocidade do jogador */
    TileAtual tile_atual; /**< Tile ocupado pelo jogador */
    Animacao animacao; /**< Animacao do jogador */
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
    
    bool em_uso; /**< Indica se o equipamento está em uso */
    float tempo_preparo_restante; /**< Tempo restante no preparo de um alimento */
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
    Cliente cliente; /**< Cliente atendido atualmente */
    EquipamentoCozinha equipamentos[NUMERO_EQUIPAMENTOS - 1]; /**< Equipamentos da cozinha */
    int turno_atual; /**< Turno atual em que o jogo se encontra */
    FilaClientes fila_clientes; /**< Fila de clientes */
    int pontuacao; /**< Pontuacao obtida pelo jogador */
    TelaAtual tela_atual; /**< Tela atual que o jogo está apresentando */
    bool jogando; /**< Indica se uma partida está em andamento */
    float tempo; /**< Tempo decorrido na partida */
    Mapa mapa[NUMERO_MAPAS]; /**< Mapas da partida: recepcao e cozinha */
} Jogo;
