#pragma once
#include "constants.h"

/**
 * @brief Representação e categorização individual de cada alimento
 */
typedef struct {
    char simbolo_alimento; /**< Caractere que representa o alimento */
    int validade; /**< Turno de validade do alimento - se houver - */
 } Alimento;