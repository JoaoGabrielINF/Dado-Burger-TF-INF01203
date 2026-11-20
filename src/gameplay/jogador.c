#include "jogador.h"
#include <math.h>
#include "raylib.h"

/**
 * @brief Retorna a regiao solida (em pixels) de um tile do mapa.
 *        '#' colide com o tile inteiro; 'M' (mesa) colide apenas com a faixa
 *        superior do tile; demais simbolos nao colidem.
 * @param[in] tile Simbolo do tile
 * @param[in] linha Linha do tile na matriz
 * @param[in] coluna Coluna do tile na matriz
 * @return Retangulo solido do tile (largura 0 = sem colisao)
 */
static Rectangle regiao_solida_tile(char tile, int linha, int coluna)
{
    switch (tile) {
    case BLOQUEADO_SIMBOLO:
        return (Rectangle){coluna * TILE_SIZE, linha * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    case MESA_SIMBOLO:
        return (Rectangle){coluna * TILE_SIZE, linha * TILE_SIZE, TILE_SIZE, ALTURA_COLISAO_MESA};
    case MESA_LATERAL_SIMBOLO:
        /* balcao vertical: a faixa solida corre pela lateral esquerda do tile */
        return (Rectangle){coluna * TILE_SIZE, linha * TILE_SIZE, ALTURA_COLISAO_MESA, TILE_SIZE};
    case PAREDE_RODAPE_SIMBOLO:
        /* parede baixa vista de cima: faixa fina colada no rodape do tile */
        return (Rectangle){coluna * TILE_SIZE, linha * TILE_SIZE + TILE_SIZE - ALTURA_COLISAO_RODAPE,
                           TILE_SIZE, ALTURA_COLISAO_RODAPE};
    default:
        return (Rectangle){0.0f, 0.0f, 0.0f, 0.0f};
    }
}

/**
 * @brief Verifica se um retângulo em pixels sobrepõe a região sólida de algum
 *        tile do mapa, ou fica fora dos limites da matriz
 * @param[in] jogo Estado do jogo contendo o mapa
 * @param[in] r Retângulo testado
 * @return true se o retângulo colide com o mapa
 * @return false caso o retângulo esteja inteiramente sobre área livre
 */
static bool colide_mapa(const Jogo *jogo, Rectangle r)
{
    if (r.x < 0.0f || r.y < 0.0f ||
        r.x + r.width > MAPA_COLUNAS * TILE_SIZE ||
        r.y + r.height > MAPA_LINHAS * TILE_SIZE)
        return true; /* fora da matriz conta como parede */

    int coluna0 = (int)(r.x / TILE_SIZE);
    int coluna1 = (int)((r.x + r.width) / TILE_SIZE);
    int linha0 = (int)(r.y / TILE_SIZE);
    int linha1 = (int)((r.y + r.height) / TILE_SIZE);

    for (int linha = linha0; linha <= linha1; linha++) {
        for (int coluna = coluna0; coluna <= coluna1; coluna++) {
            Rectangle solido = regiao_solida_tile(jogo->mapa.tiles[linha][coluna], linha, coluna);
            if (solido.width > 0.0f && CheckCollisionRecs(r, solido))
                return true;
        }
    }
    return false;
}

void atualiza_hitbox_jogador(Jogador *jogador)
{
    /* o frame de 72x72 é desenhado num retângulo de TILE_SIZE*2.5 deslocado
       pela origem do DrawTexturePro (TILE_SIZE/2): a hitbox segue o mesmo
       deslocamento e cobre a bounding box real do personagem na imagem */
    const float lado_desenho = TILE_SIZE * 2.5f;
    const float escala = lado_desenho / 72.0f;
    const float sprite_x = jogador->posicao.x - TILE_SIZE / 2.0f;
    const float sprite_y = jogador->posicao.y - TILE_SIZE / 2.0f;

    jogador->hitbox = (Rectangle){
        sprite_x + PERSONAGEM_X0_NO_FRAME * escala,
        sprite_y + PERSONAGEM_Y0_NO_FRAME * escala,
        (PERSONAGEM_X1_NO_FRAME - PERSONAGEM_X0_NO_FRAME + 1.0f) * escala,
        (PERSONAGEM_Y1_NO_FRAME - PERSONAGEM_Y0_NO_FRAME + 1.0f) * escala};
}

void atualiza_jogador(Jogo *jogo)
{
    Jogador *jogador = &jogo->jogador;

    float dx = 0.0f;
    float dy = 0.0f;
    if (IsKeyDown(KEY_W)) dy -= 1.0f;
    if (IsKeyDown(KEY_S)) dy += 1.0f;
    if (IsKeyDown(KEY_A)) dx -= 1.0f;
    if (IsKeyDown(KEY_D)) dx += 1.0f;

    if (dx == 0.0f && dy == 0.0f)
        return;

    /* normaliza diagonais para andar na mesma velocidade em qualquer direção */
    float modulo = sqrtf(dx * dx + dy * dy);
    dx /= modulo;
    dy /= modulo;

    float velocidade = (jogador->velocidade > 0.0f) ? jogador->velocidade : VELOCIDADE_JOGADOR;
    float passo = velocidade * GetFrameTime();

    atualiza_hitbox_jogador(jogador);

    /* move um eixo por vez: ao encostar na parede num eixo, o jogador
       continua deslizando no outro */
    Rectangle teste = jogador->hitbox;
    teste.x += dx * passo;
    if (!colide_mapa(jogo, teste))
        jogador->posicao.x += dx * passo;

    teste = jogador->hitbox;
    teste.y += dy * passo;
    if (!colide_mapa(jogo, teste))
        jogador->posicao.y += dy * passo;

    /* o tile atual passa a ser o tile sobre o centro da hitbox */
    atualiza_hitbox_jogador(jogador);
    jogador->tile_atual.coluna = (int)((jogador->hitbox.x + jogador->hitbox.width / 2.0f) / TILE_SIZE);
    jogador->tile_atual.linha = (int)((jogador->hitbox.y + jogador->hitbox.height / 2.0f) / TILE_SIZE);
}
