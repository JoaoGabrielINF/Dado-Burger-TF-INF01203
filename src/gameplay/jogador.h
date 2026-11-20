#pragma once
#include "../core/models.h"

/**
 * @brief Recalcula a hitbox do jogador para encaixar no desenho do personagem
 * @param[in,out] jogador Jogador cuja hitbox será atualizada
 */
void atualiza_hitbox_jogador(Jogador *jogador);

/**
 * @brief Movimenta o jogador conforme WASD, impedindo que a hitbox atravesse
 *        os tiles bloqueados ('#') do mapa
 * @param[in,out] jogo Estado do jogo contendo o jogador e o mapa
 */
void atualiza_jogador(Jogo *jogo);
