; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TALLER System Programming - Arquitectura y Organizacion de Computadoras - FCEN
; ==============================================================================

%include "print.mac"

global start

extern GDT_DESC
extern IDT_DESC
extern screen_draw_layout
extern idt_init
extern pic_reset
extern pic_enable
extern idt_entries
extern tss_init
extern sched_init

extern run_tests

extern mmu_init_kernel_dir
extern mmu_init_task_dir


;Selector de segmento del TSS de la tarea inicial = {.indice = 11, .tableIndicator = 0, .privilegeLevel = 0}
%define INITIAL_TASK_SELECTOR 11 << 3

;Selector de segmento del TSS de la tarea idle = {.indice = 12, .tableIndicator = 0, .privilegeLevel = 0}
%define IDLE_TASK_SELECTOR 12 << 3

%define FORMATO_MENSAJES_BIENVENIDA (C_FG_WHITE | C_BG_BLACK)

;Segment selector codigo privilegiado = {.indice = 1, .tableIndicator = 0, .privilegeLevel = 0}
%define CS_RING_0_SEL 0x0008    

;Segment selector datos privilegiados = {.indice = 3, .tableIndicator = 0, .privilegeLevel = 0}
%define DS_RING_0_SEL 0x0018    


BITS 16
;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
start_rm_msg db     'Iniciando kernel en Modo Real'
start_rm_len equ    $ - start_rm_msg

start_pm_msg db     'Iniciando kernel en Modo Protegido'
start_pm_len equ    $ - start_pm_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ;Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ;Limpiar parte alta de los registros que usaremos para imprimir el mensaje
    xor bx, bx
    xor cx, cx

    mov ax, FORMATO_MENSAJES_BIENVENIDA

    ;Mensaje de bienvenida a modo real
    print_text_rm start_rm_msg, start_rm_len, ax, bx, cx

    ; Habilitar A20
    ; (revisar las funciones definidas en a20.asm)
    call A20_enable

    ;Cargar la GDT
    lgdt [GDT_DESC]

    ;Setear el bit PE del registro CR0
    mov eax, cr0
    or eax, 0b1
    mov cr0, eax

    ;Saltamos a modo protegido
    jmp CS_RING_0_SEL:modo_protegido

BITS 32

section .data

section .text
modo_protegido:
    ; Establecer selectores de segmentos DS, ES, GS, FS y SS en el segmento de datos de nivel 0
    mov ax, DS_RING_0_SEL
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
    mov ss, ax

    ; COMPLETAR - Establecer el tope y la base de la pila
    mov ebp, 0x25000
    mov esp, 0x25000

    ;Preparamos argumentos para llamar a print_text_pm
    mov ebx, 1
    xor ecx, ecx
    mov eax, FORMATO_MENSAJES_BIENVENIDA

    ;Mostramos mensaje de bienvenida al modo protegido
    print_text_pm start_pm_msg, start_pm_len, eax, ebx, ecx

    ; COMPLETAR - Inicializar pantalla
    call screen_draw_layoutsni

    ;Inicializamos la PD del kernel
    ;eax = Direccion base de la PD
    call mmu_init_kernel_dir

    mov cr3, eax

    ;Activamos paginacion seteando el bit mas alto de CR0
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ; COMPLETAR - Inicializar y cargar la IDT
    
    call idt_init
    lidt [IDT_DESC]

    ; COMPLETAR - Reiniciar y habilitar el controlador de interrupciones
    call pic_reset
    call pic_enable

    ; Inicializar tss
    call tss_init

    ; Inicializar el scheduler
    call sched_init

    ; Cargarmos el registro TR con el selector de la TSS de la tarea inicial
    mov ax, INITIAL_TASK_SELECTOR
    ltr ax

    call tasks_init

    mov ax, 2000
    out 0x40, al
    rol ax, 8
    out 0x40, al

    sti

    jmp IDLE_TASK_SELECTOR:0

    ; Probar syscall
    ;mov eax, 1
    ;int 0x80

    mov eax, cr3
    push eax

    call run_tests

    pop eax
    mov cr3, eax

    ;push 0x18000
    ;call mmu_init_task_dir
    ;mov cr3, eax
    ;pop eax

    ;mov eax, 0x8003000
    ;mov dword [eax], 10

    ;mov eax, 0x08003000
    ;mov cr2, eax
    ;int 0xe

    ; Inicializar el directorio de paginas de la tarea de prueba
    ; Cargar directorio de paginas de la tarea
    ; Restaurar directorio de paginas del kernel

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente 
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $


;; -------------------------------------------------------------------------- ;;

%include "a20.asm"