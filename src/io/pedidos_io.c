#include "pedidos_io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dados.h>

int lerPedidos(FILE *fp)
{
    char linha[128];
    char receita[16]; /* até 7 chars da receita + 1 pro \0 * 2 por margem de segurança */
    int total = 0;

    if (fp == NULL)
        return -1;

    while (fgets(linha, sizeof(linha), fp) != NULL)
    {
        int cod;

        /* remove \r\n do fim (arquivos gravados no Windows) */
        size_t len = strcspn(linha, "\r\n");
        linha[len] = '\0';

        /* linha 1 do registro: código numérico do pedido */
        cod = atoi(linha);
        if (len == 0 || cod <= 0)
            continue; /* linha inválida — mudar aqui se quiserem tratar como erro */

        /* linha 2 do registro: receita (string de 5 a 7 caracteres, §4.1) */
        if (fgets(linha, sizeof(linha), fp) == NULL)
            break; /* arquivo terminou sem a receita: registro incompleto */

        len = strcspn(linha, "\r\n");
        linha[len] = '\0';
        if (len < 5 || len > 7)
            continue;

        memcpy(receita, linha, len + 1);

        ListaReceita listaReceita;
        PilhaHamburger pilhaHamburguer;
        inicializarLista(&listaReceita);
        inicializaPilha(&pilhaHamburguer);

        for (int i = 0; receita[i] != '\0'; i++)
        {
            if (!inserirFimLista(&listaReceita, receita[i]))         // adiciona os ingredientes na lista
                printf("Erro ao inserir item na lista de receitas"); // imprime no console se der erro (mais pra debug do que qualquer outra coisa)
        }

        Pedido pedido = {
            cod,
            listaReceita,
            pilhaHamburguer,
            false
        };
        pedidos_avl = avlInserir(pedidos_avl, pedido);
        if (cod > maior_codigo_avl)
            maior_codigo_avl = cod;
        total++;
    }

    return total;
}
