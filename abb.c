#include "abb.h"
#include <stdio.h>

#define EXITO 0
#define ERROR -1

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

/*
 * Procedimiento recursivo 
 */
void arbol_eliminar_elementos_recursivamente(abb_t* arbol, nodo_abb_t* nodo_hijo) { //recorrido postorden
    if (!nodo_hijo) return;
    if (nodo_hijo->izquierda) {
        arbol_eliminar_elementos_recursivamente(arbol, nodo_hijo->izquierda);
    }
    if (nodo_hijo->derecha) {
        arbol_eliminar_elementos_recursivamente(arbol, nodo_hijo->derecha);
        
    }
    
    arbol->destructor(nodo_hijo->elemento);
    free(nodo_hijo);
    //return nodo_hijo;
}


void arbol_destruir(abb_t* arbol) {
    if (arbol && (!arbol_vacio(arbol))) {
        arbol_eliminar_elementos_recursivamente(arbol, arbol->nodo_raiz);
    }
    
    free(arbol);
}

/*
 * Funcion recursiva
 * 
*/
nodo_abb_t* encontrar_elemento(abb_comparador comparador, nodo_abb_t* nodo_raiz, void* elemento, int accion, nodo_abb_t* nodo_anterior) {
    if (!nodo_raiz) return NULL;
    int comparacion = comparador(nodo_raiz->elemento, elemento);
    //nodo_anterior = nodo_raiz;
    if ((comparacion == IGUAL) && ((accion == BUSCAR) || (accion == ELIMINAR))) {
        printf("\nELEMENTO ES IGUAL\n");
        nodo_raiz = nodo_raiz;      
    }
    else if (((comparacion == MAYOR)) && (nodo_raiz->derecha)) {
        printf("\nENTRO A MAYOR\n");
        nodo_anterior = nodo_raiz;
        nodo_raiz = encontrar_elemento(comparador,nodo_raiz->derecha, elemento, accion, nodo_anterior);
    }
    else if ((comparacion == MENOR) && (nodo_raiz->izquierda)) {
        printf("\nENTRO A MENOR\n");
        nodo_anterior = nodo_raiz;
        nodo_raiz = encontrar_elemento(comparador,nodo_raiz->izquierda, elemento, accion, nodo_anterior);
    }
    
    if (accion == ELIMINAR && comparacion == IGUAL) {
        printf("\nELEMENTO NODO ANTERIOR: %d\n", *(int*)(nodo_anterior->elemento));
        return nodo_anterior;
    }
     
    return nodo_raiz;
}

