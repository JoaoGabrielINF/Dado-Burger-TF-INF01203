#pragma once
#include <stdio.h>
#include <stdbool.h>


/**
 * @brief Lê o arquivo de histórico converte pra lista contígua.
 * @param[in] fp arquivo já aberto em modo r (o fopen(argv[2], "r") da main).
 * @return quantidade de registros lidos com sucesso, ou -1 se fp for NULL.
 */
int ler_historico(FILE *fp);

/**
 * @brief Acrescenta uma partida encerrada no fim do arquivo de histórico.
 * @param[in] caminho caminho do arquivo de histórico (o argv[2] do main).
 * @param[in] nome nome do jogador (até 20 caracteres).
 * @param[in] pontuação pontuação da partida (nº de clientes atendidos).
 * @return true se o registro foi gravado.
 * @return false se de erro.
 */
bool salvar_partida_historico(const char *caminho, const char *nome, int pontuacao);
