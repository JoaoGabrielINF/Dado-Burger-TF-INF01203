#include "mapa.h"

void carrega_estruturas_mapa(const char mapa[][MAPA_COLUNAS], Jogo *jogo){

    for(int linha = 0; linha < MAPA_LINHAS; linha++) {

        for(int coluna = 0; coluna < MAPA_COLUNAS; coluna++){
            float posicao_pixels_x = coluna * TILE_SIZE;
            float posicao_pixels_y = linha * TILE_SIZE;
            Vector2 posicao_pixels = {posicao_pixels_x, posicao_pixels_y};
            
            char tile_atual = mapa[linha][coluna];

            switch (tile_atual)
            {
            case BLOQUEADO_SIMBOLO:
                break;
            case CLIENTE_SIMBOLO:
                jogo->cliente.posicao = posicao_pixels;
                jogo->cliente.tile_inicial.linha = linha;
                jogo->cliente.tile_inicial.coluna = coluna;
                jogo->cliente.tile_atual.linha = linha;
                jogo->cliente.tile_atual.coluna = coluna;
                jogo->cliente.textura_atual = 0;
                break;
            case JOGADOR_SIMBOLO:
                jogo->jogador.posicao = posicao_pixels;
                jogo->jogador.tile_inicial.linha = linha;
                jogo->jogador.tile_inicial.coluna = coluna;
                jogo->jogador.tile_atual.linha = linha;
                jogo->jogador.tile_atual.coluna = coluna;
            break;
            case FOGAO_SIMBOLO:
                jogo-> equipamentos[FOGAO].posicao_pixels = posicao_pixels;
                jogo-> equipamentos[FOGAO].tile_atual.linha = linha;
                jogo-> equipamentos[FOGAO].tile_atual.coluna = coluna;
                break;
            case BANCADA_SIMBOLO:
                jogo-> equipamentos[BANCADA].posicao_pixels = posicao_pixels;
                jogo-> equipamentos[BANCADA].tile_atual.linha = linha;
                jogo-> equipamentos[BANCADA].tile_atual.coluna = coluna;
                break;
            case TABUA_SIMBOLO:
                jogo-> equipamentos[TABUA].posicao_pixels = posicao_pixels;
                jogo-> equipamentos[TABUA].tile_atual.linha = linha;
                jogo-> equipamentos[TABUA].tile_atual.coluna =  coluna;
                break;
            default:
                break;
            }
        } // Fim da coluna
    }
}

