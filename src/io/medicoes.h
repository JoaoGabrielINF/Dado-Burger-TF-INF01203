#pragma once
#include <stdio.h>

/**
 * @brief Sobrescreve o arquivo de log.
 * @param[in] caminho caminho do log (usar "medicoes.log")
 */
void medicoes_reiniciar(const char *caminho);

/**
 * @brief Grava as métricas do momento 1 (5.1 no PDF da atv): depois do carregamento, antes de exibir o menu.
 * @param[in] destino arquivo já aberto (log em "a" ou stdout)
 */
void medicoes_gravar_pos_carregamento(FILE *destino);

/**
 * @brief Grava o Relatório de Desempenho COMPLETO no momento 2 (5.2 no PDF da atv), ao encerrar a partida (vitória, derrota ou saída voluntária).
 * @param[in] destino arquivo já aberto (log em "a" ou stdout)
 */
void medicoes_gravar_relatorio_completo(FILE *destino);

/**
 * @brief Grava a seção de ordenação do histórico (5.2.3 no PDF da atv). Chamada a cada acesso ao Histórico.
 * @param[in] destino arquivo já aberto (log em "a" ou stdout)
 */
void medicoes_gravar_ordenacao(FILE *destino);