void* arbol_buscar(abb_t* arbol, void* elemento) {
    if (!arbol || !elemento || arbol_vacio(arbol) || !arbol->comparador) return NULL;
    nodo_abb_t* encontrado = NULL;
    printf("\nELEMENTO DE RAIZ: %d\n", *(int*)arbol->nodo_raiz->elemento); 
  //  printf("\nELEMENTO DE RAIZ: %d\n", *(int*)arbol->nodo_raiz->izquierda->elemento);   
   // printf("\nELEMENTO DE RAIZ: %d\n", *(int*)arbol->nodo_raiz->derecha->elemento);   

    printf("\nELEMENTO A BUSCAR: %d\n", *(int*)elemento);
    encontrado = encontrar_elemento(arbol->comparador, arbol->nodo_raiz, elemento, BUSCAR, encontrado);
    printf("\nELEMENTO ENCONTRADO: %d\n", *(int*)(encontrado->elemento));
    int comparacion = arbol->comparador(elemento, encontrado->elemento);
    if (comparacion != IGUAL) return NULL;
  /*  
    if (encontrado) {
        printf("\nENTRO A encontrado\n");
        //printf("\nCOMPARACION: %d\n", comparacion);
    }*/
        
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

/*
nodo_abb_t* elemento_menor(nodo_abb_t* hijo_menor) {
    if (hijo_menor->izquierda) {
        hijo_menor = hijo_menor->izquierda;
        hijo_menor = elemento_mas_proximo(hijo_menor);
    }    
    return hijo_menor;
}*/

/*
 * Procedimiento 
*/
/*
void nodo_con_dos_hijos(abb_t* arbol, nodo_abb_t* nodo_a_borrar, nodos_t* nuevo_arbol, int es_la_raiz) {
    nuevo_arbol->hijo_izquierdo = nodo_a_borrar->izquierda;
    nuevo_arbol->hijo_derecho = nodo_a_borrar->derecha;
    nodo_abb_t* nodo_anterior = arbol->nodo_raiz;
    nuevo_arbol->nuevo_padre = elemento_mas_aproximado_al_elemento_a_borrar(nodo_a_borrar->izquierda, nodo_anterior);
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
}*/

nodo_abb_t* nodo_con_dos_hijos(abb_t* arbol, nodo_abb_t* nodo_padre, nodo_abb_t* nodo_a_borrar, nodo_abb_t* sucesor) {
    nodo_abb_t* hijo_mayor = NULL;
    nodo_abb_t* padre_del_sucesor = nodo_padre;
    sucesor = elemento_sucesor_inorden(nodo_a_borrar->derecha, padre_del_sucesor);
    bool hijo_es_sucesor = !(arbol->comparador(nodo_a_borrar->derecha->elemento, sucesor->elemento));
        printf("\nNodo sucesor elemento:%d", *(int*)sucesor->elemento);
        
        printf("\nNodo a borrar elemento:%d", *(int*)nodo_a_borrar->elemento);
        printf("\nNODO hijo derecho:%d", *(int*)nodo_a_borrar->derecha->elemento);

        
        printf("\nHIJO ES SUCESOR:%d", hijo_es_sucesor);

    if (!hijo_es_sucesor) {
        printf("\nNODO PADRE DEL SUCESOR:%d", *(int*)padre_del_sucesor->elemento);
        padre_del_sucesor = encontrar_elemento(arbol->comparador, arbol->nodo_raiz, sucesor->elemento, ELIMINAR, arbol->nodo_raiz);
        printf("\nNODO PADRE DEL SUCESOR:%d", *(int*)padre_del_sucesor->elemento);
        padre_del_sucesor->izquierda = NULL;
        if(!sucesor->derecha)
            sucesor->derecha = nodo_a_borrar->derecha;
        else if (sucesor->derecha) {
            hijo_mayor = buscar_hijo_mayor(sucesor->derecha, padre_del_sucesor);
            printf("\nHIJO MAYORRRRR:%d", *(int*)hijo_mayor->elemento);
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
        printf("\ncompariacon %d \n", comparacion);  
    
    if (comparacion == MAYOR)  // el nodo a borrar es mayor que su padre
        nodo_padre->derecha = sucesor_a_nodo_borrar;
    else if (comparacion == MENOR) // el nodo a borrar es menor que su padre
        nodo_padre->izquierda = sucesor_a_nodo_borrar;
    if (es_la_raiz) {
        printf("\nENtro a Es raiz \n");  
        arbol->nodo_raiz = sucesor_a_nodo_borrar;

    //printf("\nElemento sucesor: %d\n", *(int*)sucesor_a_nodo_borrar->elemento);
   // printf("\nElemento sucesor iz: %d\n", *(int*)sucesor_a_nodo_borrar->izquierda->elemento);
   // printf("\nElemento sucesor der: %d\n", *(int*)sucesor_a_nodo_borrar->derecha->elemento);
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
        printf("\nhijo derecho que no existeeeeeeeeee: %d \n", *(int*)nodo_a_borrar->derecha);  

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
    nodo_a_borrar = encontrar_elemento(arbol->comparador, nodo_padre, elemento, BUSCAR, nodo_padre);
    printf("\nnodo a BOttarrr: %d\n", *(int*)nodo_a_borrar->elemento);
    printf("\nRAIZ: %d\n", *(int*)arbol->nodo_raiz->elemento);
    
    if (!nodo_a_borrar) return ERROR;  //el elemento no se encuentra en el arbol
    int hijos = nodo_tiene_hijos(nodo_a_borrar);
    printf("\ncantidad de hijos: %d\n", hijos);
    nodo_padre = encontrar_elemento(arbol->comparador, nodo_padre, elemento, ELIMINAR, nodo_padre);
    printf("\nnodo padre del borrar: %d\n", *(int*)nodo_padre->elemento);
    
    bool es_la_raiz = !(arbol->comparador(arbol->nodo_raiz->elemento, elemento));
    int comparacion = arbol->comparador(nodo_padre->elemento, elemento);

    printf("\n%d ES LA RAIZ: %d\n", *(int*)elemento,es_la_raiz);
    borrar_segun_hijos(arbol, nodo_padre, nodo_a_borrar, hijos, es_la_raiz, comparacion);
    //printf("\ncantidad de hijos: %d\n", nodo_tiene_hijos(arbol->nodo_raiz));
    
    //printf(" \nhijo derecho: %d\n", *(int*)nodo_a_borrar->izquierda->elemento);
    //printf("\nELEMENTO DE RAIZ: %d\n", *(int*)arbol->nodo_raiz->elemento); 
    //printf("\nELEMENTO izq DE RAIZ: %d\n", *(int*)arbol->nodo_raiz->izquierda->elemento);   
    //printf("\nELEMENTO der DE RAIZ: %d\n", *(int*)arbol->nodo_raiz->derecha->elemento); 

    return EXITO;
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
        printf("\nELEMENTO ultimo nodo(?): %d\n", *(int*)nodo->elemento);  
        if (nodo) { //no tiene hijos
            int comparacion = arbol->comparador(nodo->elemento, elemento);
            printf("\ncomparacion: %d\n", comparacion);  
            if (comparacion == MAYOR || comparacion == IGUAL){
                insertado = insertar_elemento(&nodo->derecha, elemento);
                printf("\nELEMENTO der DE RAIZ: %d\n", *(int*)arbol->nodo_raiz->derecha->elemento);  

            }
            else if (comparacion == MENOR)  {
                insertado = insertar_elemento(&nodo->izquierda, elemento);
                printf("\nELEMENTO izq DE RAIZ: %d\n", *(int*)arbol->nodo_raiz->izquierda->elemento);  
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