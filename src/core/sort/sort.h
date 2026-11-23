#pragma once
#include "../data_structures/lista_contigua_historico.h"
/**
 * @brief Função auxiliar que ordena o histórico por pontuação, usada pelo merge_sort_rec
 * @param a lista dos registros do histórico a serem ordenados
 * @param aux lista auxiliar para receber cópia dos dados de a
 * @param ini índice de início pro mergesort
 * @param meio índice de meio pro mergesort
 * @param fim índice de fim pro mergesort
 */
void merge(RegistroHistorico a[], RegistroHistorico aux[], int ini, int meio, int fim);

/**
 * @brief Função auxiliar recursiva que ordena o histórico por pontuação, usada pelo merge_sort_pontuacao
 * @param a lista dos registros do histórico a serem ordenados
 * @param aux lista auxiliar para receber cópia dos dados de a
 * @param ini índice de início pro mergesort
 * @param fim índice de fim pro mergesort
 */
void merge_sort_rec(RegistroHistorico a[], RegistroHistorico aux[], int ini, int fim);

/**
 * @brief Função auxiliar recursiva que ordena o histórico por pontuação, usada pelo merge_sort_pontuacao
 * @param a lista de registros de histórico a ser ordenada por pontuação
 * @param n tamanho da lista
 */
void merge_sort_pontuacao(RegistroHistorico a[], int n);

/**
 * @brief Função auxiliar recursiva que ordena o histórico por ordem alfabética, usada pelo merge_sort_alfabetico
 * @param a lista dos registros do histórico a serem ordenados
 * @param aux lista auxiliar para receber cópia dos dados de a
 * @param ini índice de início pro mergesort
 * @param fim índice de fim pro mergesort
 */
void merge_alfabetico(RegistroHistorico a[], RegistroHistorico aux[], int ini, int meio, int fim);

/**
 * @brief Função auxiliar recursiva que ordena o histórico por ordem alfabética, usada pelo merge_sort_alfabetico
 * @param a lista dos registros do histórico a serem ordenados
 * @param aux lista auxiliar para receber cópia dos dados de a
 * @param ini índice de início pro mergesort
 * @param fim índice de fim pro mergesort
 */
void merge_sort_rec_alfabetico(RegistroHistorico a[], RegistroHistorico aux[], int ini, int fim);

/**
 * @brief Função auxiliar recursiva que ordena o histórico por ordem alfabética, usada pelo merge_sort_alfabetico
 * @param a lista de registros de histórico a ser ordenada por pontuação
 * @param n tamanho da lista
 */
void merge_sort_alfabetico(RegistroHistorico a[], int n);


/**
 * @brief Retorna uma nova lista contendo os registros ordenados, sem modificar a original.
 * @param[in] historico Ponteiro para a lista original (somente leitura).
 * @param[in] is_pontuacao true para ordenar por pontuação (decrescente); false para ordem alfabética.
 * @return Uma nova ListaContHistorico alocada independentemente e já ordenada.
 */
ListaContHistorico ordena_historico(const ListaContHistorico *historico, bool is_pontuacao);
