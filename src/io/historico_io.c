#include "historico_io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dados.h>

int lerHistorico(FILE *fp)
{
    char linha[128];
    char nome[21]; /* tamanho limite de 20 + 1 pro \0 */
    int total = 0;

    if (fp == NULL)
        return -1;

    while (fgets(linha, sizeof(linha), fp) != NULL) {
        int pontos;

        /* remove \r\n do fim (arquivos gravados no Windows) */
        size_t len = strcspn(linha, "\r\n");
        linha[len] = '\0';

        /* linha 1 do registro: nome do jogador (pode conter espaço) */
        if (len == 0 || len > 20)
            continue; /* linha inválida */

        memcpy(nome, linha, len + 1);

        /* linha 2 do registro: pontuação */
        if (fgets(linha, sizeof(linha), fp) == NULL)
            break; /* arquivo terminou sem a pontuação: registro incompleto */

        pontos = atoi(linha);
        inserir(&historico_partidas, criarRegistro(total, nome, pontos), total);

        total++;
    }

    return total;
}

bool salvarPartidaHistorico(const char *caminho, const char *nome, int pontuacao)
{
    FILE *fp = fopen(caminho, "a"); /* APPEND: preserva as partidas anteriores */
    if (fp == NULL)
        return false;

    fprintf(fp, "%s\n%d\n", nome, pontuacao);
    fclose(fp);
    return true;
}
