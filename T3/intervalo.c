#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "intervalo.h"

Nodo *extractMax(Nodo **pa) {
    if (*pa == NULL) {
        return NULL;
    }
    if ((*pa)->der == NULL) {
        Nodo *res = (*pa);
        *pa = (*pa)->izq;
        return res;
    } else {
        return extractMax(&(*pa)->der);
    }
}

Nodo *mezclar(Nodo **izq, Nodo **der) {
    if (*izq == NULL) {
        return *der;
    }
    if (*der == NULL) {
        return *izq;
    }
    Nodo* res = extractMax(izq);
    res->izq = *izq;
    res->der = *der;
    return res;
}

void elimIntervalo(Nodo **pa, int inf, int sup) {
    Nodo* a = *pa; // ptr a la raíz del árbol
    
    if (a == NULL) { // caso base: árbol vacío, simplemente termina
        return;
    }

    if (a -> id < inf) { // si el entero guardado en id es menor que el extremo inferior del intervalo
        elimIntervalo(&(a -> der), inf, sup); // llamo recursivamente a la función con el subárbol derecho
    }

    if (a -> id > sup) { // si el entero guardado en id es mayor que el extremo inferior del intervalo
        elimIntervalo(&(a -> izq), inf, sup); // llamo recursivamente a la función con el subárbol izquierdo
    }

    if (inf <= a -> id && a -> id <= sup) { // si el entero guardado en id está en el intervalo, llamo recursivamente con los subárboles izq y der
        elimIntervalo(&(a -> izq), inf, sup);
        elimIntervalo(&(a -> der), inf, sup);

        Nodo* left = (*pa)->izq; // guardo los subárboles izq y der
        Nodo* right = (*pa)->der;
        free(*pa); // libero el nodo donde estoy

        *pa = mezclar(&left, &right); // y sobreescribo el puntero con el resultado de mezclar ambos subárboles
    }
}
