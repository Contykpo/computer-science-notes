#include "ej1.h"

<<<<<<< HEAD

=======
>>>>>>> upstream/master
/**
 * Marca el ejercicio 1 como hecho (`true`) o pendiente (`false`).
 *
 * Funciones a implementar:
 *   - ej1
 */
<<<<<<< HEAD
bool EJERCICIO_1_HECHO = true;
=======
bool EJERCICIO_1_HECHO = false;
>>>>>>> upstream/master

/**
 * Convierte una imagen dada (`src`) a escala de grises y la escribe en el
 * canvas proporcionado (`dst`).
 *
 * Para convertir un píxel a escala de grises alcanza con realizar el
 * siguiente cálculo:
 * ```
 * luminosidad = 0.2126 * rojo + 0.7152 * verde + 0.0722 * azul 
 * ```
 *
 * Como los píxeles de las imágenes son RGB entonces el píxel destino será
 * ```
 * rojo  = luminosidad
 * verde = luminosidad
 * azul  = luminosidad
 * alfa  = 255
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
void ej1(rgba_t* dst, rgba_t* src, uint32_t width, uint32_t height)
{
    // Constantes de luminosidad
    const float red_coefficient = 0.2126f;
    const float green_coefficient = 0.7152f;
    const float blue_coefficient = 0.0722f;
    
    for (uint32_t y = 0; y < height; y++)
	{
        for (uint32_t x = 0; x < width; x++)
		{
            // Indice del pixel actual
            uint32_t index = y * width + x;
            
            // Obtenemos componentes RGB de la imagen de origen
            uint8_t r = src[index].r;
            uint8_t g = src[index].g;
            uint8_t b = src[index].b;
            
            // Calculamos la luminosidad ponderada
            uint8_t luminosity = (uint8_t)(red_coefficient * r + green_coefficient * g + blue_coefficient * b);
            
            // Asignamos la misma luminosidad a los canales R, G, B del destino
            dst[index].r = luminosity;
            dst[index].g = luminosity;
            dst[index].b = luminosity;
            
            // El canal alfa siempre es 255
            dst[index].a = 255;
        }
    }
=======
void ej1(
	rgba_t* dst,
	rgba_t* src,
	uint32_t width, uint32_t height
) {
>>>>>>> upstream/master
}
