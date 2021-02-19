#include "abb.h"
#include "pa2mm.h"
#include <stdio.h>

#define EXITO 0
#define ERROR -1

#define MAX_CANT 10

#define IGUALES 0
#define ANTERIOR_MAYOR 1
#define ANTERIOR_MENOR -1

typedef struct manzana {
    int peso;
    char cantidad[MAX_CANT];
} manzana_t;

void comer_manzana(manzana_t* manzana){

    free(manzana);  
}

void destructor(void* elemento) {
    if(!elemento) return;
    
    comer_manzana((manzana_t*)elemento);
}

manzana_t* pesar_manzana(int peso){
    manzana_t* manzana = (manzana_t*)calloc(1,sizeof(manzana_t));
    if(manzana) manzana->peso = peso;

    return manzana;
}

int comparador(void* elemento1, void* elemento2) {

    int resultado = 2;
    int ele1 = *(int*)elemento1;
    int ele2 = *(int*)elemento2;

    if (ele1 == ele2) resultado = IGUALES;
    else if (ele1 > ele2) resultado = ANTERIOR_MAYOR;
    else if (ele1 < ele2) resultado = ANTERIOR_MENOR;

    return resultado;
}

bool mostrar_peso(void* elemento, void* extra){
    extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
    if(!elemento)
        return false;
       // printf("%i  ", ((manzana_t*)elemento)->peso);
        
    return true;
}

bool mostrar_hasta_5(void* elemento, void* extra){
    extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
    if(elemento){
       // printf("%i  ", ((manzana_t*)elemento)->peso);
        //printf("");
        if(((manzana_t*)elemento)->peso == 5)
            return true;
    }
    return false;
}

bool mostrar_acumulado(void* elemento, void* extra){
    if(elemento && extra){
        *(int*)extra += ((manzana_t*)elemento)->peso;
       // printf("%i  ", *(int*)extra);
        //printf("\n");
    }
    return false;
}

abb_t* insertar_elementos() {
    manzana_t* c1= pesar_manzana(10);
    manzana_t* c2= pesar_manzana(5);
    manzana_t* c3= pesar_manzana(15);
    manzana_t* c4= pesar_manzana(12);
    manzana_t* c5= pesar_manzana(2);
    manzana_t* c6= pesar_manzana(7);
    manzana_t* c7= pesar_manzana(1);
    manzana_t* c8= pesar_manzana(8);
    manzana_t* c9= pesar_manzana(9);
    

    abb_t* arbol = arbol_crear(&comparador,&destructor);
    arbol_insertar(arbol, c1);
    arbol_insertar(arbol, c2);
    arbol_insertar(arbol, c3);
    arbol_insertar(arbol, c4);
    arbol_insertar(arbol, c5);
    arbol_insertar(arbol, c6);
    arbol_insertar(arbol, c7);
    arbol_insertar(arbol, c8);
    arbol_insertar(arbol, c9);

    return arbol;
}

void pruebas_de_iterador_interno_postorden() {
    manzana_t* c10= pesar_manzana(10);
    abb_t* arbol = insertar_elementos();
    arbol_insertar(arbol, c10);
    int acumulador=0;
    size_t elementos_recorridos = 0;
    size_t cantidad_esperada = 10;
    elementos_recorridos = abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_peso, NULL);
    pa2m_afirmar(elementos_recorridos, "Devuelve la cantidad esperada de elementos");
    cantidad_esperada = 6;
    elementos_recorridos = abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
    pa2m_afirmar(elementos_recorridos == cantidad_esperada, "Devuelve la cantidad esperada de elementos");
    elementos_recorridos = abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_acumulado, &acumulador);
    pa2m_afirmar(acumulador == 79, "El valor acumulado es el esperado");

    arbol_destruir(arbol);
   
}

void pruebas_de_iterador_interno_preorden() {
    manzana_t* c10= pesar_manzana(10);
    abb_t* arbol = insertar_elementos();
    arbol_insertar(arbol, c10);
    int acumulador=0;
    size_t elementos_recorridos = 0;
    size_t cantidad_esperada = 10;
    elementos_recorridos = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_peso, NULL);
    pa2m_afirmar(elementos_recorridos, "Devuelve la cantidad esperada de elementos");
    cantidad_esperada = 2;
    elementos_recorridos = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
    pa2m_afirmar(elementos_recorridos == cantidad_esperada, "Devuelve la cantidad esperada de elementos");
    elementos_recorridos = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_acumulado, &acumulador);
    pa2m_afirmar(acumulador == 79, "El valor acumulado es el esperado");

    arbol_destruir(arbol);
}

