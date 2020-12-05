#include "abb.h"
#include <stdio.h>

#define EXITO 0
#define ERROR -1
#define BUSCAR 0 //sacar
#define INSERTAR 1 //sacar
#define ELIMINAR -1
#define IGUAL 0
#define MENOR 1
#define MAYOR -1

bool arbol_vacio(abb_t* arbol) {
    if (!arbol || !(arbol->nodo_raiz) || !(arbol->nodo_raiz->elemento)) return true;
    return false;
}

void* arbol_raiz(abb_t* arbol) {
    if (!arbol || !(arbol->nodo_raiz)) return NULL;
    return arbol->nodo_raiz->elemento;
}

nodo_abb_t* encontrar_elemento(abb_comparador comparador, nodo_abb_t* nodo_raiz, void* elemento, int accion) {
    if (!comparador) return NULL; 
    int comparacion = comparador(nodo_raiz->elemento, elemento);

    if ((comparacion == IGUAL) && (accion == BUSCAR))
        nodo_raiz = nodo_raiz;
    else if (((comparacion == MAYOR) || (comparacion == IGUAL)) && (nodo_raiz->derecha))
        nodo_raiz = encontrar_elemento(comparador,nodo_raiz->derecha, elemento, INSERTAR);
    else if ((comparacion == MENOR) && (nodo_raiz->izquierda))
        nodo_raiz = encontrar_elemento(comparador,nodo_raiz->izquierda, elemento, INSERTAR);

    return nodo_raiz;
}

void* arbol_buscar(abb_t* arbol, void* elemento) {
    if (!arbol || !elemento || arbol_vacio(arbol)) return NULL;
    nodo_abb_t* encontrado = NULL;
    if (arbol->nodo_raiz->elemento) 
        encontrado = encontrar_elemento(arbol->comparador, arbol->nodo_raiz, elemento, BUSCAR);
    
    return encontrado->elemento;
}

int arbol_borrar(abb_t* arbol, void* elemento) {
    if (!arbol) return ERROR;
    return EXITO;
}

int insertar_elemento(nodo_abb_t** nodo_raiz, void* elemento) {
    if (!elemento) return ERROR;
    nodo_abb_t* nodo = (nodo_abb_t*)calloc(1, sizeof(nodo_abb_t));
    if (!nodo) return ERROR;
    
    nodo->elemento = elemento;
    *nodo_raiz = nodo;
    
    return EXITO;
}

int arbol_insertar(abb_t* arbol, void* elemento) {
    if (!arbol || !elemento) return ERROR;
    int insertado = ERROR;
    if (arbol_vacio(arbol))
        insertado = insertar_elemento(&arbol->nodo_raiz, elemento);
    else {
        nodo_abb_t* nodo = encontrar_elemento(arbol->comparador, arbol->nodo_raiz, elemento, INSERTAR);
        if (nodo) { //no tiene hijos
            int comparacion = arbol->comparador(nodo->elemento, elemento);
            if (comparacion == MAYOR || comparacion == IGUAL)
                insertado = insertar_elemento(&nodo->derecha, elemento);
            else if (comparacion == MENOR)  
                insertado = insertar_elemento(&nodo->izquierda, elemento);
        }
    }
    return insertado;
}
/*
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
        } else if ((comparacion == MAYOR) || (comparacion == IGUAL)) {
            //printf("\nENTRO A MAYOR\n");
            nodo_abb_t* nodo_der = calloc(1, sizeof(nodo_abb_t));
            if (!nodo_der) return ERROR;
            arbol->nodo_raiz->derecha = nodo_der;
            arbol->nodo_raiz->derecha->elemento = elemento;
        }
    }
    return EXITO;
}*/

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {
    if (!comparador || !destructor) return NULL;

    abb_t* arbol = calloc(1, sizeof(abb_t));
    if (!arbol) return NULL;
    
    arbol->comparador = comparador;
    arbol->destructor = destructor;

    return arbol;
}