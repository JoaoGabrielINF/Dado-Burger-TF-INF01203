#include "jogo.h"

void inicializa_clientes(Jogo *jogo)
{
    Cliente cliente_padrao;
    if (!jogo || !dequeueFila(&jogo->fila_clientes, &cliente_padrao))
    {
        return;
    }

    cliente_padrao.codigo_pedido = 0;
    cliente_padrao.paciencia_atual = PACIENCIA_MAXIMA_FACIL;
    animacao_inicializar(&cliente_padrao.animacao);
    cliente_padrao.animacao.atual = 1;
    cliente_padrao.animacao.ultimo = 3;
    cliente_padrao.animacao.primeiro = 1;
    cliente_padrao.textura_atual = 1;
    cliente_padrao.andando = false;

    for (int i = 0; i < MAX_CLIENTES_FILA; i++)
    {
        if (!enqueueFila(&jogo->fila_clientes, &cliente_padrao))
        {
            break;
        }

        cliente_padrao.posicao.x -= TILE_SIZE;
        cliente_padrao.tile_atual.coluna--;
        cliente_padrao.tile_inicial.coluna--;
        cliente_padrao.textura_atual++;
        if (cliente_padrao.textura_atual > 6)
            cliente_padrao.textura_atual = 1;
    }
}

void inicializa_jogo(Jogo *jogo)
{
    if (!jogo)
        return;

    *jogo = (Jogo){0};
    jogo->dificuldade = FACIL;
    jogo->turno_atual = 0;
    jogo->pontuacao = 0;
    jogo->tela_atual = MENU;
    jogo->jogando = false;
    jogo->tempo = 0.0f;
    jogo->jogador.velocidade = VELOCIDADE_JOGADOR;
    jogo->jogador.pedido_atual.pedido_pronto = false;
    jogo->jogador.pedido_atual.pedido_entregue = false;
    jogo->proximo_cliente = false;
    jogo->fim_partida.nome[0] = '\0';
    jogo->fim_partida.pontuacao = 0; /* TODO: configurar cálculo adicional da pontuação */
    jogo->fim_partida.salvo = false;
    jogo->fim_partida.caminho_historico = NULL;
    jogo->primeiro_cliente = true;

    for (int i = 0; i < NUMERO_EQUIPAMENTOS; i++)
    {
        jogo->equipamentos[i].em_uso = false;
        jogo->equipamentos[i].foi_utilizado = false;
        jogo->equipamentos[i].turno_pronto = 0;
    }

    const char simbolos_perenes[MAXIMO_PERENES] = {
        [PICLES] = PICLES_SIMBOLO,
        [ALFACE] = ALFACE_SIMBOLO,
        [QUEIJO_SUICO] = QUEIJO_SUICO_SIMBOLO,
        [QUEIJO_CHEDDAR] = QUEIJO_CHEDDAR_SIMBOLO,
        [CEBOLA] = CEBOLA_SIMBOLO,
        [TOMATE] = TOMATE_SIMBOLO};
    for (int i = 0; i < MAXIMO_PERENES; i++)
    {
        jogo->jogador.estoque_perenes[i].alimento = simbolos_perenes[i];
        jogo->jogador.estoque_perenes[i].quantidade = 0;
    }

    inicializaFila(&jogo->fila_clientes);
    inicializaPilha(&jogo->jogador.pedido_atual.pilha_hamburger);
    inicializarLista(&jogo->jogador.pedido_atual.receita_pedido);

    const char simbolos_heap[QUANTIDADE_ALIMENTOS_PERECIVEIS] = {
        CARNE_SIMBOLO,
        OVO_FRITO_SIMBOLO,
        BACON_SIMBOLO};
    for (int i = 0; i < QUANTIDADE_ALIMENTOS_PERECIVEIS; i++)
    {
        inicializaHeap(&jogo->jogador.heap_estoque[i]);
        jogo->jogador.heap_estoque[i].alimento = simbolos_heap[i];
        for(int j = 0; j < MAX_ALIM; j++){
            jogo->jogador.heap_estoque[i].validade_alimentos[j] = 999;
        }
    }

    animacao_inicializar(&jogo->jogador.animacao);
}

