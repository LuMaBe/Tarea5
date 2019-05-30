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

struct nodoQueue {
  avl_t avl;
  nodoQueue *sig;
};
// Declaración del tipo 'nodoQueue'

// Representación de `cola_avls_t'.
// Se debe definir en cola_avls.cpp
struct rep_cola_avls {
  nodoQueue *cabezal;
  nodoQueue *cola;
  nat cantidad;
};
// Declaración del tipo `cola_avls_t'
typedef struct rep_cola_avls *cola_avls_t;

/*  Devuelve una cola_avls_t vacía (sin elementos). */
cola_avls_t crear_cola_avls() {
  cola_avls_t c = new rep_cola_avls;
  c->cabezal = c->cola = NULL;
  c->cantidad = 0;
  return c;
};

/* Encola `avl' en `c'. */
void encolar(avl_t b, cola_avls_t &c) {
  nodoQueue *nuevo = new nodoQueue;
  nuevo->avl = b;
  if (c->cantidad == 0) {
    nuevo->sig = NULL;
    c->cabezal = nuevo;
    c->cola = nuevo;
  } else {
    c->cola->sig = nuevo;
    c->cola = nuevo;
  }
  c->cantidad++;
};

/*
  Remueve de `c' el elemento que está en el frente.
  NO libera la memoria del elemento removido.
  Si es_vacia_cola_avls(c) no hace nada.
 */
void desencolar(cola_avls_t &c) {
  if (c->cantidad != 0) {
    if (c->cantidad == 1) // Si la cola tiene un solo elemento, entonces cabezal==cola.
      c->cabezal = c->cola = NULL;
    else { // Si c->cantidad > 1, entonces el cabezal pasa a apuntar al siguiente elemento.
      c->cabezal = c->cabezal->sig;
    }
    c->cantidad--;
  }
};

/* Libera la memoria asignada a `c', pero NO la de sus elementos. */
void liberar_cola_avls(cola_avls_t &c) { delete(c); };

/* Devuelve `true' si y sólo si `c' es vacía (no tiene elementos). */
bool es_vacia_cola_avls(cola_avls_t c) { return (c->cantidad == 0); };

/*
  Devuelve el elemento que está en el frente de `c'.
  Precondición: ! es_vacia_cola_avls(c);
 */
avl_t frente(cola_avls_t c) {
  avl_t res = NULL;
  if (c->cabezal->avl != NULL)
    res =  c->cabezal->avl;
  return res;
};
