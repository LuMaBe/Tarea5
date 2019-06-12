/* 5223744 - 4937759 */

 /* BIBLIOTECAS */
#include "../include/hash.h"
#include "../include/heap.h"
#include "../include/info.h"
#include "../include/avl.h"
#include "../include/cola_avls.h"
#include "../include/pila.h"
#include "../include/conjunto.h"
/* BIBLIOTECAS */

/* LIBRERIAS */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* LIBRERIAS */

// Representación de `heap_t'
// Se debe definir en heap.cpp
struct rep_heap {
  info_t *infos;
  int *PosValor;
  nat capacidad;
  nat cant;
  nat maxValor;
};
// Declaración del tipo `heap_t'
typedef rep_heap *heap_t;

/* FUNCIONES AUXILIARES */

static void filtrado_ascendente_rec(heap_t h, nat pos) {
  if ((pos > 1) && (h->elems[pos/2] > h->elems[pos])) {
    info_t swap = h->elems[pos];
    h->elems[pos] = h->elems[pos/2];
    h->PosValor[numero_info(h->elems[pos])] = pos;
    h->elems[pos/2] = swap;
    h->PosValor[numero_info(h->elems[pos/2])];
    filtrado_ascendente_rec(h, (pos/2));
  }
};

static void filtrado_descendente(int *arreglo, int n, nat pos) {
  bool salir = false;
  int swap = arreglo[pos];
  while ((!salir) && (2*pos <= n)) {
    int hijo = 2*pos;
    if ((hijo + 1 <= n) && (arreglo[hijo + 1] < arreglo[hijo]))
      hijo = hijo + 1;
    if (arreglo[hijo] < swap) {
      arreglo[pos] = arreglo[hijo];
      pos = hijo;
    } else
      salir = true;
  }
  arreglo[pos] = swap;
};

/* FUNCIONES AUXILIARES */
/*
  Devuelve un `heap' que puede contener hasta `tamanio' elementos.
  Los datos numéricos pueden estar en el rango 0 .. max_valor.
 */
heap_t crear_heap(nat tamanio, nat max_valor) {
  heap_t h = new rep_heap;
  h->infos = new info_t[tamanio];
  h->PosValor = new int[max_valor + 1];
  h->capacidad = tamanio;
  h->cant = 0;
  h->maxValor = max_valor;
};

/*
  Si inserta el elemento `i'.
  Precondición: !es_lleno_heap(h) y !hay_valor(v,h) y v <= max_valor(h),
  donde v = numero_info(i).
  El tiempo de ejecución es O(log tamanio).
 */
void insertar_en_heap(info_t i, heap_t &h) {
  h->cant++;
  h->infos[h->cant] = i;
  h->PosValor[numero_info(i)] = h->cant;
  filtrado_ascendente_rec(h, h->cant);
};

/*
  Reduce a v/2 el valor del elemento cuyo valor actual es `v'.
  Precondición: hay_valor(v, h) y !hay_valor(v/2, h).
  No debe quedar memoria inaccesible.
  El tiempo de ejecución es O(log tamanio).
 */
void reducir(nat v, heap_t &h);

/*
  Elimina de 'h' el elemento de menor valor y libera la memoria que tiene
  asignada.
  Precondición: ! es_vacia_heap(h).
  El tiempo de ejecución es O(log tamanio).
 */
void eliminar_menor(heap_t &h) {
  h->cant--;
  h->PosValor[numero_info(h->infos[0])] = 0;
  liberar_info(h->infos[0]);
  filtrado_descendente(h->infos, h->cant, h->cant);
};

/*  Libera la menoria asignada a `h' y a sus elementos. */
void liberar_heap(heap_t &h) {
  delete [] infos;
  delete [] PosValor;
  delete(h);
};

/*
  Devuelve `true' si y sólo si en `h' no hay elementos.
  El tiempo de ejecución es O(1).
 */
bool es_vacio_heap(heap_t h) {
  bool res = false;
  if (h->cant == 0)
    res = true;
  return res;
};

/*
  Devuelve `true' si y sólo si en `h' hay `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool es_lleno_heap(heap_t h) {
  bool res = false;
  if (h->cant == h->capacidad)
    res = true;
  return res;
};

/*
  Devuelve `true' si y sólo si en 'h' hay un elemento con valor `v'.
  El tiempo de ejecución es O(1).
 */
bool hay_valor(nat v, heap_t h) {
  bool res = false;
  if (h->PosValor[v] == 1)
    res = true;
}

/*
  Devuelve el elemento de 'h' con menor valor.
  Precondición: ! es_vacio_h(h).
  El tiempo de ejecución es O(1).
 */
info_t menor(heap_t h) {
  return (h->infos[0]);
};

/*
  Devuelve el máximo valor del rango para los datos numericos, establecido en
  crear_h.
 */
nat max_valor(heap_t h) {
  return (h->maxValor);
};
