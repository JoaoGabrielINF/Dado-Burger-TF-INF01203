#include "heap_estoque.h"
#include <stdio.h>

void inicializaHeap(HeapEstoque* heap){
    heap->tamanho_heap = 0;
    
}

/* heapify: restaura a propriedade do min-heap descendo o nó i.
   a[] = vetor do heap, n = número de elementos ativos, i = nó a descer. */
void heapify(int validade[], int n, int i) {
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
    if(alimento == heap->alimento){
        heap->validade_alimentos[heap->tamanho_heap] = validade;
        siftUp(heap->validade_alimentos, heap->tamanho_heap);
        heap->tamanho_heap++;
        return true;
    }
    return false; 

}

bool removerHeap(HeapEstoque *heap, char* alimento){
    
    if(heap->tamanho_heap <= 0){
        return false;
    }

    *alimento = heap->alimento; 
    heap->tamanho_heap--;
    if(heap->tamanho_heap == 0){
        *alimento = heap->alimento;
        heap->validade_alimentos[0] = 0;
        return true;
    }
    heap->validade_alimentos[0] = heap->validade_alimentos[heap->tamanho_heap];
    heapify(heap->validade_alimentos, heap->tamanho_heap, 0);
    return true;
}

bool consultarTopoHeap(HeapEstoque *heap, int turno_atual, char *alimento){
    if(heap->validade_alimentos[0] == turno_atual){
        while(heap->validade_alimentos[0] == turno_atual){
            printf("[%d]", heap->validade_alimentos[0]);
            printf("  |  [%d]", turno_atual);
            removerHeap(heap, alimento);
        }
        return true;
    }

    return false;
}