void inicializa_pedido_cliente(Jogo *jogo)
{
    //     Sorteio de pedido de cliente
    srand((unsigned)time(NULL));
    int pedido_cliente = 1 + rand() % (maior_codigo_avl - 1 + 1);
    jogo->fila_clientes.frente->cliente.codigo_pedido = pedido_cliente;
    if ((jogo->jogador.pedido_atual.receita_pedido.ini =
             buscarHash(&cache_pedidos, pedido_cliente)) != NULL)
    {
        // se o valor da chave por diferente de null -> HIT
        metricas.hash_hits++;
    }
    else
    {
        metricas.hash_misses++;
        NodoAvl *pedido_buscado;
        pedido_buscado = avlBuscar(pedidos_avl, pedido_cliente);
        metricas.total_buscas++;
        if (inserirHash(&cache_pedidos, pedido_cliente, &pedido_buscado->dado.receita_pedido))
        {
            metricas.hash_colisoes++;
        }
        jogo->jogador.pedido_atual.receita_pedido.ini = pedido_buscado->dado.receita_pedido.ini;
    }

    reiniciaPilha(&jogo->jogador.pedido_atual.pilha_hamburger);
    jogo->jogador.pedido_atual.pedido_entregue = false;
    jogo->jogador.pedido_atual.pedido_pronto = false;
}

void gerencia_turnos(Jogo *jogo)
{
    for (int i = 0; i < NUMERO_EQUIPAMENTOS; i++)
    {

        if (jogo->equipamentos[i].foi_utilizado)
        {
            // Se foi colocado algum item no equipamento para fazer ou se empilhou/desempilhou no hamburger
            jogo->equipamentos[i].em_uso = true;
            if (i == FOGAO)
            {
                jogo->equipamentos[i].turno_pronto = jogo->turno_atual + TURNOS_COZIMENTO;
            }

            if (i != BANCADA)
            {
                jogo->equipamentos[i].foi_utilizado = false;
            }
            jogo->turno_atual++;
            jogo->aumentou_turno = true;
        }
    }
}

void gerencia_paciencia(Jogo *jogo)
{
    if (jogo->aumentou_turno)
    {
        jogo->fila_clientes.frente->cliente.paciencia_atual -= 1;
    }
}

void gerencia_estoque_pereciveis(Jogo *jogo)
{
    if (jogo->aumentou_turno)
    {
        for (int i = 0; i < QUANTIDADE_ALIMENTOS_PERECIVEIS; i++)
        {
            char removido;
            consultarTopoHeap(&jogo->jogador.heap_estoque[i], jogo->turno_atual, &removido);
        }
    }
    jogo->aumentou_turno = false;
}

void prepara_ingredientes(Jogo *jogo)
{
    if (jogo->equipamentos[FOGAO].em_uso)
    {
        if (jogo->equipamentos[FOGAO].turno_pronto == jogo->turno_atual)
        {
            jogo->equipamentos[FOGAO].em_uso = false;
            char alimento = jogo->equipamentos[FOGAO].alimento_preparado;
            for (int i = 0; i < QUANTIDADE_ALIMENTOS_PERECIVEIS; i++)
            {
                if (jogo->jogador.heap_estoque[i].alimento == alimento)
                {
                    inserirHeap(&jogo->jogador.heap_estoque[i], jogo->turno_atual + TURNOS_PERECIVEIS, alimento);
                }
            }
        }
    }

    if (jogo->equipamentos[TABUA].em_uso)
    {
        char alimento = jogo->equipamentos[TABUA].alimento_preparado;
        switch (alimento)
        {
        case PICLES_SIMBOLO:
            jogo->jogador.estoque_perenes[PICLES].quantidade++;
            break;
        case ALFACE_SIMBOLO:
            jogo->jogador.estoque_perenes[ALFACE].quantidade++;
            break;
        case QUEIJO_SUICO_SIMBOLO:
            jogo->jogador.estoque_perenes[QUEIJO_SUICO].quantidade++;
            break;
        case QUEIJO_CHEDDAR_SIMBOLO:
            jogo->jogador.estoque_perenes[QUEIJO_CHEDDAR].quantidade++;
            break;
        case CEBOLA_SIMBOLO:
            jogo->jogador.estoque_perenes[CEBOLA].quantidade++;
            break;
        case TOMATE_SIMBOLO:
            jogo->jogador.estoque_perenes[TOMATE].quantidade++;
            break;
        default:
            break;
        }
        jogo->equipamentos[TABUA].em_uso = false;
    }
}


