/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"
#include "defines.h"

#include "kassert.h"

#define PDE_ATTR_OFFSET_RW 1
#define PDE_ATTR_OFFSET_US 2
#define PDE_ATTR_OFFSET_PWT 3
#define PDE_ATTR_OFFSET_PCD 4
#define PDE_ATTR_OFFSET_ACCESSED 5
#define PDE_ATTR_OFFSET_IGNORED 6

#define PTE_ATTR_OFFSET_RW PDE_ATTR_OFFSET_RW
#define PTE_ATTR_OFFSET_US PDE_ATTR_OFFSET_US
#define PTE_ATTR_OFFSET_PWT PDE_ATTR_OFFSET_PWT
#define PTE_ATTR_OFFSET_PCD PDE_ATTR_OFFSET_PCD
#define PTE_ATTR_OFFSET_ACCESSED PDE_ATTR_OFFSET_ACCESSED
#define PTE_ATTR_OFFSET_DIRTY 6
#define PTE_ATTR_OFFSET_PAT 7
#define PTE_ATTR_OFFSET_GRANULARITY 8
#define PTE_ATTR_OFFSET_IGNORED 9

#define PAGE_ATTR_READ_WRITE 1
#define PAGE_ATTR_READ_ONLY 0
#define PAGE_ATTR_USER_LEVEL 1
#define PAGE_ATTR_SYSTEM_LEVEL 0
#define PAGE_ATTR_CACHE_ENABLED 0
#define PAGE_ATTR_NOT_DIRTY 0
#define PAGE_ATTR_4KB_GRANULARITY 0
#define PAGE_ATTR_WRITE_THROUGH_DISABLED 0

#define PAGE_ATTR_NOT_ACCESSED 0

#define PAGE_ATTR_ABSENT_PAGE 0

#define VADDR_OFFSET_SIZE 12

#define PAGE_PHYS_ADDR_FROM_PTE(pte) (paddr_t)(pte->page<<VADDR_OFFSET_SIZE)
#define PT_PHYS_ADDR_FROM_PDE(pde) (paddr_t)(pde->pt<<VADDR_OFFSET_SIZE)

#define PDE(RW, US, PWT, PCD, ACCESSED) (uint32_t)(1  | RW << PDE_ATTR_OFFSET_RW \
                                                      | US << PDE_ATTR_OFFSET_US \
                                                      | PWT << PDE_ATTR_OFFSET_PWT \
                                                      | PCD << PDE_ATTR_OFFSET_PCD \
                                                      | ACCESSED << PDE_ATTR_OFFSET_ACCESSED \
                                                      | 0x1 << PDE_ATTR_OFFSET_IGNORED)

#define PTE(RW, US, PWT, PCD, ACCESSED, DIRTY, GRANULARITY) (uint32_t)(1  | RW << PTE_ATTR_OFFSET_RW \
                                                                          | US << PTE_ATTR_OFFSET_US \
                                                                          | PWT << PTE_ATTR_OFFSET_PWT \
                                                                          | PCD << PTE_ATTR_OFFSET_PCD \
                                                                          | ACCESSED << PTE_ATTR_OFFSET_ACCESSED \
                                                                          | DIRTY << PTE_ATTR_OFFSET_DIRTY \
                                                                          | GRANULARITY << PTE_ATTR_OFFSET_GRANULARITY\
                                                                          | 0x7 << PTE_ATTR_OFFSET_IGNORED)

static pd_entry_t* kpd = (pd_entry_t*)KERNEL_PAGE_DIR;
static pt_entry_t* kpt = (pt_entry_t*)KERNEL_PAGE_TABLE_0;

//static const uint32_t identity_mapping_end = 0x003FFFFF;
//static const uint32_t user_memory_pool_end = 0x02FFFFFF;

static paddr_t next_free_kernel_page = 0x100000;
static paddr_t next_free_user_page = 0x400000;

