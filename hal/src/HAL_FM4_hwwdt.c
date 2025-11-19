/** \file HAL_FM4_hwwdt.c
* A brief file description.
* Created on:    2021/11/19
* Last modified:
*/

#include <stdint.h>
#include "s6e2cc.h"
#include "HAL_FM4_hwwdt.h"

/**
 * @brief Inicializa Hardware Watchdog
 *
 * @param [in] wdogload  Valor del registro de carga del HWWDT
 * @param [in] wdogreset 1/0 activa generación de reset
 *
 * @return   No retorna nada
 *
 * @note Esta función solo configura el HWWDT
 *       Si se ejecuta Hwwdg_Start() HWWDT empieza a funcionar.
 */
void HWWDT_Init( uint32_t wdogload, uint8_t wdogreset)
{
    //TODO: Implementar función
}

/**
* @brief Inicia Hardware Watchdog si no lo está
*
* @return   No retorna nada
*/
void HWWDT_Start(void)
{
    //TODO: Implementar función
}

/**
* @brief Devuelve el estado de la interrupción del HWWDT
*
* @return   1/0 estado de la interrupción
*/
uint8_t HWWDT_GetIntStatus(void)
{
    //TODO: Implementar función
}

/**
* @brief Lee el valor del Hardware Watchdog
*
* @retval uint32_t:valor del HWWDT
*/
uint32_t HWWDT_ReadWdgValue(void)
{
    //TODO: Implementar función
}

/**
* @brief Feed Hardware Watchdog (HWWDT)
*
* @details Esta función "alimenta" el HWWDT con la secuencia
*          unlock -> feed -> lock. Los valores arbitrarios deben escogerse
*          para evitar que el HWWDT se "alimente" de forma fortuita.
*
* @param [in] u8ClearPattern1   Patron de valor arbitrario
* @param [in] u8ClearPattern2   Inverso del patron de valor arbitrario
*
*/
void HWWDT_Feed(uint8_t u8ClearPattern1, uint8_t u8ClearPattern2)
{
    //TODO: Implementar función
}
