/* 5223744 - 4937759 */

 /* BIBLIOTECAS */
#include "../include/info.h"
#include "../include/avl.h"
#include "../include/cola_avls.h"
#include "../include/pila.h"
#include "../include/conjunto.h"
/* BIBLIOTECAS */

/* LIBRERIAS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* LIBRERIAS */

// Declaración del tipo `conjunto_t'
// struct rep_conjunto es la representación de `conjunto_t',
// definida en conjunto.cpp

struct nodo {
  info_t dato;
  nodo *sig;
};

struct rep_iterador {
  nodo *inicio, *fin, *actual;
  bool bloqueado;
};

struct rep_avl {
  info_t dato;
	nat altura;
  nat cantidad;
  avl_t izq, der;
};

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
  conjunto_t c = new rep_conjunto;
  c->arbol = NULL;
  return c;
};

/*
  Devuelve un conjunto_t cuyo único elemento es `i'.
  El tiempo de ejecución es O(1).
 */
conjunto_t singleton(info_t i) {
  rep_avl *res = new rep_avl;
  res->dato = i;
  res->altura = 1;
  res->cantidad = 1;
  res->izq = NULL;
  res->der = NULL;
  // Le asigno al avl 'res' todos los datos.
  conjunto_t c = new rep_conjunto;
  c->arbol = res;
  // Por último agrego 'res' al conjunto.
  return c;
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
    res = NULL;
  else {
    iterador_t iter1 = iterador_conjunto(c1);
    iterador_t iter2 = iterador_conjunto(c2);
    // iter1 e iter2 NO comparten memoria con c1 y c2 respectivamente.. LIBERAR MEMORIA AL FINAL!!
    if ((iter1->inicio != NULL) && (iter2->inicio != NULL)) {
      iter1->actual = iter1->inicio;
      iter2->actual = iter2->inicio;
      while (esta_definida_actual(iter1) && esta_definida_actual(iter2)) {
        insertar_en_avl(copia_info(actual_en_iterador(iter1)), res->arbol);
        // Inserto el dato haciendo una copia_info en res->arbol, para
        // después cuando libere los iteradores no se me pierda la memoria.
        while (esta_definida_actual(iter2) && (numero_info(actual_en_iterador(iter2)) < numero_info(actual_en_iterador(iter1)))) {
          insertar_en_avl(copia_info(actual_en_iterador(iter2)), res->arbol);
          avanzar_iterador(iter2);
        }
        if (esta_definida_actual(iter2) && (numero_info(actual_en_iterador(iter2)) == numero_info(actual_en_iterador(iter1))))
          avanzar_iterador(iter2);
        avanzar_iterador(iter1);
      }
    }
    while (esta_definida_actual(iter1)) {
      insertar_en_avl(copia_info(actual_en_iterador(iter1)), res->arbol);
      avanzar_iterador(iter1);
    }
    while (esta_definida_actual(iter2)) {
      insertar_en_avl(copia_info(actual_en_iterador(iter2)), res->arbol);
      avanzar_iterador(iter2);
    }
    liberar_iterador(iter1);
    liberar_iterador(iter2);
    // Libero la memoria de ambos iteradores para que no haya perdida de memoria.
  }
  return res;
  // Si c1 y c2 eran vacíos no entra al if y directamente devuelve un conjunto vacío, sino
  // me devuelve el conjunto esperado.
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
  conjunto_t res = crear_conjunto();
  if (es_vacio_conjunto(c1))
    res = NULL;
  else {
    iterador_t iter1 = iterador_conjunto(c1);
    iterador_t iter2 = iterador_conjunto(c2);
    // iter1 e iter2 NO comparten memoria con c1 y c2 respectivamente.. LIBERAR MEMORIA AL FINAL!!
    iter1->actual = iter1->inicio;
    if (iter2->inicio != NULL) {
      iter2->actual = iter2->inicio;
      // Si 'c2' no es vacío, entonces 'iter2' tampoco y entonces me interesa buscar cuales elementos de 'c1' NO
    // pertenecen a 'c2' y por eso es necesario que entre a este 'while' de abajo.
      while (esta_definida_actual(iter1) && esta_definida_actual(iter2)) {
        if (numero_info(actual_en_iterador(iter2)) > numero_info(actual_en_iterador(iter1))) {
        // Si el número actual en 'iter2' es > al actual en 'iter1', entonces sé que el elemento no va a
      // estar en 'c2', sería IMPOSIBLE. Por lo tanto, lo inserto y avanzo al siguiente en 'iter1'.
          insertar_en_avl(copia_info(actual_en_iterador(iter1)), res->arbol);
          avanzar_iterador(iter1);
        } else if (numero_info(actual_en_iterador(iter2)) == numero_info(actual_en_iterador(iter1))) {
        // Si sus números son iguales avanzo en ambos iteradores.
          avanzar_iterador(iter1);
          avanzar_iterador(iter2);
        } else if (numero_info(actual_en_iterador(iter2)) < numero_info(actual_en_iterador(iter1)))
          avanzar_iterador(iter2);
      } // 'while'.
      while (esta_definida_actual(iter1)) {
        insertar_en_avl(copia_info(actual_en_iterador(iter1)), res->arbol);
        avanzar_iterador(iter1);
      }
    }
    liberar_iterador(iter1);
    liberar_iterador(iter2);
    // Libero la memoria de ambos iteradores para que no haya perdida de memoria.
  }
  return res;
  // Si c1 y c2 eran vacíos no entra al if y directamente devuelve un conjunto vacío, sino
  // me devuelve el conjunto esperado.
};

/*
  Libera la memoria asignada a `c' y la de todos sus elementos.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos de `c'.
 */
void liberar_conjunto(conjunto_t &c) {
  liberar_avl(c->arbol);
  delete(c);
};

/*
  Devuelve `true' si y sólo si `info' es un elemento de `c'.
  El tiempo de ejecución es O(log n), siendo `n' es la cantidad de
  elementos de `c'.
 */
bool pertenece_conjunto(info_t info, conjunto_t s) {
  avl_t avl = buscar_en_avl(numero_info(info), s->arbol);
  bool res;
  if (!es_vacio_avl(avl)) {
    if (son_iguales(raiz_avl(avl), info))
      res = true;
    else
      res = false;
  } else
    res = false;
  return res;
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
  if (n != 0) {
    conjunto_t res = new rep_conjunto;
    avl_t avl = arreglo_a_avl(infos, n);
    // Creo un conjunto 'c' y devuelvo a 'res' con el avl que formé a partir del arreglo '*infos'.
    res->arbol = avl;
    // Por último, simplemente le "paso" al conjunto 'c' el avl 'res' que obtuve.
    return res;
  } else
    return NULL;
};

/*
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
