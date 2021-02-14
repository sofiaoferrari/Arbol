#include "abb.h"
#include <stdio.h>

#define EXITO 0
#define ERROR -1
#define VACIO 0

#define BUSCAR 0 
#define INSERTAR 1 
#define ELIMINAR -1

#define IGUAL 0
#define MENOR 1     //izquierda
#define MAYOR -1   //derecha

#define SIN_HIJOS 0
#define UN_HIJO_I 1
#define UN_HIJO_D -1
#define DOS_HIJOS 2

bool arbol_vacio(abb_t* arbol) {
   
    if (!arbol || !(arbol->nodo_raiz)) return true;
  
    return false;
}

void* arbol_raiz(abb_t* arbol) {
    if (!arbol || !(arbol->nodo_raiz))
         return NULL;
    return arbol->nodo_raiz->elemento;
}

void iterador_interno_inorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), bool* resultado_funcion, void* extra, size_t* elementos_recorridos){
    if(!nodo || (*resultado_funcion == true)) return;

    iterador_interno_inorden(nodo->izquierda, funcion, resultado_funcion, extra, elementos_recorridos);
    if(*resultado_funcion == true) return;
    (*elementos_recorridos)++;
    *resultado_funcion = (*funcion)(nodo->elemento,extra);
    iterador_interno_inorden(nodo->derecha, funcion, resultado_funcion, extra, elementos_recorridos);
}


void iterador_interno_preorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), bool* resultado_funcion, void* extra, size_t* elementos_recorridos){
    if(!nodo || (*resultado_funcion == true)) return;

    (*elementos_recorridos)++;
    *resultado_funcion = (*funcion)(nodo->elemento,extra);
    iterador_interno_preorden(nodo->izquierda, funcion, resultado_funcion, extra, elementos_recorridos);
    if(*resultado_funcion == true) return;
    iterador_interno_preorden(nodo->derecha, funcion, resultado_funcion, extra, elementos_recorridos);
}


void iterador_interno_postorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), bool* resultado_funcion, void* extra, size_t* elementos_recorridos){
    if(!nodo || (*resultado_funcion == true)) return;

    iterador_interno_postorden(nodo->izquierda, funcion, resultado_funcion, extra, elementos_recorridos);
    if(*resultado_funcion == true) return;
    iterador_interno_postorden(nodo->derecha, funcion, resultado_funcion, extra, elementos_recorridos);
    if(*resultado_funcion == true) return;
    *resultado_funcion = (*funcion)(nodo->elemento, extra);
    (*elementos_recorridos)++;
}


size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
    if(!arbol || !funcion) return VACIO;
    size_t elementos_recorridos = VACIO;
    bool resultado_funcion = false;

    if(recorrido == ABB_RECORRER_INORDEN)
        iterador_interno_inorden(arbol->nodo_raiz, funcion, &resultado_funcion, extra, &elementos_recorridos);
    else if(recorrido == ABB_RECORRER_PREORDEN)
        iterador_interno_preorden(arbol->nodo_raiz, funcion, &resultado_funcion, extra, &elementos_recorridos);
    else if(recorrido == ABB_RECORRER_POSTORDEN)
        iterador_interno_postorden(arbol->nodo_raiz, funcion, &resultado_funcion, extra, &elementos_recorridos);
    
    return elementos_recorridos;
}

void recorrido_postorden(nodo_abb_t* nodo, size_t* elementos_almacenados, void** array, size_t tamanio_array){
    if(!nodo) return;

    recorrido_postorden(nodo->izquierda, elementos_almacenados, array, tamanio_array);
    recorrido_postorden(nodo->derecha, elementos_almacenados, array, tamanio_array);

    if( (*elementos_almacenados) >= tamanio_array) return;

    array[*elementos_almacenados] = nodo->elemento;
    (*elementos_almacenados)++;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array) {
     if(!arbol) return VACIO;

    size_t elementos_almacenados = VACIO;
    recorrido_postorden(arbol->nodo_raiz, &elementos_almacenados, array, tamanio_array);
    return elementos_almacenados;
}

void recorrido_preorden(nodo_abb_t* nodo, size_t* elementos_almacenados, void** array, size_t tamanio_array){
    if(!nodo || (*elementos_almacenados) >= tamanio_array) return;

    array[*elementos_almacenados] = nodo->elemento;
    (*elementos_almacenados)++;

    recorrido_preorden(nodo->izquierda, elementos_almacenados, array, tamanio_array);
    recorrido_preorden(nodo->derecha, elementos_almacenados, array, tamanio_array);
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array) {
    if(!arbol) return VACIO;

    size_t elementos_almacenados = VACIO;
    recorrido_preorden(arbol->nodo_raiz, &elementos_almacenados, array, tamanio_array);

    return elementos_almacenados;
}


