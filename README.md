# tda_abb
TDA ABB - Algoritmos y Programacion II

- Introduccion:
Este programa fue realizado para fortalecer los conocimientos sobre el TDA Arbol Binario de Busqueda (ABB) e Iteradores Internos. Para ello se tuvo que llevar a cabo la cracion de un ABB, respetando sus caracteristicas de funcionamiento.

- Funcionamiento:
Para la implementacion del TDA ABB se debieron crear las siguientes funciones
como operaciones principales de un ABB: crear, destruir, insertar, eliminar, 
buscar y recorrer. 

- Compilacion:
El programa debe ser compilado mediante gcc con la siguiente linea de compilacion:

gcc *.c -o abb -g -std=c99 -Wall -Wconversion -Wtype -limits -pedantic -Werror -O0

O tambien se puede realizar utilizando el makefile con la siguiente linea:

   make compilar
   
- Ejecucion:
Una vez compilado se debe ejecutar con la siguiente linea de ejecuccion:

   ./abb
   
O tambien se puede realizar utilizando el makefile con la siguiente linea:

   make ejecutar
   
   
Conceptos a saber:

   1. Diferencia entre Arbol Binario y ABB:
      Un Arbol Binario es un tipo de arbol relacionado con las operaciones de busqueda.
      Este puede estar vacio o tener como nodo principal un nodo raiz que a su vez tiene
      dos subarboles, uno a su izquierda y otro a su derecha, conocidos como "hijos". El
      Arbol Binario de Busqueda (ABB) es un arbol binario que a su vez tiene la capacidad
      de saber que si se accede al subarbol derecho, se esta acciediendo a un subarbol con
      nodos que contienen claves mayores, y si se accede al izquierdo, este contiene las 
      claves menores. Esto facilita muchisimo a la hora de la busqueda en comparacion al
      Arbol Binario. Gracias a su estructura, el ABB tiene las ventajas de las listas 
      enlazadas y a su vez puede obtener la velocidad de la busqueda binaria. Por ello,
      el ABB es de mayor utilidad que el Arbol Binario.

   2. Funcion de Destruccion:
      El objetivo de tener una funcion de destruccion en el TDA es para poder liberar la memoria 
      reservada para insertar los elementos al ABB. El hecho de que el usuario contenga dicha
      funcion a su disposicion es de suma utilidad para asi poder liberar la memoria de
      ciertos elementos, por ejemplo el uso de elementos auxiliares.

   3. Complejidad de las diferentes opercaiones del ABB:
      Las operaciones de un ABB son: Busqueda, Insercion y Borrado, y tienen como complejidad
      O(log(n)) en el mejor de los casos, que es cuando el arbol se encuentra relativamente
      equilibrado y permite realizar la busqueda de la forma de busqueda binaria. En este caso
      la cantidad de comparaciones que se deberan realizar son el numero de niveles que tenga
      dicho arbol. Por otro lado, en el peor de los casos, las operaciones tienen complejidad
      O(n), donde n es la altura del arbol. Esto es en los casos que se debe recorrer todo el
      arbol, siendo similar a una busqueda de lista enlazada normal.
