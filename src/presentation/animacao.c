#include "animacao.h"
#include <stddef.h>

void atualiza_animacao(Animacao *animacao) {
    if (animacao == NULL) {
        return;
    }

    if ((animacao->passo > 0 && animacao->primeiro > animacao->ultimo) ||
        (animacao->passo < 0 && animacao->primeiro < animacao->ultimo)) {
        return;
    }

    bool frame_fora_da_sequencia = animacao->passo > 0
        ? animacao->atual < animacao->primeiro ||
              animacao->atual > animacao->ultimo
        : animacao->atual > animacao->primeiro ||
              animacao->atual < animacao->ultimo;
    if (frame_fora_da_sequencia) {
        animacao->atual = animacao->primeiro;
    }

    if (animacao->velocidade <= 0.0f || animacao->passo == 0 ||
        animacao->primeiro == animacao->ultimo) {
        return;
    }

    animacao->duracao_restante -= GetFrameTime();
    while (animacao->duracao_restante <= 0.0f) {
        animacao->duracao_restante += animacao->velocidade;
        animacao->atual += animacao->passo;

        if ((animacao->passo > 0 && animacao->atual > animacao->ultimo) ||
            (animacao->passo < 0 && animacao->atual < animacao->ultimo)) {
            animacao->atual = animacao->primeiro;
        }
    }
}

void animacao_inicializar(Animacao *animacao) {
    if (animacao == NULL) {
        return;
    }

    animacao->primeiro = 0;
    animacao->ultimo = 0;
    animacao->atual = 0;
    animacao->velocidade = 0.1f;
    animacao->duracao_restante = animacao->velocidade;
    animacao->tipo = PARADO;
    animacao->passo = 1;
}

Rectangle tamanho_frames(const Animacao *animacao, int largura_frame,
                        int altura_frame, int frames_por_linha) {
    if (animacao == NULL || largura_frame <= 0 || altura_frame <= 0 ||
        frames_por_linha <= 0 || animacao->atual < 0) {
        return (Rectangle){0};
    }

    return (Rectangle){
        .x = (float)(animacao->atual % frames_por_linha) * largura_frame,
        .y = (float)(animacao->atual / frames_por_linha) * altura_frame,
        .width = (float)largura_frame,
        .height = (float)altura_frame,
    };
}

void atualiza_anim_entidades(Jogo *jogo) {
    if (jogo == NULL) {
        return;
    }

    atualiza_animacao(&jogo->jogador.animacao);

    for (NodoFila *nodo = jogo->fila_clientes.frente;
         nodo != NULL;
         nodo = nodo->prox) {
        Cliente *cliente = &nodo->cliente;
        if (cliente->andando) {
            atualiza_animacao(&cliente->animacao);
        } else {
            cliente->animacao.atual = cliente->animacao.primeiro;
            cliente->animacao.duracao_restante = cliente->animacao.velocidade;
        }
    }
}
