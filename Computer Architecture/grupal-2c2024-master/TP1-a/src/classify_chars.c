#include "classify_chars.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>

// Auxiliar:
// Verifica si un carácter es una vocal.
int is_vowel(char c)
{
    // Convierte a minúscula para comparar.
    c = tolower(c); 
    
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// Clasifica los caracteres de un string en vocales y consonantes.
void classify_chars_in_string(char* string, char** vowels_and_cons)
{
    // Se reserva memoria para las vocales y consonantes.
    // Como cada string nunca tendrá más de 64 vocales ni más de 64 consonantes, se asignan: 64 espacios para caracteres + 1 para el carácter nulo ('\0').
    vowels_and_cons[0] = calloc(65, sizeof(char));
    vowels_and_cons[1] = calloc(65, sizeof(char));

    size_t vocal_index = 0;
    size_t cons_index = 0;

    // Recorrer el string y clasificar cada carácter.
    for (size_t i = 0; string[i] != '\0'; i++)
    {
        if (is_vowel(string[i]))
        {
            vowels_and_cons[0][vocal_index++] = string[i];
        }
        else
        {
            // Solo se clasifican letras como consonantes.
            vowels_and_cons[1][cons_index++] = string[i];
        }
    }
}

// Clasifica caracteres en múltiples strings.
void classify_chars(classifier_t* array, uint64_t size_of_array)
{
    for (uint64_t i = 0; i < size_of_array; i++)
    {
        //Reservar memoria para los punteros a vocales y consonantes
        array[i].vowels_and_consonants = calloc(2, sizeof(char*));
    
        classify_chars_in_string(array[i].string, array[i].vowels_and_consonants);
    }
}