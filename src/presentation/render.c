#include "render.h"
#include "../gameplay/jogador.h"
#include "../core/dados.h"
#include "../core/sort/sort.h"
#include "../core/time/time.h"
#include "../core/metricas.h"
#include "../io/medicoes.h"
#include <stdio.h>

Texture2D fundo;
static Font fonte_jogo;
Texture2D recepcao;
Texture2D cozinha;
Texture2D jogador_frames;
Texture2D parede_baixo;
Texture2D bancada_normal;
Texture2D bancada_tabua;
Texture2D fogao;
Texture2D mochila;
static bool estoque_aberto;
static int pagina_estoque;
enum { NUMERO_ALIMENTOS_ESTOQUE = 12 };
static const char *const caminhos_alimentos_estoque[NUMERO_ALIMENTOS_ESTOQUE] = {
    "assets/imagens/ingredientes/pao_cima.png",
    "assets/imagens/ingredientes/ketchup.png",
    "assets/imagens/ingredientes/mostarda.png",
    "assets/imagens/ingredientes/picles.png",
    "assets/imagens/ingredientes/alface.png",
    "assets/imagens/ingredientes/queijo_suico.png",
    "assets/imagens/ingredientes/queijo_cheddar.png",
    "assets/imagens/ingredientes/cebola.png",
    "assets/imagens/ingredientes/tomate.png",
    "assets/imagens/ingredientes/carne.png",
    "assets/imagens/ingredientes/ovo_frito.png",
    "assets/imagens/ingredientes/bacon.png"
};
static const char *const nomes_alimentos_estoque[NUMERO_ALIMENTOS_ESTOQUE] = {
    "Pao de cima",
    "Ketchup",
    "Mostarda",
    "Picles",
    "Alface",
    "Queijo suico",
    "Queijo cheddar",
    "Cebola",
    "Tomate",
    "Carne",
    "Ovo frito",
    "Bacon"
};
static Texture2D texturas_alimentos_estoque[NUMERO_ALIMENTOS_ESTOQUE];

