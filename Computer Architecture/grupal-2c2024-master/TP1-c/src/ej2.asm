section .rodata
; Poner acá todas las máscaras y coeficientes que necesiten para el filtro

ALIGN 16
shuffle_keeping_rg_mask: dd 0xFF_01_FF_00, 0xFF_05_FF_04, 0xFF_09_FF_08, 0xFF_0D_FF_0C
r_mask: 								times 4 dd 0x00_00_00_FF ; Mascara que toma solo el color azul
g_mask: 								times 4 dd 0x00_00_FF_00 ; Mascara que toma solo el color azul
b_mask: 								times 4 dd 0x00_FF_00_00 ; Mascara que toma solo el color azul
alpha_mask: 							times 4 dd 0xFF_00_00_00 ; Mascara que toma solo el alpha
three_in_4_dwords: 						times 4 dd 3.0
one_hundred_ninety_two_in_4_dwords: 	times 4 dd 192
sixty_four_in_4_dwords: 				times 4 dd 64
three_hundred_eighty_four_in_4_dwords: 	times 4 dd 384
two_hundred_fifty_five_in_4_dwords: 	times 4 dd 255

section .text

; Marca un ejercicio como aún no completado (esto hace que no corran sus tests)
FALSE EQU 0
; Marca un ejercicio como hecho
TRUE  EQU 1

; Marca el ejercicio 2 como hecho (`true`) o pendiente (`false`).
;
; Funciones a implementar:
;   - ej1
global EJERCICIO_2_HECHO
EJERCICIO_2_HECHO: db TRUE ; Cambiar por `TRUE` para correr los tests.

