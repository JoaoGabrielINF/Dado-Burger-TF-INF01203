#include "render.h"

Texture2D fundo;
static Font fonte_jogo;
Texture2D recepcao;
Texture2D cozinha;
Texture2D jogador_frames;
void carregaAssets(void)
{
    jogador_frames = LoadTexture("assets/imagens/principal.png");
    recepcao = LoadTexture("assets/imagens/mapas/mapa_1.png");
    cozinha = LoadTexture("assets/imagens/mapas/mapa_2.png");
    fundo = LoadTexture("assets/imagens/Imagem_Fundo_Dado_Burger.png");
    fonte_jogo = GetFontDefault();
}

bool coloreSeColide(Rectangle rec, Vector2 pos_mouse)
{
    if (CheckCollisionPointRec(pos_mouse, rec))
    {
        DrawRectangleRec(rec, MAROON);
        return true;
    }
    return false;
}

void desenhaTextoCentralizado(Font fonte, const char *texto, Rectangle ret,
                              float tamanho, float espaco, Color cor)
{
    Vector2 t = MeasureTextEx(fonte, texto, tamanho, espaco);

    Vector2 pos = {
        ret.x + ret.width / 2 - (t.x / 2),
        ret.y + ret.height / 2 - (t.y / 2)};

    DrawTextEx(fonte, texto, pos, tamanho, espaco, cor);
}

/* Desenha texto com quebra de linha por palavras dentro de largura_maxima.
   Devolve o numero de linhas desenhadas. */
static int desenhaTextoQuebrado(Font fonte, const char *texto, float x, float y,
                                float tamanho, float espaco, float passo,
                                float largura_maxima, Color cor)
{
    char linha[256] = "";
    char palavra[64];
    char teste[256];
    int linhas = 0;
    const char *p = texto;

    while (*p != '\0')
    {
        /* le a proxima palavra */
        int n = 0;
        while (*p != ' ' && *p != '\0' && n < 63)
            palavra[n++] = *p++;
        palavra[n] = '\0';
        while (*p == ' ')
            p++;

        /* monta o teste: linha atual + palavra */
        if (linha[0] == '\0')
            snprintf(teste, sizeof(teste), "%.63s", palavra);
        else
            snprintf(teste, sizeof(teste), "%.190s %.63s", linha, palavra);

        if (linha[0] != '\0' &&
            MeasureTextEx(fonte, teste, tamanho, espaco).x > largura_maxima)
        {
            /* nao coube: desenha a linha atual e comeca outra com a palavra */
            DrawTextEx(fonte, linha, (Vector2){x, y + linhas * passo}, tamanho, espaco, cor);
            linhas++;
            snprintf(linha, sizeof(linha), "%.63s", palavra);
        }
        else
        {
            snprintf(linha, sizeof(linha), "%.255s", teste);
        }
    }

    if (linha[0] != '\0')
    {
        DrawTextEx(fonte, linha, (Vector2){x, y + linhas * passo}, tamanho, espaco, cor);
        linhas++;
    }
    return linhas;
}

