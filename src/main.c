#include <math.h>
#include "core/models.h"
#include "render/render.h"

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(JANELA_LARGURA, JANELA_ALTURA, "Dado Burger");
    SetWindowMinSize(JANELA_LARGURA / 2, JANELA_ALTURA / 2);
    SetTargetFPS(60);

    RenderTexture2D alvo = LoadRenderTexture(JANELA_LARGURA, JANELA_ALTURA);
    SetTextureFilter(alvo.texture, TEXTURE_FILTER_BILINEAR);

    /* botão em coordenadas LÓGICAS */

    Jogo meu_jogo;
    meu_jogo.telaAtual = MENU;

    carregaAssets();

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11)) ToggleFullscreen();

        /* escala e offset da janela real */
        float escala = fminf((float)GetScreenWidth()  / JANELA_LARGURA,
                             (float)GetScreenHeight() / JANELA_ALTURA);
        float w = JANELA_LARGURA * escala;
        float h = JANELA_ALTURA  * escala;
        float offX = (GetScreenWidth()  - w) / 2;
        float offY = (GetScreenHeight() - h) / 2;

        /* mouse passa a devolver coordenadas lógicas */
        SetMouseOffset((int)-offX, (int)-offY);
        SetMouseScale(1.0f / escala, 1.0f / escala);


        /* 1. desenha tudo na textura lógica */
        BeginTextureMode(alvo);
            ClearBackground(RAYWHITE);
            desenhaJogo(&meu_jogo);
        EndTextureMode();

        /* 2. apresenta escalada, mantendo proporção */
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(alvo.texture,
                (Rectangle){0, 0, (float)alvo.texture.width, -(float)alvo.texture.height},
                (Rectangle){offX, offY, w, h},
                (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    descarregaAssets();
    UnloadRenderTexture(alvo);
    CloseWindow();
    return 0;
}