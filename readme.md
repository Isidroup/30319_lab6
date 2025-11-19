# 30319 Laboratorio 6: *Watch-dog timer*

El proyecto consiste en la implementación y configuración de un *watch-dog timer* (WDT) en un sistema embebido basado en la placa FM4. El WDT es un temporizador de seguridad que reinicia el sistema si no se "alimenta" periódicamente, lo que ayuda a recuperar el control en caso de fallos o bloqueos del software.

## Descripción General

Este laboratorio implementa el Hardware Watchdog Timer (HWWDT) del microcontrolador S6E2CCAJ0A de la familia FM4. El proyecto incluye ejemplos de configuración, manejo de interrupciones y pruebas del funcionamiento del watchdog.
El sistema implementa las siguientes funcionalidades:
- Diseño de una capa HAL para el *hw watch-dog timer* del microcontrolador FM4.
- Verificación en un entorno controlado de la capa HAL diseñada.
- Integración del WDT en el sistema implementado en el laboratorio 5.
## Estructura del Proyecto

```
lab6_2025/
│
├── src/ # Archivos fuente principales
│    ├── main.c # Punto de entrada de la aplicación
│    └── isr.c # Implementaciones ISR adicionales
│
├── test/ # Archivos de prueba
│    ├── test_hwwdt.c # Pruebas básicas del HWWDT
│    └── test_hwwdt_isr.c # Pruebas de interrupciones del HWWDT
│
├── hal/ # Capa de Abstracción de Hardware
│    ├── include/ # Archivos de cabecera HAL
│    │    ├── HAL_FM4_hwwdt.h # Driver del watchdog hardware
│    │    ├── HAL_FM4_gpio.h # Control de GPIO
│    │    ├── HAL_FM4_dtimer.h # Temporizador dual
│    │    ├── HAL_FM4_i2c.h # Comunicación I2C
│    │    ├── HAL_FM4_i2s.h # Comunicación I2S
│    │    └── HAL_SysTick.h # Temporizador del sistema
│    └── src/ # Implementaciones HAL
│
├── bsp/ # Paquete de Soporte de Placa
│    ├── include/ # Cabeceras BSP
│    │    ├── FM4_leds_sw.h # Control de LEDs y pulsadores
│    │    └── FM4_WM8731.h # Interfaz del códec de audio
│    └── src/ # Implementaciones BSP
│
├── shared/ # Bibliotecas compartidas de laboratorios anteriores
│    ├── includes/ # Cabeceras compartidas
│    │     ├── circ_buf.h # Buffer circular
│    │     ├── dds.h # Síntesis digital directa
│    │     ├── lab4.h # Funciones del Lab 4
│    │     ├── lab5.h # Funciones del Lab 5
│    │     └── pulsaciones.h # Manejo de pulsaciones
│    └── lib/ # Bibliotecas compiladas
│
└── build_keil/ # Archivos de compilación Keil μVision
     └── lab6.uvprojx # Archivo de proyecto principal
```

## Características Implementadas

- **Hardware Watchdog Timer (HWWDT)**: Configuración y control del temporizador de vigilancia por hardware
- **Gestión de interrupciones**: Manejo de interrupciones del HWWDT antes del reset
- **Control de GPIO**: Manejo de LEDs y pulsadores de la placa
- **Integración SysTick**: Temporizador del sistema para control temporal
- **Soporte de periféricos**: I2C, I2S para comunicaciones
- **Procesamiento digital de señales**: DDS, buffers circulares
- **Reutilización de código**: Integración con laboratorios 4 y 5

## Requisitos de Hardware

- Placa de desarrollo FM4 con microcontrolador S6E2CCAJ0A
- Códec de audio WM8731 (opcional, para características de audio)
- LEDs y pulsadores integrados en la placa

## Requisitos de Software

- Keil μVision IDE (MDK-ARM)
- Compilador ARM Compiler 6 (ARMCLANG)
- Bibliotecas CMSIS

## Compilación del Proyecto

1. Abrir [`build_keil/lab6.uvprojx`](build_keil/lab6.uvprojx) en Keil μVision
2. Seleccionar el objetivo de compilación deseado:
   - **lab6**: Aplicación principal
   - **Test_HWWDT**: Pruebas del watchdog
3. Compilar el proyecto (F7)
4. Flashear en la placa destino
