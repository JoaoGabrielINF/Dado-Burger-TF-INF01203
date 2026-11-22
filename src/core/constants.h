

#pragma once
/** Numero de linhas da matriz do mapa */
#define MAPA_LINHAS 16
/** Numero de colunas da matriz do mapa */
#define MAPA_COLUNAS 32

/** Tamanho de cada tile em pixels */
#define TILE_SIZE 40

/** Numero de mapas do jogo */
#define NUMERO_MAPAS 2
/** Indice do mapa da recepcao no vetor de mapas */
#define MAPA_RECEPCAO 0
/** Indice do mapa da cozinha no vetor de mapas */
#define MAPA_COZINHA 1

/** Numero de clientes por partida */
#define CLIENTES_POR_PARTIDA 7

/** Altura reservada para a HUD em pixels */
#define HUD_ALTURA 80

/** Largura total da janela em pixels */
#define JANELA_LARGURA (MAPA_COLUNAS * TILE_SIZE)

/** Altura total da janela em pixels incluindo a HUD */
#define JANELA_ALTURA (MAPA_LINHAS * TILE_SIZE + HUD_ALTURA)

/** Tamanho da fonte dos botões em relação à altura da janela */
#define TAMANHO_FONTE_BOTAO   (JANELA_ALTURA * 0.05f)
/** Tamanho da fonte dos títulos em relação à fonte dos botões */
#define TAMANHO_FONTE_TITULO  (TAMANHO_FONTE_BOTAO * 1.2f)
/** Tamanho da fonte do texto em relação à altura da janela */
#define TAMANHO_FONTE_TEXTO   (JANELA_ALTURA * 0.035f)
/** Espaçamento vertical entre linhas como múltiplo do tamanho da fonte */
#define ESPACAMENTO_LINHA     1.5f
/** Espaçamento entre caracteres do texto */
#define ESPACO_FONTE          2.0f

/** Largura dos botões do menu inicial */
#define LARGURA_BOTAO_INICIO (JANELA_LARGURA * (380.0f / 1920.0f))
/** Altura dos botões do menu inicial */
#define ALTURA_BOTAO_INICIO (JANELA_ALTURA * (85.0f / 1080.0f))
/** Coordenada horizontal dos botões do menu inicial */
#define X_BOTAO_INICIO (JANELA_LARGURA * (1380.0f / 1920.0f))
/** Coordenada vertical do botão central do menu inicial */
#define Y_BOTAO_INICIO (JANELA_ALTURA / 2 - ALTURA_BOTAO_INICIO / 2)
/** Espaçamento vertical entre os botões do menu inicial */
#define ESPACAMENTO_BOTAO_INICIO (JANELA_ALTURA * (30.0f / 1080.0f))

/** Altura do painel de exibição no menu inicial */
#define ALTURA_DISPLAY_INICIO 340.0f
/** Largura do painel de exibição no menu inicial */
#define LARGURA_DISPLAY_INICIO 350.0f
/** Coordenada vertical do painel de exibição no menu inicial */
#define Y_DISPLAY_INICIO (Y_BOTAO_INICIO + ALTURA_BOTAO_INICIO / 2 - ALTURA_DISPLAY_INICIO / 2 )
/** Coordenada horizontal do painel de exibição no menu inicial */
#define X_DISPLAY_INICIO (X_BOTAO_INICIO + LARGURA_BOTAO_INICIO / 2 - LARGURA_DISPLAY_INICIO / 2)

/** Paciencia maxima medida em turnos dos clientes no modo fácil */
#define PACIENCIA_MAXIMA_FACIL 20

/** Paciencia maxima medida em turnos dos clientes no modo médio */
#define PACIENCIA_MAXIMA_MEDIO 15

/** Paciencia maxima medida em turnos dos clientes no modo difícil */
#define PACIENCIA_MAXIMA_DIFICIL 12

/** Numero de equipamentos na cozinha */
#define NUMERO_EQUIPAMENTOS 3

/** Quantidade de alimentos pereciveis na heap */
#define QUANTIDADE_ALIMENTOS_PERECIVEIS 3

/** Posição da heap do alimento carne no vetor de heaps*/
#define HEAP_CARNE 0

/** Posição da heap do alimento ovo no vetor de heaps*/
#define HEAP_OVO 1 

/** Posição da heap do alimento bacon no vetor de heaps*/
#define HEAP_BACON 2

/** Validade inicial dos alimentos perecíveis, medida em turnos */
#define TURNOS_PERECIVEIS 9

/** Simbolo do pão em pedidos.txt */
#define PAO_SIMBOLO 'z'

/** Simbolo do ketchup em pedidos.txt */
#define KETCHUP_SIMBOLO 'k'

/** Simbolo da mostarda em pedidos.txt */
#define MOSTARDA_SIMBOLO 'm'

/** Simbolo do picles em pedidos.txt */
#define PICLES_SIMBOLO 'p'

/** Simbolo do alface em pedidos.txt */
#define ALFACE_SIMBOLO 'a'

/** Simbolo do queijo suíço em pedidos.txt */
#define QUEIJO_SUICO_SIMBOLO 's'

/** Simbolo do queijo cheddar em pedidos.txt */
#define QUEIJO_CHEDDAR_SIMBOLO 'q'

/** Simbolo da cebola em pedidos.txt */
#define CEBOLA_SIMBOLO 'c'

/** Simbolo do tomate em pedidos.txt */
#define TOMATE_SIMBOLO 't'

