#include "medicoes.h"
#include "../core/metricas.h"
#include "../core/data_structures/hash.h"
#include <stdio.h>

#define ROTULO_LARGURA 32

/* A seção de ordenação só entra no relatório se o Histórico já foi acessado */
static bool ordenacao_ja_medida = false;

/* Escreve "rótulo .................. valor" com o rótulo alinhado à esquerda. */
static void linha_valor(FILE *destino, const char *rotulo, const char *valor)
{
    fprintf(destino, "%-*s %s\n", ROTULO_LARGURA, rotulo, valor);
}

static void linha_int(FILE *destino, const char *rotulo, int valor)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "%d", valor);
    linha_valor(destino, rotulo, buf);
}

static void linha_tempo(FILE *destino, const char *rotulo, double segundos)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "%.6f s", segundos);
    linha_valor(destino, rotulo, buf);
}

static void secao_avl_carregamento(FILE *destino)
{
    fprintf(destino, "-- AVL: carregamento --\n");
    linha_int(destino, "Nos inseridos:", metricas.nos_inseridos);
    linha_int(destino, "Altura resultante:", metricas.altura_resultante);
    linha_int(destino, "Rotacoes (insercao):", metricas.rotacoes_insercao);
    linha_tempo(destino, "Tempo de carregamento:", metricas.tempo_carregamento);
    fputc('\n', destino);
}

static void secao_historico_carregamento(FILE *destino)
{
    fprintf(destino, "-- Historico: carregamento --\n");
    linha_int(destino, "Entradas carregadas:", metricas.entradas_historico);
    fputc('\n', destino);
}

static void secao_avl_buscas(FILE *destino)
{
    /* média 0 se não houve nenhuma busca na partida (5.1 no PDF da atv) */
    double media = (metricas.total_buscas > 0)
                       ? (double)metricas.total_comparacoes / metricas.total_buscas
                       : 0.0;

    fprintf(destino, "-- AVL: buscas durante a partida --\n");
    linha_int(destino, "Total de buscas:", metricas.total_buscas);
    linha_int(destino, "Total de comparacoes:", metricas.total_comparacoes);
    char buf[64];
    snprintf(buf, sizeof(buf), "%.2f", media);
    linha_valor(destino, "Media de comparacoes por busca:", buf);
    linha_tempo(destino, "Tempo total acumulado:", metricas.tempo_buscas);
    fputc('\n', destino);
}

static void secao_hash(FILE *destino)
{
    int acessos = metricas.hash_hits + metricas.hash_misses;
    double lambda = (TAMANHO_HASH > 0) ? (double)metricas.hash_n / TAMANHO_HASH : 0.0;
    double taxa = (acessos > 0) ? 100.0 * metricas.hash_hits / acessos : 0.0;

    fprintf(destino, "-- Tabela hash --\n");
    linha_int(destino, "Tamanho (m):", TAMANHO_HASH);
    linha_int(destino, "Entradas ocupadas (n):", metricas.hash_n);
    char buf[64];
    snprintf(buf, sizeof(buf), "%.2f", lambda);
    linha_valor(destino, "Fator de carga (lambda):", buf);
    linha_int(destino, "Total de hits:", metricas.hash_hits);
    linha_int(destino, "Total de misses:", metricas.hash_misses);
    snprintf(buf, sizeof(buf), "%.1f%%", taxa);
    linha_valor(destino, "Taxa de acerto:", buf);
    linha_int(destino, "Total de colisoes:", metricas.hash_colisoes);
    fputc('\n', destino);
}

void medicoes_reiniciar(const char *caminho)
{
    FILE *f = fopen(caminho, "w"); /* "w" trunca: log novo a cada execução (5 no PDF da atv) */
    if (f != NULL)
        fclose(f);
}

void medicoes_gravar_pos_carregamento(FILE *destino)
{
    secao_avl_carregamento(destino);
    secao_historico_carregamento(destino);
}

void medicoes_gravar_relatorio_completo(FILE *destino)
{
    fprintf(destino, "=== RELATORIO DE DESEMPENHO ===\n\n");
    secao_avl_carregamento(destino);
    secao_historico_carregamento(destino);
    secao_avl_buscas(destino);
    secao_hash(destino);
    if (ordenacao_ja_medida)
        medicoes_gravar_ordenacao(destino);
    fprintf(destino, "================================\n");
}

void medicoes_gravar_ordenacao(FILE *destino)
{
    ordenacao_ja_medida = true;
    fprintf(destino, "-- Ordenacao do historico (ao acessar Historico) --\n");
    char buf[96];
    snprintf(buf, sizeof(buf), "%d entradas", metricas.ordenacao_tamanho);
    linha_valor(destino, "Tamanho:", buf);
    linha_tempo(destino, "Merge Sort", metricas.ordenacao_tempo);
    fputc('\n', destino);
}
