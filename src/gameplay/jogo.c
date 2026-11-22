#include "jogo.h"

void inicializa_estruturas(Jogo *jogo){
    inicializaFila(&jogo->fila_clientes);
    inicializaPilha(&jogo->jogador.pedido_atual.pilha_hamburger);
    incializaLista(&jogo->jogador.pedido_atual.receita_pedido);
    for(int i = 0; i < QUANTIDADE_ALIMENTOS_PERECIVEIS - 1; i++){
        inicializaHeap(&jogo->jogador.heap_estoque[i]);
    }
    inicializarHash(&jogo->jogador.hash);

}

