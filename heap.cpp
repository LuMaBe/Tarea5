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
  nat *PosValor;
  nat capacidad;
  nat cant;
  nat maxValor;
};
// Declaración del tipo `heap_t'
typedef rep_heap *heap_t;

/* FUNCIONES AUXILIARES */

static void filtrado_ascendente_rec(heap_t h, nat pos) {
  if ((pos > 1) && (numero_info(h->infos[pos/2]) > numero_info(h->infos[pos]))) {
    info_t swap = copia_info(h->infos[pos]);
    liberar_info(h->infos[pos]);
    h->infos[pos] = h->infos[pos/2];
    h->PosValor[numero_info(h->infos[pos])] = pos;
    h->infos[pos/2] = swap;
    h->PosValor[numero_info(h->infos[pos/2])] = (pos/2);
    filtrado_ascendente_rec(h, (pos/2));
  }
};

static void filtrado_descendente(heap_t &h, nat pos) {
  while( (pos != 1) && (numero_info(h->infos[pos]) < numero_info(h->infos[pos/2])) ) {
    info_t copinf = copia_info(h->infos[pos/2]);
    liberar_info(h->infos[pos/2]);
    info_t copinf2 = copia_info(h->infos[pos]);
    h->infos[pos/2] = copinf2;
    liberar_info(h->infos[pos]);
    h->infos[pos] = copinf;
    h->PosValor[numero_info(h->infos[pos/2])] = pos/2;
    h->PosValor[numero_info(h->infos[pos])] = pos;
    pos = pos/2;
  }
};

static void filtrado_descendente_menor(heap_t &h) {
    bool salir = false;
    info_t swap = h->infos[h->cant];
    nat hijo = 2;
    nat lugar = 1;
    while ( (!salir) && ((hijo <= h->cant) && ((hijo +1) <= h->cant)) ) {
      if( (numero_info(swap) < numero_info(h->infos[hijo])) && (numero_info(swap) <  numero_info(h->infos[hijo + 1]))) {
          info_t inf = swap;
          h->infos[lugar] = inf;
          h->PosValor[numero_info(swap)] = lugar;
          salir = true;
      } else {
          if( (numero_info(h->infos[hijo])) < (numero_info(h->infos[hijo + 1])) ) {
              h->infos[lugar] = h->infos[hijo];
              h->PosValor[numero_info(h->infos[lugar])] = lugar;
              lugar = hijo;
              hijo = lugar * 2;
          } else {
              h->infos[lugar] = h->infos[hijo + 1];
              h->PosValor[numero_info(h->infos[lugar])] = lugar;
              lugar = hijo + 1;
              hijo = lugar * 2;
          }
      }
  }
  if( (!salir) && (hijo >= h->cant) && (lugar <= h->maxValor) ) {
      info_t inf = swap;
      h->infos[lugar] = inf;
      h->PosValor[numero_info(swap)] = lugar;
  } else if((!salir) && (hijo >= h->cant)) {
    info_t inf = swap;
    h->infos[lugar/2] = inf;
    h->PosValor[numero_info(swap)] = lugar/2;
    liberar_info(swap);
  }
};

/* FUNCIONES AUXILIARES */
/*
  Devuelve un `heap' que puede contener hasta `tamanio' elementos.
  Los datos numéricos pueden estar en el rango 0 .. max_valor.
 */
heap_t crear_heap(nat tamanio, nat max_valor) {
  heap_t h = new rep_heap;
  h->infos = new info_t[tamanio + 1];
  h->PosValor = new nat[max_valor + 1];
  h->capacidad = tamanio;
  h->cant = 0;
  h->maxValor = max_valor;
  for(nat i=0; i <= (max_valor); i++)
    h->PosValor[i] = 0;
  return h;
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
 void reducir(nat v, heap_t &h) {
    nat pos = h->PosValor[v];
    int vReducido = v/2;
    char *Frase = new char[strlen(frase_info(h->infos[pos])) + 1];
    strcpy(Frase, frase_info(h->infos[pos]));
    liberar_info(h->infos[pos]);
    info_t info = crear_info(vReducido, Frase);
    h->infos[pos] = info;
    h->PosValor[v] = 0;
    if(h->cant > 1)
      filtrado_descendente(h, pos);
 };

/*
  Elimina de 'h' el elemento de menor valor y libera la memoria que tiene
  asignada.
  Precondición: ! es_vacia_heap(h).
  El tiempo de ejecución es O(log tamanio).
 */
void eliminar_menor(heap_t &h) {
  if (h->cant > 1) {
    h->PosValor[numero_info(h->infos[1])] = 0;
    liberar_info(h->infos[1]);
    filtrado_descendente_menor(h);
  } else {
    h->PosValor[numero_info(h->infos[1])] = 0;
    liberar_info(h->infos[1]);
  }
  h->cant--;
};

/*  Libera la menoria asignada a `h' y a sus elementos. */
void liberar_heap(heap_t &h) {
  while (h->cant > 0) {
    nat cant = h->cant;
    liberar_info(h->infos[cant]);
    h->cant--;
  }
  delete [] h->infos;
  delete [] h->PosValor;
  delete(h);
};

/*
  Devuelve `true' si y sólo si en `h' no hay elementos.
  El tiempo de ejecución es O(1).
 */
bool es_vacio_heap(heap_t h) {
  return (h->cant == 0);
  // Si la cantidad del heap es cero, entonces no tiene elementos y por lo tanto es vacío.
};

/*
  Devuelve `true' si y sólo si en `h' hay `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool es_lleno_heap(heap_t h) {
  return (h->cant == h->capacidad);
  // Si la cantidad de elementos en el heap == la capacidad del heap, entonces está lleno.
};

/*
  Devuelve `true' si y sólo si en 'h' hay un elemento con valor `v'.
  El tiempo de ejecución es O(1).
 */
bool hay_valor(nat v, heap_t h) {
  bool res = false;
  if (v <= h->maxValor) {
    // Si v está dentro del rango 0..maxValor.
    if (h->PosValor[v] != 0)
      res = true;
  }
  return res;
};

/*
  Devuelve el elemento de 'h' con menor valor.
  Precondición: ! es_vacio_h(h).
  El tiempo de ejecución es O(1).
 */
info_t menor(heap_t h) {
  return (h->infos[1]);
  // El elemento de 'h' con menor valor, se encuentra SIEMPRE en la posicion [1] del arreglo.
};

/*
  Devuelve el máximo valor del rango para los datos numericos, establecido en
  crear_h.
 */
nat max_valor(heap_t h) {
  return (h->maxValor);
  // Devuelvo el campo en el que guardo el maxValor del heap.
};
