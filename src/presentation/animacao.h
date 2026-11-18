#pragma once
#include "raylib.h"
#include "../core/models.h"

/**
 * @brief Avança a animação e reinicia no primeiro frame ao alcançar o último
 * @param[in,out] animacao Dados da animação
 */
void atualiza_animacao(Animacao *animacao);

/**
 * @brief Reinicia os valores padrão de uma animação para o estado inicial
 * @param[in,out] animacao Animação que será reinicializada
 */
void animacao_inicializar(Animacao *animacao);

/**
 * @brief Atualiza as animações do jogador e dos clientes do jogo
 * @param[in,out] jogo Estado principal do jogo
 */
void atualiza_anim_entidades(Jogo *jogo);

/**
 * @brief Seleciona o retângulo de corte do frame atual no sprite sheet
 * @param[in] animacao Dados da animação
 * @param[in] largura_frame Largura de cada frame em pixels
 * @param[in] altura_frame Altura de cada frame em pixels
 * @param[in] frames_por_linha Quantidade de frames por linha no sprite sheet
 * @return Retângulo de corte no sprite sheet
 */
Rectangle tamanho_frames(const Animacao *animacao, int largura_frame,
                         int altura_frame, int frames_por_linha);