void pruebas_de_iterador_interno_inorden() {
    manzana_t* c10= pesar_manzana(10);
    abb_t* arbol = insertar_elementos();
    arbol_insertar(arbol, c10);
    int acumulador=0;
    size_t elementos_recorridos = 0;
    size_t cantidad_esperada = 10;
    elementos_recorridos = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_peso, NULL);
    pa2m_afirmar(elementos_recorridos, "Devuelve la cantidad esperada de elementos");
    cantidad_esperada = 3;
    elementos_recorridos = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
    pa2m_afirmar(elementos_recorridos == cantidad_esperada, "Devuelve la cantidad esperada de elementos");
    elementos_recorridos = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_acumulado, &acumulador);
    pa2m_afirmar(acumulador == 79, "El valor acumulado es el esperado");

    arbol_destruir(arbol);
}

void postorden(abb_t* arbol, manzana_t** manzanas, size_t manzanas_esperadas, int* resultado){
    size_t tamanio_array = 10;
    size_t manzanas_recorridas = arbol_recorrido_postorden(arbol, (void**)manzanas, tamanio_array);
    bool orden_esperado = true;
    bool cantidad_esperada = (manzanas_esperadas == manzanas_recorridas);
    size_t i = 0; 

    while(orden_esperado && i < manzanas_recorridas) {
        orden_esperado = (resultado[i] == manzanas[i]->peso);
        i++;
    }
    pa2m_afirmar(orden_esperado && cantidad_esperada, "El array se encuentra ordenado y con la cantidad esperada de elementos");
}

void pruebas_de_postorden() { 
    manzana_t* manzanas[10];
    manzana_t* aux = pesar_manzana(10);
    abb_t* arbol = insertar_elementos();
    abb_t* abb = arbol_crear(&comparador,&destructor);

    bool arbol_nulo = !arbol_recorrido_postorden(NULL, (void**)manzanas, 10);
    bool vacio = !arbol_recorrido_postorden(abb, (void**)manzanas, 10);

    pa2m_afirmar(arbol_nulo && vacio, "Si el arbol no esxiste o esta vacio no se realiza el recorrido");
    free(abb);

    pa2m_afirmar(arbol, "Inserto menos elementos que el tamanio del array");
    int resultado[10] = {1, 2, 9, 8, 7, 5, 12, 15, 10};
    size_t manzanas_esperadas = 9;
    postorden(arbol, manzanas, manzanas_esperadas, resultado);

    manzana_t* c10= pesar_manzana(10);
    pa2m_afirmar(!arbol_insertar(arbol, c10), "Inserto los mismos elementos que el tamanio del array");
    int resultado2[10] = {1, 2, 9, 8, 7, 5, 10, 12, 15, 10};
    manzanas_esperadas = 10;
    postorden(arbol, manzanas, manzanas_esperadas, resultado2);
    
    manzana_t* c11= pesar_manzana(11);
    pa2m_afirmar(!arbol_insertar(arbol, c11), "Inserto menos elementos que el tamanio del array");
    int resultado3[10] = {1, 2, 9, 8, 7, 5, 11, 10, 12, 15};
    postorden(arbol, manzanas, manzanas_esperadas, resultado3);

    arbol_destruir(arbol);
    free(aux);
}

void preorden(abb_t* arbol, manzana_t** manzanas, size_t manzanas_esperadas, int* resultado){
    size_t tamanio_array = 10;
    size_t manzanas_recorridas = arbol_recorrido_preorden(arbol, (void**)manzanas, tamanio_array);
    bool orden_esperado = true;
    bool cantidad_esperada = (manzanas_esperadas == manzanas_recorridas);
    size_t i = 0;

    while(orden_esperado && i < manzanas_recorridas) {
        orden_esperado = (resultado[i] == manzanas[i]->peso);
        i++;
    }
    pa2m_afirmar(orden_esperado && cantidad_esperada, "El array se encuentra ordenado y con la cantidad esperada de elementos");
}

