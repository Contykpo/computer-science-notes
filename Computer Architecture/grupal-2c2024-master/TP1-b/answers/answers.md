Ejercicio 0: Conceptos Generales.

1. ¿Qué se entiende por convención de llamada? 
Convención de llamada se refiere a un conjunto de reglas que dictan cómo las funciones en un programa interactúan en el nivel de ensamblador. Esto incluye cómo se pasan los parámetros a las funciones, cómo se retornan los valores, cómo se alinean las pilas de llamadas, qué registros se usan y cuáles deben preservarse.

Cómo está definida en la ABI de System V para 64 y 32 bits?
En la ABIde System V, la convención de llamada está definida de las siguientes formas segun las arquitecturas 64 y 32 bits:
En 64 bits:
    - Los primeros seis argumentos enteros o punteros se pasan a través de registros: rdi, rsi, rdx, rcx, r8, r9.
    - Los primeros ocho argumentos de punto flotante se pasan en registros xmm0 a xmm7.
    - Si hay más argumentos, se pasan a través de la pila.
    - El valor de retorno se coloca en el registro rax.
    - Los registros rbx, rbp, r12, r13, r14, y r15 deben preservarse entre llamadas a funciones callees-save.
    - La pila debe estar alineada a 16 bytes antes de una llamada a función.
Y en 32 bits:
    - Los argumentos se pasan en la pila, en orden de derecha a izquierda.
    - El valor de retorno se coloca en el registro eax.
    - Los registros ebx, esi, edi, y ebp deben preservarse entre llamadas a funciones.
    - La pila debe estar alineada a 16 bytes.

2. ¿Quién toma la responsabilidad de asegurar que se cumple la convención de llamada en C? ¿Quién toma la responsabilidad de asegurar que se cumple la convención de llamada en ASM?
El compilador es el encargado de asegurarse que se mantenga la convención de llamada en C, mientras que en ASM es tarea exclusiva del programador.

3. ¿Qué es un stack frame?
Es una estructura de datos utilizada para almacenar información sobre una llamada a función activa. Incluye datos como parámetros de la función, variables locales y dirección de retorno, lo cual permite realizar un seguimiento de la ejecución del programa y retornar a la función anterior después de que la función actual termine.
¿A qué se le suele decir prólogo y epílogo?
El prólogo es las instrucciones al inicio de una función que preparan el stack frame para la llamada. Incluye la reserva de espacio para variables locales y la preservación de registros.
Y epílogo se compone de las instrucciones al final de una funcion que restauran el estado anterior del stack frame y los registros, y finalmente retornan el control a la función llamadora.

4. Cuál es el mecanismo utilizado para almacenar variables temporales?
Las variables locales son guardadas en la pila despues de los registros que se deben restaurar al final de la funcion.

5. ¿A cuántos bytes es necesario alinear la pila si utilizamos funciones de libc?
Para utilizar funciones de libc, la pila debe estar alineada a 16 bytes antes de realizar la llamada a una función.
¿Si la pila está alineada a 16 bytes al realizarse una llamada función, cuál va a ser su alineamiento al ejecutar la primera instrucción de la función llamada?
Si la pila esta alineada a 16 bytes antes de realizarse una llamada a función, el push del registro de retorno, que ocupa 8 bytes, desalinearia la pila a 8 bytes al ejecutar la primera instrucción de la función llamada. Por eso, la función callee tiene que realinear la pila a 16 bytes si va a realizar otra llamada.

6. Una actualización de bibliotecas realiza los siguientes cambios a distintas funciones. ¿Cómo se ven impactados los programas ya compilados?

6.a. Si no se recompila con la nueva versión entonces dentro de la función cuando intente hacer referencia a algún campo de la estructura, como se compilo para la versión original, terminará accediendo a uno distinto del esperado, por ejemplo, si intenta acceder al rojo, accederá al alpha y si intenta acceder al verde, accederá al rojo.

6.b. Se reordenan los parámetros (intercambian su posición) de la función float sumar_floats(float* array, uint64_t tamano):
Si los parametros se intercambian, los programas que ya están compilados seguirián pasando los argumentos en el orden anterior, lo que causaria un comportamiento incorrecto, ya que la funcion interpretara incorrectamente los valores en los registros rdi para el puntero y rsi para el tamaño.

6.c. Se cambia el tipo de retorno en la funcion uint16_t registrar_usuario(char* nombre, char* contraseña) por uint64_t para soportar más usuarios:
Es posible que se ignoren los 6 bytes mas significativos.

6.d. Cambio de tipo de argumento en cambiar_nombre:
Un cambio en el tipo de un argumento significa que el compilador y el código precompilado esperan datos en diferentes registros o en diferentes tamaños, lo que puede causar corrupcion de datos o un comportamiento inesperado.

6.e. Se reordenan los parámetros de int32_t multiplicar(float a, int32_t b):
Los floats y los ints 32 tienen el mismo tamaño asi que por ese lado no habría problemas, pero como se interpretan distinto en memoria el resultado será distinto al esperado.

7. Situación general: ¿Qué sucede si una función externa utilizada por nuestro programa cambia su interfaz (parámetros o tipo devuelto) luego de una actualización?
Cuando una función externa cambia su interfaz, los programas ya compilados que dependen de esa funcion pueden comportarse de manera incorrecta o fallar por completo. Esto podria deberse a:
- Una lectura incorrecta de parametros, si los parametros cambian de orden o tipo, la funcion puede interpretar incorrectamente los datos proporcionados.
- Problemas de alineacion y tamaño, los cambios en tipos de retorno o tipos de datos pueden afectar la alineacion de la pila y los registros, llevando a fallos de segmentacion.
- Incompatibilidad entre binarios: La ABI garantiza ciertas convenciones para la compatibilidad binaria, pero un cambio de esas caracteristicas romperia estas garantias, requiriendo una recompilacion del programa para ajustar el nuevo ABI.


Ejercicio 4: La pila...

3. Para encontrar la clave divisamos dos alternativas para rastrear la funcion de autentificacion con el parametro entero 'miss' y a partir de esta hallar la clave: 

-El primer metodo fue utilizar gdb para acceder al codigo ensamblado mediante el comando 'lay next' donde se podia observar los llamados a las distintas funciones. Entre ellas encontramos 'print_authentication_message', la funcion que buscabamos, luego revisamos el callstack y de ahi vimos que es llamada por 'do_some_more_stuff' en la cual se invoca a strcmp, para ver si el string pasado coincide con la clave. Entonces colocamos un breakpoint antes de la llamada a la funcion de comparacion, ejecutamos el programa y analizamos el contenido de la memoria apuntada por el registro rdi, que efectivamente resulto ser la clave.
-El segundo metodo fue un poco menos directo, nos permitio llegar mas facilmente observando el listado de funciones con el comando 'info functions' hasta hallar una funcion con la firma de 'print_authentication_message', marcarla con un breakpoint con el comando 'break print_authentication_message' y luego observar sus argumentos con 'info args'. Una vez confirmada su identidad, observamos el callstack con 'backtrace' y descubrimos que esta es llamada por 'do_some_more_stuff', colocamos un breakpoint en la misma, volvimos a correr el programa y avanzamos paso a paso con el comando 'step' hasta encontrar una llamada a 'strcmp' para ver si el string pasado coincide con la clave. En ese punto analizamos el contenido de la memoria apuntada por el registro rdi, lo que nos permitio dar con la clave una vez mas. 