void compara_lista_e_pilha(PilhaHamburger *pilha, const ListaReceita *lista){
    PilhaHamburger pilha_aux;
    NodoLista *aux = lista->ini;
    char ingrediente_auxiliar;
    inicializaPilha(&pilha_aux);
    while(!estaVaziaPilha(pilha)){
        popPilha(pilha, &ingrediente_auxiliar);
        pushPilha(&pilha_aux, ingrediente_auxiliar);
    }

    while(!estaVaziaPilha(&pilha_aux)){
        popPilha(&pilha_aux, &ingrediente_auxiliar);
        pushPilha(pilha, ingrediente_auxiliar);
        if(aux->ingrediente == ingrediente_auxiliar){
            pilha->topo->ingrediente_correto = true;
        }
        else{
            pilha->topo->ingrediente_correto = false;
        }
        aux = aux->prox;
    }

}


void monta_hamburger(Jogo *jogo)
{
    if (jogo->equipamentos[BANCADA].foi_utilizado)
    {

        if (jogo->jogador.pedido_atual.opcao == REMOVE)
        {
            char alimento_removido;
            popPilha(&jogo->jogador.pedido_atual.pilha_hamburger, &alimento_removido);
            jogo->equipamentos[BANCADA].foi_utilizado = false;
        }

        else if (jogo->jogador.pedido_atual.opcao == ADICIONA)
        {
            char alimento_adicionado = jogo->jogador.pedido_atual.adicionar_pilha;

            if (alimento_adicionado == PAO_SIMBOLO || alimento_adicionado == KETCHUP_SIMBOLO || alimento_adicionado == MOSTARDA_SIMBOLO)
            {
                // Se o alimento for ilimitado, não diminui nada de nenhum estoque
                pushPilha(&jogo->jogador.pedido_atual.pilha_hamburger, alimento_adicionado);
                jogo->equipamentos[BANCADA].foi_utilizado = false;
                
                
            }
            else
            {

                for (int i = 0; i < MAXIMO_PERENES; i++)
                {
                    if (jogo->jogador.estoque_perenes[i].alimento == alimento_adicionado && jogo->jogador.estoque_perenes[i].quantidade > 0)
                    {
                        pushPilha(&jogo->jogador.pedido_atual.pilha_hamburger, alimento_adicionado);
                        jogo->equipamentos[BANCADA].foi_utilizado = false;
                        jogo->jogador.estoque_perenes[i].quantidade--;
                       
                    }
                }

                for (int i = 0; i < QUANTIDADE_ALIMENTOS_PERECIVEIS; i++)
                {
                    if (jogo->jogador.heap_estoque[i].alimento == alimento_adicionado && jogo->jogador.heap_estoque[i].tamanho_heap > 0)
                    {
                        removerHeap(&jogo->jogador.heap_estoque[i], &alimento_adicionado);
                        pushPilha(&jogo->jogador.pedido_atual.pilha_hamburger, alimento_adicionado);
                        jogo->equipamentos[BANCADA].foi_utilizado = false;
                       
                    }
                }
            }
        }
    }
    char teste;
    topoPilha(&jogo->jogador.pedido_atual.pilha_hamburger, &teste);

    if(jogo->equipamentos[BANCADA].foi_utilizado) jogo->equipamentos[BANCADA].foi_utilizado = false;

    compara_lista_e_pilha(&jogo->jogador.pedido_atual.pilha_hamburger, &jogo->jogador.pedido_atual.receita_pedido);

    if (estaVaziaPilha(&jogo->jogador.pedido_atual.pilha_hamburger))
    {
        jogo->equipamentos[BANCADA].em_uso = false;
    }
    else
    {
        jogo->equipamentos[BANCADA].em_uso = true;
    }
}
void reinicia_jogo(Jogo *jogo)
{
    if (!jogo)
        return;

    esvaziaFila(&jogo->fila_clientes);
    reiniciaPilha(&jogo->jogador.pedido_atual.pilha_hamburger);
    destruirLista(&jogo->jogador.pedido_atual.receita_pedido);
    reiniciaHash(&cache_pedidos);

    jogo->dificuldade = FACIL;
    jogo->turno_atual = 0;
    jogo->pontuacao = 0;
    jogo->jogando = false;
    jogo->tempo = 0.0f;
    jogo->tela_atual = MENU;
    jogo->jogador.velocidade = VELOCIDADE_JOGADOR;
    jogo->jogador.pedido_atual.pedido_pronto = false;
    jogo->jogador.pedido_atual.pedido_entregue = false;
    jogo->proximo_cliente = false;
    jogo->fim_partida.nome[0] = '\0';
    jogo->fim_partida.pontuacao = 0; /* TODO: configurar cálculo adicional da pontuação */
    jogo->fim_partida.salvo = false;
    jogo->fim_partida.caminho_historico = NULL;
    jogo->primeiro_cliente = true;

    for (int i = 0; i < NUMERO_EQUIPAMENTOS; i++)
    {
        jogo->equipamentos[i].em_uso = false;
        jogo->equipamentos[i].foi_utilizado = false;
        jogo->equipamentos[i].turno_pronto = 0;
    }

    const char simbolos_perenes[MAXIMO_PERENES] = {
        [PICLES] = PICLES_SIMBOLO,
        [ALFACE] = ALFACE_SIMBOLO,
        [QUEIJO_SUICO] = QUEIJO_SUICO_SIMBOLO,
        [QUEIJO_CHEDDAR] = QUEIJO_CHEDDAR_SIMBOLO,
        [CEBOLA] = CEBOLA_SIMBOLO,
        [TOMATE] = TOMATE_SIMBOLO};
    for (int i = 0; i < MAXIMO_PERENES; i++)
    {
        jogo->jogador.estoque_perenes[i].alimento = simbolos_perenes[i];
        jogo->jogador.estoque_perenes[i].quantidade = 0;
    }

    inicializaFila(&jogo->fila_clientes);
    inicializaPilha(&jogo->jogador.pedido_atual.pilha_hamburger);
    inicializarLista(&jogo->jogador.pedido_atual.receita_pedido);

    const char simbolos_heap[QUANTIDADE_ALIMENTOS_PERECIVEIS] = {
        CARNE_SIMBOLO,
        OVO_FRITO_SIMBOLO,
        BACON_SIMBOLO};
    for (int i = 0; i < QUANTIDADE_ALIMENTOS_PERECIVEIS; i++)
    {
        inicializaHeap(&jogo->jogador.heap_estoque[i]);
        jogo->jogador.heap_estoque[i].alimento = simbolos_heap[i];
        for(int j = 0; j < MAX_ALIM; j++){
            jogo->jogador.heap_estoque[i].validade_alimentos[j] = 999;
        }
    }

    inicializa_clientes(jogo);
}

void atualiza_jogo(Jogo *jogo)
{
    gerencia_turnos(jogo);
    gerencia_paciencia(jogo);
    gerencia_estoque_pereciveis(jogo);
    prepara_ingredientes(jogo);
    monta_hamburger(jogo);
}