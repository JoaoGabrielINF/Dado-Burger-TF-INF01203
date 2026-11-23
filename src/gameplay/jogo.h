#pragma once
#include "../core/models.h"
#include <stdlib.h>
#include <time.h>
#include "../presentation/animacao.h"
#include "../core/dados.h"
#include "metricas.h"

void inicializa_clientes(Jogo *jogo);

void inicializa_jogo(Jogo *jogo);

/**
 * @brief Função que inicializa pedido do cliente, faz a busca na hash, na AVL e inicia paciência do cliente
 * @param jogo estado atual do jogo
 */
void inicializa_pedido_cliente(Jogo *jogo);

/**
 * @brief Dinamica de montagem do hamburger no jogo 
 * @param [in, out] jogo atual do jogo para fazer modificações na pilha do pedido
 */
void monta_hamburger(Jogo* jogo);

/**
 * @brief Função responsável pelo controle de tempo de preparo e alocação de alimentos no estoque na confecção das comidas
 * @param jogo estado atual do jogo para fazer modificações na pilha do pedido
 */
void prepara_ingredientes(Jogo* jogo);

/**
 * @brief Função responsável pelo gerenciamento de turnos do jogo
 * @param jogo Estado atual do jogo para fazer o gerenciamento de turnos
 */
void gerencia_turnos(Jogo* jogo);

/**
 * @brief Função responsável pelo gerenciamento de paciência dos clientes
 * @param jogo  Estado atual do jogo para fazer o gerenciamento de paciência
 */
void gerencia_paciencia(Jogo* jogo);


/**
 * @brief Verifica se um item chegou na validade. Se sim, retira ele to estoque
 * @param jogo Estaod atual do jogo para modificar a heap
 */
void gerencia_estoque_pereciveis(Jogo* jogo);