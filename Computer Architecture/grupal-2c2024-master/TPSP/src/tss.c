/* ** por compatibilidad se omiten tildes **
================================================================================
 TALLER System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "defines.h"
#include "kassert.h"
#include "mmu.h"

/*
 * TSS de la tarea inicial (sólo se usa para almacenar el estado del procesador
 * al hacer el salto a la tarea idle
 */
tss_t tss_initial = {0};
// TSS de la tarea idle
tss_t tss_idle = {
  .ss1 = 0,
  .cr3 = KERNEL_PAGE_DIR,
  .eip = TASK_IDLE_CODE_START,
  .eflags = EFLAGS_IF,
  .esp = KERNEL_STACK,
  .ebp = KERNEL_STACK,
  .cs = GDT_CODE_0_SEL,
  .ds = GDT_DATA_0_SEL,
  .es = GDT_DATA_0_SEL,
  .gs = GDT_DATA_0_SEL,
  .fs = GDT_DATA_0_SEL,
  .ss = GDT_DATA_0_SEL,
};
// Lista de tss, de aquí se cargan (guardan) las tss al hacer un cambio de contexto
tss_t tss_tasks[MAX_TASKS] = {0};

gdt_entry_t tss_gdt_entry_for_task(tss_t* tss) {
  return (gdt_entry_t) {
    .g = 0,
    .limit_15_0 = sizeof(tss_t) - 1,
    .limit_19_16 = 0x0,
    .base_15_0 = GDT_BASE_LOW(tss),
    .base_23_16 = GDT_BASE_MID(tss),
    .base_31_24 = GDT_BASE_HIGH(tss),
    .p = 1,
    .type = DESC_TYPE_32BIT_TSS,
    .s = DESC_SYSTEM,
    .dpl = 0,
  };
}

/**
 * Define el valor de la tss para el indice task_id
 */
void tss_set(tss_t tss, int8_t task_id) {
  kassert(task_id >= 0 && task_id < MAX_TASKS, "Invalid task_id");

  tss_tasks[task_id] = tss;
}

/**
 * Crea una tss con los valores por defecto y el eip code_start
 */
tss_t tss_create_user_task(paddr_t code_start) {

  //COMPLETAR: es correcta esta llamada a mmu_init_task_dir?
  // Inicializamos el directorio de paginas para la tarea
  uint32_t cr3 = mmu_init_task_dir(code_start);

  // Direccion virtual para la pila de usuario
  vaddr_t stack = TASK_STACK_BASE; 

  // Direccion virtual del codigo
  vaddr_t code_virt = TASK_CODE_VIRTUAL; 

  // Asignamos una pagina para la pila de nivel 0
  vaddr_t stack0 = mmu_alloc_page(); 

  // Agregamos un espacio de pila para el nivel 0
  vaddr_t esp0 = stack0 + PAGE_SIZE; 

  return (tss_t) {
    .cr3 = cr3,
    .esp = stack,
    .ebp = stack,
    .eip = code_virt,
    .cs = GDT_CODE_3_SEL,
    .ds = GDT_DATA_3_SEL,
    .es = GDT_DATA_3_SEL,
    .fs = GDT_DATA_3_SEL,
    .gs = GDT_DATA_3_SEL,
    .ss = GDT_DATA_3_SEL,
    .ss0 = GDT_DATA_0_SEL,   // Selector de segmento para la pila de nivel 0
    .esp0 = esp0,            // Apunta al tope de la pila de nivel 0
    .eflags = EFLAGS_IF,
  };
}

/**
 * Inicializa las primeras entradas de tss (inicial y idle)
 */
void tss_init(void) {
  // COMPLETAR
  gdt[GDT_IDX_TASK_IDLE] = tss_gdt_entry_for_task(&tss_idle);
  gdt[GDT_IDX_TASK_INITIAL] = tss_gdt_entry_for_task(&tss_initial);
}
