#include "heap_estoque.h"

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
    if(alimento.tipoAlimento == PERECIVEL && alimento.simboloAlimento == heap->alimento){
        heap->estoquePerecivel[heap->tamanhoHeap] = alimento;
        siftUp(heap->estoquePerecivel, heap->tamanhoHeap);
        heap->tamanhoHeap++;
        return true;
    }
    return false; 

}

bool removerHeap(HeapEstoque *heap, Alimento* alimento){
    
    if(heap->tamanhoHeap <= 0){
        return false;
    }
    *alimento = heap->estoquePerecivel[0];
    heap->estoquePerecivel[0] = heap->estoquePerecivel[heap->tamanhoHeap - 1];
    heap->tamanhoHeap--;
    heapify(heap->estoquePerecivel, heap->tamanhoHeap, 0);
    return true;
}

bool consultarTopoHeap(HeapEstoque *heap, int turno_atual, Alimento *alimento){
    if(heap->estoquePerecivel[0].validade == turno_atual){
        while(heap->estoquePerecivel[0].validade == turno_atual){
            removerHeap(heap, alimento);
        }
        return true;
    }

    return false;
}