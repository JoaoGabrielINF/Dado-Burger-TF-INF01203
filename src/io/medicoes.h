#pragma once
#include <stdio.h>

/* Limites da versão em linhas do relatório (para exibição na tela). */
#define MEDICOES_MAX_LINHAS 48
#define MEDICOES_TAM_ROTULO 40
#define MEDICOES_TAM_VALOR 56

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

/**
 * @brief Grava o Relatório de Desempenho completo direto no arquivo de log
 *        (abre em modo "a", grava e fecha). Conveniência para o fim da
 *        partida (5.2: vitória, derrota ou saída voluntária).
 * @param[in] caminho caminho do log (usar "medicoes.log")
 */
void medicoes_gravar_relatorio_em_arquivo(const char *caminho);

/**
 * @brief Monta o Relatório de Desempenho (mesmo conteúdo gravado no log)
 *        em pares rótulo/valor para EXIBIÇÃO NA TELA (5.2: "tanto na tela
 *        quanto gravado em arquivo"). Linhas de seção vêm com valor "".
 * @param[out] rotulos matriz de rótulos (linhas de MEDICOES_TAM_ROTULO chars)
 * @param[out] valores matriz de valores (linhas de MEDICOES_TAM_VALOR chars)
 * @param[in] max capacidade das matrizes (usar MEDICOES_MAX_LINHAS)
 * @return quantidade de linhas preenchidas (<= max)
 */
int medicoes_obter_relatorio(char rotulos[][MEDICOES_TAM_ROTULO],
                             char valores[][MEDICOES_TAM_VALOR], int max);
