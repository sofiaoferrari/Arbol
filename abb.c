#include "abb.h"
#include <stdio.h>

#define EXITO 0
#define ERROR -1

#define BUSCAR 0 
#define INSERTAR 1 
#define ELIMINAR -1

#define IGUAL 0
#define MENOR 1
#define MAYOR -1

#define SIN_HIJOS 0
#define UN_HIJO 1
#define DOS_HIJOS 2

bool arbol_vacio(abb_t* arbol) {
    if (!arbol || !(arbol->nodo_raiz) || !(arbol->nodo_raiz->elemento)) return true;
    return false;
}

void* arbol_raiz(abb_t* arbol) {
    if (!arbol || !(arbol->nodo_raiz)) return NULL;
    return arbol->nodo_raiz->elemento;
}

void destruir_nodo(nodo_abb_t* nodo) {
    if (nodo->izquierda)
        destruir_nodo(nodo->izquierda);
    free(nodo);
}

void arbol_destruir(abb_t* arbol) {
    if (arbol && (!arbol_vacio(arbol))) {
        destruir_nodo(arbol->nodo_raiz);
    }
    if (arbol) {
        free(arbol);
    }
}

/*
 * Funcion recursiva
 * 
*/
nodo_abb_t* encontrar_elemento(abb_comparador comparador, nodo_abb_t* nodo_raiz, void* elemento, int accion, nodo_abb_t* nodo_anterior) {
    if (!comparador) return NULL; 
    int comparacion = comparador(nodo_raiz->elemento, elemento);
    nodo_anterior = nodo_raiz;
    if ((comparacion == IGUAL) && ((accion == BUSCAR) || (accion == ELIMINAR)))
        nodo_raiz = nodo_raiz;
    else if (((comparacion == MAYOR) || (comparacion == IGUAL)) && (nodo_raiz->derecha)) {
        nodo_anterior = nodo_raiz->derecha;
        nodo_raiz = encontrar_elemento(comparador,nodo_raiz->derecha, elemento, INSERTAR, nodo_anterior);
    }
    else if ((comparacion == MENOR) && (nodo_raiz->izquierda)) {
        nodo_anterior = nodo_raiz->izquierda;
        nodo_raiz = encontrar_elemento(comparador,nodo_raiz->izquierda, elemento, INSERTAR, nodo_anterior);
    }
    if (accion == ELIMINAR)
        return nodo_anterior;
    return nodo_raiz;
}

void* arbol_buscar(abb_t* arbol, void* elemento) {
    if (!arbol || !elemento || arbol_vacio(arbol)) return NULL;
    nodo_abb_t* encontrado = NULL;
   // if (arbol->nodo_raiz->elemento) 
    encontrado = encontrar_elemento(arbol->comparador, arbol->nodo_raiz, elemento, BUSCAR, encontrado);
    
    return encontrado->elemento;
}

nodo_abb_t* elemento_mas_proximo(nodo_abb_t* nodo_hijo) {
    if (nodo_hijo->izquierda)
        nodo_hijo = nodo_hijo->izquierda;
    return nodo_hijo;
}

int borrar(abb_t* arbol, nodo_abb_t* nodo_anterior, void* elemento, int comparacion, int hijos){
    nodo_abb_t* hijo_derecho = NULL;
    nodo_abb_t* hijo_izquierdo = NULL;
    nodo_abb_t* nuevo_padre = NULL;
    if ((comparacion == MAYOR) || (comparacion == IGUAL)) {
        arbol->destructor(nodo_anterior->derecha->elemento);
        if (hijos == UN_HIJO || hijos == DOS_HIJOS) 
            hijo_derecho = nodo_anterior->derecha->derecha;
        if (hijos == DOS_HIJOS) {
            hijo_izquierdo = nodo_anterior->izquierda->izquierda;
            nuevo_padre = elemento_mas_proximo(nodo_anterior->derecha);
            arbol_borrar(arbol, nuevo_padre->elemento);
        }
        free(nodo_anterior->derecha);
        if (nuevo_padre)
            nodo_anterior->derecha = nuevo_padre;
        
    } else if (comparacion == MENOR) {
        arbol->destructor(nodo_anterior->izquierda->elemento);
        if (hijos == UN_HIJO || hijos == DOS_HIJOS) 
            hijo_derecho = nodo_anterior->izquierda->izquierda;
        if (hijos == DOS_HIJOS) {
            hijo_izquierdo = nodo_anterior->izquierda->izquierda;
            nuevo_padre = elemento_mas_proximo(nodo_anterior->derecha);
            arbol_borrar(arbol, nuevo_padre->elemento);
        }
        free(nodo_anterior->izquierda);
        if (nuevo_padre)
            nodo_anterior->izquierda = nuevo_padre;
    }
    nodo_anterior->derecha = hijo_derecho;
    nodo_anterior->izquierda = hijo_izquierdo;
    return EXITO;
}

int arbol_borrar(abb_t* arbol, void* elemento) {
    if (!arbol || !elemento || arbol_vacio(arbol)) return ERROR;
    nodo_abb_t* nodo_anterior = arbol->nodo_raiz;
    nodo_anterior = encontrar_elemento(arbol->comparador, nodo_anterior, elemento, ELIMINAR, nodo_anterior);
    //printf("\nELEMENTO ANTERIOR: %d\n", *(int*)nodo_anterior->elemento);
    //printf("\nELEMENTO A BORRAR: %d\n", *(int*)nodo_anterior->izquierda->elemento);
    int comparacion = arbol->comparador(nodo_anterior->elemento, elemento);
    int tiene_hijos = SIN_HIJOS;
    int se_pudo = ERROR;
    if (!nodo_anterior->derecha->derecha && !nodo_anterior->izquierda->izquierda) {
        printf("\nENTRO ACA\n");
    } else if ((!nodo_anterior->derecha->derecha) || (!nodo_anterior->izquierda->izquierda)) {
        tiene_hijos = UN_HIJO;
    } else if (nodo_anterior->derecha->derecha && nodo_anterior->izquierda->izquierda) {
        tiene_hijos = DOS_HIJOS;
    }
    se_pudo = borrar(arbol, nodo_anterior, elemento, comparacion, tiene_hijos);

    if (*(int*)arbol_buscar(arbol, elemento) == *(int*)elemento) 
        se_pudo =  ERROR;
    
    return se_pudo;
}

/*
 * Funcion
 * 
*/
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
        nodo_abb_t* nodo = NULL;
        nodo = encontrar_elemento(arbol->comparador, arbol->nodo_raiz, elemento, INSERTAR, nodo);
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

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {
    if (!comparador || !destructor) return NULL;

    abb_t* arbol = (abb_t*)calloc(1, sizeof(abb_t));
    if (!arbol) return NULL;
    
    arbol->comparador = comparador;
    arbol->destructor = destructor;

    return arbol;
}