void recorrido_inorden(nodo_abb_t* nodo, size_t* elementos_almacenados, void** array, size_t tamanio_array){
    if(!nodo) return;

    recorrido_inorden(nodo->izquierda, elementos_almacenados, array, tamanio_array);
    if(*elementos_almacenados >= tamanio_array) return;

    array[*elementos_almacenados] = nodo->elemento;
    (*elementos_almacenados)++;

    recorrido_inorden(nodo->derecha, elementos_almacenados, array, tamanio_array);
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array) {
    if (!arbol) return VACIO;

    size_t elementos_almacenados = VACIO;
    recorrido_inorden(arbol->nodo_raiz, &elementos_almacenados, array, tamanio_array);
    return elementos_almacenados;
}


/*
 * Procedimiento recursivo 
 */
void arbol_eliminar_elementos_recursivamente(abb_t* arbol, nodo_abb_t* nodo_hijo) { //recorrido postorden
  //  if (!nodo_hijo) return;
    if (nodo_hijo->izquierda) {
        arbol_eliminar_elementos_recursivamente(arbol, nodo_hijo->izquierda);
    }
    if (nodo_hijo->derecha) {
        arbol_eliminar_elementos_recursivamente(arbol, nodo_hijo->derecha);   
    }
    
    arbol->destructor(nodo_hijo->elemento);
    free(nodo_hijo);
}


void arbol_destruir(abb_t* arbol) {

    if (arbol && (!arbol_vacio(arbol)) && arbol->destructor) {
        arbol_eliminar_elementos_recursivamente(arbol, arbol->nodo_raiz);
    }
    
    free(arbol);
}

/*
 * Funcion recursiva
 * 
*/
nodo_abb_t* buscar_nodo_segun_elemento(abb_comparador comparador, nodo_abb_t* nodo_raiz, void* elemento, int accion, nodo_abb_t* nodo_anterior) {
    if (!nodo_raiz) return NULL;
    int comparacion = comparador(nodo_raiz->elemento, elemento);
   
    if ((comparacion == IGUAL) && ((accion == BUSCAR) || (accion == ELIMINAR))) {
        nodo_raiz = nodo_raiz;      
    }
    else if (((comparacion == MAYOR) || (comparacion == IGUAL && accion == INSERTAR)) && (nodo_raiz->derecha)) {
        nodo_anterior = nodo_raiz;
        nodo_raiz = buscar_nodo_segun_elemento(comparador,nodo_raiz->derecha, elemento, accion, nodo_anterior);
    }
    else if ((comparacion == MENOR) && (nodo_raiz->izquierda)) {
        nodo_anterior = nodo_raiz;
        nodo_raiz = buscar_nodo_segun_elemento(comparador,nodo_raiz->izquierda, elemento, accion, nodo_anterior);
    }
    if (accion == ELIMINAR && comparacion == IGUAL) 
        return nodo_anterior;

    return nodo_raiz;
}

nodo_abb_t* verifico_nodo_sea_el_esperado(abb_t* arbol, void* elemento, nodo_abb_t* nodo_encontrado){
    nodo_encontrado = buscar_nodo_segun_elemento(arbol->comparador, arbol->nodo_raiz, elemento, BUSCAR, nodo_encontrado);
    if (arbol->comparador(nodo_encontrado->elemento,elemento) != IGUAL)
        return NULL;
    return nodo_encontrado;
}

void* arbol_buscar(abb_t* arbol, void* elemento) {
    if (!arbol || !elemento || arbol_vacio(arbol) || !arbol->comparador) return NULL;
    nodo_abb_t* encontrado = NULL;   

    encontrado = verifico_nodo_sea_el_esperado(arbol, elemento, encontrado);
    if (!encontrado) return NULL;
  //  int comparacion = arbol->comparador(elemento, encontrado->elemento);
  //  if (comparacion != IGUAL) return NULL;
        
    return encontrado->elemento;
}

/*
 * Funcion recursiva
*/
nodo_abb_t* elemento_sucesor_inorden(nodo_abb_t* nodo_hijo, nodo_abb_t* nodo_padre) { //lamara con derecha
    if (nodo_hijo->izquierda) {
        nodo_padre = nodo_hijo;
        nodo_hijo = nodo_hijo->izquierda;
        nodo_hijo = elemento_sucesor_inorden(nodo_hijo, nodo_padre);
    }
    return nodo_hijo;
}


nodo_abb_t* buscar_hijo_mayor(nodo_abb_t* nodo_hijo, nodo_abb_t* nodo_padre) { 
    if (nodo_hijo->derecha) {
        nodo_padre = nodo_hijo;
        nodo_hijo = nodo_hijo->derecha;
        nodo_hijo = buscar_hijo_mayor(nodo_hijo, nodo_padre);
    }
    return nodo_hijo;
}

