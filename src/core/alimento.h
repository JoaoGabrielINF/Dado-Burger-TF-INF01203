#pragma once
#include "constants.h"

/**
 * @brief Representação e categorização individual de cada alimento
 */
typedef struct {
    char simbolo_alimento; /**< Caractere que representa o alimento */
    TipoAlimento tipo_alimento; /**< Classificação do alimento quanto à validade */
    int validade; /**< Turno de validade do alimento - se houver - */
 } Alimento;