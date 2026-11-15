#include "../core/models.h"
#include <stdio.h>
#include <math.h>

void desenhaTextoCentralizado(Font fonte, const char *texto, Rectangle ret, float tamanho, float espaco, Color cor);

bool coloreSeColide(Rectangle rec, Vector2 pos_mouse);

void desenhaJogo(Jogo *jogo);

void descarregaAssets(void);

void carregaAssets(void);