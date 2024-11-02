#include "lista_enlazada.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


lista_t* nueva_lista(void)
{
    lista_t* nueva_lista = (lista_t*)malloc(sizeof(lista_t));
    
    if (nueva_lista != NULL)
    {
        nueva_lista->head = NULL;
    }
    
    return nueva_lista;
}

uint32_t longitud(lista_t* lista)
{
    uint32_t length = 0;
    nodo_t* current = lista->head;
    
    while (current != NULL)
    {
        length++;
    
        current = current->next;
    }
    
    return length;
}

void agregar_al_final(lista_t* lista, uint32_t* arreglo, uint64_t longitud)
{
    nodo_t* nuevo_nodo = (nodo_t*)malloc(sizeof(nodo_t));
    
    if (nuevo_nodo == NULL)
    {
        return;
    }

    nuevo_nodo->arreglo = (uint32_t*)malloc(longitud * sizeof(uint32_t));
    
    if (nuevo_nodo->arreglo == NULL)
    {
        free(nuevo_nodo);
   
        return;
    }
    
    memcpy(nuevo_nodo->arreglo, arreglo, longitud * sizeof(uint32_t));
    
    nuevo_nodo->longitud = longitud;
    nuevo_nodo->next = NULL;

    if (lista->head == NULL)
    {
        lista->head = nuevo_nodo;
    }
    else
    {
        nodo_t* current = lista->head;
    
        while (current->next != NULL)
        {
            current = current->next;
        }
        
        current->next = nuevo_nodo;
    }
}

nodo_t* iesimo(lista_t* lista, uint32_t i)
{
    nodo_t* current = lista->head;
    uint32_t count = 0;

    while (current != NULL && count < i)
    {
        current = current->next;
    
        count++;
    }
    
    return current;
}

uint64_t cantidad_total_de_elementos(lista_t* lista)
{
    uint64_t total_elements = 0;
    nodo_t* current = lista->head;

    while (current != NULL)
    {
        total_elements += current->longitud;
    
        current = current->next;
    }
    
    return total_elements;
}

void imprimir_lista(lista_t* lista)
{
    nodo_t* current = lista->head;
    
    while (current != NULL)
    {
        printf("| %llu | -> ", (unsigned long long)current->longitud);
    
        current = current->next;
    }

    printf("null\n");
}

// Función auxiliar para lista_contiene_elemento
int array_contiene_elemento(uint32_t* array, uint64_t size_of_array, uint32_t elemento_a_buscar)
{
    for (uint64_t i = 0; i < size_of_array; i++)
    {
        if (array[i] == elemento_a_buscar)
        {
            return 1;
        }
    }

    return 0;
}

int lista_contiene_elemento(lista_t* lista, uint32_t elemento_a_buscar)
{
    nodo_t* current = lista->head;

    while (current != NULL)
    {
        if (array_contiene_elemento(current->arreglo, current->longitud, elemento_a_buscar))
        {
            return 1;
        }
        
        current = current->next;
    }

    return 0;
}

// Devuelve la memoria otorgada para construir la lista indicada por el primer argumento.
// Tener en cuenta que ademas, se debe liberar la memoria correspondiente a cada array de cada elemento de la lista.
void destruir_lista(lista_t* lista)
{
    nodo_t* current = lista->head;

    while (current != NULL)
    {
        nodo_t* temp = current;

        current = current->next;

        free(temp->arreglo);
        free(temp);
    }

    free(lista);
}