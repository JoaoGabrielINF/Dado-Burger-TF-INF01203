/* medicoes.c — camada de formatação/escrita do medicoes.log (§5 da especificação).
   Formato das seções: Apêndice B. Os valores vêm do container `metricas`
   (preenchido pelo grupo nas estruturas e nos pontos de medição). Apenas os
   derivados (média, lambda, taxa) são calculados aqui, conforme a §5.1.
   O Relatório de Desempenho é montado UMA vez em linhas rótulo/valor
   (medicoes_obter_relatorio) e consumido pelo log E pela tela — mesma
   formatação nos dois, como a §5.2 exige. */
#include "medicoes.h"
#include "../core/metricas.h"
#include "../core/data_structures/hash.h" /* TAMANHO_HASH (m) p/ o fator de carga */
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

void medicoes_reiniciar(const char *caminho)
{
    FILE *f = fopen(caminho, "w"); /* "w" trunca: log novo a cada execução (§5) */
    if (f != NULL)
        fclose(f);
}

void medicoes_gravar_pos_carregamento(FILE *destino)
{
    secao_avl_carregamento(destino);
    secao_historico_carregamento(destino);
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

/* =================== Relatório completo: montagem única =================== */

/* Coletor de linhas rótulo/valor do relatório completo. */
typedef struct {
    char rotulos[MEDICOES_MAX_LINHAS][MEDICOES_TAM_ROTULO];
    char valores[MEDICOES_MAX_LINHAS][MEDICOES_TAM_VALOR];
    int n;
} Relatorio;

static void rel_secao(Relatorio *r, const char *titulo)
{
    if (r->n < MEDICOES_MAX_LINHAS) {
        snprintf(r->rotulos[r->n], MEDICOES_TAM_ROTULO, "%s", titulo);
        r->valores[r->n][0] = '\0';
        r->n++;
    }
}

static void rel_valor(Relatorio *r, const char *rotulo, const char *valor)
{
    if (r->n < MEDICOES_MAX_LINHAS) {
        snprintf(r->rotulos[r->n], MEDICOES_TAM_ROTULO, "%s", rotulo);
        snprintf(r->valores[r->n], MEDICOES_TAM_VALOR, "%s", valor);
        r->n++;
    }
}

static void rel_int(Relatorio *r, const char *rotulo, int valor)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", valor);
    rel_valor(r, rotulo, buf);
}

static void rel_tempo(Relatorio *r, const char *rotulo, double segundos)
{
    char buf[48];
    snprintf(buf, sizeof(buf), "%.6f s", segundos);
    rel_valor(r, rotulo, buf);
}

int medicoes_obter_relatorio(char rotulos[][MEDICOES_TAM_ROTULO],
                             char valores[][MEDICOES_TAM_VALOR], int max)
{
    Relatorio r;
    r.n = 0;
    char buf[96];

    rel_secao(&r, "-- AVL: carregamento --");
    rel_int(&r, "Nos inseridos:", metricas.nos_inseridos);
    rel_int(&r, "Altura resultante:", metricas.altura_resultante);
    rel_int(&r, "Rotacoes (insercao):", metricas.rotacoes_insercao);
    rel_tempo(&r, "Tempo de carregamento:", metricas.tempo_carregamento);

    rel_secao(&r, "-- Historico: carregamento --");
    rel_int(&r, "Entradas carregadas:", metricas.entradas_historico);

    /* §5.1: média 0 se não houve nenhuma busca na partida */
    double media = (metricas.total_buscas > 0)
                       ? (double)metricas.total_comparacoes / metricas.total_buscas
                       : 0.0;
    rel_secao(&r, "-- AVL: buscas durante a partida --");
    rel_int(&r, "Total de buscas:", metricas.total_buscas);
    rel_int(&r, "Total de comparacoes:", metricas.total_comparacoes);
    snprintf(buf, sizeof(buf), "%.2f", media);
    rel_valor(&r, "Media de comparacoes por busca:", buf);
    rel_tempo(&r, "Tempo total acumulado:", metricas.tempo_buscas);

    int acessos = metricas.hash_hits + metricas.hash_misses;
    double lambda = (TAMANHO_HASH > 0) ? (double)metricas.hash_n / TAMANHO_HASH : 0.0;
    double taxa = (acessos > 0) ? 100.0 * metricas.hash_hits / acessos : 0.0;
    rel_secao(&r, "-- Tabela hash --");
    rel_int(&r, "Tamanho (m):", TAMANHO_HASH);
    rel_int(&r, "Entradas ocupadas (n):", metricas.hash_n);
    snprintf(buf, sizeof(buf), "%.2f", lambda);
    rel_valor(&r, "Fator de carga (lambda):", buf);
    rel_int(&r, "Total de hits:", metricas.hash_hits);
    rel_int(&r, "Total de misses:", metricas.hash_misses);
    snprintf(buf, sizeof(buf), "%.1f%%", taxa);
    rel_valor(&r, "Taxa de acerto:", buf);
    rel_int(&r, "Total de colisoes:", metricas.hash_colisoes);

    if (ordenacao_ja_medida) {
        rel_secao(&r, "-- Ordenacao do historico --");
        snprintf(buf, sizeof(buf), "%d entradas", metricas.ordenacao_tamanho);
        rel_valor(&r, "Tamanho:", buf);
        rel_tempo(&r, "Merge Sort", metricas.ordenacao_tempo);
    }

    int copiado = (r.n < max) ? r.n : max;
    for (int i = 0; i < copiado; i++) {
        snprintf(rotulos[i], MEDICOES_TAM_ROTULO, "%s", r.rotulos[i]);
        snprintf(valores[i], MEDICOES_TAM_VALOR, "%s", r.valores[i]);
    }
    return copiado;
}

void medicoes_gravar_relatorio_completo(FILE *destino)
{
    char rotulos[MEDICOES_MAX_LINHAS][MEDICOES_TAM_ROTULO];
    char valores[MEDICOES_MAX_LINHAS][MEDICOES_TAM_VALOR];
    int n = medicoes_obter_relatorio(rotulos, valores, MEDICOES_MAX_LINHAS);

    fprintf(destino, "=== RELATORIO DE DESEMPENHO ===\n\n");
    for (int i = 0; i < n; i++) {
        if (valores[i][0] == '\0') { /* linha de seção */
            fprintf(destino, "%s\n", rotulos[i]);
        } else {
            linha_valor(destino, rotulos[i], valores[i]);
        }
    }
    fprintf(destino, "================================\n");
}

void medicoes_gravar_relatorio_em_arquivo(const char *caminho)
{
    FILE *f = fopen(caminho, "a");
    if (f != NULL) {
        medicoes_gravar_relatorio_completo(f);
        fclose(f);
    }
}
