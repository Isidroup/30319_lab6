/*
 * pulsaciones.h
 *
 */

#ifndef PULSACIONES_H_
#define PULSACIONES_H_

#include <stdint.h>

#define TIEMPO1 400
#define TIEMPO2 100

/**
 * @brief   Detector de pulsación
 * @details Detecta los patrones pulsación larga y
 *             pulsación corta en el dato
 *             que se le pasa como argumento.
 * @param pulsado  estado de la pulsación:
 *                    está pulsado → 1
 *                    no está pulsado → 0
 * @param reset reseteo de la MEF si /= 0
 * @return  0      si no hay pulsacion.
 * @return  1      pulsación corta.
 * @return  2      pulsación larga.
 */
uint8_t pulsaciones (const uint8_t pulsado, const uint8_t reset);


#endif /* PULSACIONES_H_ */
