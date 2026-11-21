#include <math.h>
#include "core/models.h"
#include "presentation/render.h"
#include "io/mapa_io.h"
#include "presentation/mapa.h"
#include "gameplay/jogador.h"

static void carrega_estruturas_da_tela(Jogo *jogo)
{
    switch (jogo->tela_atual)
    {
    case RECEPCAO:
        carrega_estruturas_mapa(jogo->mapa[MAPA_RECEPCAO].tiles, jogo);
        break;
    case COZINHA:
        carrega_estruturas_mapa(jogo->mapa[MAPA_COZINHA].tiles, jogo);
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Uso: %s <pedidos> <historico>\n", argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1], "r"); // abre o arquivo de pedidos
    FILE *fh = fopen(argv[2], "r"); // abre o arquivo de histórico

    Jogo meu_jogo = {0};
    if (!carregar_mapa("dados/tela_jogo_saguao.txt", meu_jogo.mapa[MAPA_RECEPCAO].tiles))
    {
        return 1;
    }
    if (!carregar_mapa("dados/tela_jogo_cozinha.txt", meu_jogo.mapa[MAPA_COZINHA].tiles))
    {
        return 1;
    }

    carrega_estruturas_mapa(meu_jogo.mapa[MAPA_RECEPCAO].tiles, &meu_jogo);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(JANELA_LARGURA, JANELA_ALTURA, "Dado Burger");
    SetWindowMinSize(JANELA_LARGURA / 2, JANELA_ALTURA / 2);
    SetTargetFPS(60);

    RenderTexture2D alvo = LoadRenderTexture(JANELA_LARGURA, JANELA_ALTURA);
    SetTextureFilter(alvo.texture, TEXTURE_FILTER_BILINEAR);

    meu_jogo.tela_atual = MENU;

    carregaAssets();
    animacao_inicializar(&meu_jogo.jogador.animacao);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        /* escala e offset da janela real */
        float escala = fminf((float)GetScreenWidth() / JANELA_LARGURA,
                             (float)GetScreenHeight() / JANELA_ALTURA);
        float w = JANELA_LARGURA * escala;
        float h = JANELA_ALTURA * escala;
        float off_x = (GetScreenWidth() - w) / 2;
        float off_y = (GetScreenHeight() - h) / 2;

        /* mouse passa a devolver coordenadas lógicas */
        SetMouseOffset((int)-off_x, (int)-off_y);
        SetMouseScale(1.0f / escala, 1.0f / escala);

        /* movimentação do jogador (com colisão contra o mapa) nas telas jogáveis */
        if (meu_jogo.tela_atual == RECEPCAO || meu_jogo.tela_atual == COZINHA)
        {
            atualiza_jogador(&meu_jogo);
        }

        /* 1. desenha tudo na textura lógica */
        TelaAtual tela_anterior = meu_jogo.tela_atual;
        BeginTextureMode(alvo);
        ClearBackground(RAYWHITE);
        desenhaJogo(&meu_jogo);
        EndTextureMode();
        if (meu_jogo.tela_atual != tela_anterior)
            carrega_estruturas_da_tela(&meu_jogo);

        /* 2. apresenta escalada, mantendo proporção */
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(alvo.texture,
                       (Rectangle){0, 0, (float)alvo.texture.width, -(float)alvo.texture.height},
                       (Rectangle){off_x, off_y, w, h},
                       (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    descarregaAssets();
    UnloadRenderTexture(alvo);
    CloseWindow();
    return 0;
}