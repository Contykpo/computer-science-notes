<<<<<<< HEAD
;########### ESTOS SON LOS OFFSETS Y TAMAÑO DE LOS STRUCTS
NODO_LENGTH            EQU     32      ; tamaño de nodo_t
LONGITUD_OFFSET        EQU     24      ; offset del campo longitud en nodo_t

PACKED_NODO_LENGTH     EQU     21      ; tamaño de packed_nodo_t
PACKED_LONGITUD_OFFSET EQU     17      ; offset del campo longitud en packed_nodo_t

section .text

global cantidad_total_de_elementos
global cantidad_total_de_elementos_packed

;extern uint32_t obtener_cantidad_total_de_elementos(void* lista, int longitud_offset);
; registros: lista[rdi], longitud_offset[rsi]
obtener_cantidad_total_de_elementos:
    push rbp
    mov rbp, rsp
    mov rax, 0                  ; Inicializamos el acumulador para el total

    ; Puntero al primer nodo de la lista
    mov rdi, [rdi]              ; rdx = lista->head

.loop: 
    test rdi, rdi               ; Verificamos si el nodo actual es NULL
    jz .end                     ; Si es NULL, terminamos

    ; Sumamos longitud del nodo actual al acumulador
    mov ecx, [rdi + rsi]        ; ecx = nodo->longitud
    add rax, rcx                ; Acumulamos en rax

    ; Avanzamos al siguiente nodo
    mov rdi, [rdi]              ; rdx = nodo->next

    jmp .loop                   ; Repetimos el ciclo

.end:
    pop rbp                     
    ret                         ; Retornamos con el resultado en rax


;extern uint32_t cantidad_total_de_elementos(lista_t* lista);
; registros: lista[rdi]
cantidad_total_de_elementos:
    push rbp
    mov rbp, rsp
    mov rsi, LONGITUD_OFFSET                ; Asignamos el offset de longitud correspondiente para lista_t

    call obtener_cantidad_total_de_elementos
    
    pop rbp
    ret


;extern uint32_t cantidad_total_de_elementos_packed(packed_lista_t* lista);
; registros: lista[rdi]
cantidad_total_de_elementos_packed:
    push rbp
    mov rbp, rsp
    mov rsi, PACKED_LONGITUD_OFFSET         ; Asignamos el offset de longitud correspondiente para packed_lista_t

    call obtener_cantidad_total_de_elementos
    
    pop rbp
    ret
=======


;########### ESTOS SON LOS OFFSETS Y TAMAÑO DE LOS STRUCTS
; Completar:
NODO_LENGTH	EQU	??
LONGITUD_OFFSET	EQU	??

PACKED_NODO_LENGTH	EQU	??
PACKED_LONGITUD_OFFSET	EQU	??

;########### SECCION DE DATOS
section .data

;########### SECCION DE TEXTO (PROGRAMA)
section .text

;########### LISTA DE FUNCIONES EXPORTADAS
global cantidad_total_de_elementos
global cantidad_total_de_elementos_packed

;########### DEFINICION DE FUNCIONES
;extern uint32_t cantidad_total_de_elementos(lista_t* lista);
;registros: lista[?]
cantidad_total_de_elementos:
	ret

;extern uint32_t cantidad_total_de_elementos_packed(packed_lista_t* lista);
;registros: lista[?]
cantidad_total_de_elementos_packed:
	ret

>>>>>>> upstream/master
