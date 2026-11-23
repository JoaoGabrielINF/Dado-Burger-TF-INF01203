#pragma once
#include "../core/models.h"
#include <stdlib.h>
#include <time.h>
#include "../presentation/animacao.h"
#include "../core/dados.h"
#include "../core/time/time.h"
#include "metricas.h"

/**
 * @brief Inicializa os clientes padrão da fila.
 * @param[in,out] jogo Estado do jogo cuja fila será preenchida.
 */
void inicializa_clientes(Jogo *jogo);

/**
 * @brief Inicializa os valores padrão de uma partida.
 * @param[in,out] jogo Estado do jogo a inicializar.
 */
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
 * @param jogo Estado atual do jogo para fazer o gerenciamento de paciência
 */
void gerencia_paciencia(Jogo* jogo);


/**
 * @brief Verifica se um item chegou na validade. Se sim, retira ele to estoque
 * @param jogo Estado atual do jogo para modificar a heap
 */
void gerencia_estoque_pereciveis(Jogo* jogo);


/**
 * @brief Reinicia o jogo após uma partida se encerrar
 * @param jogo estado atual do jogo
 */
 
void reinicia_jogo(Jogo *jogo);

/**
 * @brief Une todas as funções anteriores envolvendo gerenciamento de comida e paciência em uma função
 * @param jogo Estado atual do jogo para aplicar de argumento nas funções
 */
void atualiza_jogo(Jogo* jogo);

/**
 * @brief Compara os ingredientes da pilha de hamburger e da lista de receita
 * @param pilha ponteiro para a pilha de hamburger
 * @param lista ponteiro para a lista de receita
 */
void compara_lista_e_pilha(PilhaHamburger *pilha, const ListaReceita *lista);