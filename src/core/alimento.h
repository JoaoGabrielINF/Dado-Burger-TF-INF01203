#include "constants.h"

/**
 * @brief Representação e categorização individual de cada alimento
 */
typedef struct {
    char simboloAlimento; /**< Caractere do alimento */
    TipoAlimento tipoAlimento; /**< ENUM que diz se o alimento é perecível, perene ou ilimitado  */
    int validade; /**< Turno de validade do alimento - se houver - */
 } Alimento;