extern sumar_c
extern restar_c
;########### SECCION DE DATOS
section .data

;########### SECCION DE TEXTO (PROGRAMA)
section .text

;########### LISTA DE FUNCIONES EXPORTADAS

global alternate_sum_4
global alternate_sum_4_simplified
global alternate_sum_8
global product_2_f
global product_9_f
global alternate_sum_4_using_c

;########### DEFINICION DE FUNCIONES
; uint32_t alternate_sum_4(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4);
<<<<<<< HEAD
; registros: x1[edi], x2[esi], x3[edx], x4[ecx]
global alternate_sum_4
alternate_sum_4:
    ; Prologo
    push rbp
    mov rbp, rsp

    ; x1, x2, x3, x4 estan en los registros: rdi, rsi, rdx, rcx
    mov eax, edi  ; eax = x1 (movemos rdi a eax)
    sub eax, esi  ; eax = eax - x2 (eax - rsi)
    add eax, edx  ; eax = eax + x3 (eax + rdx)
    sub eax, ecx  ; eax = eax - x4 (eax - rcx)

    ; Epilogo
    pop rbp
    ret


; uint32_t alternate_sum_4_using_c(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4);
; registros: x1[edi], x2[esi], x3[edx], x4[ecx]
global alternate_sum_4_using_c
alternate_sum_4_using_c:
    ; Prologo
    push rbp
    mov rbp, rsp

    ; Llamamos a restar_c(x1, x2)
    mov edi, edi  ; primer argumento (x1) is already in edi
    mov esi, esi  ; segundo argumento (x2) is already in esi
    call restar_c ; eax = x1 - x2

    ; Llamamos a sumar_c(resultado anterior, x3)
    mov edi, eax  ; primer argumento (resultado de restar_c)
    mov esi, edx  ; segundo argumento (x3)
    call sumar_c  ; eax = (x1 - x2) + x3

    ; Llamamos a restar_c(resultado anterior, x4)
    mov edi, eax  ; primer argumento (resultado de sumar_c)
    mov esi, ecx  ; segundo argumento (x4)
    call restar_c ; eax = ((x1 - x2) + x3) - x4

    ; Epilogo
    pop rbp
    ret


; uint32_t alternate_sum_4_simplified(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4);
; registros: x1[edi], x2[esi], x3[edx], x4[ecx]
global alternate_sum_4_simplified
alternate_sum_4_simplified:

    mov eax, edi    ; eax = x1
    sub eax, esi    ; eax = eax - x2
    add eax, edx    ; eax = eax + x3
    sub eax, ecx    ; eax = eax - x4
    ret


; uint32_t alternate_sum_8(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4, uint32_t x5, uint32_t x6, uint32_t x7, uint32_t x8);
; registros y pila: x1[edi], x2[esi], x3[edx], x4[ecx], x5[r8d], x6[r9d], x7[rbp+0x10], x8[rbp+0x18]
global alternate_sum_8
alternate_sum_8:
    ; Prologo
    push rbp
    mov rbp, rsp

    ; x1 a x6 estan en registros, x7 y x8 en la pila
    mov eax, edi   ; eax = x1
    sub eax, esi   ; eax = eax - x2
    add eax, edx   ; eax = eax + x3
    sub eax, ecx   ; eax = eax - x4
    add eax, r8d   ; eax = eax + x5
    sub eax, r9d   ; eax = eax - x6

    ; Cargar x7 y x8 desde la pila
    mov r8d, [rbp+0x10]  ; x7
    mov r9d, [rbp+0x18]  ; x8
    add eax, r8d       ; eax = eax + x7
    sub eax, r9d       ; eax = eax - x8

    ; Epilogo
    pop rbp
    ret
=======
; registros: x1[?], x2[?], x3[?], x4[?]
alternate_sum_4:
	;prologo
	; COMPLETAR

	;recordar que si la pila estaba alineada a 16 al hacer la llamada
	;con el push de RIP como efecto del CALL queda alineada a 8

	;epilogo
	; COMPLETAR
	ret

; uint32_t alternate_sum_4_using_c(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4);
; registros: x1[rdi], x2[rsi], x3[rdx], x4[rcx]
alternate_sum_4_using_c:
	;prologo
	push rbp ; alineado a 16
	mov rbp,rsp

	; COMPLETAR

	;epilogo
	pop rbp
	ret



; uint32_t alternate_sum_4_simplified(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4);
; registros: x1[?], x2[?], x3[?], x4[?]
alternate_sum_4_simplified:
	ret


; uint32_t alternate_sum_8(uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4, uint32_t x5, uint32_t x6, uint32_t x7, uint32_t x8);
; registros y pila: x1[?], x2[?], x3[?], x4[?], x5[?], x6[?], x7[?], x8[?]
alternate_sum_8:
	;prologo

	; COMPLETAR

	;epilogo
	ret
>>>>>>> upstream/master


; SUGERENCIA: investigar uso de instrucciones para convertir enteros a floats y viceversa
;void product_2_f(uint32_t * destination, uint32_t x1, float f1);
<<<<<<< HEAD
;registros: destination[edi], x1[esi], f1[xmm0]
global product_2_f
product_2_f:
    push rbp
    mov rbp, rsp

    ; destination en rdi, x1 en rsi, f1 en xmm0
    cvtsi2ss xmm1, esi  ; Convertir x1 (rsi) a float y almacenarlo en xmm1
    mulss xmm0, xmm1    ; Multiplicar xmm0 (f1) por xmm1 (x1 convertido)
    cvttss2si eax, xmm0 ; Convertir el resultado truncado a entero y guardarlo en eax
    mov [rdi], eax      ; Guardar el resultado en el puntero destino (rdi)

    pop rbp

    ret
