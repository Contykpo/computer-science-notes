#include <stdlib.h>
<<<<<<< HEAD
#include <stddef.h>

#include "ej1.h"


=======

#include "ej1.h"

>>>>>>> upstream/master
/**
 * Marca el ejercicio 2 como hecho (`true`) o pendiente (`false`).
 *
 * Funciones a implementar:
 *   - ej1
 */
<<<<<<< HEAD
bool EJERCICIO_2_HECHO = true;
=======
bool EJERCICIO_2_HECHO = false;
>>>>>>> upstream/master


/**
 * Aplica un efecto de "mapa de calor" sobre una imagen dada (`src`). Escribe
 * la imagen resultante en el canvas proporcionado (`dst`).
 *
 * Para calcular el mapa de calor lo primero que hay que hacer es computar la
 * "temperatura" del pixel en cuestión:
 * ```
 * temperatura = (rojo + verde + azul) / 3
 * ```
 *
 * Cada canal del resultado tiene la siguiente forma:
 * ```
 * |          ____________________
 * |         /                    \
 * |        /                      \        Y = intensidad
 * | ______/                        \______
 * |
 * +---------------------------------------
 *              X = temperatura
 * ```
 *
 * Para calcular esta función se utiliza la siguiente expresión:
 * ```
 * f(x) = min(255, max(0, 384 - 4 * |x - 192|))
 * ```
 *
 * Cada canal esta offseteado de distinta forma sobre el eje X, por lo que los
 * píxeles resultantes son:
 * ```
 * temperatura  = (rojo + verde + azul) / 3
 * salida.rojo  = f(temperatura)
 * salida.verde = f(temperatura + 64)
 * salida.azul  = f(temperatura + 128)
 * salida.alfa  = 255
 * ```
 *
 * Parámetros:
 *   - dst:    La imagen destino. Está a color (RGBA) en 8 bits sin signo por
 *             canal.
 *   - src:    La imagen origen A. Está a color (RGBA) en 8 bits sin signo por
 *             canal.
 *   - width:  El ancho en píxeles de `src` y `dst`.
 *   - height: El alto en píxeles de `src` y `dst`.
 */
<<<<<<< HEAD

// Funcion auxiliar para calcular la intensidad de un canal dado una temperatura
static uint8_t f(int32_t x)
{
    // Usamos una formula para obtener la intensidad en el canal de salida
    int32_t result = 384 - 4 * abs(x - 192);

    if (result < 0) result = 0;
    if (result > 255) result = 255;

    return (uint8_t)result;
}

void ej2(rgba_t* dst, rgba_t* src, uint32_t width, uint32_t height)
{
    // Calculamos el total de pixeles
    size_t total_pixels = width * height;

    // Procesamos en bloques de 4 pixeles
    size_t i = 0;
    for (; i + 4 <= total_pixels; i += 4)
	{
        // Temperaturas de 4 pixeles
        uint8_t temperaturas[4];

        // Cargamos los valores RGB de 4 pixeles
        for (int j = 0; j < 4; j++)
		{
            uint8_t r = src[i + j].r;
            uint8_t g = src[i + j].g;
            uint8_t b = src[i + j].b;

            // Calculamos la temperatura del pixel
            temperaturas[j] = (r + g + b) / 3;
        }

        // Calculamos los valores RGB de salida para 4 pixeles
        for (int j = 0; j < 4; j++)
		{
            uint8_t t = temperaturas[j];
  
            dst[i + j].r = f(t);
            dst[i + j].g = f(t + 64);
            dst[i + j].b = f(t + 128);
            dst[i + j].a = 255;
        }
    }

    // Procesamos los pixeles restantes en caso de que no queden bloques de 4 pixeles
    for (; i < total_pixels; i++)
	{
        uint8_t r = src[i].r;
        uint8_t g = src[i].g;
        uint8_t b = src[i].b;
        uint8_t temperatura = (r + g + b) / 3;

        dst[i].r = f(temperatura);
        dst[i].g = f(temperatura + 64);
        dst[i].b = f(temperatura + 128);
        dst[i].a = 255;
    }
=======
void ej2(
	rgba_t* dst,
	rgba_t* src,
	uint32_t width, uint32_t height
) {
>>>>>>> upstream/master
}
