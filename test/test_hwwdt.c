/**
 * @file test_hwwdt.c
 * @date :2025/11/04 09:01:27
 * @brief Programa de test para el Hardware Watchdog Timer (HWWDT)
 *
 * Este programa implementa un test básico para verificar el funcionamiento
 * del Hardware Watchdog Timer. El test simula diferentes escenarios de operación:
 *
 * Secuencia de test:
 * 1. Inicialización: LED RGB parpadea en ROJO durante 3 segundos
 * 2. Operación normal: LED RGB parpadea en VERDE (sistema funciona correctamente)
 * 3. Simulación de bloqueo: Al detectar pulsación larga en SW2, entra en bucle
 *    infinito con LED RGB parpadeando en AMARILLO (simula fallo del sistema)
 *
 * Comportamiento esperado del HWWDT:
 * - Durante operación normal: el watchdog debe ser alimentado periódicamente
 * - Durante bloqueo simulado: el watchdog NO se alimenta, provocando:
 *   a) Interrupción NMI (si está configurada)
 *   b) Reset del sistema tras timeout
 *
 * Código de colores LED RGB:
 * - 🔴 ROJO: Proceso de inicialización (3 segundos)
 * - 🟢 VERDE: Operación normal del sistema
 * - 🟡 AMARILLO: Sistema bloqueado (simulación de fallo)
 * - 🔵 AZUL: Interrupción NMI detectada (manejada en NMI_Handler)
 */


// Cabeceras de los módulos propios
#include "pulsaciones.h"

// Cabeceras de los módulos HAL y BSP
#include "HAL_SysTick.h"
#include "HAL_FM4_hwwdt.h"
#include "FM4_leds_sw.h"

// Cabeceras estándar
#include <stdint.h>

/**
 *  @brief Función main(). Incluye la configuración e inicialización de
 *  periféricos y el "scheduling" de tareas
 */
int32_t main(void)
{
  // Configuración de otros periféricos
  // Config GPIO para uso de leds y SW2
  LedsSwInit();

  // Configuración e inicio Systick
  SysTick_Init(SystemCoreClock / 1000); //  base de tiempos -> 1ms



  // parpadeo RGB rojo durante 3 segundos, fin inicializacion
  for (uint16_t i = 0; i < 3000; i++)
  {
    while (SysTick_ChkOvf() == 0)
    { /* empty while*/
    }
    parpadeo512ms(RED);
  }


  uint8_t pulsacion = 0;
  while (1)
  {
    // 🗲 Tareas que se ejecutan cada ~1ms
    if (SysTick_ChkOvf())
    { // evalúa pulsación
      uint8_t entrada = Sw2Read();
      pulsacion = pulsaciones(entrada,0);
      // parpadeo RGB verde
      parpadeo512ms(GREEN);
    }

    // Utilizamos la pulsación larga para modelar un bloqueo de la aplicación
    if (pulsacion == 2)
    {
      LedRGB(OFF);
      while (1)
      { // parpadeo RGB amarillo
        if (SysTick_ChkOvf())
        {
          parpadeo512ms(YELLOW);
        }
      }
    }
  }
}