/**
 * kmemset asigna el valor c a un rango de memoria interpretado
 * como un rango de bytes de largo n que comienza en s
 * @param s es el puntero al comienzo del rango de memoria
 * @param c es el valor a asignar en cada byte de s[0..n-1]
 * @param n es el tamaño en bytes a asignar
 * @return devuelve el puntero al rango modificado (alias de s)
*/
static inline void* kmemset(void* s, int c, size_t n) {
  uint8_t* dst = (uint8_t*)s;
  for (size_t i = 0; i < n; i++) {
    dst[i] = c;
  }
  return dst;
}

/**
 * zero_page limpia el contenido de una página que comienza en addr
 * @param addr es la dirección del comienzo de la página a limpiar
*/
static inline void zero_page(paddr_t addr) {
  kmemset((void*)addr, 0x00, PAGE_SIZE);
}


void mmu_init(void) {}


/**
 * mmu_next_free_kernel_page devuelve la dirección física de la próxima página de kernel disponible. 
 * Las páginas se obtienen en forma incremental, siendo la primera: next_free_kernel_page
 * @return devuelve la dirección de memoria de comienzo de la próxima página libre de kernel
 */
paddr_t mmu_next_free_kernel_page(void) {
  paddr_t ret_page_addr = next_free_kernel_page;

  next_free_kernel_page += PAGE_SIZE;

  return ret_page_addr;
}

/**
 * mmu_next_free_user_page devuelve la dirección de la próxima página de usuarix disponible
 * @return devuelve la dirección de memoria de comienzo de la próxima página libre de usuarix
 */
paddr_t mmu_next_free_user_page(void) {
  paddr_t ret_page_addr = next_free_user_page;

  next_free_user_page += PAGE_SIZE;

  return ret_page_addr;
}

/**
 * mmu_init_kernel_dir inicializa las estructuras de paginación vinculadas al kernel y
 * realiza el identity mapping
 * @return devuelve la dirección de memoria de la página donde se encuentra el directorio
 * de páginas usado por el kernel
 */
paddr_t mmu_init_kernel_dir(void) {

  kpd[0] = (pd_entry_t){
      .attrs  = PDE(PAGE_ATTR_READ_WRITE, 
                    PAGE_ATTR_SYSTEM_LEVEL, 
                    PAGE_ATTR_WRITE_THROUGH_DISABLED, 
                    PAGE_ATTR_CACHE_ENABLED, 
                    PAGE_ATTR_NOT_ACCESSED),
      .pt     = ((uint32_t)kpt >> VADDR_OFFSET_SIZE)
    };

  for(uint32_t i = 0; i < 1024; ++i)
  {
    kpt[i] = (pt_entry_t){
      .attrs  = PTE(PAGE_ATTR_READ_WRITE,
                    PAGE_ATTR_SYSTEM_LEVEL,
                    PAGE_ATTR_WRITE_THROUGH_DISABLED,
                    PAGE_ATTR_CACHE_ENABLED,
                    PAGE_ATTR_NOT_ACCESSED,
                    PAGE_ATTR_NOT_DIRTY,
                    PAGE_ATTR_4KB_GRANULARITY),
      .page   = i
    };
  }

  return (paddr_t)kpd;
}

/**
 * mmu_map_page agrega las entradas necesarias a las estructuras de paginación de modo de que
 * la dirección virtual virt se traduzca en la dirección física phy con los atributos definidos en attrs
 * @param cr3 el contenido que se ha de cargar en un registro CR3 al realizar la traducción
 * @param virt la dirección virtual que se ha de traducir en phy
 * @param phy la dirección física que debe ser accedida (dirección de destino)
 * @param attrs los atributos a asignar en la entrada de la tabla de páginas
 * @attention Se asume que las estructuras de paginacion estan en direcciones de memoria identity-mapped
 */