/** Simbolo da carne em pedidos.txt */
#define CARNE_SIMBOLO 'n'

/** Simbolo do ovo frito em pedidos.txt */
#define OVO_FRITO_SIMBOLO 'o'

/** Simbolo do bacon em pedidos.txt */
#define BACON_SIMBOLO 'b'

/** Simbolo do fogão em tela_jogo_cozinha.txt */
#define FOGAO_SIMBOLO 'f'

/** Simbolo da bancada em tela_jogo_cozinha.txt */
#define BANCADA_SIMBOLO 'c'

/** Simbolo da tábua em tela_jogo_cozinha.txt */
#define TABUA_SIMBOLO 'u'

/** Simbolo da faixa de colisao frontal dos equipamentos em tela_jogo_cozinha.txt */
#define EQUIPAMENTO_FRENTE_SIMBOLO 'E'

/** Simbolo do jogador nos .txt */
#define JOGADOR_SIMBOLO 'j'

/** Simbolo do cliente em tela_jogo_recepcao.txt */
#define CLIENTE_SIMBOLO 'l'

/** Simbolo do tile bloqueado nos .txt */
#define BLOQUEADO_SIMBOLO '#'

/** Simbolo da mesa nos .txt: colide apenas com a faixa superior do tile
 *  (a tampa da mesa), permitindo o jogador sobrepor visualmente a frente dela */
#define MESA_SIMBOLO 'M'

/** Simbolo da mesa lateral nos .txt (balcao vertical): colide apenas com a
 *  faixa esquerda do tile, de largura ALTURA_COLISAO_MESA */
#define MESA_LATERAL_SIMBOLO 'V'

/** Simbolo da parede baixa vista de cima nos .txt: colide apenas com uma
 *  faixa fina no RODAPE do tile (usado onde a parede desenhada comeca um
 *  pouco acima da borda do tile de baixo) */
#define PAREDE_RODAPE_SIMBOLO 'N'

/** Altura, em pixels, da faixa de colisao no rodape do tile (simbolo N) */
#define ALTURA_COLISAO_RODAPE 8

/** Altura, em pixels, da faixa de colisao de uma mesa dentro do tile */
#define ALTURA_COLISAO_MESA (TILE_SIZE / 2)

/** Altura, em pixels, da faixa de colisao frontal dos equipamentos */
#define ALTURA_COLISAO_EQUIPAMENTO 8

/** Velocidade de deslocamento do jogador, em pixels por segundo */
#define VELOCIDADE_JOGADOR 180.0f

/** Máximo de clientes desenhados ao mesmo tempo na fila */
#define MAX_CLIENTES_VISIVEIS 6

#define MAX_CLIENTES_FILA 10

/** Limites do desenho do personagem dentro do frame de 72x72 do sprite sheet
 *  (bounding box medida em assets/imagens/principal.png) */
#define PERSONAGEM_X0_NO_FRAME 24.0f
#define PERSONAGEM_X1_NO_FRAME 50.0f
#define PERSONAGEM_Y0_NO_FRAME 15.0f
#define PERSONAGEM_Y1_NO_FRAME 71.0f

/** Duração do cozimento de um alimento, medida em turnos */
#define TURNOS_COZIMENTO 3



 typedef enum {
    ILIMITADO = 0, /**< Alimento que não acaba */
    PERENE = 1, /**< Alimento que acaba mas não tem validade */
    PERECIVEL = 2 /**< Alimento que acaba e possui validade */
 } TipoAlimento;

 /**
 * @brief Representa qual o equipamento utilizado na cozinha
 */

typedef enum {
    FOGAO = 0, /**< Representação fogão*/
    TABUA = 1, /**< Representação tábua */
    BANCADA = 2 /**< Representação bancada */
} MateriaisCozinha;

/**
 * @brief Representa a ação atual do jogador na animação 
 */

typedef enum {
    PARADO = 0, /**< Animação da entidade parada */
    DIREITA = 1, /**< Animação da entidade andando para a direita */
    ESQUERDA = 2, /**< Animação da entidade andando para a esquerda */
    CIMA = 3, /**< Animação da entidade andando para a esquerda */
    BAIXO = 4, /**< Animação da entidade andando para baixo */
    CIMA_DIREITA = 5,
    CIMA_ESQUERDA = 6,
    BAIXO_DIREITA = 7,
    BAIXO_ESQUERDA = 8
} TipoAnimacao;

/**
 * @brief Representa as opcoes de dificuldade do jogo
 */

typedef enum {
    FACIL = 0, /**< Representação da dificuldade fácil */
    MEDIO = 1, /**< Representação da dificuldade média */
    DIFICIL = 2 /**< Representação da dificuldade difícil */
} DificuldadeJogo;

/**
 * @brief Representa as telas disponíveis no jogo
 */

typedef enum {
    MENU = 0, /**< Representação da tela menu */
    COMO_JOGAR = 1, /**< Representação da tela como jogar */
    HISTORICO = 2, /**< Representação da tela histórico */
    ESCOLHER_DIFICULDADE = 3, /**< Representação da tela de escolher a dificuldade */
    RECEPCAO = 4, /**< Representação da tela da recepção */
    COZINHA = 5, /**< Representação da tela da cozinha */
    VITORIA = 6, /**< Representação da tela de vitória */
    DERROTA = 7 /**< Representação da tela de derrota */
 } TelaAtual;