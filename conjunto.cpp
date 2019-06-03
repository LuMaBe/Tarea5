/* 5223744 - 4937759 */

/* DIRECTORIOS */
#include "../include/avl.h"
#include "../include/info.h"
#include "../include/iterador.h"
/* DIRECTORIOS */

/* BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* BIBLIOTECAS */

// Declaración del tipo `conjunto_t'
// struct rep_conjunto es la representación de `conjunto_t',
// definida en conjunto.cpp

struct rep_conjunto { // PNG
  avl_t arbol;
};

typedef struct rep_conjunto *conjunto_t;

/* Constructoras */

/*
  Devuelve un conjunto_t vacío (sin elementos).
  El tiempo de ejecución es O(1).
 */
conjunto_t crear_conjunto() {
  conjunto_t nuevo = new rep_conjunto;
  nuevo->arbol = NULL;
  return nuevo;
};

/*
  Devuelve un conjunto_t cuyo único elemento es `i'.
  El tiempo de ejecución es O(1).
 */
conjunto_t singleton(info_t i) {
  avl_t res = new rep_avl;
  res->dato = i;
  res->altura = 1;
  res->cantidad = 1;
  res->izq = NULL;
  res->der = NULL;
  conjunto_t c = crear_conjunto();
  c->arbol = res;
};

/*
  Devuelve un conjunto_t con los elementos que pertenecen a  `c1' o `c2'.
  Si en ambos conjuntos hay un elemento con el mismo dato  numérico en el
  conjunto_t devuelto se debe incluir el que pertenece a `c1'.
  El tiempo de ejecucion es O(n1 + n2 + n.log n), siendo `n1' y `n2' la
  cantidad de elementos de `c1' y `c2' respectivamente y `n' la del conjunto_t
  resultado.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
conjunto_t union_conjunto(conjunto_t c1, conjunto_t c2) {
  conjunto_t res = crear_conjunto();
  if (es_vacio_conjunto(c1) && es_vacio_conjunto(c2))
    return res;
  else {
    iterador_t iter1 = iterador_conjunto(c1);
    iterador_t iter2 = iterador_conjunto(c2);
    iter1->actual = iter1->inicio;
    iter2->actual = iter2->inicio,
    while ((iter1->actual != NULL) && (iter2->actual != NULL)) {
      insertar_en_avl(copia_info(iter1->actual->dato), res->arbol);
      if (numero_info(iter2->actual->dato) < numero_info(iter1->actual->dato)) {
        insertar_en_avl(copia_info(iter2->actual->dato), res->arbol);
        iter2->actual = iter2->actual->siguiente;
      } else if (numero_info(iter2->actual->dato) == numero_info(iter1->actual->dato))
        iter2->actual = iter2->actual->siguiente;
      iter1->actual = iter1->actual->siguiente;
    }
    if ((iter1->actual == NULL) && (iter2->actual != NULL))
      while (iter2->actual != NULL) {
        insertar_en_avl(copia_info(iter2->actual->dato), res->arbol);
        iter2->actual = iter2->actual->siguiente;
      }
    else if ((iter1->actual != NULL) && (iter2->actual == NULL))
      while (iter1->actual != NULL) {
        insertar_en_avl(copia_info(iter1->actual->dato), res->arbol);
        iter1->actual = iter2->actual->siguiente;
      }
  }
  return res;
};

/*
  Devuelve un conjunto_t con los elementos de `c1' cuyos datos numéricos no
  pertenecen a `c2'.
  El tiempo de ejecucion es O(n1 + n2 + n.log n), siendo `n1' y `n2' la
  cantidad de elementos de `c1' y `c2' respectivamente y `n' la del conjunto_t
  resultado.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
conjunto_t diferencia(conjunto_t c1, conjunto_t c2) {
  return 0;
};

/*
  Libera la memoria asignada a `c' y la de todos sus elementos.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos de `c'.
 */
void liberar_conjunto(conjunto_t &c) {};

/*
  Devuelve `true' si y sólo si `info' es un elemento de `c'.
  El tiempo de ejecución es O(log n), siendo `n' es la cantidad de
  elementos de `c'.
 */
bool pertenece_conjunto(info_t info, conjunto_t s) {
  return 0;
};

/*
  Devuelve `true' si y sólo `c' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool es_vacio_conjunto(conjunto_t c) {
  bool res = false;
  if (c->arbol == NULL)
    res = true;
  return res;
};

/*
  Devuelve un conjunto_t con los `n' elementos que están en en el rango
  [0 .. n - 1] del arreglo `infos'.
  Los elementos están ordenados de manera creciente estricto (creciente y sin
  repetidos) según los datos numércos.
  El tiempo de ejecución es O(n).
 */
conjunto_t arreglo_a_conjunto(info_t *infos, nat n) {
  return 0;
};

/* PNG
  Devuelve un iterador_t de los elementos de `c'.
  En la recorrida del iterador devuelto los datos numéricos aparecerán en orden
  creciente.
  El tiempo de ejecución es O(n), siendo `n' es la cantidad de elementos de `c'.
  El iterador_t resultado NO comparte memoria con `c'.
 */
iterador_t iterador_conjunto(conjunto_t c) {
  iterador_t res = crear_iterador();
  info_t *infos = en_orden_avl(c->arbol);
  for (nat i = 0; i < cantidad_en_avl(c->arbol); i++)
    agregar_a_iterador(infos[i], res);
  bloquear_iterador(res);
  delete[] infos;
  return res;
};
