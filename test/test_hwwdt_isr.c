/**
 * @file test_hwwdt_isr.c
 * @date :2025/11/30 21:19:45
 * @brief Rutinas de servicio de interrupción para el sistema
 *
 * Este fichero contiene las rutinas de interrupción (ISR) del sistema,
 * principalmente orientadas a la gestión de eventos críticos como la
 * interrupción no enmascarable (NMI) generada por el Hardware Watchdog.
 *
 * Contenido:
 * - NMI_Handler: ISR de interrupción no enmascarable
 *
 * @note Las ISR deben ser lo más cortas y eficientes posible
 * @note La NMI tiene la máxima prioridad en el sistema Cortex-M
 *
 */

#include "FM4_leds_sw.h"
#include "HAL_SysTick.h"


void NMI_Handler(void)
{

 /**
   * Bucle infinito de bloqueo con indicación visual
   *
   * El LED azul parpadeante sirve como diagnóstico:
   * - Confirma que la NMI se ha generado correctamente
   * - Indica que el sistema está esperando el reset del HWWDT
   *
   * TODO:
   *   Implementa el algoritmo:
   *
   *   si (si la NMI fue generada por el Hardware Watchdog)
   *   {
   *       repetir indefinidamente
   *       {
   *           si systick ha generado overflow (cada 1 ms) entonces
   *           {
   *               Led azul parpadea
   *           }
   *       }
   *   }
   */


}
//EOF
