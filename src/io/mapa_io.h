#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "../core/constants.h"

/**
 * @brief Carrega o mapa de um arquivo para uma matriz de caracteres.
 * @param[in] caminho caminho do arquivo que contém o mapa
 * @param[out] mapa matriz que receberá os caracteres lidos
 * @return true se a leitura atingir MAPA_LINHAS quebras de linha ou se,
 *         sem quebra de linha final, a última linha tiver MAPA_COLUNAS caracteres
 * @return false se o arquivo não puder ser aberto ou se a leitura for insuficiente
 */
bool carregar_mapa(const char *caminho, char mapa[MAPA_LINHAS][MAPA_COLUNAS]);