void mmu_map_page(uint32_t cr3, vaddr_t virt, paddr_t phy, uint32_t attrs) {

  uint32_t page_directory_index = VIRT_PAGE_DIR(virt);
  uint32_t page_table_index     = VIRT_PAGE_TABLE(virt);

  pd_entry_t* page_directory_entry = &((pd_entry_t*)CR3_TO_PAGE_DIR(cr3))[page_directory_index];

  //Si entrada en el directorio de paginas no presente, la cargamos y asignamos una nueva pagina para la page table
  if(!(page_directory_entry->attrs & 0x1)){
    page_directory_entry->attrs = PDE(PAGE_ATTR_READ_WRITE, 
                                      PAGE_ATTR_USER_LEVEL, 
                                      PAGE_ATTR_WRITE_THROUGH_DISABLED, 
                                      PAGE_ATTR_CACHE_ENABLED, 
                                      PAGE_ATTR_NOT_ACCESSED);

     page_directory_entry->pt = mmu_next_free_kernel_page() >> VADDR_OFFSET_SIZE;
  }

  pt_entry_t* page_table_entry    = &((pt_entry_t*)PT_PHYS_ADDR_FROM_PDE(page_directory_entry))[page_table_index];

  page_table_entry->attrs = attrs;
  page_table_entry->page  = phy >> 12;
}

/**
 * mmu_unmap_page elimina la entrada vinculada a la dirección virt en la tabla de páginas correspondiente
 * @param virt la dirección virtual que se ha de desvincular
 * @return la dirección física de la página desvinculada
 * @attention Se asume que las estructuras de paginacion estan en direcciones de memoria identity-mapped
 */
paddr_t mmu_unmap_page(uint32_t cr3, vaddr_t virt) {
  uint32_t page_directory_index = VIRT_PAGE_DIR(virt);
  uint32_t page_table_index     = VIRT_PAGE_TABLE(virt);

  pd_entry_t page_directory_entry = ((pd_entry_t*)CR3_TO_PAGE_DIR(cr3))[page_directory_index];
  pt_entry_t* page_table_entry    = &((pt_entry_t*)PT_PHYS_ADDR_FROM_PDE((&page_directory_entry)))[page_table_index];

  paddr_t page_physical_address = PAGE_PHYS_ADDR_FROM_PTE(page_table_entry);

  page_table_entry->attrs = PAGE_ATTR_ABSENT_PAGE;

  return page_physical_address;
}

#define DST_VIRT_PAGE 0xA00000
#define SRC_VIRT_PAGE 0xB00000
#define COPY_PAGE_VIRT_PAGE_ATTR PTE( PAGE_ATTR_READ_WRITE, \
                                      PAGE_ATTR_SYSTEM_LEVEL,\
                                      PAGE_ATTR_WRITE_THROUGH_DISABLED,\
                                      PAGE_ATTR_CACHE_ENABLED,\
                                      PAGE_ATTR_NOT_ACCESSED,\
                                      PAGE_ATTR_NOT_DIRTY,\
                                      PAGE_ATTR_4KB_GRANULARITY)

/**
 * copy_page copia el contenido de la página física localizada en la dirección src_addr a la página física ubicada en dst_addr
 * @param dst_addr la dirección a cuya página queremos copiar el contenido
 * @param src_addr la dirección de la página cuyo contenido queremos copiar
 *
 * Esta función mapea ambas páginas a las direcciones SRC_VIRT_PAGE y DST_VIRT_PAGE, respectivamente, realiza
 * la copia y luego desmapea las páginas. Usar la función rcr3 definida en i386.h para obtener el cr3 actual
 */
void copy_page(paddr_t dst_addr, paddr_t src_addr) {
  mmu_map_page(rcr3(), DST_VIRT_PAGE, dst_addr, COPY_PAGE_VIRT_PAGE_ATTR);

  mmu_map_page(rcr3(), SRC_VIRT_PAGE, src_addr, COPY_PAGE_VIRT_PAGE_ATTR);

  tlbflush();

  for(size_t i = 0; i < (PAGE_SIZE/sizeof(uint32_t)); ++i)
    ((uint32_t*)DST_VIRT_PAGE)[i] = ((uint32_t*)SRC_VIRT_PAGE)[i];
  
    
  mmu_unmap_page(rcr3(), DST_VIRT_PAGE);
  mmu_unmap_page(rcr3(), SRC_VIRT_PAGE);

  tlbflush();
}

