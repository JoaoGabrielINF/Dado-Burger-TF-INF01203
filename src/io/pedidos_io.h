#pragma once
#include <stdio.h>

/**
 * @brief Lê o arquivo de pedidos e os organiza numa AVL na variável global/universal do projeto pedidos_avl
 *
 * @param[in] fp arquivo já aberto em modo r (o fopen(argv[1], "r") da main)
 * @return quantidade de registros lidos com sucesso, ou -1 se fp for NULL
 */
int lerPedidos(FILE *fp);
