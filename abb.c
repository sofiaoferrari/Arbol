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

typedef struct nodos {
    nodo_abb_t* hijo_izquierdo;
    nodo_abb_t* hijo_derecho;
    nodo_abb_t* nuevo_padre;
} nodos_t;

bool arbol_vacio(abb_t* arbol) {
    if (!arbol) return true;
    else if (!(arbol->nodo_raiz)) return true;
    return false;
}

void* arbol_raiz(abb_t* arbol) {
    if (!arbol || !(arbol->nodo_raiz)) return NULL;
    return arbol->nodo_raiz->elemento;
}

/*
 * Procedimiento recursivo 
 */
void destruir_nodo(abb_t* arbol, nodo_abb_t* nodo_hijo) { //recorrido postorden
    if (!nodo_hijo) return;
    if (nodo_hijo->izquierda) {
        destruir_nodo(arbol, nodo_hijo->izquierda);
    }
    if (nodo_hijo->derecha) {
        destruir_nodo(arbol, nodo_hijo->derecha);
        
    }
    
    arbol->destructor(nodo_hijo->elemento);
    free(nodo_hijo);
    //return nodo_hijo;
}


void arbol_destruir(abb_t* arbol) {
    if (arbol && (!arbol_vacio(arbol))) {
        destruir_nodo(arbol, arbol->nodo_raiz);

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
    int comparacion = comparador(nodo_raiz->elemento, elemento);
    //nodo_anterior = nodo_raiz;
    if ((comparacion == IGUAL) && ((accion == BUSCAR) || (accion == ELIMINAR))) {
        //printf("\nELEMENTO ES IGUAL\n");
        nodo_raiz = nodo_raiz;
    }
    else if (((comparacion == MAYOR) || (comparacion == IGUAL)) && (nodo_raiz->derecha)) {
        //printf("\nENTRO A MAYOR\n");
        nodo_anterior = nodo_raiz;
        nodo_raiz = encontrar_elemento(comparador,nodo_raiz->derecha, elemento, accion, nodo_anterior);
    }
    else if ((comparacion == MENOR) && (nodo_raiz->izquierda)) {
        //printf("\nENTRO A MENOR\n");
        nodo_anterior = nodo_raiz;
        nodo_raiz = encontrar_elemento(comparador,nodo_raiz->izquierda, elemento, accion, nodo_anterior);
    }
    
    if (accion == ELIMINAR) {
        //printf("\nELEMENTO NODO ANTERIOR: %d\n", *(int*)(nodo_anterior->elemento));
        return nodo_anterior;
    }

    return nodo_raiz;
}

void* arbol_buscar(abb_t* arbol, void* elemento) {
    if (!arbol || !elemento || arbol_vacio(arbol) || !arbol->comparador) return NULL;
    nodo_abb_t* encontrado = NULL;
    encontrado = encontrar_elemento(arbol->comparador, arbol->nodo_raiz, elemento, BUSCAR, encontrado);
    
    if (encontrado) {
        printf("\nENTRO A encontrado\n");
        int comparacion = arbol->comparador(elemento, encontrado->elemento);
        if (comparacion != IGUAL) return NULL;
        //printf("\nCOMPARACION: %d\n", comparacion);
        //printf("\nELEMENTO ENCONTRADO: %d\n", *(int*)(encontrado->elemento));
        //printf("\nELEMENTO A BUSCAR: %d\n", *(int*)elemento);
        //printf("\nELEMENTO DEL HIJO DE RAIZ: %d\n", *(int*)arbol->nodo_raiz->derecha->elemento);   
    }
        
    return encontrado->elemento;
}

nodo_abb_t* elemento_mas_proximo(nodo_abb_t* nodo_hijo, nodo_abb_t* nodo_anterior) { 
    if (nodo_hijo->derecha) {
        nodo_anterior = nodo_hijo;
        nodo_hijo = nodo_hijo->derecha;
        nodo_hijo = elemento_mas_proximo(nodo_hijo, nodo_anterior);
    }
    return nodo_hijo;
}
/*
nodo_abb_t* elemento_menor(nodo_abb_t* hijo_menor) {
    if (hijo_menor->izquierda) {
        hijo_menor = hijo_menor->izquierda;
        hijo_menor = elemento_mas_proximo(hijo_menor);
    }    
    return hijo_menor;
}*/

void nodo_con_dos_hijos(abb_t* arbol, nodo_abb_t* nodo_a_borrar, nodos_t* nuevo_arbol, int es_la_raiz) {
    nuevo_arbol->hijo_izquierdo = nodo_a_borrar->izquierda;
    nuevo_arbol->hijo_derecho = nodo_a_borrar->derecha;
    nodo_abb_t* nodo_anterior = arbol->nodo_raiz;
    nuevo_arbol->nuevo_padre = elemento_mas_proximo(nodo_a_borrar->izquierda, nodo_anterior);
    int comparacion = arbol->comparador(nodo_anterior->elemento, nuevo_arbol->nuevo_padre->elemento);

    if (nuevo_arbol->nuevo_padre->izquierda) {
        printf("\ntiene hijo izquierdo\n");

        nuevo_arbol->hijo_izquierdo = nuevo_arbol->nuevo_padre->izquierda;
        //
    } else nuevo_arbol->nuevo_padre->izquierda = nuevo_arbol->hijo_izquierdo;

    nuevo_arbol->nuevo_padre->derecha = nuevo_arbol->hijo_derecho;

    if ((comparacion == MAYOR || comparacion == IGUAL) && (!es_la_raiz))
        nodo_anterior->derecha = NULL;
    else if((comparacion == MENOR) && (!es_la_raiz))
        nodo_anterior->izquierda = NULL;
}

void nodo_con_hijo(nodo_abb_t* nodo_a_borrar, nodos_t* nuevo_arbol) {  //no necesito comparacion

    if (nodo_a_borrar->derecha)
        nuevo_arbol->nuevo_padre = nodo_a_borrar->derecha;
    if (nodo_a_borrar->izquierda)
        nuevo_arbol->nuevo_padre = nodo_a_borrar->izquierda;
}

int borrar(abb_t* arbol, nodo_abb_t* nodo_anterior, nodo_abb_t* nodo_a_borrar, int hijos, int es_la_raiz){
    nodos_t* nuevo_arbol = calloc(1, sizeof(nodo_abb_t));
    if (!nuevo_arbol) return ERROR;
    if (hijos != SIN_HIJOS) {
        if (hijos == UN_HIJO) 
            nodo_con_hijo(nodo_a_borrar, nuevo_arbol);
        else if (hijos == DOS_HIJOS) 
            nodo_con_dos_hijos(arbol, nodo_a_borrar, nuevo_arbol, es_la_raiz);
        
        if (!nuevo_arbol->nuevo_padre) {
            //free(nuevo_arbol);
            return ERROR;
        }
    }
    if (es_la_raiz)
            arbol->nodo_raiz = nuevo_arbol->nuevo_padre;

    int comparacion = arbol->comparador(nodo_anterior->elemento, nodo_a_borrar->elemento);

    arbol->destructor(nodo_a_borrar->elemento);
    if (((comparacion == MAYOR) || (comparacion == IGUAL)) && (!es_la_raiz)) {
         if (hijos == SIN_HIJOS) 
            nodo_anterior->derecha = NULL;
        else 
            nodo_anterior->derecha = nuevo_arbol->nuevo_padre;
    } else if ((comparacion == MENOR ) && (!es_la_raiz)) {
        printf("\nentro aca\n");

         if (hijos == SIN_HIJOS) 
            nodo_anterior->izquierda = NULL;
        else 
            nodo_anterior->izquierda = nuevo_arbol->nuevo_padre;      
    }
    free(nodo_a_borrar);
    //free(nuevo_arbol->hijo_derecho);
    //free(nuevo_arbol->hijo_derecho);
    //free(nuevo_arbol->nuevo_padre);
    free(nuevo_arbol);
    return EXITO;
}

int arbol_borrar(abb_t* arbol, void* elemento) {
    if (!arbol || !elemento || arbol_vacio(arbol)) return ERROR;
    else if (!arbol->destructor || !arbol->comparador) return ERROR;
    nodo_abb_t* nodo_anterior = arbol->nodo_raiz;
    nodo_abb_t* nodo_a_borrar = NULL;
    nodo_anterior = encontrar_elemento(arbol->comparador, nodo_anterior, elemento, ELIMINAR, nodo_anterior);
    nodo_a_borrar = encontrar_elemento(arbol->comparador, nodo_anterior, elemento, BUSCAR, nodo_anterior);
    
    int es_la_raiz = !(arbol->comparador(arbol->nodo_raiz->elemento, nodo_a_borrar->elemento));
    int tiene_hijos = SIN_HIJOS;
    int se_pudo = EXITO;
    if ((!nodo_a_borrar->derecha) && (!nodo_a_borrar->izquierda)) 
        tiene_hijos = SIN_HIJOS;
    else if ((!nodo_a_borrar->derecha) || (!nodo_a_borrar->izquierda)) 
        tiene_hijos = UN_HIJO;
    else if (nodo_a_borrar->derecha && nodo_a_borrar->izquierda) 
        tiene_hijos = DOS_HIJOS;
    printf("\ncantidad de hijos: %d\n", tiene_hijos);
    //printf(" \nhijo derecho: %d\n", *(int*)nodo_a_borrar->izquierda->elemento);
    
    se_pudo = borrar(arbol, nodo_anterior, nodo_a_borrar, tiene_hijos, es_la_raiz);
    
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

/*
//printf("\nELEMENTO padre: %d\n", *(int*)nodo_anterior->derecha->derecha->elemento);
        //printf("\nELEMENTO hijo derecha: %d\n", *(int*)nodo_anterior->derecha->derecha->elemento);
        //printf("\nELEMENTO hijo izq: %d\n", *(int*)nodo_anterior->izquierda->izquierda->elemento);

        printf("\nCOMPARACION: %d\n", comparacion);

printf("\nENTRO DOS HIJOS\n");

//printf("\nELEMENTO ANTERIOR: %d\n", *(int*)nodo_anterior->elemento);
    //printf("\nELEMENTO A BORRAR: %d\n", *(int*)nodo_anterior->izquierda->elemento);


printf("\nNUEVO PADRE: %d\n", *(int*)nuevo_arbol->nuevo_padre->elemento);
    printf("NUEVO hijo izq: %d\n", *(int*)nuevo_arbol->nuevo_padre->izquierda->elemento);
    printf("NUEVO der: %d\n", *(int*)nuevo_arbol->nuevo_padre->derecha->elemento);
    printf("Nodo anterior: %d\n", *(int*)nodo_anterior->elemento);
    printf("NUEVO a borrar: %d\n", *(int*)nodo_a_borrar->elemento);

printf("\nNUEVO PADRE raiz: %d\n", *(int*)arbol->nodo_raiz->izquierda->elemento);
    //printf("\nHAY NODO PADRE\n");
    printf("\nNodo a borrar: %d\n", *(int*)nodo_a_borrar->elemento);

     printf("\nNUEVO PADRE: %d\n", *(int*)nuevo_arbol->nuevo_padre->elemento);
    printf("NODO ANTERIOR: %d\n", *(int*)nodo_anterior->elemento);

    printf(" \nhijo derecho: %d\n", *(int*)nuevo_arbol->nuevo_padre->derecha->elemento);


    //nodo_abb_t* hijo_menor = NULL;
        //hijo_menor = elemento_menor(nuevo_arbol->nuevo_padre->izquierda);
        //if (arbol->comparador(nuevo_arbol->hijo_izquierdo->elemento, hijo_menor->elemento) <= IGUAL) {
            //hijo_menor->izquierda = nuevo_arbol->hijo_izquierdo;
        //nodo_anterior->izquierda = NULL;
*/