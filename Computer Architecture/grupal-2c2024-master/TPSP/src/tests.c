#include "mmu.h"
#include "i386.h"
#include "screen.h"

void copy_page(paddr_t dst_addr, paddr_t src_addr);

void run_tests(void)
{
    //Prueba copia
    copy_page(0x210000, 0x25000);

    //Prueba cambio de directorio de paginas
    //uint32_t temp = rcr3();

    paddr_t task_pd_addr = mmu_init_task_dir(0x18000);

    lcr3(task_pd_addr);

    tlbflush();

    ((uint32_t*)(0x08003000))[0] = 10;
    ((uint32_t*)(0x08003001))[0] = 20;

    // //lcr3(temp);

    // tlbflush();
}