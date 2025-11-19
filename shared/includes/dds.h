#include <stdint.h>

#ifndef __DDS_H__
#define __DDS_H__

/**
* Estructura para representar un DDS
*/
typedef struct
{
    uint16_t phaseAccumulator; /**< acumulador de fase */
    uint16_t phaseIncrement; /**< incremento de fase */
} dds16bits_t;

/**
 * @brief    Da valor a la fase en un objeto de tipo DDS16Bits
 * @param [out]  p_dds puntero a la estructura a inicializar
 * @param [in]   fase    valor de la fase codificada en 16 bits [0->2pi)
 *
 * @return    void
 *
 * @note
 *-------------------------------------------------------------------*/
void DDS16Bits_setPhase(dds16bits_t *p_dds, uint16_t phase);

/**
 * @brief    Da valor al incremento de fase en un objeto de tipo DDS16Bits
 * @param [out]  p_dds puntero a la estructura a inicializar
 * @param [in]   faseinc    valor del incremento de fase codificado en 16 bits
 *
 * @return    void
 *
 * @note
 *-------------------------------------------------------------------*/
void DDS16Bits_setPhaseInc(dds16bits_t *p_dds, uint16_t phaseinc);

/**
 * @brief   Devuelve el siguiente valor de amplitud de la señal
 * @details Devuelve en 16 bits el valor de amplitud de un
 *             tono obtenido mediante DDS.
 * @param [inout]  p_dds puntero a un módulo DDS
 * @return  amplitud codificada en 16 bits (int16_t)
 *
 * @note    es necesario dar valor previamente a la fase y al incremento de fase
 *-------------------------------------------------------------------*/
int16_t DDS16Bits_getNextSample(dds16bits_t *p_dds);


#endif