=======
;registros: destination[?], x1[?], f1[?]
product_2_f:
	ret
>>>>>>> upstream/master


;extern void product_9_f(double * destination
;, uint32_t x1, float f1, uint32_t x2, float f2, uint32_t x3, float f3, uint32_t x4, float f4
;, uint32_t x5, float f5, uint32_t x6, float f6, uint32_t x7, float f7, uint32_t x8, float f8
;, uint32_t x9, float f9);
<<<<<<< HEAD
;registros y pila: destination[rdi], x1[esi], f1[xmm0], x2[edx], f2[xmm1], x3[ecx], f3[xmm2], x4[r8d], f4[xmm3]
;	, x5[r9d], f5[xmm4], x6[rbp+0x10], f6[xmm5], x7[rbp+0x18], f7[xmm6], x8[rbp+0x20], f8[xmm7],
;	, x9[0x28], f9[0x30]
global product_9_f
product_9_f:
    ; Prologo
    push rbp              ; Guardamos el valor de rbp en la pila
    mov rbp, rsp          ; Establecemos rbp al valor actual de rsp (nuevo frame base)

    ; Convertimos los floats (f1 - f8) en los registros xmm a doubles
    cvtss2sd xmm0, xmm0
    cvtss2sd xmm1, xmm1
    cvtss2sd xmm2, xmm2
    cvtss2sd xmm3, xmm3
    cvtss2sd xmm4, xmm4
    cvtss2sd xmm5, xmm5
    cvtss2sd xmm6, xmm6
    cvtss2sd xmm7, xmm7

    ; Multiplicamos los floats convertidos a doubles y acumulamos el resultado en xmm0
    mulsd xmm0, xmm1      ; xmm0 *= xmm1 (f1 * f2)
    mulsd xmm0, xmm2      ; xmm0 *= xmm2 (f1 * f2 * f3)
    mulsd xmm0, xmm3      ; xmm0 *= xmm3 (f1 * f2 * f3 * f4)
    mulsd xmm0, xmm4      ; xmm0 *= xmm4 (f1 * f2 * f3 * f4 * f5)
    mulsd xmm0, xmm5      ; xmm0 *= xmm5 (f1 * f2 * f3 * f4 * f5 * f6)
    mulsd xmm0, xmm6      ; xmm0 *= xmm6 (f1 * f2 * f3 * f4 * f5 * f6 * f7)
    mulsd xmm0, xmm7      ; xmm0 *= xmm7 (f1 * f2 * f3 * f4 * f5 * f6 * f7 * f8)

    ; Convertimos f9 a double (f9 está en [rbp + 0x30]) y multiplicamos xmm0 *= xmm1 (f1 * f2 * ... * f9)
    cvtss2sd xmm1, dword [rbp + 0x30]
    mulsd xmm0, xmm1

    ; Convertimos los enteros x1 - x9 a doubles y multiplicarlos acumulativamente
    cvtsi2sd xmm1, esi
    cvtsi2sd xmm2, edx
    cvtsi2sd xmm3, ecx
    cvtsi2sd xmm4, r8d
    cvtsi2sd xmm5, r9d
    cvtsi2sd xmm6, dword [rbp + 0x10]
    cvtsi2sd xmm7, dword [rbp + 0x18]

    ; Multiplicamos cada entero convertido a double
    mulsd xmm0, xmm1      ; xmm0 *= xmm1
    mulsd xmm0, xmm2      ; xmm0 *= xmm2
    mulsd xmm0, xmm3      ; xmm0 *= xmm3
    mulsd xmm0, xmm4      ; xmm0 *= xmm4
    mulsd xmm0, xmm5      ; xmm0 *= xmm5
    mulsd xmm0, xmm6      ; xmm0 *= xmm6
    mulsd xmm0, xmm7      ; xmm0 *= xmm7

    ; Convertimos x8 y x9 a doubles y los multiplicamos
    cvtsi2sd xmm1, dword [rbp + 0x20]
    cvtsi2sd xmm2, dword [rbp + 0x28]

    ; Multiplicamos el resultado acumulado por x8 y luego por x9 
    mulsd xmm0, xmm1      ; xmm0 *= xmm1
    mulsd xmm0, xmm2      ; xmm0 *= xmm2

    ; Guardar el resultado final en el puntero destination (rdi)
    movsd qword [rdi], xmm0

    ; Epilogo
    ; Restauramos el valor original de rbp y retornamos
    pop rbp
    ret
=======
;registros y pila: destination[rdi], x1[?], f1[?], x2[?], f2[?], x3[?], f3[?], x4[?], f4[?]
;	, x5[?], f5[?], x6[?], f6[?], x7[?], f7[?], x8[?], f8[?],
;	, x9[?], f9[?]
product_9_f:
	;prologo
	push rbp
	mov rbp, rsp

	;convertimos los flotantes de cada registro xmm en doubles
	; COMPLETAR

	;multiplicamos los doubles en xmm0 <- xmm0 * xmm1, xmmo * xmm2 , ...
	; COMPLETAR

	; convertimos los enteros en doubles y los multiplicamos por xmm0.
	; COMPLETAR

	; epilogo
	pop rbp
	ret


>>>>>>> upstream/master
