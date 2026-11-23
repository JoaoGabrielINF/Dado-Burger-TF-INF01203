#pragma once
#include "../core/models.h"
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include "animacao.h"
#include <string.h>

/**
 * @brief Desenha um texto centralizado dentro de um retângulo.
 * @param[in] fonte Fonte usada para desenhar o texto
 * @param[in] texto Texto a ser desenhado
 * @param[in] ret Retângulo que delimita a área do texto
 * @param[in] tamanho Tamanho da fonte
 * @param[in] espaco Espaçamento entre caracteres
 * @param[in] cor Cor do texto
 */
void desenha_texto_centralizado(Font fonte, const char *texto, Rectangle ret, float tamanho, float espaco, Color cor);

/**
 * @brief Verifica se o cursor está dentro de um retângulo e o destaca.
 * @param[in] rec Retângulo a verificar
 * @param[in] pos_mouse Posição atual do cursor
 * @return true se o cursor estiver dentro do retângulo
 * @return false caso contrário
 */
bool colore_se_colide(Rectangle rec, Vector2 pos_mouse);

/**
 * @brief Atualiza a direção do jogador com base nas teclas pressionadas.
 * @param[in,out] jogador Jogador cuja direção será atualizada
 */
void determina_direcao(Jogador *jogador);

/**
 * @brief Desenha o jogador com o frame correspondente à direção e ao movimento.
 * @param[in,out] jogador Jogador a desenhar e atualizar
 */
void desenha_jogador(Jogador *jogador);

/**
 * @brief Desenha a tela de vitória e processa a entrada do nome.
 * @param[in,out] jogo Estado atual do jogo.
 */
void desenha_tela_vitoria(Jogo *jogo);

/**
 * @brief Desenha a tela de derrota e processa a entrada do nome.
 * @param[in,out] jogo Estado atual do jogo.
 */
void desenha_tela_derrota(Jogo *jogo);

/**
 * @brief Funcao que desenha os equipamentos utilizados na cozinha (fogao, tabua e bancada)
 * @param[in,out] jogo Estado atual do jogo.
 */
void desenha_equipamentos(Jogo* jogo);

/**
 * @brief Desenha acima do equipamento em colisão os ingredientes disponíveis.
 *
 * O fogão mostra ovo, bacon e carne somente quando não está em uso. A tábua
 * mostra picles, alface, queijo suíço, queijo cheddar, cebola e tomate.
 *
 * @param[in] jogo Estado atual do jogo.
 */
void desenha_opcoes_equipamentos(Jogo *jogo);

/**
 * @brief Desenha o turno atual do jogo.
 * @param[in] jogo Estado atual do jogo.
 */
void desenha_turno(const Jogo *jogo);

/**
 * @brief Desenha até MAX_CLIENTES_VISIVEIS clientes da fila na tela do saguão.
 * @param[in] fila Fila de clientes a desenhar
 */
void desenha_fila(const FilaClientes *fila);

/**
 * @brief Desenha o texto das camadas do hamburger
 * @param[in,out] jogo Estado atual do jogo.
 */
void desenha_hamburger(Jogo* jogo);

/**
 * @brief Desenha a barra vertical de paciência do cliente que está na frente da fila.
 * @param[in] jogo Estado do jogo que contém o cliente atual e a dificuldade.
 */
void desenha_paciencia_cliente(const Jogo *jogo);

/**
 * @brief Desenha a tecla de entrega ao colidir com a frente do balcão.
 * @param[in,out] jogo Estado atual do jogo.
 */
void desenha_entrega_pedido(Jogo *jogo);

/**
 * @brief Move cada cliente um tile em direção à posição do cliente removido.
 * @param[in,out] jogo Estado do jogo cuja fila será avançada.
 */
void anda_fila(Jogo *jogo);

/**
 * @brief Desenha a comanda com os ingredientes de uma receita.
 * @param[in] receita Lista de ingredientes a apresentar
 */
void desenha_comanda(const ListaReceita *receita);

/**
 * @brief Desenha os ícones, nomes, quantidades e controles de paginação do estoque.
 *
 * Cada alimento é apresentado em um retângulo branco com ícone sobre fundo cinza,
 * nome e campo de quantidade. A primeira página exibe sete alimentos e a segunda
 * os cinco restantes; as setas da barra lateral alternam entre as páginas.
 *
 * @param[in] retangulo_estoque Retângulo que delimita o painel do estoque.
 * @param[in] jogo estado atual do jogo para saber numero de alimentos.
 */
void desenha_alimentos_no_estoque(Rectangle retangulo_estoque, const Jogo *jogo);

/**
 * @brief Desenha o contorno vermelho do painel de estoque na cozinha.
 * O painel ocupa um quarto da largura da janela, fica alinhado à direita e
 * estende-se do topo da janela até um pouco acima do cartão da mochila.
 * @param[in] jogo estado atual do jogo para saber numero de alimentos.
 */
void desenha_estoque(const Jogo* jogo);

/**
 * @brief Desenha os elementos da tela atual do jogo.
 * @param[in,out] jogo Estado do jogo a desenhar
 */
void desenha_jogo(Jogo *jogo);

/**
 * @brief Libera as texturas carregadas pela apresentação.
 */
void descarrega_assets(void);

/**
 * @brief Carrega as texturas e a fonte usadas pela apresentação.
 */
void carrega_assets(void);