extern malloc
extern free
extern fprintf

section .data

section .text

global strCmp
global strClone
global strDelete
global strPrint
global strLen

; ** String **

; int32_t strCmp(char* a, char* b)
<<<<<<< HEAD
; eax = 0 si a y b apuntan a strings iguales
; eax = 1 si a apunta a un string lexicograficamente mayor al de b
; eax = -1 si a apunta a un string lexicograficamente menor al de b
strCmp:

	push rbp
	mov rbp, rsp

	.string_compare_loop:
		mov cl, byte [rdi]				;Obtenemos caracteres en la misma posicion de los strings
		mov dl, byte [rsi]
		cmp cl, dl
		jne .strings_distintos			;Si los caracteres difieren, saltamos al tag .strings_distintos
		inc rdi							;Si no, apuntamos al proximo caracter
		inc rsi
		test cl, cl
		jne .string_compare_loop		;Si el caracter actual no es '\0', aun hay caracteres por comparar

	.strings_iguales:					;Si llegamos aqui es porque los strings son iguales caracter a caracter
		xor rax, rax					;rax = 0
		pop rbp
		ret

	.strings_distintos:
		setg cl							; Si cl (caracter a) > dl (caracter b), cl = -1						
		setl dl							; Caso contrarion, dl = -1
		sub dl, cl
		movsx eax, dl					; Movemos resultado a eax desde dl conservando el signo
		pop rbp
		ret
		
	

; char* strClone(char* a)
strClone:
	push rbp
	mov rbp, rsp
	push r12						
	sub rsp, 8						;Stack alineado a 16bytes
	mov r12, rdi					

	call strLen						;eax = Longitud de la cadena a

	mov edi, eax
	inc edi							;edi = Longitud de la cadena a + 1 para incluir el caracter nulo

	call malloc						;Pedimos memoria para el nuevo string
									;rax = Direccion base del nuevo string

	mov rdi, rax

	.clone_loop:					;Copiamos byte a byte al nuevo string		
		mov cl, byte [r12]			
		mov byte [rdi], cl	
		inc rdi
		inc r12
		test cl, cl					;Si llegamos al caracter de '\0', terminamos de clonar
		jne .clone_loop

	add rsp, 8						;Restauramos stack y registros
	pop r12
	pop rbp

=======
strCmp:
	ret

; char* strClone(char* a)
strClone:
>>>>>>> upstream/master
	ret

; void strDelete(char* a)
strDelete:
<<<<<<< HEAD
	push rbp						;Stack alineada a 16bytes
	mov rbp, rsp					
	call free
	pop rbp
=======
>>>>>>> upstream/master
	ret

; void strPrint(char* a, FILE* pFile)
strPrint:
<<<<<<< HEAD
	push rbp						;Stack alineada a 16bytes
	mov rbp, rsp

	xchg rdi, rsi					;Intercambiamos rdi con rsi pues fprintf los recibe en el orden inverso

	call fprintf

	pop rbp

=======
>>>>>>> upstream/master
	ret

; uint32_t strLen(char* a)
strLen:
<<<<<<< HEAD
	push rbp
	mov rbp, rsp
	mov eax, -1						;eax = -1 para evitar contar el caracter nulo

	.loop_body:						;Por cada byte del string, eax += 1
		inc eax
		mov cl, byte [rdi]
		inc rdi
		test cl, cl					;Si llegamos al caracter nulo, terminamos de contar
		jne .loop_body

	pop rbp
		
	ret
=======
	ret


>>>>>>> upstream/master
