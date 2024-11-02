section .text

; Marca un ejercicio como aun no completado (esto hace que no corran sus tests)
FALSE EQU 0
; Marca un ejercicio como hecho
TRUE  EQU 1

; Marca el ejercicio 3A como hecho (`true`) o pendiente (`false`).
;
; Funciones a implementar:
;   - ej3a
global EJERCICIO_3A_HECHO
EJERCICIO_3A_HECHO: db TRUE ; Cambiar por `TRUE` para correr los tests.

; Dada una imagen origen escribe en el destino `scale * px + offset` por cada
; pixel en la imagen.
;
; Parametros:
;   - dst_depth: La imagen destino (mapa de profundidad). Esta en escala de
;                grises a 32 bits con signo por canal.
;   - src_depth: La imagen origen (mapa de profundidad). Esta en escala de
;                grises a 8 bits sin signo por canal.
;   - scale:     El factor de escala. Es un entero con signo de 32 bits.
;                Multiplica a cada pixel de la entrada.
;   - offset:    El factor de corrimiento. Es un entero con signo de 32 bits.
;                Se suma a todos los pixeles luego de escalarlos.
;   - width:     El ancho en pixeles de `src_depth` y `dst_depth`.
;   - height:    El alto en pixeles de `src_depth` y `dst_depth`.

global ej3a
ej3a:
    ; Parámetros
    ; rdi: int32_t* dst_depth
    ; rsi: uint8_t* src_depth
    ; edx: int32_t scale
    ; ecx: int32_t offset
    ; r8d: uint32_t width
    ; r9d: uint32_t height

    push rbp
	mov rbp, rsp

	movd xmm15, edx	; xmm15 = escala
	movd xmm14, ecx	; xmm14 = offset

	pshufd xmm15, xmm15, 0b00_00_00_00 ;xmm13 = escala|escala|escala|escala
	pshufd xmm14, xmm14, 0b00_00_00_00 ;xmm12 = offset|offset|offset|offset 

	mov eax, r8d	;eax = Ancho imagen
	mul r9d			;eax = total de pixeles
	xor r8, r8		;r8 = 0, sera nuestro indice de pixel actual

	.loop:

		pmovzxbd xmm0, dword [rsi + r8]	;xmm0 = 4 pixeles actuales

		pmulld xmm0, xmm15			;xmm0 = pixeles * escala
		paddd xmm0, xmm14			;xmm0 = pixeles * escala + offset

		movdqu [rdi + r8 * 4], xmm0	

		add r8, 4					;Incrementamos contador en 4 pues procesamos de a 4pixeles		
		cmp r8d, eax
		jl .loop

	pop rbp

	ret


; Marca el ejercicio 3B como hecho (`true`) o pendiente (`false`).
;
; Funciones a implementar:
;   - ej3b
global EJERCICIO_3B_HECHO
EJERCICIO_3B_HECHO: db TRUE ; Cambiar por `TRUE` para correr los tests.

; Dadas dos imagenes de origen (`a` y `b`) en conjunto con sus mapas de
; profundidad escribe en el destino el pixel de menor profundidad por cada
; pixel de la imagen. En caso de empate se escribe el pixel de `b`.
;
; Parametros:
;   - dst:     La imagen destino. Esta a color (RGBA) en 8 bits sin signo por
;              canal.
;   - a:       La imagen origen A. Esta a color (RGBA) en 8 bits sin signo por
;              canal.
;   - depth_a: El mapa de profundidad de A. Esta en escala de grises a 32 bits
;              con signo por canal.
;   - b:       La imagen origen B. Esta a color (RGBA) en 8 bits sin signo por
;              canal.
;   - depth_b: El mapa de profundidad de B. Esta en escala de grises a 32 bits
;              con signo por canal.
;   - width:  El ancho en pixeles de todas las imagenes parametro.
;   - height: El alto en pixeles de todas las imagenes parametro.

global ej3b
ej3b:
    ; Parámetros
    ; rdi: rgba_t* dst
    ; rsi: rgba_t* a
    ; rdx: int32_t* depth_a
    ; rcx: rgba_t* b
    ; r8:  int32_t* depth_b
    ; r9d: uint32_t width
	; [rbp + 16]: uint32_t height
    
    push    rbp
    mov     rbp, rsp

    mov     r10, rdx             	; Guardamos el valor de rdx pues sera alterado en su parte baja al multiplicar
    mov     eax, dword [rbp + 16]	; eax = alto de la imagen
    mul     r9d                  	; eax = total de pixeles
    mov     rdx, r10             	; Restauramos rdx

    xor     r9, r9             		; r9 = 0, indice del pixel actual

.loop_b:
    ; Cargamos 4 pixeles de cada imagen y el mapa de profundidad
    movdqu xmm0, [rsi + r9 * 4] ; xmm0 = 4 pixeles actuales de la imagen A
    movdqu xmm1, [rcx + r9 * 4] ; xmm1 = 4 pixeles actuales de la imagen B
    movdqu xmm2, [rdx + r9 * 4] ; xmm2 = 4 valores de profundidad de A
    movdqu xmm3, [r8 + r9 * 4]  ; xmm3 = 4 valores de profundidad de B

    ; Comparamos profundidades
    pcmpgtd xmm3, xmm2           ; xmm3 = (depth_b > depth_a)

    pand    xmm0, xmm3           ; xmm0 = (depth_b > depth_a) ? imagen A : 0
    pandn   xmm3, xmm1           ; xmm3 = (depth_b <= depth_a) ? imagen B : 0
	por 	xmm0, xmm3			 ; xmm0 = xmm0 | xmm3

    ; Guardamos resultado en dst
    movdqu [rdi + r9 * 4], xmm0

    add     r9, 4               ; Incrementamos el indice en 4, pues procesamos de a 4 pixeles
    cmp     r9d, eax
    jl      .loop_b 

    ; Restauramos registros base
    pop     rbp

    ret
