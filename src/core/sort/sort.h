#pragma once
#include "../data_structures/lista_contigua_historico.h"
/**
 * @brief Função auxiliar que ordena o histórico por pontuação, usada pelo mergeSortRec
 * @param a lista dos registros do histórico a serem ordenados
 * @param aux lista auxiliar para receber cópia dos dados de a
 * @param ini índice de início pro mergesort
 * @param meio índice de meio pro mergesort
 * @param fim índice de fim pro mergesort
 */
void merge(RegistroHistorico a[], RegistroHistorico aux[], int ini, int meio, int fim);

/**
 * @brief Função auxiliar recursiva que ordena o histórico por pontuação, usada pelo mergeSortPontuacao
 * @param a lista dos registros do histórico a serem ordenados
 * @param aux lista auxiliar para receber cópia dos dados de a
 * @param ini índice de início pro mergesort
 * @param fim índice de fim pro mergesort
 */
void mergeSortRec(RegistroHistorico a[], RegistroHistorico aux[], int ini, int fim);

/**
 * @brief Função auxiliar recursiva que ordena o histórico por pontuação, usada pelo mergeSortPontuacao
 * @param a lista de registros de histórico a ser ordenada por pontuação
 * @param n tamanho da lista
 */
void mergeSortPontuacao(RegistroHistorico a[], int n);

/**
 * @brief Função auxiliar recursiva que ordena o histórico por ordem alfabética, usada pelo mergeSortAlfabetico
 * @param a lista dos registros do histórico a serem ordenados
 * @param aux lista auxiliar para receber cópia dos dados de a
 * @param ini índice de início pro mergesort
 * @param fim índice de fim pro mergesort
 */
void mergeAlfabetico(RegistroHistorico a[], RegistroHistorico aux[], int ini, int meio, int fim);

/**
 * @brief Função auxiliar recursiva que ordena o histórico por ordem alfabética, usada pelo mergeSortAlfabetico
 * @param a lista dos registros do histórico a serem ordenados
 * @param aux lista auxiliar para receber cópia dos dados de a
 * @param ini índice de início pro mergesort
 * @param fim índice de fim pro mergesort
 */
void mergeSortRecAlfabetico(RegistroHistorico a[], RegistroHistorico aux[], int ini, int fim);

/**
 * @brief Função auxiliar recursiva que ordena o histórico por ordem alfabética, usada pelo mergeSortAlfabetico
 * @param a lista de registros de histórico a ser ordenada por pontuação
 * @param n tamanho da lista
 */
void mergeSortAlfabetico(RegistroHistorico a[], int n);


/**
 * @brief Retorna uma nova lista contendo os registros ordenados, sem modificar a original.
 * @param[in] historico Ponteiro para a lista original (somente leitura).
 * @param[in] isPontuacao true para ordenar por pontuação (decrescente); false para ordem alfabética.
 * @return Uma nova ListaContHistorico alocada independentemente e já ordenada.
 */
ListaContHistorico ordenaHistorico(const ListaContHistorico *historico, bool isPontuacao);
