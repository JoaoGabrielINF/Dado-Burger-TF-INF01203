

/** Numero de linhas da matriz do mapa */
#define MAPA_LINHAS 30
/** Numero de colunas da matriz do mapa */
#define MAPA_COLUNAS 30

/** Tamanho de cada tile em pixels */
#define TILE_SIZE 30

/** Altura reservada para a HUD em pixels */
#define HUD_ALTURA 80

/** Largura total da janela em pixels */
#define JANELA_LARGURA (MAPA_COLUNAS * TILE_SIZE)

/** Altura total da janela em pixels incluindo a HUD */
#define JANELA_ALTURA (MAPA_LINHAS * TILE_SIZE + HUD_ALTURA)

/** Paciencia maxima medida em turnos dos clientes no modo fácil */
#define PACIENCIA_MAXIMA_FACIL 20

/** Paciencia maxima medida em turnos dos clientes no modo médio */
#define PACIENCIA_MAXIMA_MEDIO 15

/** Paciencia maxima medida em turnos dos clientes no modo difícil */
#define PACIENCIA_MAXIMA_DIFICIL 12

/** Validade dos produtos perecíveis medida em turnos */
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

/** Definição de tempos */
#define TURNOS_COZIMENTO 3 

/**
 * @brief Representa qual o equipamento utilizado na cozinha
 */

typedef enum {
    FOGAO = 0,
    TABUA = 1,
    BANCADA = 2
} MateriaisCozinha;

/**
 * @brief Representa a ação atual do jogador na animação 
 */

typedef enum {
    PARADO = 0, /**< Animação da entidade parada */
    ANDANDO_DIREITA = 1, /**< Animação da entidade andando para a direita */
    ANDANDO_ESQUERDA = 2,
    ANDANDO_CIMA = 3, /**< Animação da entidade andando para a esquerda */
    ANDANDO_BAIXO = 4
} TipoAnimacao;

/**
 * @brief Representa as opcoes de dificuldade do jogo
 */

typedef enum {
    FACIL = 0,
    MEDIO = 1,
    DIFICIL = 2
} DificuldadeJogo;

/**
 * @brief Representa as telas disponíveis no jogo
 */

typedef enum {
    MENU = 0,
    COMO_JOGAR = 1,
    HISTORICO = 2,
    ESCOLHER_DIFICULDADE = 3,
    RECEPCAO = 4,
    COZINHA = 5,
    VITORIA = 6,
    DERROTA = 7
 } TelaAtual;