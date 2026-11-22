#include "heap_estoque.h"

void inicializaHeap(HeapEstoque* heap){
    heap->tamanho_heap = 0;
    
}

/* heapify: restaura a propriedade do min-heap descendo o nó i.
   a[] = vetor do heap, n = número de elementos ativos, i = nó a descer. */
void heapify(Alimento a[], int n, int i) {
    int menor = i;
    int esq   = 2*i + 1;
    int dir   = 2*i + 2;

    if (esq < n && a[esq].validade < a[menor].validade) menor = esq;
    if (dir < n && a[dir].validade < a[menor].validade) menor = dir;

    if (menor != i) {
        Alimento tmp = a[i]; a[i] = a[menor]; a[menor] = tmp;
        heapify(a, n, menor);
    }
}

/* sift-up: restaura a propriedade do min-heap subindo o nó i. */
void siftUp(Alimento a[], int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (a[i].validade < a[pai].validade) {
            Alimento tmp = a[i]; a[i] = a[pai]; a[pai] = tmp;
            i = pai;
        } else {
            break;
        }
    }
}

bool inserirHeap(HeapEstoque *heap, const Alimento alimento){
    if(alimento.simbolo_alimento == heap->alimento){
        heap->estoque_perecivel[heap->tamanho_heap] = alimento;
        siftUp(heap->estoque_perecivel, heap->tamanho_heap);
        heap->tamanho_heap++;
        return true;
    }
    return false; 

}

bool removerHeap(HeapEstoque *heap, Alimento* alimento){
    
    if(heap->tamanho_heap <= 0){
        return false;
    }
    *alimento = heap->estoque_perecivel[0];
    heap->estoque_perecivel[0] = heap->estoque_perecivel[heap->tamanho_heap - 1];
    heap->tamanho_heap--;
    heapify(heap->estoque_perecivel, heap->tamanho_heap, 0);
    return true;
}

bool consultarTopoHeap(HeapEstoque *heap, int turno_atual, Alimento *alimento){
    if(heap->estoque_perecivel[0].validade == turno_atual){
        while(heap->estoque_perecivel[0].validade == turno_atual){
            removerHeap(heap, alimento);
        }
        return true;
    }

    return false;
}