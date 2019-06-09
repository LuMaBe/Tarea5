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
struct rep_heap;
// Declaración del tipo `heap_t_t'
typedef rep_heap *heap_t;

/*
  Devuelve un `heap' que puede contener hasta `tamanio' elementos.
  Los datos numéricos pueden estar en el rango 0 .. max_valor.
 */
heap_t crear_heap(nat tamanio, nat max_valor);

/*
  Si inserta el elemento `i'.
  Precondición: !es_lleno_heap(h) y !hay_valor(v,h) y v <= max_valor(h),
  donde v = numero_info(i).
  El tiempo de ejecución es O(log tamanio).
 */
void insertar_en_heap(info_t i, heap_t &h);

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
void eliminar_menor(heap_t &h);

/*  Libera la menoria asignada a `h' y a sus elementos. */
void liberar_heap(heap_t &h);

/*
  Devuelve `true' si y sólo si en `h' no hay elementos.
  El tiempo de ejecución es O(1).
 */
bool es_vacio_heap(heap_t h);

/*
  Devuelve `true' si y sólo si en `h' hay `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool es_lleno_heap(heap_t h);

/*
  Devuelve `true' si y sólo si en 'h' hay un elemento con valor `v'.
  El tiempo de ejecución es O(1).
 */
bool hay_valor(nat v, heap_t h);

/*
  Devuelve el elemento de 'h' con menor valor.
  Precondición: ! es_vacio_h(h).
  El tiempo de ejecución es O(1).
 */
info_t menor(heap_t h);

/*
  Devuelve el máximo valor del rango para los datos numericos, establecido en
  crear_h.
 */
nat max_valor(heap_t h);