; Aplica un efecto de "mapa de calor" sobre una imagen dada (`src`). Escribe la
; imagen resultante en el canvas proporcionado (`dst`).
;
; Para calcular el mapa de calor lo primero que hay que hacer es computar la
; "temperatura" del pixel en cuestión:
; ```
; temperatura = (rojo + verde + azul) / 3
; ```
;
; Cada canal del resultado tiene la siguiente forma:
; ```
; |          ____________________
; |         /                    \
; |        /                      \        Y = intensidad
; | ______/                        \______
; |
; +---------------------------------------
;              X = temperatura
; ```
;
; Para calcular esta función se utiliza la siguiente expresión:
; ```
; f(x) = min(255, max(0, 384 - 4 * |x - 192|))
; ```
;
; Cada canal esta offseteado de distinta forma sobre el eje X, por lo que los
; píxeles resultantes son:
; ```
; temperatura  = (rojo + verde + azul) / 3
; salida.rojo  = f(temperatura)
; salida.verde = f(temperatura + 64)
; salida.azul  = f(temperatura + 128)
; salida.alfa  = 255
; ```
;
; Parámetros:
;   - dst:    La imagen destino. Está a color (RGBA) en 8 bits sin signo por
;             canal.
;   - src:    La imagen origen A. Está a color (RGBA) en 8 bits sin signo por
;             canal.
;   - width:  El ancho en píxeles de `src` y `dst`.
;   - height: El alto en píxeles de `src` y `dst`.
global ej2
ej2:
	; Te recomendamos llenar una tablita acá con cada parámetro y su
	; ubicación según la convención de llamada. Prestá atención a qué
	; valores son de 64 bits y qué valores son de 32 bits.
	;
	; r/m64 = rgba_t*  dst		(rdi)
	; r/m64 = rgba_t*  src		(rsi)
	; r/m32 = uint32_t width	(edx)
	; r/m32 = uint32_t height	(ecx)

	push rbp
	mov rbp, rsp

	;Cargamos todas las mascaras y numeros que deberemos utilizar
	movdqa xmm15, [one_hundred_ninety_two_in_4_dwords]		;xmm15 = 192|192|192|192
	movdqa xmm14, [shuffle_keeping_rg_mask]
	movdqa xmm13, [b_mask]
	movdqa xmm12, [three_in_4_dwords]
	movdqa xmm11, [sixty_four_in_4_dwords]
	movdqa xmm10, [alpha_mask]					;xmm9 = 4|4|4|4
	movdqa xmm8, [three_hundred_eighty_four_in_4_dwords]	;xmm8 = 384|384|384|384
	movdqa xmm7, [two_hundred_fifty_five_in_4_dwords]		;xmm7 = 255|255|255|255	

	mov eax, edx
	mul ecx				;eax = total de pixeles de la imagen

	xor r8, r8			;r8 = 0, indice del proximo pixel

	.loop:

		movdqu xmm0, [rsi + r8 * 4]		; Cargamos 4 pixeles a xmm0
		movdqa xmm1, xmm0
		pshufb xmm1, xmm14				; Guardamos los valores de rojo y verde de cada pixel en espacios de 16 bytes
		phaddw xmm1, xmm0				; Hacemos suma horizontal y en los primeros 64bits quedan los resultados de sumar rojo y verde de cada bit en espacios de 16bits
		pmovzxwd xmm1, xmm1				; Extendemos los resultados de las sumas a 32bits
		pand xmm0, xmm13				; Nos quedamos solo con el azul en xmm0
		psrld xmm0, 16 					; Pasamos los azules a los bits menos significados de cada dword
		paddd xmm0, xmm1				; Queda en xmm0 la suma de los tres canales de cada pixel en dwords
		cvtdq2ps xmm0, xmm0				; Convertimos suma de tres canales a floats
		divps xmm0, xmm12				; Dividimos por 3
		cvttps2dq xmm0, xmm0			; Volvemos a convertir a enteros de 32 truncando	

		movdqa xmm3, xmm0				; xmm3 = temperatura0|temperatura1|temperatura2|temperatura3

		;Calculamos nuevo rojo
		psubd xmm0, xmm15				;Restamos 192 a todas las temperaturas
		pabsd xmm0, xmm0				;Calculamos el valor absoluto del resultado de la resta
		psllw xmm0, 2					;Multiplicamos todos los valores absolutos por 4
		movdqa xmm1, xmm8				;xmm1 = 384
		psubusw xmm1, xmm0				;Hacemos una resta sin signo saturada entre 384 y el resultado de la multiplicacion, 
										;como es saturada, si el resultado es menor a 0, se queda en 0
		pminsd xmm1, xmm7				;xmm1 = min(255, resultado de la resta anterior para cada dword)

		movdqa xmm2, xmm1				;xmm2 = Pixeles finales con solo valor de rojo
		paddd xmm3, xmm11				;xmm3 = temperaturas + 64
		movdqa xmm0, xmm3						

		;Nuevo verde
		psubd xmm0, xmm15
		pabsd xmm0, xmm0
		psllw xmm0, 2
		movdqa xmm1, xmm8	
		psubusw xmm1, xmm0
												
		pminsd xmm1, xmm7						

		pslld xmm1, 8							
		por xmm2, xmm1					;xmm2 = Pixeles finales con rojo y verde

		paddd xmm3, xmm11				;xmm3 = temperaturas + 128
		movdqa xmm0, xmm3

		;Nuevo azul
		psubd xmm0, xmm15
		pabsd xmm0, xmm0
		psllw xmm0, 2
		movdqa xmm1, xmm8
		psubusw xmm1, xmm0		 
									
		pminsd xmm1, xmm7			

		pslld xmm1, 16
		por xmm2, xmm1							;xmm2 = Pixeles finales con rgb
		por xmm2, xmm10							;xmm2 = Pixeles completos con su valor de alpha original
		movdqu [rdi + r8 * 4], xmm2				;Escribimos los 4 pixeles a la imagen final

		add r8, 4						; Incrementamos indice en 4 pues procesamos de a 4
		cmp r8d, eax
		jl .loop
	
	;Fin procesamiento

	pop rbp

	ret