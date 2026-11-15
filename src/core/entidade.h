#include "constants.h"

/**
  * @brief Posicao discreta no mapa baseada em linha e coluna
  */

 typedef struct {
    int linha; /**<Indice da linha no grid do mapa */
    int coluna; /**<Indice da coluna no grid do mapa */
 } TileAtual;

 /**
 * @brief Elementos necessários para realizar a animação das entidades
 */
 typedef struct  {
    int primeiro; /**<Primeiro frame */
    int ultimo; /**<Ultimo frame*/
    int atual; /**<Frame atual*/
    float velocidade; /**<Velocidade de mudança do frame */
    float duracaoRestante; /**<Duração restante do frame atual */
    TipoAnimacao tipo; /** <Ação e direção atual da animação */
    int passo; /**<Numero de frames que são pulados por iteração */
} Animacao;