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


/**/
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
    //destruir
    abb_t* abb = arbol_crear(&comparador,&destructor);
    pa2m_afirmar(arbol_insertar(abb, NULL) == EXITO, "Se pudo insertar un elemento NULL");
    pa2m_afirmar(arbol_raiz(abb) == NULL, "El nodo raiz es NULL");
    arbol_destruir(abb);
    free(aux);
    
        //destruir

}

void pruebas_de_abb_con_4_elementos() { 
    manzana_t* c1= pesar_manzana(1);
    manzana_t* c6= pesar_manzana(6);
    manzana_t* c3= pesar_manzana(3);
    manzana_t* c8= pesar_manzana(8);
    manzana_t* c5= pesar_manzana(5);
   // manzana_t* c9= pesar_manzana(9);
    manzana_t* c7= pesar_manzana(7);
    manzana_t* auxiliar = pesar_manzana(0);  

    abb_t* abb = arbol_crear(&comparador,destructor);
    pa2m_afirmar(abb != NULL, "El abb se puede crear");
    pa2m_afirmar(arbol_vacio(abb) == true, "El abb esta vacio");
    pa2m_afirmar(arbol_insertar(abb, c5) == EXITO, "Se pudo insertar un elemento");  
    pa2m_afirmar(((manzana_t*)(abb->nodo_raiz->elemento))->peso == 5, "EL elemento RAIZ es el esperado");
    pa2m_afirmar(arbol_vacio(abb) == false, "El abb no esta vacio");
    pa2m_afirmar(((manzana_t*)arbol_raiz(abb))->peso == 5, "La raiz del arbol es la esperada");
    pa2m_afirmar(arbol_insertar(abb, c7) == EXITO, "Se pudo insertar un elemento mayor");  
    pa2m_afirmar(((manzana_t*)(abb->nodo_raiz->derecha->elemento))->peso == 7, "EL elemento derecho de la raiz es el esperado");
    pa2m_afirmar((abb->nodo_raiz->derecha)&&(!abb->nodo_raiz->izquierda), "La raiz tiene hijo derecho pero no izquierdo");

    pa2m_afirmar(arbol_insertar(abb, c3) == EXITO, "Se pudo insertar un elemento menor");  
    pa2m_afirmar(((manzana_t*)(abb->nodo_raiz->izquierda->elemento))->peso == 3, "EL elemento izquierdo de la raiz es el esperado");
    pa2m_afirmar((abb->nodo_raiz->derecha)&&(abb->nodo_raiz->izquierda), "La raiz tiene hijo derecho e izquierdo");
    auxiliar->peso = 5;
   
    pa2m_afirmar(((manzana_t*)(arbol_buscar(abb,auxiliar)))->peso == 5, "Se encontro el 5");
    auxiliar->peso = 3;

    pa2m_afirmar(((manzana_t*)(arbol_buscar(abb,auxiliar)))->peso == 3, "Se encontro el 3");
    pa2m_afirmar(arbol_insertar(abb, c5) == EXITO, "Se pudo insertar un elemento igual que la raiz");  
    pa2m_afirmar(((manzana_t*)(abb->nodo_raiz->derecha->izquierda->elemento))->peso == 5, "EL elemento izquierdo de la raiz es el esperado");
    auxiliar->peso = 7;

   // pa2m_afirmar(((manzana_t*)(arbol_buscar(abb,auxiliar)))->peso == 7, "Se encontro el 7");
    pa2m_afirmar(arbol_insertar(abb, c1) == EXITO, "Inserto el elemento 1");  
    pa2m_afirmar(((manzana_t*)(abb->nodo_raiz->izquierda->izquierda->elemento))->peso == 1, "EL elemento izquierdo de la raiz es el esperado");
    pa2m_afirmar(arbol_insertar(abb, c6) == EXITO, "Inserto el elemento 6");  
    //pa2m_afirmar(arbol_insertar(abb, pesar_manzana(4)) == EXITO, "Inserto el elemento 4"); 
    //pa2m_afirmar(arbol_insertar(abb, pesar_manzana(5)) == EXITO, "Inserto el elemento 5");  
    pa2m_afirmar(arbol_insertar(abb, c8) == EXITO, "Inserto el elemento 8");
    //pa2m_afirmar(abb->nodo_raiz->derecha->derecha->derecha, "8 tiene hijo");

    

   // pa2m_afirmar(arbol_insertar(abb, pesar_manzana(7)) == EXITO, "Inserto el elemento 7");  
    //pa2m_afirmar(arbol_insertar(abb, pesar_manzana(8)) == EXITO, "Inserto el elemento 8");
    //pa2m_afirmar(arbol_insertar(abb, pesar_manzana(7)) == EXITO, "Inserto el elemento 7");
    auxiliar->peso = 6;
    pa2m_afirmar(((manzana_t*)(arbol_buscar(abb, auxiliar)))->peso == 6, "Se encontro el 6");
    auxiliar->peso = 5;
    pa2m_afirmar(((manzana_t*)(arbol_buscar(abb,auxiliar)))->peso == 5, "Se encontro el 5");
   // pa2m_afirmar(((manzana_t*)(arbol_buscar(abb, (auxiliar->peso = 3))))->peso == 7, "Se encontro el 7");
  //  pa2m_afirmar(((manzana_t*)(arbol_buscar(abb,(auxiliar->peso = 8))))->peso == 8, "Se encontro el 8");
    auxiliar->peso = 10;

    pa2m_afirmar(arbol_buscar(abb,auxiliar) == (void*)NULL, "NO se encontro el 10");
    auxiliar->peso = 11;

    pa2m_afirmar(arbol_buscar(abb,auxiliar) == (void*) NULL, "NO se encontro el 11");
    //pa2m_afirmar(((manzana_t*)(arbol_buscar(abb,pesar_manzana(4))))->peso == 4, "Se encontro el 4");
    

   // pa2m_afirmar(arbol_borrar(abb, pesar_manzana(5)) == EXITO, "Se pudo borrar el elemento 5");
   // pa2m_afirmar(arbol_buscar(abb,pesar_manzana(5)) == (void*) NULL, "No se encontro el 5");
  //  pa2m_afirmar(((manzana_t*)arbol_raiz(abb))->peso == 5, "La raiz del arbol vuelve a ser 5");
    
    pa2m_afirmar(((manzana_t*)(abb->nodo_raiz->derecha->elemento))->peso == 7, "EL elemento derecho de la raiz es el esperado");
    pa2m_afirmar(((manzana_t*)(abb->nodo_raiz->izquierda->elemento))->peso == 3, "EL elemento izquierdo de la raiz es el esperado");
   

   // pa2m_afirmar(((manzana_t*)(arbol_buscar(abb,pesar_manzana(1))))->peso == 1, "Se encontro el 1");
    pa2m_afirmar(arbol_borrar(abb, c1) == EXITO, "Se pudo borrar el elemento 1");
   // pa2m_afirmar(arbol_buscar(abb,pesar_manzana(1)) == (void*) NULL, "No se encontro el 1");
  
    pa2m_afirmar(arbol_borrar(abb, c7) == EXITO, "Se pudo borrar el elemento 7");
    pa2m_afirmar(arbol_borrar(abb, c8) == EXITO, "Se pudo borrar el elemento 8");
   // pa2m_afirmar(((manzana_t*)(abb->nodo_raiz->derecha->elemento))->peso == 8, "EL elemento derecho de la raiz es el esperado");
   // pa2m_afirmar(((manzana_t*)(abb->nodo_raiz->derecha->elemento))->peso == 6, "EL elemento derecho de la raiz es el esperado");

    pa2m_afirmar(arbol_borrar(abb,c6) == EXITO, "Se pudo borrar el elemento 6");
    

  //  pa2m_afirmar(arbol_borrar(abb, pesar_manzana(5)) == EXITO, "Se pudo borrar el elemento 5");
    pa2m_afirmar(arbol_borrar(abb, c3) == EXITO, "Se pudo borrar el elemento 3");
   


   // pa2m_afirmar(arbol_vacio(abb) == true, "El arbol esta vacio");
    
    
    arbol_destruir(abb);
    free(auxiliar);
   /* 
    pa2m_afirmar(abb_elementos(abb) == 4, "El abb contiene 4 elementos");
    pa2m_afirmar(abb_elemento_en_posicion(abb, 2) != NULL, "Puedo obtener un elemento de una posicion especifica");
    pa2m_afirmar(abb_elemento_en_posicion(abb, 5) == NULL, "Obtengo NULL al acceder a una posicion inexistente");
    probar_si_elementos_son_los_esperados(abb, elementos);
    pa2m_afirmar(abb_borrar(abb) == EXITO, "Puedo borrar el ultimo elemento del abb");
    pa2m_afirmar(abb_borrar_de_posicion(abb, 0) == EXITO, "Puedo borrar el primer elemento del abb");
    pa2m_afirmar(abb_elementos(abb) == 2, "El abb contiene 2 elementos");
    pa2m_afirmar(abb_ultimo(abb) != NULL, "Puedo obtener el ultimo elemento del abb");    
    abb_destruir(abb);*/
    printf("\n");   
}

