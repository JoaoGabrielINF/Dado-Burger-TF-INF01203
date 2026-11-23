#include "../data_structures/lista_contigua_historico.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h> // pra ter ctz de que consigo usar o strcasecmp

/* Intercala a[ini..meio] e a[meio+1..fim], ambos já ordenados. */
void merge(RegistroHistorico a[], RegistroHistorico aux[], int ini, int meio, int fim) {
    int t, i, j, k;

    for (t = ini; t <= fim; t++)      /* linhas 1-2: copia para Aux */
        aux[t] = a[t];

    i = ini;  j = meio + 1;  k = ini; /* linhas 3-5 */

    while (i <= meio && j <= fim) {   /* linhas 6-12 */
        if (aux[i].pontuacao >= aux[j].pontuacao)         /* >= (e não <=) pq a pontuação é em ordem decrescente, e pra manter a estabilidade */
            a[k++] = aux[i++];
        else
            a[k++] = aux[j++];
    }
    while (i <= meio) a[k++] = aux[i++];  /* linhas 13-16 */
    while (j <= fim)  a[k++] = aux[j++];  /* linhas 17-20 */
}

void merge_sort_rec(RegistroHistorico a[], RegistroHistorico aux[], int ini, int fim) {
    if (ini >= fim) return;               /* conquista: 0 ou 1 elemento */
    int meio = ini + (fim - ini) / 2;     /* divisão: ao meio */
    merge_sort_rec(a, aux, ini, meio);
    merge_sort_rec(a, aux, meio + 1, fim);
    merge(a, aux, ini, meio, fim);        /* recombinação */
}

void merge_sort_pontuacao(RegistroHistorico a[], int n) {
    RegistroHistorico *aux = malloc(n * sizeof(RegistroHistorico));   /* o vetor extra: O(n) de memória */
    merge_sort_rec(a, aux, 0, n - 1);
    free(aux);
}

void merge_alfabetico(RegistroHistorico a[], RegistroHistorico aux[], int ini, int meio, int fim) {
    int t, i, j, k;

    for (t = ini; t <= fim; t++)      /* linhas 1-2: copia para Aux */
        aux[t] = a[t];

    i = ini;  j = meio + 1;  k = ini; /* linhas 3-5 */

    while (i <= meio && j <= fim) {   /* linhas 6-12 */
        if (strcasecmp(aux[i].nome, aux[j].nome) <= 0) // tem que fazer strcasecmp pq tô comparando strings e a letra ser maiúscula ou minúscula não pode interferir (pela tabela ASCII mostraria tds os maiúsculos primeiro). <= 0 pra estabilidade
            a[k++] = aux[i++];
        else
            a[k++] = aux[j++];
    }
    while (i <= meio) a[k++] = aux[i++];  /* linhas 13-16 */
    while (j <= fim)  a[k++] = aux[j++];  /* linhas 17-20 */
}

void merge_sort_rec_alfabetico(RegistroHistorico a[], RegistroHistorico aux[], int ini, int fim) {
    if (ini >= fim) return;               /* conquista: 0 ou 1 elemento */
    int meio = ini + (fim - ini) / 2;     /* divisão: ao meio */
    merge_sort_rec_alfabetico(a, aux, ini, meio);
    merge_sort_rec_alfabetico(a, aux, meio + 1, fim);
    merge_alfabetico(a, aux, ini, meio, fim);        /* recombinação */
}

void merge_sort_alfabetico(RegistroHistorico a[], int n) {
    RegistroHistorico *aux = malloc(n * sizeof(RegistroHistorico));   /* o vetor extra: O(n) de memória */
    merge_sort_rec_alfabetico(a, aux, 0, n - 1);
    free(aux);
}

ListaContHistorico ordena_historico(ListaContHistorico *historico, bool is_pontuacao) {
    ListaContHistorico copia; // vou precisar copiar os dados pra não afetar o historico original (talvez não seja necessário, mas não é prejuízo de desempenho significativo e dá uma flexibilidade de uso maior)
    inicializar(&copia);

    if (historico == NULL || historico->tamanho == 0) return copia; // pra evitar de causar erros nos merge sorts por receber lista vazia
    for (int i = 0; i < historico->tamanho; i++) // copia o histórico pra cópia
        inserir(&copia, historico->dados[i], i);
    if (is_pontuacao)
        merge_sort_pontuacao(copia.dados, copia.tamanho);
    else
        merge_sort_alfabetico(copia.dados, copia.tamanho);

    return copia;
}
