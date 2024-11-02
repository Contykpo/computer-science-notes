section .rodata ; Poner aca todas las mascaras y coeficientes que necesiten para el filtro
    ; Constantes de luminosidad
    ; Luminosidad = 0.2126 * R + 0.7152 * G + 0.0722 * B
    ALIGN 16
    red_coefficient:    times 4 dd 0.2126
    green_coefficient:  times 4 dd 0.7152
    blue_coefficient:   times 4 dd 0.0722
    mask_right_most_channel: times 4 dd 0x00_00_00_FF
    rgb_shuffle: dd 0xFF_00_00_00, 0xFF_04_04_04, 0xFF_08_08_08, 0xFF_0C_0C_0C
    full_alpha: times 4 dd 0xFF_00_00_00


section .text

; Marca un ejercicio como aun no completado (esto hace que no corran sus tests)
FALSE EQU 0
; Marca un ejercicio como hecho
TRUE  EQU 1

; Marca el ejercicio 1 como hecho (`true`) o pendiente (`false`).
;
; Funciones a implementar:
;   - ej1

global EJERCICIO_1_HECHO
EJERCICIO_1_HECHO: db TRUE ; Cambiar por `TRUE` para correr los tests.

; Convierte una imagen dada (`src`) a escala de grises y la escribe en el
; canvas proporcionado (`dst`).
;
; Para convertir un pixel a escala de grises alcanza con realizar el siguiente
; calculo:
; luminosidad = 0.2126 * rojo + 0.7152 * verde + 0.0722 * azul 
;
; Como los pixeles de las imagenes son RGB entonces el pixel destino sera
; rojo  = luminosidad
; verde = luminosidad
; azul  = luminosidad
; alfa  = 255
;
; Parametros:
;   - dst:    La imagen destino. Esta a color (RGBA) en 8 bits sin signo por
;             canal.
;   - src:    La imagen origen A. Esta a color (RGBA) en 8 bits sin signo por
;             canal.
;   - width:  El ancho en pixeles de `src` y `dst`.
;   - height: El alto en pixeles de `src` y `dst`.

global ej1
ej1:
    ; Guardamos los registros base
    push rbp
    mov rbp, rsp

    ; Parametros
    ; rdi = dst, rsi = src, edx = width, ecx = height

    ; Inicializamos registros SIMD con los coeficientes de luminosidad
    movdqa xmm8, [rgb_shuffle]
    movaps xmm7, [red_coefficient]
    movaps xmm6, [green_coefficient]
    movaps xmm5, [blue_coefficient]
    movdqa xmm4, [full_alpha]   	

    ; Numero total de pixeles
    mov eax, ecx
    mul edx           	            ; eax = width * height (total pixels)
    xor r9, r9                 	    ; r9d = i = 0 (indice de pixeles)
    xor r10, r10

.loop:
    cmp r9d, eax                 	    ; Comparamos indice con el total de pixeles
    jge .end_loop                	; Si indice >= total, salimos del bucle

    ; Cargamos 4 pixeles RGBA en xmm0
    movdqu xmm0, [rsi + r10]

    ; Extraemos los canales RGB
    movdqa xmm1, xmm0            	; Copia de los pixeles
    pand xmm1, [mask_right_most_channel]          	; Mascara para extraer el canal rojo

    movdqa xmm2, xmm0            	; Copia de los pixeles
    psrld xmm2, 8               	; Movemos 8 bits a la derecha para obtener el canal verde
    pand xmm2, [mask_right_most_channel]          	; Mascara para extraer el canal verde

    movdqa xmm3, xmm0            	; Copia de los pixeles
    psrld xmm3, 16                	; Movemos 8 bits a la derecha para obtener el canal azul
    pand xmm3, [mask_right_most_channel]          	; Mascara para extraer el canal azul

    ; Convertimos a flotantes y multiplicamos por los factores de luminosidad
    cvtdq2ps xmm1, xmm1          	; Convertimos rojo a flotante
    mulps xmm1, xmm7             	; Multiplicamos por el coeficiente rojo

    cvtdq2ps xmm2, xmm2          	; Convertimos verde a flotante
    mulps xmm2, xmm6             	; Multiplicamos por el coeficiente verde

    cvtdq2ps xmm3, xmm3          	; Convertimos azul a flotante
    mulps xmm3, xmm5             	; Multiplicamos por el coeficiente azul

    ; Sumamos los resultados parciales
    addps xmm1, xmm2
    addps xmm1, xmm3

    ; Convertimos de flotante a entero
    cvttps2dq xmm1, xmm1

    pshufb xmm1, xmm8
    por xmm1, xmm4

    movdqu [rdi + r10], xmm1 	; Guardamos en la imagen destino

    add r9d, 4                   	; Incrementamos indice en 4, ya que son 4 pixeles procesados
    add r10, 16
    jmp .loop                    	; Repetimos el bucle

.end_loop:
    ; Restauramos registros base
    pop rbp
    ret