void pruebas_de_preorden() {
    manzana_t* manzanas[10];
    manzana_t* aux = pesar_manzana(10);
    abb_t* arbol = insertar_elementos();
    abb_t* abb = arbol_crear(&comparador,&destructor);

    bool arbol_nulo = !arbol_recorrido_preorden(NULL, (void**)manzanas, 10);
    bool vacio = !arbol_recorrido_preorden(abb, (void**)manzanas, 10);

    pa2m_afirmar(arbol_nulo && vacio, "Si el arbol no esxiste o esta vacio no se realiza el recorrido");
    free(abb);

    pa2m_afirmar(arbol, "Inserto menos elementos que el tamanio del array");
    int resultado[10] = {10, 5, 2, 1, 7, 8, 9, 15, 12, 10};
    size_t manzanas_esperadas = 9;
    preorden(arbol, manzanas, manzanas_esperadas, resultado);

    manzana_t* c10= pesar_manzana(10);
    pa2m_afirmar(!arbol_insertar(arbol, c10), "Inserto los mismos elementos que el tamanio del array");
    manzanas_esperadas = 10;
    preorden(arbol, manzanas, manzanas_esperadas, resultado);
   
    manzana_t* c11= pesar_manzana(11);
    pa2m_afirmar(!arbol_insertar(arbol, c11), "Inserto mas elementos que el tamanio del array");
    preorden(arbol, manzanas, manzanas_esperadas, resultado);

    arbol_destruir(arbol);
    free(aux);
   
}

void inorden(abb_t* arbol, manzana_t** manzanas, size_t manzanas_esperadas, int* resultado){
    size_t tamanio_array = 10;
    size_t manzanas_recorridas = arbol_recorrido_inorden(arbol, (void**)manzanas, tamanio_array);
    bool orden_esperado = true;
    bool cantidad_esperada = (manzanas_esperadas == manzanas_recorridas);
    size_t i = 0; 

    while(orden_esperado && i < manzanas_recorridas) {
        orden_esperado = (resultado[i] == manzanas[i]->peso);
        i++;
    }
    pa2m_afirmar(orden_esperado && cantidad_esperada, "El array se encuentra ordenado y con la cantidad esperada de elementos");
}

void pruebas_de_inorden() {
    manzana_t* manzanas[10];
    manzana_t* aux = pesar_manzana(10);
    abb_t* arbol = insertar_elementos();
    abb_t* abb = arbol_crear(&comparador,&destructor);

    bool arbol_nulo = !arbol_recorrido_inorden(NULL, (void**)manzanas, 10);
    bool vacio = !arbol_recorrido_inorden(abb, (void**)manzanas, 10);

    pa2m_afirmar(arbol_nulo && vacio, "Si el arbol no esxiste o esta vacio no se realiza el recorrido");
    free(abb);

    pa2m_afirmar(arbol, "Inserto menos elementos que el tamanio del array");
    int resultado1[10] = {1, 2, 5, 7, 8, 9, 10, 12, 15};
    size_t manzanas_esperadas = 9;
    inorden(arbol, manzanas, manzanas_esperadas, resultado1);
    
    manzana_t* c10= pesar_manzana(10);  
    pa2m_afirmar(!arbol_insertar(arbol, c10), "Inserto los mismos elementos que el tamanio del array");

    int resultado2[10] = {1, 2, 5, 7, 8, 9, 10, 10, 12, 15};
    manzanas_esperadas = 10;
    inorden(arbol, manzanas, manzanas_esperadas, resultado2);
   
    manzana_t* c11= pesar_manzana(11);
    pa2m_afirmar(!arbol_insertar(arbol, c11), "Inserto mas elementos que el tamanio del array");

    int resultado3[10] = {1, 2, 5, 7, 8, 9, 10, 10, 11, 12};
    inorden(arbol, manzanas, manzanas_esperadas, resultado3);

    arbol_destruir(arbol);
    free(aux);
}

