#include "mapa_io.h"

bool carregar_mapa(const char *caminho, char mapa[MAPA_LINHAS][MAPA_COLUNAS]) {
    FILE *arquivo = fopen(caminho, "r");
    if (arquivo == NULL) return false;

    int linha = 0, coluna = 0, c;
    while (linha < MAPA_LINHAS && (c = fgetc(arquivo)) != EOF) {
        if (c == '\n') {
            coluna = 0;
            linha++;
        } else if (c != '\r' && coluna < MAPA_COLUNAS) {
            mapa[linha][coluna++] = (char)c;
        }
    }
    fclose(arquivo);

    /* leu as 16 linhas (com ou sem \n no final do arquivo) */
    return linha == MAPA_LINHAS ||
           (linha == MAPA_LINHAS - 1 && coluna == MAPA_COLUNAS);
}