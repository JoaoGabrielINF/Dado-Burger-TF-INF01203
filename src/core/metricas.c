#include "metricas.h"
#include <string.h>

Metricas metricas;

void metricas_limpar_execucao(void)
{
    memset(&metricas, 0, sizeof(metricas));
}

void metricas_limpar_partida(void)
{
    metricas.total_buscas = 0;
    metricas.total_comparacoes = 0;
    metricas.tempo_buscas = 0.0;
    metricas.hash_hits = 0;
    metricas.hash_misses = 0;
    metricas.hash_colisoes = 0;
    metricas.hash_n = 0;
}
