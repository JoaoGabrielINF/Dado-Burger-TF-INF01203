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