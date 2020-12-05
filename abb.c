#include "abb.h"
#include <stdio.h>

#define EXITO 0
#define ERROR -1
#define VACIO 0
#define PRIMERO 0
#define UNITARIO 1
#define IGUALES 0
#define MENOR 1
#define MAYOR -1

bool arbol_vacio(abb_t* arbol) {
    if (!arbol || !(arbol->nodo_raiz)) return true;
    return false;
}

void* arbol_raiz(abb_t* arbol) {
    if (!arbol) return NULL;
    return arbol->nodo_raiz->elemento;
}

void* arbol_buscar(abb_t* arbol, void* elemento) {
    if (!arbol) return NULL;
    return elemento;
}

int arbol_borrar(abb_t* arbol, void* elemento) {
    if (!arbol) return ERROR;
    return EXITO;
}

int arbol_insertar(abb_t* arbol, void* elemento) {
    if (!arbol || !elemento) return ERROR;
    else if (arbol_vacio(arbol)) {
        nodo_abb_t* nodo_raiz = calloc(1, sizeof(nodo_abb_t));
        if (!nodo_raiz) return ERROR;
        arbol->nodo_raiz = nodo_raiz;
        arbol->nodo_raiz->elemento = elemento;
    } else {
        int comparacion = arbol->comparador(arbol->nodo_raiz->elemento,elemento);
        if (comparacion == MENOR) {
            //printf("\nENTRO A MENOR\n");
            nodo_abb_t* nodo_izq = calloc(1, sizeof(nodo_abb_t));
            if (!nodo_izq) return ERROR;
            arbol->nodo_raiz->izquierda = nodo_izq;
            arbol->nodo_raiz->izquierda->elemento = elemento;
        } else if ((comparacion == MAYOR) || (comparacion == IGUALES)) {
            //printf("\nENTRO A MAYOR\n");
            nodo_abb_t* nodo_der = calloc(1, sizeof(nodo_abb_t));
            if (!nodo_der) return ERROR;
            arbol->nodo_raiz->derecha = nodo_der;
            arbol->nodo_raiz->derecha->elemento = elemento;
        }
    }
    return EXITO;
}

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {
    if (!comparador || !destructor) return NULL;

    abb_t* arbol = calloc(1, sizeof(abb_t));
    if (!arbol) return NULL;
    
    arbol->comparador = comparador;
    arbol->destructor = destructor;

    return arbol;
}