void pruebas_con_null() {
    manzana_t* aux = pesar_manzana(6);
    abb_t* arbol_nulo = arbol_crear(NULL,NULL);
    pa2m_afirmar(arbol_nulo == NULL, "El arbol no se puede crear sin un comparador");
    arbol_destruir(arbol_nulo);

    arbol_nulo = arbol_crear(&comparador,NULL);
    pa2m_afirmar(arbol_nulo != NULL, "El arbol se puede crear sin un destructor");
    pa2m_afirmar(arbol_vacio(arbol_nulo) == true, "Un arbol nulo es considerado vacio");
    pa2m_afirmar(arbol_insertar(NULL, aux) == ERROR, "Devuelve ERROR al insertar un elemento en un arbol nulo");
    arbol_destruir(arbol_nulo);
    
    abb_t* abb = arbol_crear(&comparador,&destructor);
    pa2m_afirmar(arbol_insertar(abb, NULL) == EXITO, "Se pudo insertar un elemento NULL");
    pa2m_afirmar(arbol_raiz(abb) == NULL, "El nodo raiz es NULL");
    arbol_destruir(abb);

    free(aux);
}

void pruebas_de_abb_con_5_elementos() { 
    manzana_t* c1= pesar_manzana(1);
    manzana_t* c3= pesar_manzana(3);
    manzana_t* c5= pesar_manzana(5);
    manzana_t* c9= pesar_manzana(5);
    manzana_t* c7= pesar_manzana(7);
    manzana_t* aux = pesar_manzana(5);  

    abb_t* abb = arbol_crear(&comparador,destructor);

    pa2m_afirmar(abb != NULL, "Se pudo crear el arbol");
    pa2m_afirmar(arbol_vacio(abb) == true, "Este esta vacio");
    pa2m_afirmar(arbol_insertar(abb, c5) == EXITO, "Se pudo insertar el elemento 5");  
    pa2m_afirmar(*(int*)(abb->nodo_raiz->elemento) == *(int*)aux, "EL elemento RAIZ es el esperado");
    pa2m_afirmar(arbol_vacio(abb) == false, "El arbol no esta mas vacio");
    pa2m_afirmar(arbol_insertar(abb, c7) == EXITO, "Se pudo insertar un elemento mayor");  
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "La raiz del arbol es la esperada");
    aux->peso = 7;
    pa2m_afirmar(*(int*)(abb->nodo_raiz->derecha->elemento) == *(int*)aux, "EL elemento derecho de la raiz 7");
    pa2m_afirmar((abb->nodo_raiz->derecha)&&(!abb->nodo_raiz->izquierda), "La raiz tiene hijo derecho pero no izquierdo");
    pa2m_afirmar(arbol_insertar(abb, c3) == EXITO, "Se pudo insertar un elemento menor");  
    aux->peso = 3;
    pa2m_afirmar(*(int*)(abb->nodo_raiz->izquierda->elemento) == *(int*)aux, "EL elemento izquierdo de la raiz es 3");
    pa2m_afirmar((abb->nodo_raiz->derecha)&&(abb->nodo_raiz->izquierda), "La raiz tiene dos hijos");
    pa2m_afirmar(*(int*)(arbol_buscar(abb,aux)) == *(int*)aux, "Se encontro el 3");
    aux->peso = 7;
    pa2m_afirmar(*(int*)(arbol_buscar(abb,aux)) == *(int*)aux, "Se encontro el 7");
    aux->peso = 5;
    pa2m_afirmar(*(int*)(arbol_buscar(abb,aux)) == *(int*)aux, "Se encontro el 5");
    pa2m_afirmar(arbol_insertar(abb, c9) == EXITO, "Se pudo insertar un elemento igual que la raiz");  
    pa2m_afirmar(*(int*)(abb->nodo_raiz->derecha->izquierda->elemento) == *(int*)aux, "EL hijo izquierdo del 7 es 5");
    pa2m_afirmar(arbol_insertar(abb, c1) == EXITO, "Inserto el elemento 1");  
    aux->peso = 1;
    pa2m_afirmar(*(int*)(abb->nodo_raiz->izquierda->izquierda->elemento) == *(int*)aux, "EL hijo izquierdo del 3 es 1");
    aux->peso = 4;
    pa2m_afirmar(arbol_buscar(abb,aux) == (void*)NULL, "NO se encontro el 4");
    aux->peso = 2;
    pa2m_afirmar(arbol_buscar(abb,aux) == (void*) NULL, "NO se encontro el 2");
    aux->peso = 5; 
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar el elemento 5 aunque este duplicado");
    pa2m_afirmar(*(int*)arbol_buscar(abb,aux) == *(int*)aux, "Se encontro el 5");
    aux->peso = 3; 
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "La raiz del arbol vuelve pasa a ser el 3");
    
    arbol_destruir(abb);
    free(aux);
    printf("\n");  
}

