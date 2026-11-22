#pragma once
#include <stdbool.h>

typedef struct {
    // AVL: carregamento
    int nos_inseridos;         /** pedidos efetivamente inseridos na AVL na carga */
    int altura_resultante;     /** PRA SEGUIR A CONVENÇÃO DE VAZIO = 0 E RAIZ = 1, AVALIADO COMO avlAltura(raiz) + 1) */
    int rotacoes_insercao;     /** rotações da inserção */
    double tempo_carregamento; /** tempo de carregamento em segundos */

    // Histórico: carregamento
    int entradas_historico;    /** registros lidos do argv[2] (retorno de lerHistorico) */

    // AVL: buscas durante a partida
    int total_buscas;          /** buscas feitas na AVL, só quando dá MISS no cache (4.3 no PDF da atv) */
    int total_comparacoes;     /** 1 por comparação de chave com nó visitado (5.1 no PDF da atv) */
    double tempo_buscas;       /** tempo acumulado das buscas em segundos */

    int hash_hits;             /** consultas ao cache que encontraram o pedido */
    int hash_misses;           /** consultas que não encontraram */
    int hash_colisoes;         /** 1 por INSERÇÃO que acha a posição ocupada, não por nó percorrido (4.3 no PDF da atv) */
    int hash_n;                /** entradas ocupadas no fim da partida (campo n da TabelaHash) */

    /*  Ordenação do histórico (ao acessar o Histórico) */
    bool historico_ordenado;   /** booleano que indica se o histórico já foi acessado nessa execução */
    int ordenacao_tamanho;     /** nº de entradas ordenadas (na cópia independente) */
    double ordenacao_tempo;    /** tempo de execução do sort em segundos (timer) */
} Metricas;

/** Instância única do jogo, fica tudo centralizado aqui pra evitar ter que ficar "catando" os dados em cada canto depois. */
extern Metricas metricas;

/**
 * @brief Zera todos os campos. Chamada uma vez por execução junto com medicoes_reiniciar("medicoes.log") (5 no PDF da atv, o log é sobrescrito).
 */
void metricas_limpar_execucao(void);

/**
 * @brief Zera apenas o Bloco 2 (métricas da partida).
 * É chamada no início de cada partida.
 */
void metricas_limpar_partida(void);
