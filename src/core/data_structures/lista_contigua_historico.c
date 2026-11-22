#include "lista_contigua_historico.h"

void inicializar(ListaContHistorico *l)
{
    l->tamanho = 0;
    l->capacidade = CAP_INICIAL;
    l->dados = (RegistroHistorico*) malloc(l->capacidade * sizeof(RegistroHistorico));

    if (l->dados == NULL)
    {
        l->capacidade = 0;
    }
}

int tamanho(const ListaContHistorico *l)
{
    return l->tamanho;
}

RegistroHistorico acessar(const ListaContHistorico *l, int pos)
{
    RegistroHistorico regAux;

    if (pos >= l->tamanho || pos < 0)
    { // posição inválida
        regAux.cod = -1;
        regAux.nome[0] = '\0'; // zerando td p criar um registro inválido
        regAux.pontuacao = 0;
    }
    else
    {
        regAux = l->dados[pos];
    }

    return regAux;
}

int inserir(ListaContHistorico *l, RegistroHistorico novo, int pos)
{
    int i;

    if (pos > l->tamanho || pos < 0)
        return 0; // posição inválida

    // dobra a capacidade se a lista tiver cheia
    if (l->tamanho == l->capacidade)
    {
        int novaCapacidade = (l->capacidade == 0) ? CAP_INICIAL : l->capacidade * 2; // se usar o TAD certinho nem tem como a capacidade ser 0, mas é um bom safeguard
        RegistroHistorico *temp = (RegistroHistorico *)realloc(l->dados, novaCapacidade * sizeof(RegistroHistorico));

        if (temp == NULL)
            return 0; // botei num temporário pra se der erro (tipo n ter espaço) n dar bo. aqui retorna 0 se der erro

        l->dados = temp;
        l->capacidade = novaCapacidade;
    }

    for (i = l->tamanho; i > pos; i--)
    {
        l->dados[i] = l->dados[i - 1]; // arrasta tudo q vem dps pra esquerda
    }

    l->dados[pos] = novo;
    l->tamanho++;
    return 1;
}

int remover(ListaContHistorico *l, int pos)
{
    int i;

    if (pos >= l->tamanho || pos < 0)
        return 0; // posição inválida

    for (i = pos; i < l->tamanho - 1; i++)
    { // puxa elementos seguintes para a esquerda
        l->dados[i] = l->dados[i + 1];
    }

    l->tamanho--;
    return 1;
}

int buscar(const ListaContHistorico *l, int cod)
{
    int i;

    for (i = 0; i < l->tamanho; i++)
    {
        if (l->dados[i].cod == cod)
        {
            return i; // posição onde o produto foi encontrado
        }
    }

    return -1; // não encontrado
}

void destruir(ListaContHistorico *l)
{
    free(l->dados);
    l->dados = NULL;
    l->tamanho = 0;
    l->capacidade = 0;
}

RegistroHistorico criarRegistro(int cod, const char *nome, int pontuacao)
{
    RegistroHistorico reg;
    reg.cod = cod;
    reg.pontuacao = pontuacao;
    strcpy(reg.nome, nome);
    return reg;
}