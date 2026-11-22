#ifndef LISTA_CONTIGUA_HISTORICO_H
#define LISTA_CONTIGUA_HISTORICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 21 // tamanho do nome (com 1 reservado pro \0)
#define CAP_INICIAL 4 // capacidade inicial da lista (o valor é meio arbitrário, mas é potência de 2 pq vai dobrando dps conforme acaba o espaço)


typedef struct {
    int cod;
    char nome[TAM];
    int pontuacao;
} RegistroHistorico;


typedef struct {
    int tamanho;
    int capacidade;
    RegistroHistorico *dados;
} ListaContHistorico;

/**
 * @brief Cria um RegistroHistorico preenchido.
 * @param[in] cod código do registro.
 * @param[in] nome nome do registro.
 * @param[in] pontuacao pontuação do registro.
 * @return RegistroHistorico criado.
 */
RegistroHistorico criarRegistro(int cod, const char *nome, int pontuacao);

/**
 * @brief Inicializa uma lista vazia.
 * @param[out] l ponteiro pra lista.
 */
void inicializar(ListaContHistorico *l);

/**
 * @brief Calcula o tamanho da lista.
 * @param[in] l ponteiro pra lista.
 * @return Tamanho da lista.
 */
int tamanho(const ListaContHistorico *l);

/**
 * @brief Insere um registro na posição passada; se não tiver espaço, dobra o espaço dinamicamente.
 * @param[in,out] l ponteiro pra lista onde se quer inserir o registro.
 * @param[in] novo registro histórico que se quer inserir.
 * @param[in] pos índice da posição onde se quer inserir o registro.
 * @return 1 se inserido com sucesso.
 * @return 0 se der erro.
 */
int inserir(ListaContHistorico *l, RegistroHistorico novo, int pos);

/**
 * @brief Retorna o registro armazenado na posição passada.
 * @param[in] l ponteiro pra lista consultada.
 * @param[in] pos índice da posição em que se quer consultar o registro.
 * @return O registro histórico da posição passada, ou um com cod = -1 se a posição for inválida.
 */
RegistroHistorico acessar(const ListaContHistorico *l, int pos);

/**
 * @brief Busca um registro na lista pelo código.
 * @param[in] l ponteiro pra lista em que se quer buscar o registro.
 * @param[in] cod código do registro procurado.
 * @return Índice do registro na lista ou -1 caso não seja encontrado.
 */
int buscar(const ListaContHistorico *l, int cod);

/**
 * @brief Remove o registro da posição informada e move os seguintes pra esquerda.
 * @param[in,out] l ponteiro pra a lista de onde se quer remover o registro.
 * @param[in] pos índice do elemento que se quer remover.
 * @return 1 se for removido com sucesso.
 * @return 0 se der erro.
 */
int remover(ListaContHistorico *l, int pos);

/**
 * @brief Destrói a lista.
 * @param[in,out] l ponteiro pra lista que se quer destruir.
 */
void destruir(ListaContHistorico *l);

#endif