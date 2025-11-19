/**
 * @file circ_buf.h
 * @date :2025/10/19 19:00:51
 * @brief Implementación de un buffer circular.
 *
 * Este archivo define las estructuras de datos y las funciones para
 * gestionar un buffer circular de muestras de audio estéreo.
 *
 * @note
 * El buffer circular permite almacenar y recuperar muestras de forma eficiente
 * entre el bucle principal y las rutinas de interrupción (ISR).
 *
 * - El número efectivo de slots utilizables en el buffer es CIRC_BUF_SIZE - 1.
 * - El buffer está vacío cuando head == tail.
 * - El buffer está lleno cuando (head + 1) % CIRC_BUF_SIZE == tail.
 *
 * - head indica la posición donde se escribirá el próximo dato (puntero de escritura).
 * - tail indica la posición de donde se leerá el próximo dato (puntero de lectura).
 *
 * Funciones disponibles:
 *   - circ_buf_init()      : Inicializa el buffer circular.
 *   - circ_buf_is_empty()  : Comprueba si el buffer está vacío.
 *   - circ_buf_is_full()   : Comprueba si el buffer está lleno.
 *   - circ_buf_push()      : Inserta una muestra en el buffer.
 *   - circ_buf_pop()       : Extrae una muestra del buffer.
 *
 * Objetos y variables declaradas:
 *   - g_rx_buffer: Buffer circular global para recepción (declaración extern).
 *   - g_tx_buffer: Buffer circular global para transmisión (declaración extern).
 */

#ifndef _CIRC_BUF_H_
#define _CIRC_BUF_H_

#include <stdint.h>

#define CIRC_BUF_SIZE 8  /**< Número de muestras en el buffer circular */


/**
 * @struct circ_buf_t
 * @brief Estructura que representa un buffer circular de muestras de audio.
 */
typedef struct {
    int16_t buffer[CIRC_BUF_SIZE];   /**< Array de muestras  */
    uint16_t head;      /**< Índice de la cabeza (posición de escritura) */
    uint16_t tail;      /**< Índice de la cola (posición de lectura) */
} circ_buf_t;


/**
 * @brief Buffer circular global para recepción de muestras de audio.
 *        Usado por la ISR de recepción y el bucle principal.
 */
extern circ_buf_t g_rx_buffer;

/**
 * @brief Buffer circular global para transmisión de muestras de audio.
 *        Usado para compartir datos entre el bucle principal y la ISR de transmisión.
 */
extern circ_buf_t g_tx_buffer;


/**
 * @brief Inicializa el buffer circular.
 * @param cb Puntero a la estructura del buffer circular.
 * @param head Valor inicial para el índice de escritura (head).
 * @param tail Valor inicial para el índice de lectura (tail).
 *
 * Esta función establece los índices de escritura (head) y lectura (tail).
 * Permite definir el estado inicial del buffer, normalmente ambos en cero
 *    para indicar que está vacío.
 */
void circ_buf_init(circ_buf_t * const cb, uint16_t head, uint16_t tail);

/**
 * @brief Comprueba si el buffer circular está vacío.
 * @param cb Puntero a la estructura del buffer circular.
 * @return 1 si está vacío, 0 en caso contrario.
 * @note Un buffer está vacío cuando head == tail
 */
uint8_t circ_buf_is_empty(circ_buf_t * const cb);

/**
 * @brief Comprueba si el buffer circular está lleno.
 * @param cb Puntero a la estructura del buffer circular.
 * @return 1 si está lleno, 0 en caso contrario.
 * @note Un buffer está lleno cuando (head + 1) % size == tail
 */
uint8_t circ_buf_is_full(circ_buf_t * const cb);

/**
 * @brief Inserta una muestra de audio en el buffer circular.
 * @param cb Puntero a la estructura del buffer circular.
 * @param item Muestra  a insertar.
 * @return 0 si tiene éxito, -1 si el buffer está lleno.
 */
int8_t circ_buf_push(circ_buf_t * const cb, int16_t item);

/**
 * @brief Extrae una muestra de audio del buffer circular.
 * @param cb Puntero a la estructura del buffer circular.
 * @param item Puntero donde se almacenará la muestra extraída.
 * @return 0 si tiene éxito, -1 si el buffer está vacío.
 */
int8_t circ_buf_pop(circ_buf_t * const cb, int16_t * const item);

#endif  /* _CIRC_BUF_H_ */