void determinaDirecao(Jogador *jogador)
{
    int dx = 0;
    int dy = 0;

    if (IsKeyDown(KEY_W))
        dy -= 1;
    if (IsKeyDown(KEY_S))
        dy += 1;
    if (IsKeyDown(KEY_A))
        dx -= 1;
    if (IsKeyDown(KEY_D))
        dx += 1;

    // Só muda a direção da animação se o personagem estiver se movendo
    // (se dx == 0 && dy == 0, ele mantém a última direção olhando parado)
    if (dx != 0 || dy != 0)
    {
        jogador->andando = true;
        if (dy == -1 && dx == -1)
            jogador->animacao.tipo = CIMA_ESQUERDA; // WA
        else if (dy == -1 && dx == 1)
            jogador->animacao.tipo = CIMA_DIREITA; // WD
        else if (dy == 1 && dx == -1)
            jogador->animacao.tipo = BAIXO_ESQUERDA; // SA
        else if (dy == 1 && dx == 1)
            jogador->animacao.tipo = BAIXO_DIREITA; // SD
        else if (dy == -1)
            jogador->animacao.tipo = CIMA; // W
        else if (dy == 1)
            jogador->animacao.tipo = BAIXO; // S
        else if (dx == -1)
            jogador->animacao.tipo = ESQUERDA; // A
        else if (dx == 1)
            jogador->animacao.tipo = DIREITA; // D
    }
    else{
        jogador->andando = false;
    }

}
void desenhaJogador(Jogador *jogador)
{
    Rectangle retangulo_jogador = {
        jogador->posicao.x,
        jogador->posicao.y,
        TILE_SIZE * 2.5,
        TILE_SIZE * 2.5};

    jogador->hitbox = (Rectangle){retangulo_jogador.x, retangulo_jogador.y, retangulo_jogador.width / 1.8, retangulo_jogador.height * 2/3};
    DrawRectangleRec(jogador->hitbox, RED);

    Vector2 centro = {TILE_SIZE / 2, TILE_SIZE / 2};

    determinaDirecao(jogador);
    int comando = jogador->animacao.tipo;
    bool parado = !jogador->andando;
    switch (comando)
    {
    case DIREITA:
        if(parado){
            jogador->animacao.primeiro = 8;
            jogador->animacao.ultimo = 8;
        } else{
            jogador->animacao.primeiro = 9;
            jogador->animacao.ultimo = 11;
        }
        break;

    case ESQUERDA:
    if(parado){
            jogador->animacao.primeiro = 13;
            jogador->animacao.ultimo = 13;
        } else{
            jogador->animacao.primeiro = 13;
            jogador->animacao.ultimo = 15;
        }
        break;

    case CIMA:
    if(parado){
            jogador->animacao.primeiro = 1;
            jogador->animacao.ultimo = 1;
        } else{
            jogador->animacao.primeiro = 1;
            jogador->animacao.ultimo = 3;
        }
       
        break;

    case BAIXO:
    if(parado){
            jogador->animacao.primeiro = 5;
            jogador->animacao.ultimo = 5;
        } else{
            jogador->animacao.primeiro = 5;
            jogador->animacao.ultimo = 7;
        }
        
        break;

    case CIMA_DIREITA:
    if(parado){
            jogador->animacao.primeiro = 20;
            jogador->animacao.ultimo = 20;
        } else{
            jogador->animacao.primeiro = 17;
            jogador->animacao.ultimo = 19;
        }

        break;

    case CIMA_ESQUERDA:
    if(parado){
            jogador->animacao.primeiro = 21;
            jogador->animacao.ultimo = 21;
        } else{
            jogador->animacao.primeiro = 21;
            jogador->animacao.ultimo = 23;
        }
        
        break;

    case BAIXO_DIREITA:
        if(parado){
            jogador->animacao.primeiro = 25;
            jogador->animacao.ultimo = 25;
        } else{
            jogador->animacao.primeiro = 25;
            jogador->animacao.ultimo = 27;
        }
        
        break;

    case BAIXO_ESQUERDA:
    if(parado){
            jogador->animacao.primeiro = 29;
            jogador->animacao.ultimo = 29;
        } else{
            jogador->animacao.primeiro = 29;
            jogador->animacao.ultimo = 31;
        }
        
        break;
    
    default:
        break;
    }
    DrawTexturePro(jogador_frames, tamanho_frames(&jogador->animacao, 72, 72, 16),
                   retangulo_jogador, centro, 0.0f, WHITE);
}

