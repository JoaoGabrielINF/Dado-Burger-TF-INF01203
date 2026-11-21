#pragma once 
#include <stdio.h>
#include "../core/models.h"

/**
 * @brief Identifica e inicializa as entidades descritas no mapa.
 * @param[in] mapa Matriz de caracteres do mapa
 * @param[in,out] jogo Estado do jogo que receberá as posições das entidades
 */
void carrega_estruturas_mapa(const char mapa[][MAPA_COLUNAS], Jogo *jogo);