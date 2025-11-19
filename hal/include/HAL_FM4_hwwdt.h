/**
 * @file HAL_FM4_hwwd.h
 * @date :2025/11/02 21:00:52
 * @brief Interfaz de Hardware Watchdog (HWWDT) para la plataforma FM4
 *
 * Este fichero declara las funciones y constantes necesarias para configurar,
 * arrancar y mantener el Hardware Watchdog (HWWDT) del microcontrolador FM4.
 * Proporciona mecanismos para inicializar el temporizador de vigilancia,
 * arrancarlo, comprobar su estado de interrupción, leer su valor y realizar
 * la operación de "feed" (alimentado) segura.
 *
 * Se documentan a continuación las funciones públicas disponibles en esta API.
 *
 * @section Funciones disponibles
 * - Hwwdt_Init(uint32_t wdogload, uint8_t wdogreset)
 *   - Inicializa el HWWDT con el periodo de desbordamiento y opción de reset.
 * - Hwwdt_Start(void)
 *   - Arranca el HWWDT (empieza la cuenta atrás).
 * - Hwwdt_GetIntStatus(void)
 *   - Devuelve el estado de la interrupción del HWWDT (1 = interrupción generada).
 * - Hwwdt_ReadWdgValue(void)
 *   - Lee y devuelve el valor actual del contador del HWWDT.
 * - Hwwdt_Feed(uint8_t u8ClearPattern1, uint8_t u8ClearPattern2)
 *   - Realiza la secuencia segura de "alimentado" (unlock -> feed -> lock).
 *
 * @note El HWWDT utiliza como reloj el dominio CLKLC (~100 kHz) representado
 *       por el símbolo __CLKLC en el sistema. Los parámetros de tiempo deben
 *       tener en cuenta esa frecuencia.
 *
 */

#ifndef _HAL_FM4_HWWD_H_
#define _HAL_FM4_HWWD_H_

#include <stdint.h>


/**
* @brief HWWDT unlock keys
*
*/
#define HWWDT_REG_UNLOCK_key1  (0x1ACCE551u)
#define HWWDT_REG_UNLOCK_key2  (0xE5331AAEu)

/**
* @brief Inicializa Hardware Watchdog
*
* @param [in] wdogload  Periodo de desbordamiento de HWWDT en ciclos de reloj
* @param [in] wdogreset 1/0 activa generación de reset
*
* @return   No retorna nada
*
* @note Esta función solo configura el HWWDT
*       Si se ejecuta HWWDT_Start() HWWDT empieza a funcionar.
*       HWWDT utiliza como reloj CLKLC (100 kHz)
*           el símbolo __CLKLC definido en (system_s6e2cc.h)
*           guarda la frecuencia de reloj de CLKLC.
*/
void HWWDT_Init(uint32_t wdogload, uint8_t wdogreset);

/**
* @brief Pone en marcha el Hardware Watchdog
*
* @return   No retorna nada
*/
void HWWDT_Start(void);

/**
* @brief Devuelve el estado de la interrupción del HWWDT
*
* @return   1 -> Interrupción generada
*           0 -> No se ha generado interrupción
*/
uint8_t HWWDT_GetIntStatus(void);

/**
* @brief Lee el valor del contador del HWWDT
*
* @retval uint32_t: valor del HWWDT
*/
uint32_t HWWDT_ReadWdgValue(void);

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
* @note Los valores arbitrarios deben escogerse
*          para evitar que el HWWDT se "alimente" de forma fortuita.
*/
void HWWDT_Feed(uint8_t u8ClearPattern1, uint8_t u8ClearPattern2);




#endif  /* _HAL_FM4_HWWD_H_ */