void carregaAssets(void)
{
    jogador_frames = LoadTexture("assets/imagens/principal.png");
    recepcao = LoadTexture("assets/imagens/mapas/mapa_1.png");
    cozinha = LoadTexture("assets/imagens/mapas/mapa_2.png");
    fundo = LoadTexture("assets/imagens/Imagem_Fundo_Dado_Burger.png");
    parede_baixo = LoadTexture("assets/imagens/mapas/parede_baixo_mapa_2.png");
    fonte_jogo = GetFontDefault();
    bancada_normal = LoadTexture("assets/imagens/cozinha/bancada.png");
    fogao = LoadTexture("assets/imagens/cozinha/fogao.png");
    bancada_tabua = LoadTexture("assets/imagens/cozinha/bancada_tabua.png");
    mochila = LoadTexture("assets/imagens/mochila.png");
    for (int i = 0; i < NUMERO_ALIMENTOS_ESTOQUE; i++) {
        texturas_alimentos_estoque[i] = LoadTexture(caminhos_alimentos_estoque[i]);
    }
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

static const char *nomeIngrediente(char ingrediente)
{
    switch (ingrediente)
    {
    case PAO_SIMBOLO: return "Pao de cima";
    case KETCHUP_SIMBOLO: return "Ketchup";
    case MOSTARDA_SIMBOLO: return "Mostarda";
    case PICLES_SIMBOLO: return "Picles";
    case ALFACE_SIMBOLO: return "Alface";
    case QUEIJO_SUICO_SIMBOLO: return "Queijo suico";
    case QUEIJO_CHEDDAR_SIMBOLO: return "Queijo cheddar";
    case CEBOLA_SIMBOLO: return "Cebola";
    case TOMATE_SIMBOLO: return "Tomate";
    case CARNE_SIMBOLO: return "Carne";
    case OVO_FRITO_SIMBOLO: return "Ovo frito";
    case BACON_SIMBOLO: return "Bacon";
    default: return "Ingrediente desconhecido";
    }
}

void desenhaComanda(const ListaReceita *receita)
{
    const float margem = 16.0f;
    const float largura = 240.0f;
    const float altura_cabecalho = 48.0f;
    const float altura_linha = 26.0f;
    int quantidade = 0;

    for (NodoLista *nodo = receita->ini; nodo != NULL; nodo = nodo->prox)
        quantidade++;

    float altura = altura_cabecalho + (quantidade > 0 ? quantidade : 1) * altura_linha;
    Rectangle comanda = {
        margem,
        JANELA_ALTURA - margem - altura,
        largura,
        altura
    };

    DrawRectangleRec(comanda, RAYWHITE);
    DrawRectangleLinesEx(comanda, 2.0f, DARKGRAY);
    DrawTextEx(fonte_jogo, "Comanda", (Vector2){comanda.x + 12.0f, comanda.y + 8.0f},
               22.0f, ESPACO_FONTE, BLACK);

    if (receita->ini == NULL)
    {
        DrawTextEx(fonte_jogo, "Aguardando pedido",
                   (Vector2){comanda.x + 12.0f, comanda.y + altura_cabecalho},
                   18.0f, ESPACO_FONTE, DARKGRAY);
        return;
    }

    int linha = 0;
    for (NodoLista *nodo = receita->ini; nodo != NULL; nodo = nodo->prox)
    {
        DrawTextEx(fonte_jogo, nomeIngrediente(nodo->ingrediente),
                   (Vector2){comanda.x + 12.0f, comanda.y + altura_cabecalho + linha * altura_linha},
                   18.0f, ESPACO_FONTE, BLACK);
        linha++;
    }
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

    atualiza_hitbox_jogador(jogador); /* hitbox encaixa no desenho do personagem */

    Vector2 centro = {TILE_SIZE / 2, TILE_SIZE / 2};

    determinaDirecao(jogador);
    int comando = jogador->animacao.tipo;
    bool parado = !jogador->andando;
    /* Frames do sprite sheet (principal.png, 72x72, 16 colunas x 2 linhas):
       Direção        | Parado | Andando
       CIMA           |   0    |  1-3
       BAIXO          |   4    |  5-7
       DIREITA        |   8    |  9-11
       ESQUERDA       |  12    | 13-15
       CIMA_DIREITA   |   8    | 17-19  (o frame 20 do sheet e um perfil p/ esquerda)
       CIMA_ESQUERDA  |  22    | 21-23
       BAIXO_DIREITA  |  24    | 25-27
       BAIXO_ESQUERDA |  28    | 29-31
       Os frames de "parado" foram conferidos um a um na imagem: antes, as
       diagonais e a esquerda usavam frames de passada como parado e o
       personagem parecia travar no meio do passo ao soltar a tecla. */
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
            jogador->animacao.primeiro = 12;
            jogador->animacao.ultimo = 12;
        } else{
            jogador->animacao.primeiro = 13;
            jogador->animacao.ultimo = 15;
        }
        break;

    case CIMA:
    if(parado){
            jogador->animacao.primeiro = 0;
            jogador->animacao.ultimo = 0;
        } else{
            jogador->animacao.primeiro = 1;
            jogador->animacao.ultimo = 3;
        }
       
        break;

    case BAIXO:
    if(parado){
            jogador->animacao.primeiro = 4;
            jogador->animacao.ultimo = 4;
        } else{
            jogador->animacao.primeiro = 5;
            jogador->animacao.ultimo = 7;
        }
        
        break;

    case CIMA_DIREITA:
    if(parado){
            /* o frame 20 original do sheet e um perfil olhando p/ ESQUERDA;
               usa o parado de perfil direito (frame 8) no lugar */
            jogador->animacao.primeiro = 8;
            jogador->animacao.ultimo = 8;
        } else{
            jogador->animacao.primeiro = 17;
            jogador->animacao.ultimo = 19;
        }

        break;

    case CIMA_ESQUERDA:
    if(parado){
            jogador->animacao.primeiro = 22;
            jogador->animacao.ultimo = 22;
        } else{
            jogador->animacao.primeiro = 21;
            jogador->animacao.ultimo = 23;
        }
        
        break;

    case BAIXO_DIREITA:
        if(parado){
            jogador->animacao.primeiro = 24;
            jogador->animacao.ultimo = 24;
        } else{
            jogador->animacao.primeiro = 25;
            jogador->animacao.ultimo = 27;
        }
        
        break;

    case BAIXO_ESQUERDA:
    if(parado){
            jogador->animacao.primeiro = 28;
            jogador->animacao.ultimo = 28;
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

void desenhaEquipamentos(const Jogo * jogo){
    int equipamento_destacado = -1;
    for (int i = 0; i < NUMERO_EQUIPAMENTOS; i++) {
        if (CheckCollisionRecs(jogo->jogador.hitbox, jogo->equipamentos[i].hitbox)) {
            equipamento_destacado = i;
            break;
        }
    }

    if (equipamento_destacado >= 0 && IsKeyPressed(KEY_E)) {
        /* TODO: abrir a mochila do equipamento destacado. */
    }

    Color tinta_destaque = {255, 210, 210, 255};
    Rectangle retangulo_fogao = {
        jogo->equipamentos[FOGAO].posicao_pixels.x,
        jogo->equipamentos[FOGAO].posicao_pixels.y,
        TILE_SIZE * 2.0f,
        TILE_SIZE * 2.0f
    };
    DrawTexturePro(fogao,
                   (Rectangle){0, 0, (float)fogao.width, (float)fogao.height},
                   retangulo_fogao, (Vector2){0, 0}, 0.0f,
                   equipamento_destacado == FOGAO ? tinta_destaque : WHITE);

    Rectangle retangulo_tabua = {
        jogo->equipamentos[TABUA].posicao_pixels.x,
        jogo->equipamentos[TABUA].posicao_pixels.y,
        TILE_SIZE * 2.0f,
        TILE_SIZE * 2.0f
    };
    DrawTexturePro(bancada_tabua,
                   (Rectangle){0, 0, (float)bancada_tabua.width, (float)bancada_tabua.height},
                   retangulo_tabua, (Vector2){0, 0}, 0.0f,
                   equipamento_destacado == TABUA ? tinta_destaque : WHITE);

    Rectangle retangulo_bancada = {
        jogo->equipamentos[BANCADA].posicao_pixels.x,
        jogo->equipamentos[BANCADA].posicao_pixels.y,
        TILE_SIZE * 2.0f,
        TILE_SIZE
    };
    DrawTexturePro(bancada_normal,
                   (Rectangle){0, 0, (float)bancada_normal.width, (float)bancada_normal.height},
                   retangulo_bancada, (Vector2){0, 0}, 0.0f,
                   equipamento_destacado == BANCADA ? tinta_destaque : WHITE);
}

void desenha_alimentos_no_estoque(Rectangle retangulo_estoque)
{
    const float margem = 16.0f;
    const float largura_barra = 20.0f;
    const float espaco_barra = 12.0f;
    const float altura_alimento = 64.0f;
    const float espaco_alimento = 8.0f;
    const float largura_alimento =
        retangulo_estoque.width - 2.0f * margem - largura_barra - espaco_barra;
    const float x_alimentos = retangulo_estoque.x + margem;
    const float x_barra = retangulo_estoque.x + retangulo_estoque.width -
                          margem - largura_barra;
    const float altura_botao = 24.0f;
    const float espaco_controle = 8.0f;
    Rectangle botao_cima = {
        x_barra, retangulo_estoque.y + margem, largura_barra, altura_botao};
    Rectangle botao_baixo = {
        x_barra,
        retangulo_estoque.y + retangulo_estoque.height - margem - altura_botao,
        largura_barra,
        altura_botao
    };
    Rectangle trilho = {
        x_barra,
        botao_cima.y + botao_cima.height + espaco_controle,
        largura_barra,
        botao_baixo.y - espaco_controle -
            (botao_cima.y + botao_cima.height + espaco_controle)
    };
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(0)) {
        if (CheckCollisionPointRec(mouse, botao_cima)) {
            pagina_estoque = 0;
        } else if (CheckCollisionPointRec(mouse, botao_baixo)) {
            pagina_estoque = 1;
        } else if (CheckCollisionPointRec(mouse, trilho)) {
            pagina_estoque = mouse.y < trilho.y + trilho.height / 2.0f ? 0 : 1;
        }
    }

    const int quantidade_alimentos = pagina_estoque == 0 ? 7 : 5;
    const float altura_lista =
        quantidade_alimentos * altura_alimento +
        (quantidade_alimentos - 1) * espaco_alimento;
    const float y_alimentos = retangulo_estoque.y +
                              (retangulo_estoque.height - altura_lista) / 2.0f;
    const float altura_indicador = 64.0f;
    Rectangle indicador = {
        x_barra,
        pagina_estoque == 0 ? trilho.y : trilho.y + trilho.height - altura_indicador,
        largura_barra,
        altura_indicador
    };

    DrawRectangleRec(trilho, LIGHTGRAY);
    DrawRectangleRounded(botao_cima, 0.2f, 4, WHITE);
    DrawRectangleRoundedLinesEx(botao_cima, 0.2f, 4, 1.0f, BLACK);
    DrawTriangle(
        (Vector2){botao_cima.x + largura_barra / 2.0f, botao_cima.y + 5.0f},
        (Vector2){botao_cima.x + 4.0f, botao_cima.y + 19.0f},
        (Vector2){botao_cima.x + largura_barra - 4.0f, botao_cima.y + 19.0f},
        BLACK);
    DrawRectangleRounded(botao_baixo, 0.2f, 4, WHITE);
    DrawRectangleRoundedLinesEx(botao_baixo, 0.2f, 4, 1.0f, BLACK);
    DrawTriangle(
        (Vector2){botao_baixo.x + largura_barra / 2.0f, botao_baixo.y + 19.0f},
        (Vector2){botao_baixo.x + largura_barra - 4.0f, botao_baixo.y + 5.0f},
        (Vector2){botao_baixo.x + 4.0f, botao_baixo.y + 5.0f},
        BLACK);
    DrawRectangleRounded(indicador, 0.3f, 4, GRAY);

    for (int i = 0; i < quantidade_alimentos; i++) {
        const int indice_alimento = pagina_estoque * 7 + i;
        Rectangle retangulo_alimento = {
            x_alimentos,
            y_alimentos + i * (altura_alimento + espaco_alimento),
            largura_alimento,
            altura_alimento
        };
        DrawRectangleRounded(retangulo_alimento, 0.2f, 8, WHITE);
        DrawRectangleRoundedLinesEx(retangulo_alimento, 0.2f, 8, 1.0f, BLACK);

        Rectangle fundo_icone = {
            retangulo_alimento.x + 8.0f,
            retangulo_alimento.y + 8.0f,
            48.0f,
            48.0f
        };
        DrawRectangleRounded(fundo_icone, 0.15f, 4, LIGHTGRAY);
        Texture2D textura = texturas_alimentos_estoque[indice_alimento];
        DrawTexturePro(textura,
                       (Rectangle){0, 0, (float)textura.width, (float)textura.height},
                       (Rectangle){fundo_icone.x + 4.0f, fundo_icone.y + 4.0f, 40.0f, 40.0f},
                       (Vector2){0, 0}, 0.0f, WHITE);

        const float x_texto = fundo_icone.x + fundo_icone.width + 8.0f;
        DrawTextEx(fonte_jogo, nomes_alimentos_estoque[indice_alimento],
                   (Vector2){x_texto, retangulo_alimento.y + 8.0f},
                   16.0f, 1.0f, BLACK);
        DrawTextEx(fonte_jogo, "Quantidade: 0",
                   (Vector2){x_texto, retangulo_alimento.y + 36.0f},
                   14.0f, 1.0f, DARKGRAY);
    }
}

void desenha_estoque(void)
{
    const float largura_estoque = JANELA_LARGURA / 4.0f;
    const float topo_mochila = JANELA_ALTURA - 136.0f;
    const float margem_mochila = 16.0f;
    const float margem_topo = 16.0f;
    const float limite_estoque = topo_mochila - margem_mochila;
    Rectangle retangulo_estoque = {
        JANELA_LARGURA - largura_estoque - 24.0f,
        margem_topo,
        largura_estoque,
        limite_estoque - margem_topo
    };

    DrawRectangleRec(retangulo_estoque, RED);
    DrawRectangleLinesEx(retangulo_estoque, 3.0f, BLACK);
    desenha_alimentos_no_estoque(retangulo_estoque);
}

static ListaContHistorico historico_exibicao;
static bool historico_exibicao_valida = false;
static bool historico_por_pontuacao = false; /* false = alfabética (A-Z); true = pontuação decrescente */
static int pagina_historico = 0;
static bool historico_estava_aberto = false;


static void historico_reordenar(void)
{
    /* cópia do histórico, a lista original não é modificada */
    ListaContHistorico copia;
    inicializar(&copia);
    for (int i = 0; i < tamanho(&historico_partidas); i++)
        inserir(&copia, acessar(&historico_partidas, i), i);

    /* só o algoritmo de ordenação é cronometrado */
    Timer t;
    timer_iniciar(&t);
    if (copia.tamanho > 0)
    {
        if (historico_por_pontuacao)
            mergeSortPontuacao(copia.dados, copia.tamanho);
        else
            mergeSortAlfabetico(copia.dados, copia.tamanho);
    }
    double tempo = timer_parar(&t);

    /* troca a cópia de exibição pela nova (libera a anterior) */
    if (historico_exibicao_valida)
        destruir(&historico_exibicao);
    historico_exibicao = copia;
    historico_exibicao_valida = true;

    /* métricas e log atualizado a cada medição */
    metricas.ordenacao_tamanho = copia.tamanho;
    metricas.ordenacao_tempo = tempo;

    FILE *log = fopen("medicoes.log", "a");
    if (log != NULL)
    {
        medicoes_gravar_ordenacao(log);
        fclose(log);
    }

    pagina_historico = 0;
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
    /* gancho de entrada no Histórico: cada acesso à tela reordena e remede */
    if (jogo->tela_atual == HISTORICO)
    {
        if (!historico_estava_aberto)
            historico_reordenar();
        historico_estava_aberto = true;
    }
    else
    {
        historico_estava_aberto = false;
    }

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

        /* botão Voltar */
        float altura_botao_titulo_cj = painel_titulo.height * 0.7f;
        float y_botao_titulo_cj = painel_titulo.y + (painel_titulo.height - altura_botao_titulo_cj) * 0.5f;
        Rectangle botao_voltar_como_jogar = {
            painel_titulo.x, y_botao_titulo_cj, 110.0f, altura_botao_titulo_cj};
        DrawRectangleRec(botao_voltar_como_jogar, GRAY);
        DrawRectangleLinesEx(botao_voltar_como_jogar, 2.0f, BLACK);
        desenhaTextoCentralizado(fonte_jogo, "Voltar", botao_voltar_como_jogar, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
        if (CheckCollisionPointRec(GetMousePosition(), botao_voltar_como_jogar) && IsMouseButtonPressed(0))
            jogo->tela_atual = MENU;

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

        /* botão Voltar (sem ele não tem como sair da tela) */
        float altura_botao_titulo = painel_titulo.height * 0.7f;
        float y_botao_titulo = painel_titulo.y + (painel_titulo.height - altura_botao_titulo) * 0.5f;
        Rectangle botao_voltar_historico = {
            painel_titulo.x, y_botao_titulo, 110.0f, altura_botao_titulo};
        DrawRectangleRec(botao_voltar_historico, GRAY);
        DrawRectangleLinesEx(botao_voltar_historico, 2.0f, BLACK);
        desenhaTextoCentralizado(fonte_jogo, "Voltar", botao_voltar_historico, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
        if (CheckCollisionPointRec(GetMousePosition(), botao_voltar_historico) && IsMouseButtonPressed(0))
            jogo->tela_atual = MENU;

        /* botões de ordem alfabética ou pontuação decrescente */
        Rectangle botao_ordem_alfabetica = {
            painel_titulo.x + painel_titulo.width - 2.0f * 140.0f - 12.0f,
            y_botao_titulo, 140.0f, altura_botao_titulo};
        Rectangle botao_ordem_pontuacao = {
            painel_titulo.x + painel_titulo.width - 140.0f,
            y_botao_titulo, 140.0f, altura_botao_titulo};
        DrawRectangleRec(botao_ordem_alfabetica, !historico_por_pontuacao ? SKYBLUE : GRAY);
        DrawRectangleLinesEx(botao_ordem_alfabetica, 2.0f, BLACK);
        desenhaTextoCentralizado(fonte_jogo, "Alfabetica", botao_ordem_alfabetica, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
        DrawRectangleRec(botao_ordem_pontuacao, historico_por_pontuacao ? SKYBLUE : GRAY);
        DrawRectangleLinesEx(botao_ordem_pontuacao, 2.0f, BLACK);
        desenhaTextoCentralizado(fonte_jogo, "Pontuacao", botao_ordem_pontuacao, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);

        if (IsMouseButtonPressed(0))
        {
            Vector2 mouse_ordem = GetMousePosition();
            bool quer_pontuacao = historico_por_pontuacao;
            if (CheckCollisionPointRec(mouse_ordem, botao_ordem_alfabetica))
                quer_pontuacao = false;
            else if (CheckCollisionPointRec(mouse_ordem, botao_ordem_pontuacao))
                quer_pontuacao = true;
            if (quer_pontuacao != historico_por_pontuacao)
            {
                historico_por_pontuacao = quer_pontuacao;
                historico_reordenar(); /* nova ordem = nova medição no log */
            }
        }

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

        /* paginação sobre a cópia ordenada */
        int numero_linhas = 8;
        int total_registros = historico_exibicao_valida ? tamanho(&historico_exibicao) : 0;
        int total_paginas = (total_registros + numero_linhas - 1) / numero_linhas;
        if (total_paginas < 1)
            total_paginas = 1;
        if (pagina_historico >= total_paginas)
            pagina_historico = total_paginas - 1;
        if (pagina_historico < 0)
            pagina_historico = 0;

        if (IsMouseButtonPressed(0))
        {
            Vector2 mouse_pag = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pag, botao_inferior_volta_tudo))
                pagina_historico = 0;
            else if (CheckCollisionPointRec(mouse_pag, botao_inferior_anterior) && pagina_historico > 0)
                pagina_historico--;
            else if (CheckCollisionPointRec(mouse_pag, botao_inferior_proximo) && pagina_historico < total_paginas - 1)
                pagina_historico++;
            else if (CheckCollisionPointRec(mouse_pag, botao_inferior_vai_tudo))
                pagina_historico = total_paginas - 1;
        }

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
            DrawRectangleRec(retangulo_pontos, WHITE);
            DrawRectangleLinesEx(retangulo_nome, 2.0f, BLACK);
            DrawRectangleLinesEx(retangulo_pontos, 2.0f, BLACK);

            int indice = pagina_historico * numero_linhas + (i - 1);
            if (indice < total_registros)
            {
                RegistroHistorico registro = acessar(&historico_exibicao, indice);
                desenhaTextoCentralizado(fonte_jogo, registro.nome, retangulo_nome, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
                char texto_pontos[16];
                snprintf(texto_pontos, sizeof(texto_pontos), "%d", registro.pontuacao);
                desenhaTextoCentralizado(fonte_jogo, texto_pontos, retangulo_pontos, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, BLACK);
            }
        }

        if (total_registros == 0)
            desenhaTextoCentralizado(fonte_jogo, "Historico vazio - nenhuma partida registrada ainda",
                                     painel_corpo, TAMANHO_FONTE_TEXTO, ESPACO_FONTE, DARKGRAY);

        break;
    case RECEPCAO:
        Rectangle origem = {0, 0, (float)recepcao.width, (float)recepcao.height};
        Rectangle destino = {0, 0, JANELA_LARGURA, JANELA_ALTURA}; /* 1280x720 */
        DrawTexturePro(recepcao, origem, destino, (Vector2){0, 0}, 0.0f, WHITE);
        desenhaJogador(&jogo->jogador);
        atualiza_anim_entidades(jogo);
        float distancia_para_cozinha = (MAPA_COLUNAS - 2) * TILE_SIZE;
        if(jogo->jogador.posicao.x >= distancia_para_cozinha){
            jogo->tela_atual = COZINHA;
        }
        desenhaComanda(&jogo->jogador.pedido_atual.receita_pedido);

        break;

    case COZINHA:
        Rectangle origem_2 = {0, 0, (float)cozinha.width, (float)cozinha.height};
        Rectangle destino_2 = {0, 0, JANELA_LARGURA, JANELA_ALTURA}; /* 1280x720 */
        DrawTexturePro(cozinha, origem_2, destino_2, (Vector2){0, 0}, 0.0f, WHITE);
        atualiza_hitbox_jogador(&jogo->jogador);
        desenhaEquipamentos(jogo);
        desenhaJogador(&jogo->jogador);
        Rectangle origem_parede_baixo = {
            0, 0, (float)parede_baixo.width, (float)cozinha.height};
        DrawTexturePro(parede_baixo, origem_parede_baixo, destino_2,
                       (Vector2){0, 0}, 0.0f, WHITE);
        Rectangle fundo_mochila = {
            JANELA_LARGURA - 136.0f,
            JANELA_ALTURA - 136.0f,
            112.0f,
            112.0f
        };
        bool mochila_em_foco = CheckCollisionPointRec(GetMousePosition(), fundo_mochila);
        if (mochila_em_foco && IsMouseButtonPressed(0)) {
            estoque_aberto = !estoque_aberto;
        }
        if (estoque_aberto) {
            desenha_estoque();
        }
        DrawRectangleRounded(fundo_mochila, 0.2f, 8, WHITE);
        if (mochila_em_foco) {
            DrawRectangleRounded(fundo_mochila, 0.2f, 8, (Color){0, 255, 0, 64});
        }
        DrawTexturePro(mochila,
                       (Rectangle){0, 0, (float)mochila.width, (float)mochila.height},
                       (Rectangle){fundo_mochila.x + 8.0f, fundo_mochila.y + 8.0f, 96.0f, 96.0f},
                       (Vector2){0, 0}, 0.0f,
                       mochila_em_foco ? (Color){215, 255, 215, 255} : WHITE);
        DrawRectangleRoundedLinesEx(fundo_mochila, 0.2f, 8, 2.0f, BLACK);
        desenhaComanda(&jogo->jogador.pedido_atual.receita_pedido);
        atualiza_anim_entidades(jogo);
    default:
        break;
    }
}

void descarregaAssets(void)
{
    UnloadTexture(fogao);
    UnloadTexture(bancada_normal);
    UnloadTexture(bancada_tabua);
    UnloadTexture(mochila);
    for (int i = 0; i < NUMERO_ALIMENTOS_ESTOQUE; i++) {
        UnloadTexture(texturas_alimentos_estoque[i]);
    }
    UnloadTexture(fundo);
    UnloadTexture(parede_baixo);
}