#define TASK_PAGE_DIRECTORY_ATTR  PDE(\
                                  PAGE_ATTR_READ_WRITE, \
                                  PAGE_ATTR_USER_LEVEL, \
                                  PAGE_ATTR_WRITE_THROUGH_DISABLED, \
                                  PAGE_ATTR_CACHE_ENABLED, \
                                  PAGE_ATTR_NOT_ACCESSED)

#define TASK_CODE_PAGE_ATTR PTE(\
                            PAGE_ATTR_READ_ONLY,\
                            PAGE_ATTR_USER_LEVEL,\
                            PAGE_ATTR_WRITE_THROUGH_DISABLED,\
                            PAGE_ATTR_CACHE_ENABLED,\
                            PAGE_ATTR_NOT_ACCESSED,\
                            PAGE_ATTR_NOT_DIRTY,\
                            PAGE_ATTR_4KB_GRANULARITY)

#define TASK_STACK_PAGE_ATTR  PTE(\
                              PAGE_ATTR_READ_WRITE ,\
                              PAGE_ATTR_USER_LEVEL ,\
                              PAGE_ATTR_WRITE_THROUGH_DISABLED ,\
                              PAGE_ATTR_CACHE_ENABLED ,\
                              PAGE_ATTR_NOT_ACCESSED ,\
                              PAGE_ATTR_NOT_DIRTY,\
                              PAGE_ATTR_4KB_GRANULARITY)

#define TASK_SHARED_PAGE_ATTR PTE(\
                              PAGE_ATTR_READ_WRITE ,\
                              PAGE_ATTR_USER_LEVEL ,\
                              PAGE_ATTR_WRITE_THROUGH_DISABLED ,\
                              PAGE_ATTR_CACHE_ENABLED ,\
                              PAGE_ATTR_NOT_ACCESSED ,\
                              PAGE_ATTR_NOT_DIRTY,\
                              PAGE_ATTR_4KB_GRANULARITY)

#define TASK_CODE_0_VADDR 0x08000000
#define TASK_CODE_1_VADDR 0x08001000
#define TASK_STACK_VADDR  0x08002000
#define TASK_SHARED_VADDR 0x08003000

 /**
 * mmu_init_task_dir inicializa las estructuras de paginación vinculadas a una tarea cuyo código se encuentra en la dirección phy_start
 * @pararm phy_start es la dirección donde comienzan las dos páginas de código de la tarea asociada a esta llamada
 * @return el contenido que se ha de cargar en un registro CR3 para la tarea asociada a esta llamada
 */
paddr_t mmu_init_task_dir(paddr_t phy_start) {

  paddr_t new_pd_addr = mmu_next_free_kernel_page();

  pd_entry_t* new_pd = (pd_entry_t*)new_pd_addr;

  //Mapeamos los primeros 4mb de memoria con identity mapping para no romper gdtr ni idtr
  new_pd[0] = kpd[0];

  //Mapeamos 2 paginas para el codigo de la tarea 
  mmu_map_page(new_pd_addr, TASK_CODE_0_VADDR, phy_start, TASK_CODE_PAGE_ATTR);
  mmu_map_page(new_pd_addr, TASK_CODE_1_VADDR, phy_start + PAGE_SIZE, TASK_CODE_PAGE_ATTR);

  //Mapeamos 1 pagina en el area libre de usuario para el stack de la tarea
  mmu_map_page(new_pd_addr, TASK_STACK_VADDR, mmu_next_free_user_page(), TASK_STACK_PAGE_ATTR);

  return new_pd_addr;
}

// COMPLETAR: devuelve true si se atendió el page fault y puede continuar la ejecución 
// y false si no se pudo atender
bool page_fault_handler(vaddr_t virt) {
  static int contador = 0;

  print("Atendiendo page fault...", 0, contador, C_FG_WHITE | C_BG_BLACK);

  contador++;

  if(virt < TASK_SHARED_VADDR || virt >= (TASK_SHARED_VADDR + PAGE_SIZE))
    return false;

  mmu_map_page(rcr3(), virt, mmu_next_free_kernel_page(), TASK_SHARED_PAGE_ATTR);

  return true;
}