int main() {

    pa2m_nuevo_grupo("PRUEBAS DE ARBOL");
    pruebas_de_abb_con_4_elementos();

    pa2m_nuevo_grupo("PRUEBAS CON NULL");
    pruebas_con_null();
  /*  
    pa2m_nuevo_grupo("PRUEBAS DE ABB CON UN UNICO ELEMENTO");
    pruebas_de_abb_unitaro();

    pa2m_nuevo_grupo("PRUEBAS DE ABB VACIO");
    pruebas_de_abb_vacio();

    pa2m_nuevo_grupo("PRUEBAS DE INSERCION SIMPLE");
    abb_t* abb_simple = pruebas_de_insercion_simple();

    pa2m_nuevo_grupo("PRUEBAS DE ELIMINACION SIMPLE");
    pruebas_de_eliminacion_simple(abb_simple);
    
    pa2m_nuevo_grupo("PRUEBAS DE INSERCION Y ELIMINACION MULTIPLE");
    abb_t* abb_multiple = pruebas_de_insercion_multiple();

    pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO INORDEN");
    pruebas_de_inorden();

    pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO PREORDEN");
    pruebas_de_preorden();

    pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO POSTORDEN");
    pruebas_de_postorden();
    
    pa2m_nuevo_grupo("PRUEBAS DE ITERADOR"); 
    pruebas_de_iterador();
*/
    pa2m_mostrar_reporte();
    return EXITO;
}