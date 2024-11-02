#include "task_lib.h"

#define WIDTH TASK_VIEWPORT_WIDTH
#define HEIGHT TASK_VIEWPORT_HEIGHT

#define SHARED_SCORE_BASE_VADDR (PAGE_ON_DEMAND_BASE_VADDR + 0xF00)
#define CANT_PONGS 3


// Auxiliar para mostrar el puntaje en pantalla.
void mostrar_puntaje(screen pantalla, int pong_id, int puntaje) {
    char texto[20];
    snprintf(texto, 20, "Pong %d: ", pong_id);
    task_print_dec(pantalla, puntaje, 2, pong_id % 2 == 0 ? WIDTH / 2 - 3 : WIDTH / 2 + 3, pong_id * 2, 0x0F);
}

void task(void) {

	screen score_screen;

    // Leemos los puntajes de la memoria compartida.
    uint32_t* shared_score = (uint32_t*)SHARED_SCORE_BASE_VADDR;

    // Bucle infinito para mantener la actualizacion de puntajes.
    while (true) {

        // Iteramos sobre cada instancia de Pong y mostramos su puntaje.
        for (int i = 0; i < CANT_PONGS; i++) {
            uint32_t player_1_score = shared_score[i * 2];
            uint32_t player_1_score = shared_score[i * 2 + 1];

            mostrar_puntaje(score_screen, i, player_1_score);
            mostrar_puntaje(score_screen, i, player_2_score);

            pongs_amount++;
        }

        // Se dibuja la pantalla con los puntajes actualizados.
        syscall_draw(pantalla);

        // Agregamos un delay para actualizar los puntajes cada cierto tiempo.
        // task_sleep(10);
    }
}
