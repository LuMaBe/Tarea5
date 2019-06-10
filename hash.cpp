/* 5223744 - 4937759 */

 /* BIBLIOTECAS */
#include "../include/cadena.h"
#include "../include/hash.h"
#include "../include/heap.h"
#include "../include/info.h"
#include "../include/avl.h"
#include "../include/cola_avls.h"
#include "../include/pila.h"
#include "../include/conjunto.h"
/* BIBLIOTECAS */

/* LIBRERIAS */
#include <cstdlib>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* LIBRERIAS */

// Representación de `hash_t'.
// Se debe definir en hash.cpp.
struct rep_hash {
  nat capacidad;
  cadena_t *hash[Capacidad];
  nat cantAsociaciones;
};
// Declaración del tipo `hash_t'.
typedef rep_hash *hash_t;

/*
 Crea un hash_t de asociaciones numero->texto.
 Podrá haber hasta `tamanio' asociaciones.
 */
hash_t crear_hash(nat tamanio) {
  rep_hash h = new hash_t;
  h.capacidad = tamanio - 1;
  rep_cadena *h.hash = new cadena_t;
  h.cantAsociaciones = 0;
  for(i=0; i<=(tamanio - 1); i++)
    h[i] = NULL;
  return h;
};

/*
  Inserta en `h' la asociación entre `clave' y `valor'.
  Precondición: !esta_lleno_hash(t) y !existe_asociacion(clave, h).
  El tiempo de ejecución es O(1).
 */
void asociar_en_hash(int clave, char *valor, hash_t &h) {
  nat pos = (abs(clave)%(h.capacidad)); // Posición en la que voy a almacenar la asociación.
  info_t info = crear_info(clave, valor);
  if (h[pos] == NULL) {
    h[pos] = crear_cadena();
    h[pos] = insertar_al_final(info, h[pos]);
  } else
    h[pos] = insertar_al_final(info, h[pos]);
};

/*
  Sustituye en `h' el anterior valor asociado a `clave' por `valor'.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1).
 */
void actualizar_hash(int clave, char *valor, hash_t &h) {
  eliminar_de_hash(clave, h);
  asociar_en_hash(clave, valor, h);
};

/*
  Elimina de `h' la asociación entre `clave' y algún valor y libera la menoria
  asignada a mantener esa asociación.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
void eliminar_de_hash(int clave, hash_t &h) {
  nat pos = (abs(clave) % h.capacidad);
  localizador_t loc = siguiente_clave(clave, inicio_cadena(h[pos], h[pos]));
  h[pos] = remover_de_cadena(loc, h[pos]);
};

/*
  Libera la memoria asignada a `h' y todos sus elementos.
 */
void liberar_hash(hash_t &h) {
  if (h.cantAsociaciones != 0)
    pos = 0;
    while ((pos <=  h.capacidad) && (h.cantAsociaciones != 0)) {
      if (h[pos] != NULL) {
        liberar_cadena(h[pos]);
        h.cantAsociaciones--; // Una asociación menos a borrar.
      }
      pos++;
    }
    delete(h);
};

/*
  Devuelve `true' si y sólo si en `h' hay una asociación entre `clave'
  y algún valor.
  El tiempo de ejecución es O(1) en promedio.
 */
bool existe_asociacion(int clave, hash_t h) {
  nat pos = (abs(clave) % h.capacidad);
  bool res;
  if (h[pos] == NULL)
    res = false;
  else {
    if (pertenece(clave, h[pos]))
      res = true;
    else
      res = false;
  }
};

/*
  Devuelve el valor correspondiente a la asociacion de `clave' en `h'.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
char *valor_en_hash(int clave, hash_t h) {
  nat pos = (abs(clave) % h.capacidad);
  localizador_t loc = siguiente_clave(clave, inicio_cadena(h[pos], h[pos]));
  char *frase = frase_info(info_cadena(loc, h[pos]));
  return frase;
};

/*
  Devuelve `true' si y sólo si `h' tiene `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool esta_lleno_hash(hash_t h) {
  bool res = false;
  if (h.cantAsociaciones == h.capacidad)
    res = true;
  return res;
};
