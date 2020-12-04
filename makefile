CC= gcc
WFLAGS= -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

all: compilar ejecutar_valgrind 

compilar: abb.c pruebas.c 
	$(CC) abb.c pruebas.c -o abb -g $(WFLAGS) 

ejecutar: compilar 
	./abb

ejecutar_valgrind: compilar
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb

compilar_mini: abb.c abb_minipruebas.c
	$(CC) -g abb.c abb_minipruebas.c  $(WFLAGS) -o abb_mini

ejecutar_mini: compilar_mini
	./abb_mini

ejecutar_mini_valgrind: compilar_mini
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb_mini