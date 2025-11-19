/**
 * @file isr.c
 * @date :2025/11/04 20:35:26
 * @brief Rutinas de servicio de interrupción del sistema
 *
 * Este fichero contiene las rutinas de interrupción (ISR) principales del sistema,
 * incluyendo:
 * - ISR del periférico I2S para gestión de audio streaming
 * - ISR de interrupción no enmascarable (NMI) del Hardware Watchdog
 *
 * El sistema utiliza interrupciones para:
 * 1. Transferencia eficiente de datos de audio entre buffers circulares y códec WM8731
 * 2. Detección de fallos críticos mediante el Hardware Watchdog (HWWDT)
 *
 * @section isr_i2s ISR del periférico I2S (PRGCRC_I2S_IRQHandler)
 * Gestiona las transferencias de audio bidireccionales:
 * - TX: Extrae muestras del buffer circular y las envía al códec
 * - RX: Lee muestras del códec y las almacena en el buffer circular
 *
 * @section isr_nmi ISR de NMI (NMI_Handler)
 * Captura el estado del sistema cuando el watchdog detecta un fallo:
 * - Almacena el estado de los buffers circulares para diagnóstico post-mortem
 * - Espera el reset automático del sistema por el HWWDT
 *
 * @note Frecuencia de muestreo de audio: 48 kHz
 * @note Las ISR deben ejecutarse lo más rápido posible para no perder muestras
 *
 * @warning Los errores críticos en las ISR detienen la alimentación del HWWDT,
 *          provocando un reset del sistema para recuperación automática
 */

// Cabeceras de los módulos propios
#include "circ_buf.h"
// Cabeceras de los módulos HAL y BSP
#include "FM4_WM8731.h"
#include "HAL_FM4_i2s.h"
#include "HAL_FM4_hwwdt.h"
// Cabeceras estándar
#include <stdint.h>


// =============================================================================
// VARIABLES GLOBALES PARA DIAGNÓSTICO POST-MORTEM
// =============================================================================

/**
 * @brief Variables de diagnóstico del estado de los buffers circulares
 *
 * Estas variables se utilizan en el manejador NMI para capturar el estado
 * de los buffers circulares en el momento en que el HWWDT detecta un fallo.
 *
 * @note Deben declararse en sección .noinit para preservar sus valores
 *       tras un reset del sistema
 */
uint8_t g_tx_buf_empty;  ///< Estado del buffer TX: 1 = vacío, 0 = no vacío
uint8_t g_tx_buf_full;   ///< Estado del buffer TX: 1 = lleno, 0 = no lleno
uint8_t g_rx_buf_empty;  ///< Estado del buffer RX: 1 = vacío, 0 = no vacío
uint8_t g_rx_buf_full;   ///< Estado del buffer RX: 1 = lleno, 0 = no lleno


// =============================================================================
// RUTINAS DE SERVICIO DE INTERRUPCIÓN
// =============================================================================


/**
 * @brief ISR de interrupción no enmascarable (NMI)
 *
 * Esta función se ejecuta cuando ocurre una interrupción NMI, típicamente
 * generada por el Hardware Watchdog (HWWDT) antes de provocar un reset del sistema.
 *
 * Comportamiento según configuración:
 *
 * - Captura el estado de los buffers circulares para diagnóstico post-mortem:
 *   - g_tx_buf_empty: indica si el buffer de transmisión estaba vacío
 *   - g_tx_buf_full: indica si el buffer de transmisión estaba lleno
 *   - g_rx_buf_empty: indica si el buffer de recepción estaba vacío
 *   - g_rx_buf_full: indica si el buffer de recepción estaba lleno
 * - Entra en bucle infinito esperando el reset por HWWDT
 * - Las variables globales permiten análisis post-mortem tras el reset
 *
 * @note Esta ISR tiene la máxima prioridad en el sistema Cortex-M
 * @note El HWWDT debe estar configurado para generar interrupción NMI antes del reset
 * @note Las variables g_tx_buf_* y g_rx_buf_* deben estar
 *       en sección .noinit para preservar sus valores tras el reset
 *
 * @warning Si esta función se ejecuta, indica que el sistema no ha alimentado
 *          el watchdog a tiempo, señal de un posible bloqueo o mal funcionamiento
 */