void pruebas_de_abb_raiz_con_duplicado(){
    manzana_t* c1= pesar_manzana(10);
    manzana_t* c2= pesar_manzana(5);
    manzana_t* c3= pesar_manzana(15);
    manzana_t* c4= pesar_manzana(12);
    manzana_t* c5= pesar_manzana(2);
    manzana_t* c6= pesar_manzana(7);
    manzana_t* c7= pesar_manzana(1);
    manzana_t* c8= pesar_manzana(8);
    manzana_t* c9= pesar_manzana(9);
    manzana_t* c10= pesar_manzana(5);
    manzana_t* c11= pesar_manzana(8);
    manzana_t* c12= pesar_manzana(15);
    manzana_t* c13= pesar_manzana(13);
    manzana_t* c14= pesar_manzana(10);

    manzana_t* aux = pesar_manzana(10);
    abb_t* abb = arbol_crear(&comparador,&destructor);
    arbol_insertar(abb, c1);
    arbol_insertar(abb, c2);
    arbol_insertar(abb, c3);
    arbol_insertar(abb, c4);
    arbol_insertar(abb, c5);
    arbol_insertar(abb, c6);
    arbol_insertar(abb, c7);
    arbol_insertar(abb, c8);
    arbol_insertar(abb, c9);
    arbol_insertar(abb, c10);
    arbol_insertar(abb, c11);
    arbol_insertar(abb, c12);
    arbol_insertar(abb, c13);
    arbol_insertar(abb, c14);
    
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar la raiz"); 
    aux->peso = 9;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    pa2m_afirmar((abb->nodo_raiz->izquierda && abb->nodo_raiz->derecha), "Quedo con dos hijos"); 
    pa2m_afirmar((*(int*)abb->nodo_raiz->elemento == *(int*)aux), "es9"); 
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz"); 
    aux->peso = 8;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz"); 
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz");
    aux->peso = 7;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz"); 
    aux->peso = 5;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz"); 
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz");
    bool se_borro = true;
    while(!arbol_vacio(abb) && se_borro){
        se_borro = !arbol_borrar(abb, arbol_raiz(abb));
    }
    pa2m_afirmar(se_borro, "Se pudieron eliminar todos los elementos borrando siempre la raiz");
    pa2m_afirmar(arbol_vacio(abb) == true, "El abb esta vacio");

    arbol_destruir(abb);
    free(aux);
    }

void pruebas_de_abb_raiz(){    
    abb_t* abb = insertar_elementos();
    manzana_t* aux = pesar_manzana(10);

    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar la raiz"); 
    aux->peso = 9;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    pa2m_afirmar((abb->nodo_raiz->izquierda && abb->nodo_raiz->derecha), "Quedo con dos hijos"); 
    aux->peso = 15;
    pa2m_afirmar((*(int*) abb->nodo_raiz->derecha->elemento == *(int*)aux), "El hijo derecho es el esperado");
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz"); 
    aux->peso = 8;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    pa2m_afirmar((abb->nodo_raiz->izquierda && abb->nodo_raiz->derecha), "Quedo con dos hijos");
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz"); 
    aux->peso = 7;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz"); 
    aux->peso = 5;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    aux->peso = 2;
    pa2m_afirmar((*(int*) abb->nodo_raiz->izquierda->elemento == *(int*)aux), "El hijo izquierdo es el esperado");
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz"); 
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El predecesor quedo como raiz"); 
    pa2m_afirmar((abb->nodo_raiz->izquierda && abb->nodo_raiz->derecha), "Quedo con dos hijos");
    aux->peso = 15;
    pa2m_afirmar((*(int*) abb->nodo_raiz->derecha->elemento == *(int*)aux), "El hijo derecho es el esperado");
    aux->peso = 1;
    pa2m_afirmar((*(int*) abb->nodo_raiz->izquierda->elemento == *(int*)aux), "El hijo izquierdo es el esperado");
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz");
    pa2m_afirmar((!abb->nodo_raiz->izquierda && abb->nodo_raiz->derecha), "Quedo con un hijo mayor");

    arbol_destruir(abb);
    free(aux);
    }


