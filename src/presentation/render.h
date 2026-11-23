#pragma once
#include "../core/models.h"
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include "animacao.h"
#include <string.h>

/**
 * @brief Desenha um texto centralizado dentro de um retângulo.
 * @param[in] fonte Fonte usada para desenhar o texto
 * @param[in] texto Texto a ser desenhado
 * @param[in] ret Retângulo que delimita a área do texto
 * @param[in] tamanho Tamanho da fonte
 * @param[in] espaco Espaçamento entre caracteres
 * @param[in] cor Cor do texto
 */
void desenhaTextoCentralizado(Font fonte, const char *texto, Rectangle ret, float tamanho, float espaco, Color cor);

/**
 * @brief Verifica se o cursor está dentro de um retângulo e o destaca.
 * @param[in] rec Retângulo a verificar
 * @param[in] pos_mouse Posição atual do cursor
 * @return true se o cursor estiver dentro do retângulo
 * @return false caso contrário
 */
bool coloreSeColide(Rectangle rec, Vector2 pos_mouse);

/**
 * @brief Atualiza a direção do jogador com base nas teclas pressionadas.
 * @param[in,out] jogador Jogador cuja direção será atualizada
 */
void determinaDirecao(Jogador *jogador);

/**
 * @brief Desenha o jogador com o frame correspondente à direção e ao movimento.
 * @param[in,out] jogador Jogador a desenhar e atualizar
 */
void desenhaJogador(Jogador *jogador);

/**
 * @brief Funcao que desenha os equipamentos utilizados na cozinha (fogao, tabua e bancada)
 * @param equipamentos lista de equipamentos
 */
void desenhaEquipamentos(const Jogo* jogo);

/**
 * @brief Desenha até MAX_CLIENTES_VISIVEIS clientes da fila na tela do saguão.
 * @param[in] fila Fila de clientes a desenhar
 */
void desenha_fila(const FilaClientes *fila);

/**
 * @brief Desenha a barra vertical de paciência do cliente que está na frente da fila.
 * @param[in] jogo Estado do jogo que contém o cliente atual e a dificuldade.
 */
void desenha_paciencia_cliente(const Jogo *jogo);

/**
 * @brief Move cada cliente um tile em direção à posição do cliente removido.
 * @param[in,out] jogo Estado do jogo cuja fila será avançada.
 */
void anda_fila(Jogo *jogo);

/**
 * @brief Desenha a comanda com os ingredientes de uma receita.
 * @param[in] receita Lista de ingredientes a apresentar
 */
void desenhaComanda(const ListaReceita *receita);

/**
 * @brief Desenha os ícones, nomes, quantidades e controles de paginação do estoque.
 *
 * Cada alimento é apresentado em um retângulo branco com ícone sobre fundo cinza,
 * nome e campo de quantidade. A primeira página exibe sete alimentos e a segunda
 * os cinco restantes; as setas da barra lateral alternam entre as páginas.
 *
 * @param[in] retangulo_estoque Retângulo que delimita o painel do estoque.
 * @param[in] jogo estado atual do jogo para saber numero de alimentos.
 */
void desenha_alimentos_no_estoque(Rectangle retangulo_estoque, const Jogo *jogo);

/**
 * @brief Desenha o contorno vermelho do painel de estoque na cozinha.
 * O painel ocupa um quarto da largura da janela, fica alinhado à direita e
 * estende-se do topo da janela até um pouco acima do cartão da mochila.
 * @param[in] jogo estado atual do jogo para saber numero de alimentos.
 */
void desenha_estoque(const Jogo* jogo);

/**
 * @brief Desenha os elementos da tela atual do jogo.
 * @param[in,out] jogo Estado do jogo a desenhar
 */
void desenhaJogo(Jogo *jogo);

/**
 * @brief Libera as texturas carregadas pela apresentação.
 */
void descarregaAssets(void);

/**
 * @brief Carrega as texturas e a fonte usadas pela apresentação.
 */
void carregaAssets(void);