#include "render.h"

static Texture2D fundo;
static Font fonte_jogo;

void carregaAssets(void){
    fundo = LoadTexture("assets/imagens/Imagem_Fundo_Dado_Burger.png");
    fonte_jogo = GetFontDefault();
}

bool coloreSeColide(Rectangle rec, Vector2 pos_mouse) {
    if(CheckCollisionPointRec(pos_mouse, rec)){
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
        ret.y + ret.height / 2 - (t.y / 2)
    };

    DrawTextEx(fonte, texto, pos, tamanho, espaco, cor);
}


void desenhaJogo(Jogo *jogo)
{

    switch (jogo->telaAtual)
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
            ALTURA_BOTAO_INICIO
        };


        Rectangle botao_historico = {
            X_BOTAO_INICIO,
            (Y_BOTAO_INICIO + (ALTURA_BOTAO_INICIO + ESPACAMENTO_BOTAO_INICIO)),
            LARGURA_BOTAO_INICIO,
            ALTURA_BOTAO_INICIO};

        Rectangle display_inicio = {
            X_DISPLAY_INICIO,
            Y_DISPLAY_INICIO,
            LARGURA_DISPLAY_INICIO,
            ALTURA_DISPLAY_INICIO
        };

        DrawRectangleRec(display_inicio, GREEN);
        
        DrawRectangleRec(botao_novo_jogo, RED);
        if(coloreSeColide(botao_novo_jogo, GetMousePosition()) && IsMouseButtonPressed(0)){
            jogo->telaAtual = ESCOLHER_DIFICULDADE;
        }
        desenhaTextoCentralizado(fonte_jogo, "Novo Jogo", botao_novo_jogo, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);
        
        

        DrawRectangleRec(botao_como_jogar, RED);
        if(coloreSeColide(botao_como_jogar, GetMousePosition()) && IsMouseButtonPressed(0)){
            jogo->telaAtual = COMO_JOGAR;
        }
        desenhaTextoCentralizado(fonte_jogo, "Como Jogar", botao_como_jogar, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);
        
        
        DrawRectangleRec(botao_historico, RED);
        if(coloreSeColide(botao_historico, GetMousePosition()) && IsMouseButtonPressed(0)){
            jogo->telaAtual = HISTORICO;
        }
         desenhaTextoCentralizado(fonte_jogo, "Historico", botao_historico, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);
         

       
        
        break;
        case  ESCOLHER_DIFICULDADE:
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
            ALTURA_BOTAO_INICIO
        };


        Rectangle botao_dificil = {
            X_BOTAO_INICIO,
            (Y_BOTAO_INICIO + (ALTURA_BOTAO_INICIO + ESPACAMENTO_BOTAO_INICIO)),
            LARGURA_BOTAO_INICIO,
            ALTURA_BOTAO_INICIO};

        Rectangle display_dificuldade = {
            X_DISPLAY_INICIO,
            Y_DISPLAY_INICIO,
            LARGURA_DISPLAY_INICIO,
            ALTURA_DISPLAY_INICIO
        };

        DrawRectangleRec(display_dificuldade, GREEN);
        
        DrawRectangleRec(botao_facil, RED);
        if(coloreSeColide(botao_facil, GetMousePosition()) && IsMouseButtonPressed(0)){
            jogo->telaAtual = RECEPCAO;
            jogo->dificuldade = FACIL;
        }
        desenhaTextoCentralizado(fonte_jogo, "Facil", botao_facil, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);
        
        

        DrawRectangleRec(botao_medio, RED);
        if(coloreSeColide(botao_medio, GetMousePosition()) && IsMouseButtonPressed(0)){
            jogo->telaAtual = RECEPCAO;
            jogo->dificuldade = MEDIO;
        }
        desenhaTextoCentralizado(fonte_jogo, "Medio", botao_medio, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);
        
        
        DrawRectangleRec(botao_dificil, RED);
        if(coloreSeColide(botao_dificil, GetMousePosition()) && IsMouseButtonPressed(0)){
            jogo->telaAtual = RECEPCAO;
            jogo->dificuldade = DIFICIL;
        }
         desenhaTextoCentralizado(fonte_jogo, "Dificil", botao_dificil, TAMANHO_FONTE_BOTAO, ESPACO_FONTE, BLACK);

        break;
        default:
        break;
    }
}

void descarregaAssets(void){
    UnloadTexture(fundo);
}