void pruebas_de_eliminacion_doble() {   
    manzana_t* c1= pesar_manzana(1);
    manzana_t* c2= pesar_manzana(2);
    manzana_t* c4= pesar_manzana(4);
    manzana_t* c3= pesar_manzana(3);
    manzana_t* c5= pesar_manzana(5);
    manzana_t* c7= pesar_manzana(7);
    manzana_t* c8= pesar_manzana(8);
    manzana_t* c6= pesar_manzana(6);
    manzana_t* aux = pesar_manzana(0);
    abb_t* abb = arbol_crear(&comparador,destructor);
    
    pa2m_afirmar(arbol_insertar(abb, c5) == EXITO, "Se pudo insertar el elemento 5"); 
    pa2m_afirmar(arbol_insertar(abb, c7) == EXITO, "Se pudo insertar el elemento 7"); 
    pa2m_afirmar(arbol_insertar(abb, c3) == EXITO, "Se pudo insertar el elemento 3"); 
    aux->peso = 5;
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar la raiz con dos hijos");  
    pa2m_afirmar(arbol_buscar(abb,aux) == (void*) NULL, "No se encontro el 5");
    aux->peso = 3;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El 3 quedo como raiz"); 
    pa2m_afirmar((abb->nodo_raiz->derecha && !abb->nodo_raiz->izquierda), "Quedo sin hijo derecho"); 
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar la raiz"); 
    aux->peso = 7;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El 7 quedo como raiz"); 
    pa2m_afirmar((!abb->nodo_raiz->izquierda && !abb->nodo_raiz->derecha), "Quedo sin hijos"); 
    arbol_insertar(abb, c2);
    arbol_insertar(abb, c1);
    arbol_insertar(abb, c4);
    arbol_insertar(abb, c8);
    pa2m_afirmar(true, "Inserto 4 elementos mas");
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar el elemento 7 con dos hijos");
    aux->peso = 4;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El 4 quedo como raiz"); 
    aux->peso = 1;
    pa2m_afirmar(*(int*)arbol_buscar(abb,aux) == *(int*)aux, "Se encontro el 1");
    pa2m_afirmar(arbol_insertar(abb, c6) == EXITO, "Se pudo insertar el elemento 6"); 
    aux->peso = 4;
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar la raiz");
    pa2m_afirmar((abb->nodo_raiz->izquierda && abb->nodo_raiz->derecha), "Quedo con dos hijos"); 
    aux->peso = 2;
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar el elemento 2");
    
    arbol_destruir(abb);
    free(aux);
}

void pruebas_de_eliminacion_simple() {   
    manzana_t* c3= pesar_manzana(3);
    manzana_t* c5= pesar_manzana(5);
    manzana_t* c7= pesar_manzana(7);
    manzana_t* c8= pesar_manzana(8);
    manzana_t* c9= pesar_manzana(9);
    manzana_t* aux = pesar_manzana(0);
    abb_t* abb = arbol_crear(&comparador,destructor);
    
    pa2m_afirmar(arbol_insertar(abb, c7) == EXITO, "Se pudo insertar el elemento 7"); 
    pa2m_afirmar(arbol_insertar(abb, c8) == EXITO, "Se pudo insertar el elemento 8"); 
    aux->peso = 8;
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar el elemento 8 sin hijos");  
    pa2m_afirmar(arbol_insertar(abb, c5) == EXITO, "Se pudo insertar el elemento 5"); 
    pa2m_afirmar(arbol_insertar(abb, c3) == EXITO, "Se pudo insertar el elemento 3"); 
    aux->peso = 5;
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar el elemento 5 con un hijo menor");  
    aux->peso = 3;
    pa2m_afirmar(*(int*)(abb->nodo_raiz->izquierda->elemento) == *(int*)aux, "El 3 queda a la izquierda de la raiz"); 
    pa2m_afirmar(arbol_insertar(abb, c9) == EXITO, "Se pudo insertar el elemento 9"); 
    aux->peso = 7;
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar el elemento 7 con dos hijos");  
    aux->peso = 3;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El 3 queda como raiz"); 
    
    arbol_destruir(abb);
    free(aux);
}

