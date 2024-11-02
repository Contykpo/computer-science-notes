/* ** por compatibilidad se omiten tildes **
==============================================================================
TALLER System Programming - Arquitectura y Organizacion de Computadoras - FCEN
==============================================================================

  Definiciones globales del sistema.
*/

#include <stdio.h>
#include <stdint.h>

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Misc */
/* -------------------------------------------------------------------------- */
// Y Filas
#define SIZE_N 40
#define ROWS   SIZE_N

// X Columnas
#define SIZE_M 80
#define COLS   SIZE_M

/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80

//Tamaño que ocupa cada elemento (caracter) en el buffer de video
#define VIDEO_BUFFER_ELEMENT_SIZE 2

/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT         35

#define GDT_IDX_NULL_DESC 0
#define GDT_IDX_CODE_0 1
#define GDT_IDX_CODE_3 2
#define GDT_IDX_DATA_0 3
#define GDT_IDX_DATA_3 4
#define GDT_IDX_VIDEO  5
#define GDT_IDX_TSS_INICIAL 6
#define GDT_IDX_TSS_IDLE 7

/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_IDX_OFFSET 3
#define GDT_TI_OFFSET 2
#define GDT_OFF_NULL_DESC (GDT_IDX_NULL_DESC << GDT_IDX_OFFSET)
#define GDT_OFF_VIDEO  (GDT_IDX_VIDEO << GDT_IDX_OFFSET)

/*Table indicators para los segment selectors*/
/* -------------------------------------------------------------------------- */
#define GDT_INDICATOR 0
#define LDT_INDICATOR 1

/*Privilege levels*/
/* -------------------------------------------------------------------------- */
#define DESC_PRIVILEGE_LEVEL_0 0
#define DESC_PRIVILEGE_LEVEL_1 1
#define DESC_PRIVILEGE_LEVEL_2 2
#define DESC_PRIVILEGE_LEVEL_3 3


/* COMPLETAR - Valores para los selectores de segmento de la GDT 
 * Definirlos a partir de los índices de la GDT, definidos más arriba 
 * Hint: usar operadores "<<" y "|" (shift y or) */

#define GDT_CODE_0_SEL (GDT_IDX_CODE_0 << GDT_IDX_OFFSET) | GDT_INDICATOR << GDT_TI_OFFSET | DESC_PRIVILEGE_LEVEL_0
#define GDT_DATA_0_SEL (GDT_IDX_DATA_0 << GDT_IDX_OFFSET) | GDT_INDICATOR << GDT_TI_OFFSET | DESC_PRIVILEGE_LEVEL_0
#define GDT_CODE_3_SEL (GDT_IDX_CODE_3 << GDT_IDX_OFFSET) | GDT_INDICATOR << GDT_TI_OFFSET | DESC_PRIVILEGE_LEVEL_3
#define GDT_DATA_3_SEL (GDT_IDX_DATA_3 << GDT_IDX_OFFSET) | GDT_INDICATOR << GDT_TI_OFFSET | DESC_PRIVILEGE_LEVEL_3


// Macros para trabajar con segmentos de la GDT.

// SEGM_LIMIT_4KIB es el limite de segmento visto como bloques de 4KIB
// principio del ultimo bloque direccionable.
#define GDT_LIMIT_4KIB(X)  (((X) / 4096) - 1)
#define GDT_LIMIT_BYTES(X) ((X)-1)

#define GDT_LIMIT_LOW(limit)  (uint16_t)(((uint32_t)(limit)) & 0x0000FFFF)
#define GDT_LIMIT_HIGH(limit) (uint8_t)((((uint32_t)(limit)) >> 16) & 0x0F)

#define GDT_BASE_LOW(base)  (uint16_t)(((uint32_t)(base)) & 0x0000FFFF)
#define GDT_BASE_MID(base)  (uint8_t)((((uint32_t)(base)) >> 16) & 0xFF)
#define GDT_BASE_HIGH(base) (uint8_t)((((uint32_t)(base)) >> 24) & 0xFF)

/* COMPLETAR - Valores de atributos */ 
#define DESC_CODE_DATA 0x1
#define DESC_SYSTEM 0x0
#define DESC_TYPE_EXECUTE_READ 0xA
#define DESC_TYPE_READ_WRITE 0x2
#define DESC_PRESENT 1
#define DESC_AVL 0
#define DESC_L 0
#define DESC_GRANULARITY 1
#define DESC_NO_GRANULARITY 1
#define DESC_DB 1

/* COMPLETAR - Tamaños de segmentos */ 
#define FLAT_SEGM_SIZE GDT_LIMIT_4KIB(UINT32_MAX)
#define VIDEO_SEGM_SIZE GDT_LIMIT_BYTES(VIDEO_FILS * VIDEO_COLS * VIDEO_BUFFER_ELEMENT_SIZE)


/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */

// direccion fisica de comienzo del bootsector (copiado)
#define BOOTSECTOR 0x00001000
// direccion fisica de comienzo del kernel
#define KERNEL 0x00001200
// direccion fisica del buffer de video
#define VIDEO 0x000B8000
// direccion fisica de la pagina de memoria compartida
#define SHARED 0x0001D000


/* MMU */
/* -------------------------------------------------------------------------- */
/* Definan:
VIRT_PAGE_OFFSET(X) devuelve el offset dentro de la página, donde X es una dirección virtual
VIRT_PAGE_TABLE(X)  devuelve la page table entry correspondiente, donde X es una dirección virtual
VIRT_PAGE_DIR(X)    devuelve el page directory entry, donde X es una dirección virtual
CR3_TO_PAGE_DIR(X)  devuelve el page directory, donde X es el contenido del registro CR3
MMU_ENTRY_PADDR(X)  devuelve la dirección física de la base de un page frame o de un page table, donde X es el campo de 20 bits en una PTE o PDE
*/

#define VIRT_PAGE_OFFSET(virtual_address) (uint32_t)(virtual_address & 0x0FFF)
#define VIRT_PAGE_TABLE(virtual_address)  (uint32_t)((virtual_address >> 12) & 0x03FF)
#define VIRT_PAGE_DIR(virtual_address)    (uint32_t)(virtual_address >> 22)
#define CR3_TO_PAGE_DIR(cr3)              (paddr_t)(cr3 & 0xFFFFF000)
#define MMU_ENTRY_PADDR(mmu_entry)        (paddr_t)(mmu_entry >> 12)    



#define MMU_P (1 << 0)
#define MMU_W (1 << 1)
#define MMU_U (1 << 2)

#define PAGE_SIZE 4096

// direccion virtual del codigo
#define TASK_CODE_VIRTUAL 0x08000000
#define TASK_CODE_PAGES   2
#define TASK_STACK_BASE   0x08003000
#define TASK_SHARED_PAGE  0x08003000

// direccion virtual de memoria compartida on demand
#define ON_DEMAND_MEM_START_VIRTUAL    0x07000000
#define ON_DEMAND_MEM_END_VIRTUAL      0x07000FFF
#define ON_DEMAND_MEM_START_PHYSICAL   0x03000000

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */
#define KERNEL_PAGE_DIR     (0x00025000)
#define KERNEL_PAGE_TABLE_0 (0x00026000)
#define KERNEL_STACK        (0x00025000)


#endif //  __DEFINES_H__