void NMI_Handler(void)
{

    /**
     * @brief    *
     * TODO:
     *   Implementa el algoritmo:
     *
     *      si (si la NMI fue generada por el Hardware Watchdog)
     *        {
     *            registrar estado de buffers circulares para diagnóstico post-mortem
     *            detener la ejecución (bucle infinito), espera reset de HWWDT
     *        }
     */

}


/**
 * @brief Rutina de servicio de interrupción del periférico I2S
 *
 * Esta ISR se ejecuta cuando se produce alguno de los siguientes eventos:
 * - El buffer de transmisión I2S está libre y puede aceptar nuevos datos
 * - El buffer de recepción I2S tiene datos disponibles para leer
 *
 * Operación de transmisión (TX):
 * 1. Verifica si hay espacio en el buffer de transmisión del I2S
 * 2. Extrae una muestra del buffer circular de transmisión (g_tx_buffer)
 * 3. Envía la muestra al códec WM8731 (canal izquierdo, silencio en derecho)
 *
 * Operación de recepción (RX):
 * 1. Verifica si hay datos nuevos en el buffer de recepción del I2S
 * 2. Lee la muestra estéreo del códec WM8731
 * 3. Almacena el canal izquierdo en el buffer circular de recepción (g_rx_buffer)
 *
 * @note Esta función se ejecuta en contexto de interrupción
 * @note Debe ser lo más rápida posible para no perder muestras
 * @note Los buffers circulares g_tx_buffer y g_rx_buffer deben estar correctamente inicializados
 *
 * @warning Si los buffers están vacíos (TX) o llenos (RX), detiene la ejecución
 *          indicando un error crítico en el dimensionamiento o procesamiento
 *
 * @see circ_buf_pop() Extrae dato del buffer circular
 * @see circ_buf_push() Inserta dato en el buffer circular
 * @see FM4_WM8731_wr() Escribe datos al códec de audio
 * @see FM4_WM8731_rd() Lee datos del códec de audio
 */
void PRGCRC_I2S_IRQHandler(void)
{

  // ---------------------------------------------------------------------------
  // GESTIÓN DE TRANSMISIÓN I2S (TX)
  // ---------------------------------------------------------------------------


  if (I2S_isTxBufferFree()) {

    // Extraer siguiente muestra del buffer circular de transmisión
    int16_t txdata;
    uint8_t error = circ_buf_pop(&g_tx_buffer, &txdata);

    // Verificar que la extracción fue exitosa
    if (error != 0) {
       /**
        * ERROR: Buffer de transmisión vacío
        * Causa probable:
        * - El bucle principal no genera datos suficientemente rápido
        * - El buffer es demasiado pequeño
        * - La ISR se está ejecutando más rápido que el procesamiento
        */
        //__BKPT(2); // Breakpoint de error crítico
        while(1); // Dejo de alimentar al hwwdt. ERROR crítico
    }
    // Enviar muestra al códec WM8731
    // Canal izquierdo con dato, canal derecho en silencio (0)
    FM4_WM8731_wr(txdata, 0);
  }

  // ---------------------------------------------------------------------------
  // GESTIÓN DE RECEPCIÓN I2S (RX)
  // ---------------------------------------------------------------------------

  if (I2S_isRxBufferNotEmpty()) {

    // Leer muestra del códec WM8731
    int16_t chL_rx, chR_rx;  // Canal izquierdo y derecho
    FM4_WM8731_rd(&chL_rx, &chR_rx);

    // Almacenar solo el canal izquierdo en el buffer circular
    uint8_t error_push = circ_buf_push(&g_rx_buffer, chL_rx);
    // Verificar que la inserción fue exitosa
    if (error_push != 0) {
      /**
       * ERROR: Buffer de recepción lleno
       * Causa probable:
       * - El bucle principal no procesa datos suficientemente rápido
       * - El buffer es demasiado pequeño
       * - El procesamiento consume más tiempo que el periodo de muestreo
       */
      //__BKPT(3); // Breakpoint de error crítico
      while(1); // Dejo de alimentar al hwwdt. Error crítico
    }
  }
}
// EOF