nodo_abb_t* nodo_con_dos_hijos(abb_t* arbol, nodo_abb_t* nodo_padre, nodo_abb_t* nodo_a_borrar, nodo_abb_t* sucesor) {
    nodo_abb_t* hijo_mayor = NULL;
    nodo_abb_t* padre_del_sucesor = nodo_padre;
    sucesor = elemento_sucesor_inorden(nodo_a_borrar->derecha, padre_del_sucesor);
    bool hijo_es_sucesor = !(arbol->comparador(nodo_a_borrar->derecha->elemento, sucesor->elemento));

    if (!hijo_es_sucesor) {
        padre_del_sucesor = buscar_nodo_segun_elemento(arbol->comparador, arbol->nodo_raiz, sucesor->elemento, ELIMINAR, arbol->nodo_raiz);
        padre_del_sucesor->izquierda = NULL;
        if(!sucesor->derecha)
            sucesor->derecha = nodo_a_borrar->derecha;
        else if (sucesor->derecha) {
            hijo_mayor = buscar_hijo_mayor(sucesor->derecha, padre_del_sucesor);

            hijo_mayor->derecha = nodo_a_borrar->derecha;
        }
    }

    sucesor->izquierda = nodo_a_borrar->izquierda;
    return sucesor;
}


void borrar_segun_hijos(abb_t* arbol, nodo_abb_t* nodo_padre, nodo_abb_t* nodo_a_borrar, int hijos, bool es_la_raiz, int comparacion){
    nodo_abb_t* sucesor_a_nodo_borrar = NULL; // nuevo nodo hijo
    if (hijos == UN_HIJO_D)
        sucesor_a_nodo_borrar = nodo_a_borrar->derecha;
    else if (hijos == UN_HIJO_I)
        sucesor_a_nodo_borrar = nodo_a_borrar->izquierda;
    else if (hijos == DOS_HIJOS) {
       sucesor_a_nodo_borrar = nodo_con_dos_hijos(arbol, nodo_padre, nodo_a_borrar, sucesor_a_nodo_borrar);
    }
    
    if (comparacion == MAYOR)  // el nodo a borrar es mayor que su padre
        nodo_padre->derecha = sucesor_a_nodo_borrar;
    else if (comparacion == MENOR) // el nodo a borrar es menor que su padre
        nodo_padre->izquierda = sucesor_a_nodo_borrar;
    if (es_la_raiz) {
        arbol->nodo_raiz = sucesor_a_nodo_borrar;
    }

    arbol->destructor(nodo_a_borrar->elemento);
    free(nodo_a_borrar);
}

int nodo_tiene_hijos(nodo_abb_t* nodo_a_borrar) {
    int hijos = 0;
    if ((!nodo_a_borrar->derecha) && (!nodo_a_borrar->izquierda)) 
        hijos = SIN_HIJOS;
    else if (!nodo_a_borrar->derecha)  
        hijos = UN_HIJO_I;
    else if (!nodo_a_borrar->izquierda){
        hijos = UN_HIJO_D;
    }
    else if (nodo_a_borrar->derecha && nodo_a_borrar->izquierda) 
        hijos = DOS_HIJOS;
    return hijos;
}

int arbol_borrar(abb_t* arbol, void* elemento) {
    if (!arbol || !elemento || arbol_vacio(arbol)) return ERROR;
    else if (!arbol->destructor) return ERROR;

    nodo_abb_t* nodo_a_borrar = NULL;
    nodo_abb_t* nodo_padre = arbol->nodo_raiz;
    nodo_a_borrar = verifico_nodo_sea_el_esperado(arbol, elemento, nodo_a_borrar);
    
    if (!nodo_a_borrar) return ERROR;  //el elemento no se encuentra en el arbol
    int hijos = nodo_tiene_hijos(nodo_a_borrar);
    nodo_padre = buscar_nodo_segun_elemento(arbol->comparador, arbol->nodo_raiz, elemento, ELIMINAR, nodo_padre);
    
    bool es_la_raiz = !(arbol->comparador(arbol->nodo_raiz->elemento, elemento));
    int comparacion = arbol->comparador(nodo_padre->elemento, elemento);

    borrar_segun_hijos(arbol, nodo_padre, nodo_a_borrar, hijos, es_la_raiz, comparacion);

    return EXITO;
}

/*
 * Funcion
 * 
*/
int insertar_elemento(nodo_abb_t** nodo_raiz, void* elemento) {

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
        nodo = buscar_nodo_segun_elemento(arbol->comparador, arbol->nodo_raiz, elemento, INSERTAR, nodo);

        if (nodo) { //no tiene hijos
            int comparacion = arbol->comparador(nodo->elemento, elemento);

            if ((comparacion == MAYOR || comparacion == IGUAL) && !nodo->derecha){
    
                insertado = insertar_elemento(&nodo->derecha, elemento);

            }
            else if (comparacion == MENOR && !nodo->izquierda)  {

                insertado = insertar_elemento(&nodo->izquierda, elemento);
            }
        }
    }
    return insertado;
}

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {
    if (!comparador) return NULL;

    abb_t* arbol = (abb_t*)calloc(1, sizeof(abb_t));
    if (!arbol) return NULL;
    
    arbol->comparador = comparador;
    arbol->destructor = destructor;

    return arbol;
}