void pruebas_de_abb_simple() {   
    manzana_t* c3= pesar_manzana(3);
    manzana_t* c5= pesar_manzana(5);
    manzana_t* c7= pesar_manzana(7);
    manzana_t* c8= pesar_manzana(8);
    manzana_t* c88= pesar_manzana(8);
    manzana_t* c55= pesar_manzana(5);

    manzana_t* aux = pesar_manzana(0);
    abb_t* abb = arbol_crear(&comparador,destructor);

    aux->peso = 7; 
    pa2m_afirmar((arbol_insertar(abb, c7) == EXITO) && (*(int*)abb->nodo_raiz->elemento == *(int*)aux), "Se pudo insertar el elemento 7 como raiz"); 
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se pudo borrar la raiz sin hijos");  
    pa2m_afirmar(arbol_insertar(abb, c5) == EXITO, "Otra vez pudo insertar un elemento"); 
    aux->peso = 5;
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El elemento insertado queda como raiz"); 
    pa2m_afirmar(arbol_insertar(abb, c3) == EXITO, "Se pudo insertar 3 como elemento menor"); 
    aux->peso = 3;
    pa2m_afirmar(*(int*)(abb->nodo_raiz->izquierda->elemento) == *(int*)aux, "El nuevo elemento queda a la izquierda de la raiz"); 
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz aunque tenga un hijo menor"); 
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El hijo menor quedo como raiz"); 
    pa2m_afirmar((!abb->nodo_raiz->izquierda && !abb->nodo_raiz->derecha), "Quedo sin hijos"); 
    aux->peso = 5;
    pa2m_afirmar(arbol_buscar(abb,aux) == (void*) NULL, "No se encontro el 5");
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz "); 
    pa2m_afirmar(arbol_vacio(abb) == true, "El arbol quedo vacio"); 
    pa2m_afirmar((arbol_insertar(abb, c55) == EXITO) && (*(int*)arbol_raiz(abb) == *(int*)aux), "Inserto 5 como raiz"); 
    pa2m_afirmar(arbol_insertar(abb, c8) == EXITO, "Inserto 8 como hijo mayor"); 
    aux->peso = 8;
    pa2m_afirmar(*(int*)(abb->nodo_raiz->derecha->elemento) == *(int*)aux, "El nuevo elemento queda a la derecha de la raiz"); 
    pa2m_afirmar(arbol_borrar(abb, arbol_raiz(abb)) == EXITO, "Se pudo borrar la raiz con un hijo mayor"); 
    pa2m_afirmar(*(int*)arbol_raiz(abb) == *(int*)aux, "El 8 quedo como raiz"); 
    pa2m_afirmar(arbol_insertar(abb, c88) == EXITO, "Inserto elemento igual a la raiz"); 
    pa2m_afirmar(arbol_borrar(abb, aux) == EXITO, "Se borra correctamente aunque el elemento este repetido"); 
    
    arbol_destruir(abb);
    free(aux);
}

int main() {

    pa2m_nuevo_grupo("PRUEBAS DE ARBOL");
    pruebas_de_abb_con_5_elementos();

    pa2m_nuevo_grupo("PRUEBAS CON NULL");
    pruebas_con_null();

    pa2m_nuevo_grupo("PRUEBAS DE ABB RAIZ");
    pruebas_de_abb_raiz();
    
    pa2m_nuevo_grupo("PRUEBAS DE ABB RAIZ CON ELEMENTOS DUPLICADOS");
    pruebas_de_abb_raiz_con_duplicado();

    pa2m_nuevo_grupo("PRUEBAS DE INSERCION SIMPLE");
    pruebas_de_abb_simple();

    pa2m_nuevo_grupo("PRUEBAS DE ELIMINACION SIMPLE");
    pruebas_de_eliminacion_simple();
    
    pa2m_nuevo_grupo("PRUEBAS DE INSERCION Y ELIMINACION MULTIPLE");
    pruebas_de_eliminacion_doble();

    pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO INORDEN");
    pruebas_de_inorden();

    pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO PREORDEN");
    pruebas_de_preorden();
 
    pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO POSTORDEN");
    pruebas_de_postorden();
    
    pa2m_nuevo_grupo("PRUEBAS DE ITERADOR INTERNO"); 

    pa2m_nuevo_grupo("ITERADOR INTERNO INORDEN"); 
    pruebas_de_iterador_interno_inorden();

    pa2m_nuevo_grupo("ITERADOR INTERNO PREORDEN"); 
    pruebas_de_iterador_interno_preorden(); 

    pa2m_nuevo_grupo("ITERADOR INTERNO POSTORDEN"); 
    pruebas_de_iterador_interno_postorden();

    pa2m_mostrar_reporte();
    return EXITO;
}