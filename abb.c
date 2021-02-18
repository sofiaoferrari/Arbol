#include "abb.h"
#include <stdio.h>

#define EXITO 0
#define ERROR -1
#define VACIO 0

#define IGUAL 0     //derecha
#define MAYOR 1    //derecha
#define MENOR -1  //izquierda

#define SIN_HIJOS 0
#define UN_HIJO_I -1
#define UN_HIJO_D 1
#define DOS_HIJOS 2

bool arbol_vacio(abb_t* arbol) {
    if (!arbol || !(arbol->nodo_raiz)) 
        return true;
  
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
/*
 * Procedimiento recursivo que se ocupa de llenar el array con los elementos recorridos en 
 * secuencia postorden. En el caso de que el array no tenga mas espacio para almacenar todos 
 * los elementos, sale de la funcion dejando el array con los elementos alamacenados hasta
 * el momento.
*/
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

/*
 * Procedimiento recursivo que se ocupa de llenar el array con los elementos recorridos en 
 * secuencia preorden. En el caso de que el array no tenga mas espacio para almacenar todos 
 * los elementos, sale de la funcion dejando el array con los elementos alamacenados hasta
 * el momento.
*/
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

/*
 * Procedimiento recursivo que se ocupa de llenar el array con los elementos recorridos en 
 * secuencia inorden. En el caso de que el array no tenga mas espacio para almacenar todos 
 * los elementos, sale de la funcion dejando el array con los elementos alamacenados hasta
 * el momento.
*/
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
 * Procedimiento recursivo que dado un arbol se encarga de recorrerlo en profundidad postorden e ir 
 * liberando cada uno de los nodos, y sus respectivos elementos en el caso de que el arbol contenga un
 * destructor de elementos.
 */
void arbol_liberar_nodos_recursivamente(abb_t* arbol, nodo_abb_t* nodo_hijo) { //recorrido postorden
    if (nodo_hijo->izquierda) {
        arbol_liberar_nodos_recursivamente(arbol, nodo_hijo->izquierda);
    }
    if (nodo_hijo->derecha) {
        arbol_liberar_nodos_recursivamente(arbol, nodo_hijo->derecha);   
    }

    if(arbol->destructor)
         arbol->destructor(nodo_hijo->elemento);
    free(nodo_hijo);
}

void arbol_destruir(abb_t* arbol) {

    if (arbol && (!arbol_vacio(arbol))) {
        arbol_liberar_nodos_recursivamente(arbol, arbol->nodo_raiz);
    }
    
    free(arbol);
}

/*
 * Funcion recursiva que dado un elemento a insertar en el arbol busca un nodo padre (anterior) utilizando el 
 * comparador. Cuando no se pueda comparar mas devuelve dicho nodo padre.
 */
nodo_abb_t* buscar_nuevo_nodo_padre(abb_comparador comparador, nodo_abb_t* nuevo_padre, void* elemento){ //insertar
    int comparacion = comparador(elemento, nuevo_padre->elemento);

    if (comparacion >= IGUAL && nuevo_padre->derecha) 
        nuevo_padre = buscar_nuevo_nodo_padre(comparador, nuevo_padre->derecha, elemento);
    else if (comparacion <= MENOR && nuevo_padre->izquierda)
        nuevo_padre = buscar_nuevo_nodo_padre(comparador, nuevo_padre->izquierda, elemento);

    //printf("nuevo padre: %d\n", *(int*)nuevo_padre->elemento);
    return nuevo_padre;
}

/*
 * Funcion recursiva que dado un elemento se encarga de buscar el nodo padre (anterior) de dicho elemento.
*/
nodo_abb_t* buscar_nodo_padre(abb_comparador comparador, nodo_abb_t* nodo_hijo, void* elemento, nodo_abb_t* nodo_padre) { //borrar
    int comparacion = comparador(elemento, nodo_hijo->elemento);
    if (comparacion == IGUAL) return nodo_padre;

    if (comparacion >= MAYOR && nodo_hijo->derecha) {
        nodo_padre = nodo_hijo;
        nodo_hijo = buscar_nodo_padre(comparador, nodo_hijo->derecha, elemento, nodo_padre);
    } else if (comparacion <= MENOR && nodo_hijo->izquierda) {
        nodo_padre = nodo_hijo;
        nodo_hijo = buscar_nodo_padre(comparador, nodo_hijo->izquierda, elemento, nodo_padre);
    }
    return nodo_hijo;
}

/*
 * Funcion recursiva que dado un elemento se encarga de buscar en el arbol el nodo que lo contenga.
 * En el caso de no encontrarlo devuelve el ultimo nodo comparado.
*/
nodo_abb_t* buscar_nodo_segun_elemento(abb_comparador comparador, nodo_abb_t* nodo_raiz, void* elemento) { //buscar
    int comparacion = comparador(elemento, nodo_raiz->elemento);
    if (comparacion == IGUAL) return nodo_raiz;

    if (comparacion >= MAYOR && nodo_raiz->derecha) 
        nodo_raiz = buscar_nodo_segun_elemento(comparador, nodo_raiz->derecha, elemento);
    else if (comparacion <= MENOR && nodo_raiz->izquierda)
        nodo_raiz = buscar_nodo_segun_elemento(comparador, nodo_raiz->izquierda, elemento);

    return nodo_raiz;
}

/*
 * Funcion que dado un elemento, busca un nodo que contenga dicho elemento y lo devuelve. En el caso de que 
 * el elemento no se encuentre en el arbol, devuelve NULL.
*/
nodo_abb_t* verifico_nodo_sea_el_esperado(abb_t* arbol, void* elemento, nodo_abb_t* nodo_encontrado){ //buscar
    nodo_encontrado = buscar_nodo_segun_elemento(arbol->comparador, arbol->nodo_raiz, elemento);
    if (arbol->comparador(nodo_encontrado->elemento,elemento) != IGUAL)
        return NULL;
    return nodo_encontrado;
}

void* arbol_buscar(abb_t* arbol, void* elemento) {
    if (!arbol  || arbol_vacio(arbol) || !arbol->comparador) return NULL;
    nodo_abb_t* encontrado = NULL;   

    encontrado = verifico_nodo_sea_el_esperado(arbol, elemento, encontrado);
    if (!encontrado) return NULL;
        
    return encontrado->elemento;
}

/*
 * Funcion recursiva que dado un nodo a borrar encuentra su nodo predecesor inorden.
*/
nodo_abb_t* elemento_predecesor_inorden(nodo_abb_t* nodo_hijo) { 

    if (nodo_hijo->derecha) {
        nodo_hijo = nodo_hijo->derecha;
        nodo_hijo = elemento_predecesor_inorden(nodo_hijo);
    } 

    return nodo_hijo;
}

/*
 * Funcion recursiva que dado un nodo a borrar, busca su predecesor inorden para luego encontrar
 * el padre de dicho predecesor y devolverlo.
*/
nodo_abb_t* elemento_padre_predecesor_inorden(nodo_abb_t* padre_del_sucesor, nodo_abb_t* sucesor) { 
   
    if (padre_del_sucesor->derecha) {
        if (!(padre_del_sucesor->derecha == sucesor)) 
            padre_del_sucesor = elemento_padre_predecesor_inorden(padre_del_sucesor->derecha, sucesor);
    }
    //printf("-Padre del Predecesor: %d\n", *(int*)padre_del_sucesor->elemento);
    return padre_del_sucesor;
}

/*
 * Funcion que dado un nodo devuelve la devuelve la cantidad de hijos de este. En el caso de no tener hijos 
 * devuelve 0, dos hijos devuelve 2 y en el caso de un hijo devuelve 1 si es hijo mayor (derecha) y -1 si 
 * es hijo menor (izquierda).
 */
int nodo_tiene_hijos(nodo_abb_t* nodo_a_borrar) {
    int hijos = SIN_HIJOS;
    if (!nodo_a_borrar->derecha && nodo_a_borrar->izquierda)  
        hijos = UN_HIJO_I;
    else if (!nodo_a_borrar->izquierda && nodo_a_borrar->derecha)
        hijos = UN_HIJO_D;
    else if (nodo_a_borrar->derecha && nodo_a_borrar->izquierda) 
        hijos = DOS_HIJOS;
    return hijos;
}

int arbol_borrar(abb_t* arbol, void* elemento) {
    if (!arbol || arbol_vacio(arbol)) return ERROR;
    nodo_abb_t* nodo_a_borrar = NULL;
    nodo_abb_t* nodo_padre = arbol->nodo_raiz;
    nodo_a_borrar = verifico_nodo_sea_el_esperado(arbol, elemento, nodo_a_borrar);
    if (!nodo_a_borrar) return ERROR;  //el elemento no se encuentra en el arbol

    int hijos = nodo_tiene_hijos(nodo_a_borrar);
    nodo_padre = buscar_nodo_padre(arbol->comparador, arbol->nodo_raiz, elemento, nodo_padre);
    bool es_la_raiz = !(arbol->comparador(elemento, arbol->nodo_raiz->elemento)); // el elemento a borrar es la raiz
    //printf("es la raiz: %d\n", es_la_raiz);
    int comparacion = arbol->comparador(elemento, nodo_padre->elemento);
    nodo_abb_t* predecesor = NULL;
    
    if (hijos == DOS_HIJOS) {
        nodo_abb_t* padre_del_predecesor = nodo_a_borrar;
        predecesor = elemento_predecesor_inorden(nodo_a_borrar->izquierda);
        bool hijo_es_predecesor = (predecesor == nodo_a_borrar->izquierda);
        //printf("hijo es Predecesor: %d\n", hijo_es_predecesor);

        predecesor->derecha = nodo_a_borrar->derecha; 
        if (!hijo_es_predecesor) {  //si el hijo del nodo a borrar NO es el nodo predecesor
            padre_del_predecesor = elemento_padre_predecesor_inorden(nodo_a_borrar->izquierda, predecesor);
            padre_del_predecesor->derecha = predecesor->izquierda; 
            predecesor->izquierda = nodo_a_borrar->izquierda;
        }
    //printf("Padre del Predecesor: %d\n", *(int*)padre_del_predecesor->elemento);
    } else if (hijos == UN_HIJO_D) 
        predecesor = nodo_a_borrar->derecha; 
    else if (hijos == UN_HIJO_I)
        predecesor = nodo_a_borrar->izquierda;
    //if (predecesor)  printf("Predecesor: %d\n", *(int*)predecesor->elemento);
    if (es_la_raiz) //si el elemento a ser borrado es la raiz
        arbol->nodo_raiz =  predecesor;
    else if (comparacion >= IGUAL)  //si el elemento a ser borrado es mayor o igual que su nodo padre
        nodo_padre->derecha = predecesor;
    else if(comparacion <= MENOR) //si el elemento a ser borrado es menor que su nodo padre
        nodo_padre->izquierda = predecesor;

    if(arbol->destructor)
        arbol->destructor(nodo_a_borrar->elemento);
    free(nodo_a_borrar);
    //if (arbol->nodo_raiz) printf("\nRAIZ: %d\n", *(int*)arbol->nodo_raiz->elemento);
    return EXITO;
}

int arbol_insertar(abb_t* arbol, void* elemento) {
    if (!arbol) return ERROR;

    nodo_abb_t* nodo_aux = (nodo_abb_t*)calloc(1, sizeof(nodo_abb_t));
    if (!nodo_aux) return ERROR;
    nodo_aux->elemento = elemento;

    if (arbol_vacio(arbol))
        arbol->nodo_raiz = nodo_aux;
    else {
        nodo_abb_t* nodo_padre = NULL;
        nodo_padre = buscar_nuevo_nodo_padre(arbol->comparador, arbol->nodo_raiz, elemento);
        if (nodo_padre) { //no tiene hijos
            int comparacion = arbol->comparador(elemento, nodo_padre->elemento);

            if ((comparacion >= IGUAL) && !nodo_padre->derecha)
                nodo_padre->derecha = nodo_aux;
            else if (comparacion <= MENOR && !nodo_padre->izquierda)  
                nodo_padre->izquierda = nodo_aux;  
        }
    }
    return EXITO;
}

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {
    if (!comparador) return NULL;

    abb_t* arbol = (abb_t*)calloc(1, sizeof(abb_t));
    if (!arbol) return NULL;
    
    arbol->comparador = comparador;
    arbol->destructor = destructor;

    return arbol;
}
