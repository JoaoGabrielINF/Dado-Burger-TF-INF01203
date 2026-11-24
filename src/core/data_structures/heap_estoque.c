#include "heap_estoque.h"
#include <stdio.h>

void inicializaHeap(HeapEstoque* heap){
    if (heap == NULL) {
        return;
    }

    heap->tamanho_heap = 0;
    for (int i = 0; i < MAX_ALIM; i++) {
        heap->validade_alimentos[i] = 9999;
    }
}

/* heapify: restaura a propriedade do min-heap descendo o nó i.
   a[] = vetor do heap, n = número de elementos ativos, i = nó a descer. */
void heapify(int validade[], int n, int i) {
    if (validade == NULL || n <= 0 || i < 0 || i >= n) {
        return;
    }

    int menor = i;
    int esq   = 2*i + 1;
    int dir   = 2*i + 2;

    if (esq < n && validade[esq] < validade[menor]) menor = esq;
    if (dir < n && validade[dir] < validade[menor]) menor = dir;

    if (menor != i) {
        int tmp = validade[i]; validade[i] = validade[menor]; validade[menor] = tmp;
        heapify(validade, n, menor);
    }
}

/* sift-up: restaura a propriedade do min-heap subindo o nó i. */
void siftUp(int validade[], int i) {
    if (validade == NULL || i < 0) {
        return;
    }

    while (i > 0) {
        int pai = (i - 1) / 2;
        if (validade[i] < validade[pai]) {
            int tmp = validade[i]; validade[i] = validade[pai]; validade[pai] = tmp;
            i = pai;
        } else {
            break;
        }
    }
}

bool inserirHeap(HeapEstoque *heap, int validade, const char alimento){
    if (heap == NULL || alimento != heap->alimento) {
        return false;
    }

    if (heap->tamanho_heap >= MAX_ALIM) {
        return false;
    }

    heap->validade_alimentos[heap->tamanho_heap] = validade;
    siftUp(heap->validade_alimentos, heap->tamanho_heap);
    heap->tamanho_heap++;
    return true;

}

bool removerHeap(HeapEstoque *heap, char* alimento){
    if (heap == NULL || heap->tamanho_heap <= 0) {
        return false;
    }

    if (alimento != NULL) {
        *alimento = heap->alimento;
    }
    heap->tamanho_heap--;
    if (heap->tamanho_heap == 0) {
        heap->validade_alimentos[0] = 9999;
        return true;
    }
    heap->validade_alimentos[0] = heap->validade_alimentos[heap->tamanho_heap];
    heap->validade_alimentos[heap->tamanho_heap] = 9999;
    heapify(heap->validade_alimentos, heap->tamanho_heap, 0);
    return true;
}

bool consultarTopoHeap(HeapEstoque *heap, int turno_atual, char *alimento){
    if (heap == NULL || heap->tamanho_heap <= 0) {
        return false;
    }

    if(heap->validade_alimentos[0] <= turno_atual){
        while(heap->tamanho_heap > 0 && heap->validade_alimentos[0] <= turno_atual){
            if (!removerHeap(heap, alimento)) {
                break;
            }
        }
        return true;
    }

    return false;
}