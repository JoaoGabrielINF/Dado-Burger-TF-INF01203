// variáveis de estruturas usadas universalmente pelo projeto (exceto as métricas)
#include "dados.h"

NodoAvl *pedidos_avl;
ListaContHistorico historico_partidas;
TabelaHash cache_pedidos;
int maior_codigo_avl;

void dados_inicializar(void)
{
    pedidos_avl = avlInicializar();
    inicializar(&historico_partidas);
    inicializarHash(&cache_pedidos);
    maior_codigo_avl = 0;
}
