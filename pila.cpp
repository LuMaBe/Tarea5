/* 5223744 - 4937759 */

/* Directorios */
#include "../include/info.h"
#include "../include/pila.h"
/* Directorios */

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
/* Bibliotecas */

// Representación de `pila_t'.
// Se debe definir en pila.cpp.

struct rep_nodoP {
  int dato;
  rep_nodoP *sig;
};

struct rep_pila {
  nat tope;
  nat cantidad;
  rep_nodoP *datoPila;
};

typedef struct rep_pila *pila_t;

/*
  Devuelve una pila_t vacía (sin elementos) que puede tener hasta `tamanio'
  elementos.
 */
pila_t crear_pila(int tamanio) {
  pila_t p = new rep_pila;
  p->tope = tamanio;
  p->cantidad = 0;
  p->datoPila = NULL;
  return p;
};

/*
  Apila `num' en `p'.
  Si es_llena_pila(p) no hace nada.
 */
void apilar(int num, pila_t &p) {
  if (!es_llena_pila(p)) {
    rep_nodoP *nodo = new rep_nodoP;
    nodo->dato = num;
    if (es_vacia_pila(p)) {
      p->datoPila = nodo;
      nodo->sig = NULL;
    } else {
      nodo->sig = p->datoPila;
      p->datoPila = nodo;
    }
    p->cantidad++;
  }
};

/*
  Remueve de `p' el elemento que está en la cima.
  Si es_vacia_pila(p) no hace nada.
 */
void desapilar(pila_t &p) {
  if (!es_vacia_pila(p)) {
    rep_nodoP *aux = p->datoPila;
    p->datoPila = p->datoPila->sig;
    delete(aux);
    p->cantidad--;
  }
};

/* Libera la memoria asignada a `p'. */
void liberar_pila(pila_t &p) { delete(p); };

/* Devuelve `true' si y sólo si `p' es vacía (no tiene elementos). */
bool es_vacia_pila(pila_t p) { return (p->cantidad == 0); };

/*
  Devuelve `true' si y sólo si la cantidad de elementos en `p' es `tamanio'
  (siendo `tamanio' el valor del parámetro con que fue creada `p').
 */
bool es_llena_pila(pila_t p) { return (p->cantidad == p->tope); };

/*
  Devuelve el elemento que está en la cima de `p'.
  Precondición: ! es_vacia_pila(p);
 */
int cima(pila_t p) {
  int res = p->datoPila->dato;
  return res;
};
