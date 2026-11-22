#pragma once
#include <cliente.h>


typedef struct str_NodoAvl NodoAvl;
struct str_NodoAvl {
    Pedido  dado;
    NodoAvl *esq;
    NodoAvl *dir;
    int      altura;   /* folha = 0; NULL = -1 (por convenção) */
};

/**
 * @brief "Inicializa" a AVL. Literalmente só retorna null, é uma função meio inútil e não tava no TAD da aula, mas criei mais por consistência mesmo.
 * @return NULL.
 */
NodoAvl* avlInicializar();

/**
 * @brief Fornece a altura do nó (convenção: folha=0, NULL=-1). Necessário para que 1 + max(h_esq, h_dir) funcione corretamente.
 * @param [in] no ponteiro para o nó que se quer a altura
 * @return -1 se o nó é NULL
 * @return A altura do nó se diferente de NULL
 */
int avlAltura(const NodoAvl *no);


/**
 * @brief Calcula o Fator de Balanceamento (FB) do nó; FB = h(esq) - h(dir). Positivo = pesado à esq; negativo = pesado à dir.
 * @param [in] no ponteiro para o nó que se quer o Fator de Balanceamento.
 * @return Diferença entre a altura da subárvore esquerda e da direita.
 */
int avlFb(const NodoAvl *no);


/**
 * @brief Recalcula e armazena a altura do nó com base nas alturas dos filhos; chamado sempre que um filho muda (inserção, remoção ou rotação).
 * @param [in, out] no ponteiro para o nó que se quer atualizar a altura.
 */
void avlAtualizarAltura(NodoAvl *no);

/**
 * @brief Rotação simples à DIREITA (caso LL). x sobe; B (filho dir de x) passa para filho esq de y. Atualiza y primeiro (ficou abaixo), depois x.
 * @param [in, out] y ponteiro para o nó que se quer rotacionar à direita.
 * @return Nodo atualizado a substituir a posição do nodo de entrada de acordo com a rotação.
 */
NodoAvl* avlRotDir(NodoAvl *y);

/**
 * @brief Rotação simples à ESQUERDA (caso RR). Simétrica à anterior. y sobe; B (filho esq de y) passa para filho dir de x.
 * @param [in, out] x ponteiro para o nó que se quer rotacionar à esquerda.
 * @return Nodo atualizado a substituir a posição do nodo de entrada de acordo com a rotação.
 */
NodoAvl* avlRotEsq(NodoAvl *x);

/**
 * @brief Verifica o FB e aplica a rotação correta. Usada tanto na inserção quanto na remoção.
 * @param [in, out] raiz ponteiro para a raiz da AVL que se quer reequilibrar.
 * @param [in, out] isInserir booleano que indica se a operação é de inserção, usado para as métricas/relatório
 * @return raiz da AVL equilibrada
 */
NodoAvl* avlReequilibrar(NodoAvl *raiz, bool isInserir);

/**
 * @brief Busca um pedido na AVL em O(log n).
 * @param [in] raiz ponteiro para a raiz da AVL em que se quer buscar o pedido.
 * @param [in] cod código do pedido que se quer buscar na AVL.
 * @return Nodo da AVL correspondente ao pedido com o código informado. 
 */
NodoAvl* avlBuscar(NodoAvl *raiz, int cod);

/**
 * @brief Insere um nodo na AVL, reequilibrando-a na subida.
 * @param [in, out] raiz ponteiro para a raiz da AVL em que se quer inserir o pedido.
 * @param [in, out] valor pedido que se quer inserir na AVL.
 * @return Raiz da AVL com o pedido inserido.
 */
NodoAvl* avlInserir(NodoAvl *raiz, Pedido valor);

/**
 * @brief Auxiliar: menor nó da subárvore (sucessor em-ordem).
 * @param [in, out] raiz ponteiro para a raiz da AVL de que se quer obter o menor nó.
 * @return Menor nó da árvore.
 */
NodoAvl* avlMinimo(NodoAvl *raiz);

/**
 * @brief Remove um pedido da AVL.
 * @param [in, out] raiz ponteiro para a raiz da AVL de que se quer remover o pedido.
 * @param [in] cod código do pedido que se quer remover da AVL.
 * @return Raiz da AVL com o pedido removido.
 */
NodoAvl* avlRemover(NodoAvl *raiz, int cod);

/**
 * @brief Destrói toda a árvore em pós-ordem. Uso: raiz = avlDestruir(raiz).
 * @param [in, out] raiz ponteiro para a raiz da AVL que se quer destruir.
 * @return NULL se raiz == NULL.
 */
NodoAvl* avlDestruir(NodoAvl *raiz);