void desenhaJogo(Jogo *jogo)
{

    // Declarar as constantes a serem usadas nos paineis do historico e como jogar
    float painel_margem_x = JANELA_LARGURA * 0.08f; /* ~102 px */
    float painel_margem_y = JANELA_ALTURA * 0.10f;  /* 72 px */

    Rectangle painel = {
        painel_margem_x,
        painel_margem_y,
        JANELA_LARGURA - 2.0f * painel_margem_x,
        JANELA_ALTURA - 2.0f * painel_margem_y};

    DrawRectangleRounded(painel, 0.08f, 16, LIME);

    /* Caixa de texto invisível, recuada dentro do painel */
    float painel_pad_x = painel.width * 0.06f;
    float painel_pad_y = painel.height * 0.08f;

    Rectangle painel_texto = {
        painel.x + painel_pad_x,
        painel.y + painel_pad_y,
        painel.width - 2.0f * painel_pad_x,
        painel.height - 2.0f * painel_pad_y};

    Rectangle painel_titulo = {
        painel_texto.x,
        painel_texto.y,
        painel_texto.width,
        painel_texto.height * 0.22f};

    Rectangle painel_corpo = {
        painel_texto.x,
        painel_texto.y + painel_titulo.height,
        painel_texto.width,
        painel_texto.height - painel_titulo.height};
    switch (jogo->tela_atual)
    {
    case MENU:

        DrawTexturePro(fundo,
                       (Rectangle){0, 0, (float)fundo.width, (float)fundo.height},
                       (Rectangle){0, 0, JANELA_LARGURA, JANELA_ALTURA},
                       (Vector2){0, 0}, 0.0f, WHITE);

        Rectangle botao_novo_jogo = {
            X_BOTAO_INICIO,
            (Y_BOTAO_INICIO - ALTURA_BOTAO_INICIO - ESPACAMENTO_BOTAO_INICIO),
            LARGURA_BOTAO_INICIO,
            ALTURA_BOTAO_INICIO};

        Rectangle botao_como_jogar = {
            X_BOTAO_INICIO,
            Y_BOTAO_INICIO,
            LARGURA_BOTAO_INICIO,
            ALTURA_BOTAO_INICIO};

        Rectangle botao_historico = {
            X_BOTAO_INICIO,
            (Y_BOTAO_INICIO + (ALTURA_BOTAO_INICIO + ESPACAMENTO_BOTAO_INICIO)),
            LARGURA_BOTAO_INICIO,
            ALTURA_BOTAO_INICIO};

        Rectangle display_inicio = {
            X_DISPLAY_INICIO,
            Y_DISPLAY_INICIO,
            LARGURA_DISPLAY_INICIO,
            ALTURA_DISPLAY_INICIO};

        DrawRectangleRec(display_inicio, GREEN);

        DrawRectangleRec(botao_novo_jogo, RED);
        if (coloreSeColide(botao_novo_jogo, GetMousePosition()) && IsMouseButtonPressed(0))
        {
            jogo->tela_atual = ESCOLHER_DIFICULDADE;
        }
        desenhaTextoCentralizado(fonte_jogo, "Novo Jogo", botao_novo_jogo, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);

        DrawRectangleRec(botao_como_jogar, RED);
        if (coloreSeColide(botao_como_jogar, GetMousePosition()) && IsMouseButtonPressed(0))
        {
            jogo->tela_atual = COMO_JOGAR;
        }
        desenhaTextoCentralizado(fonte_jogo, "Como Jogar", botao_como_jogar, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);

        DrawRectangleRec(botao_historico, RED);
        if (coloreSeColide(botao_historico, GetMousePosition()) && IsMouseButtonPressed(0))
        {
            jogo->tela_atual = HISTORICO;
        }
        desenhaTextoCentralizado(fonte_jogo, "Historico", botao_historico, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);

        break;

    case ESCOLHER_DIFICULDADE:
        DrawTexturePro(fundo,
                       (Rectangle){0, 0, (float)fundo.width, (float)fundo.height},
                       (Rectangle){0, 0, JANELA_LARGURA, JANELA_ALTURA},
                       (Vector2){0, 0}, 0.0f, WHITE);

        Rectangle botao_facil = {
            X_BOTAO_INICIO,
            (Y_BOTAO_INICIO - ALTURA_BOTAO_INICIO - ESPACAMENTO_BOTAO_INICIO),
            LARGURA_BOTAO_INICIO,
            ALTURA_BOTAO_INICIO};

        Rectangle botao_medio = {
            X_BOTAO_INICIO,
            Y_BOTAO_INICIO,
            LARGURA_BOTAO_INICIO,
            ALTURA_BOTAO_INICIO};

        Rectangle botao_dificil = {
            X_BOTAO_INICIO,
            (Y_BOTAO_INICIO + (ALTURA_BOTAO_INICIO + ESPACAMENTO_BOTAO_INICIO)),
            LARGURA_BOTAO_INICIO,
            ALTURA_BOTAO_INICIO};

        Rectangle display_dificuldade = {
            X_DISPLAY_INICIO,
            Y_DISPLAY_INICIO,
            LARGURA_DISPLAY_INICIO,
            ALTURA_DISPLAY_INICIO};

        DrawRectangleRec(display_dificuldade, GREEN);

        DrawRectangleRec(botao_facil, RED);
        if (coloreSeColide(botao_facil, GetMousePosition()) && IsMouseButtonPressed(0))
        {
            jogo->tela_atual = RECEPCAO;
            jogo->dificuldade = FACIL;
        }
        desenhaTextoCentralizado(fonte_jogo, "Facil", botao_facil, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);

        DrawRectangleRec(botao_medio, RED);
        if (coloreSeColide(botao_medio, GetMousePosition()) && IsMouseButtonPressed(0))
        {
            jogo->tela_atual = RECEPCAO;
            jogo->dificuldade = MEDIO;
        }
        desenhaTextoCentralizado(fonte_jogo, "Medio", botao_medio, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);

        DrawRectangleRec(botao_dificil, RED);
        if (coloreSeColide(botao_dificil, GetMousePosition()) && IsMouseButtonPressed(0))
        {
            jogo->tela_atual = RECEPCAO;
            jogo->dificuldade = DIFICIL;
        }
        desenhaTextoCentralizado(fonte_jogo, "Dificil", botao_dificil, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);

        break;

    case COMO_JOGAR:
        DrawRectangle(0, 0, JANELA_LARGURA, JANELA_ALTURA, ORANGE);
        DrawRectangleRounded(painel, 0.08f, 16, LIME);
        desenhaTextoCentralizado(fonte_jogo, "Como Jogar", painel_titulo,
                                 TAMANHO_FONTE_TITULO, ESPACO_FONTE, BLACK);

        // Desenha o texto de "Como jogar"

        static const char *titulos[3] = {"Controles", "Ingredientes", "Regras"};

        static const char *col_controles[] = {
            "WASD: andar pela cozinha.",
            "E: interagir (fogao, tabua, bancada, estoque, prato).",
            "Andar e consultar nao gastam turno.",
            "Gastam 1 turno: preparar um ingrediente, adicionar ao hamburguer e remover o topo.",
            NULL};

        static const char *col_ingredientes[] = {
            "Ilimitados (sem preparo): pao z, ketchup k, mostarda m, picles p, alface a.",
            "Perenes (preparar e guardar): suico s, cheddar q, cebola c, tomate t.",
            "Pereciveis (vencem em turnos): carne n, ovo frito o, bacon b.",
            "Vencido e descartado sozinho.",
            NULL};

        static const char *col_regras[] = {
            "Atenda o cliente da frente.",
            "Monte na ordem do pedido, de baixo para cima.",
            "O pao de baixo ja esta no prato.",
            "Feche com o pao de cima (z).",
            "So a paciencia do primeiro da fila diminui a cada turno.",
            "Vitoria: atender todos.",
            "Derrota: paciencia zerada.",
            NULL};

        static const char **colunas[3] = {col_controles, col_ingredientes, col_regras};

        float gap = painel_corpo.width * 0.03f;
        float largura_coluna = (painel_corpo.width - 2.0f * gap) / 3.0f;
        float tam = TAMANHO_FONTE_TEXTO * 0.85f;
        float passo = tam * ESPACAMENTO_LINHA;

        for (int c = 0; c < 3; c++)
        {
            float col_x = painel_corpo.x + c * (largura_coluna + gap);

            /* titulo da coluna, um pouco acima do corpo */
            DrawTextEx(fonte_jogo, titulos[c],
                       (Vector2){col_x, painel_corpo.y - tam * 0.6f},
                       tam * 1.2f, ESPACO_FONTE, WHITE);

            float y = painel_corpo.y + passo; /* y da proxima linha */

            for (int i = 0; colunas[c][i] != NULL; i++)
            {
                int usadas = desenhaTextoQuebrado(fonte_jogo, colunas[c][i],
                                                  col_x, y, tam, ESPACO_FONTE, passo,
                                                  largura_coluna, BLACK);
                y += usadas * passo;
            }
        }
        break;

    case HISTORICO:
        DrawRectangle(0, 0, JANELA_LARGURA, JANELA_ALTURA, ORANGE);
        DrawRectangleRounded(painel, 0.08f, 16, LIME);
        DrawRectangleRec(painel_corpo, ORANGE);
        DrawRectangleLinesEx(painel_corpo, 2.0f, BLACK);

        desenhaTextoCentralizado(fonte_jogo, "HISTORICO", painel_titulo,
                                 TAMANHO_FONTE_TITULO, ESPACO_FONTE, BLACK);
        /* conteudo usa painel_corpo */

        // Retangulos de baixo
        Rectangle botao_inferior_volta_tudo = {
            painel_corpo.x,
            painel_corpo.y + (painel_corpo.height * 0.9),
            painel_corpo.width * 0.11,
            painel_corpo.height * 0.1

        };
        Rectangle botao_inferior_anterior = {
            painel_corpo.x + botao_inferior_volta_tudo.width,
            painel_corpo.y + (painel_corpo.height * 0.9),
            painel_corpo.width * 0.39,
            painel_corpo.height * 0.1};
        Rectangle botao_inferior_proximo = {
            painel_corpo.x + botao_inferior_anterior.width + botao_inferior_volta_tudo.width,
            painel_corpo.y + (painel_corpo.height * 0.9),
            painel_corpo.width * 0.39,
            painel_corpo.height * 0.1

        };
        Rectangle botao_inferior_vai_tudo = {
            painel_corpo.x + botao_inferior_proximo.width + botao_inferior_anterior.width + botao_inferior_volta_tudo.width,
            painel_corpo.y + (painel_corpo.height * 0.9),
            painel_corpo.width * 0.11,
            painel_corpo.height * 0.1

        };

        DrawRectangleRec(botao_inferior_volta_tudo, GRAY);
        DrawRectangleLinesEx(botao_inferior_volta_tudo, 2.0f, BLACK);
        desenhaTextoCentralizado(fonte_jogo, "<<<", botao_inferior_volta_tudo, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
        DrawRectangleRec(botao_inferior_anterior, GRAY);
        DrawRectangleLinesEx(botao_inferior_anterior, 2.0f, BLACK);
        desenhaTextoCentralizado(fonte_jogo, "Anterior", botao_inferior_anterior, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
        DrawRectangleRec(botao_inferior_proximo, GRAY);
        DrawRectangleLinesEx(botao_inferior_proximo, 2.0f, BLACK);
        desenhaTextoCentralizado(fonte_jogo, "Proximo", botao_inferior_proximo, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
        DrawRectangleRec(botao_inferior_vai_tudo, GRAY);
        DrawRectangleLinesEx(botao_inferior_vai_tudo, 2.0f, BLACK);
        desenhaTextoCentralizado(fonte_jogo, ">>>", botao_inferior_vai_tudo, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);

        // Retangulos de cima

        Rectangle retangulo_superior_nome = {
            painel_corpo.x,
            painel_corpo.y,
            painel_corpo.width * 0.50,
            painel_corpo.height * 0.1};
        Rectangle retangulo_superior_pontuacao = {
            painel_corpo.x + retangulo_superior_nome.width,
            painel_corpo.y,
            painel_corpo.width * 0.50,
            painel_corpo.height * 0.1

        };

        DrawRectangleRec(retangulo_superior_nome, GRAY);
        DrawRectangleLinesEx(retangulo_superior_nome, 2.0f, BLACK);
        desenhaTextoCentralizado(fonte_jogo, "NOME", retangulo_superior_nome, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
        DrawRectangleRec(retangulo_superior_pontuacao, GRAY);
        DrawRectangleLinesEx(retangulo_superior_pontuacao, 2.0f, BLACK);
        desenhaTextoCentralizado(fonte_jogo, "PONTUAÇÃO", retangulo_superior_pontuacao, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);

        // Retangulos nome e retangulos pontuacao - 8 nomes cada coluna
        int numero_linhas = 8;
        for (int i = 1; i <= numero_linhas; i++)
        {
            float retangulo_nome_pontos_altura = 0.1 * painel_corpo.height;
            Rectangle retangulo_nome = {
                painel_corpo.x,
                painel_corpo.y + i * retangulo_nome_pontos_altura,
                painel_corpo.width * 0.5,
                painel_corpo.height * 0.1};

            Rectangle retangulo_pontos = {
                painel_corpo.x + retangulo_nome.width,
                painel_corpo.y + i * retangulo_nome_pontos_altura,
                painel_corpo.width * 0.5,
                painel_corpo.height * 0.1};

            DrawRectangleRec(retangulo_nome, WHITE);
            DrawRectangleLinesEx(retangulo_nome, 2.0f, BLACK);
            desenhaTextoCentralizado(fonte_jogo, "nome de teste", retangulo_nome, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
            DrawRectangleRec(retangulo_pontos, WHITE);
            desenhaTextoCentralizado(fonte_jogo, "67", retangulo_pontos, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
            DrawRectangleLinesEx(retangulo_pontos, 2.0f, BLACK);
        }

        break;
    case RECEPCAO:
        Rectangle origem = {0, 0, (float)recepcao.width, (float)recepcao.height};
        Rectangle destino = {0, 0, JANELA_LARGURA, JANELA_ALTURA}; /* 1280x720 */
        DrawTexturePro(recepcao, origem, destino, (Vector2){0, 0}, 0.0f, WHITE);
        desenhaJogador(&jogo->jogador);
        atualiza_anim_entidades(jogo);

        break;

    case COZINHA:
        Rectangle origem_2 = {0, 0, (float)recepcao.width, (float)recepcao.height};
        Rectangle destino_2 = {0, 0, JANELA_LARGURA, JANELA_ALTURA}; /* 1280x720 */
        DrawTexturePro(cozinha, origem_2, destino_2, (Vector2){0, 0}, 0.0f, WHITE);
    default:
        break;
    }
}

void descarregaAssets(void)
{
    UnloadTexture(fundo);
}