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
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* LIBRERIAS */

// Representación de `hash_t'.
// Se debe definir en hash.cpp.
struct rep_hash {
  int numero;
  char *texto;
  nat MaxAsociaciones;
};
// Declaración del tipo `hash_t'.
typedef rep_hash *hash_t;

/*
 Crea un hash_t de asociaciones numero->texto.
 Podrá haber hasta `tamanio' asociaciones.
 */
hash_t crear_hash(nat tamanio);

/*
  Inserta en `h' la asociación entre `clave' y `valor'.
  Precondición: !esta_lleno_hash(t) y !existe_asociacion(clave, h).
  El tiempo de ejecución es O(1).
 */
void asociar_en_hash(int clave, char *valor, hash_t &h);

/*
  Sustituye en `h' el anterior valor asociado a `clave' por `valor'.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1).
 */
void actualizar_hash(int clave, char *valor, hash_t &h);

/*
  Elimina de `h' la asociación entre `clave' y algún valor y libera la menoria
  asignada a mantener esa asociación.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
void eliminar_de_hash(int clave, hash_t &h);

/*
  Libera la memoria asignada a `h' y todos sus elementos.
 */
void liberar_hash(hash_t &h);

/*
  Devuelve `true' si y sólo si en `h' hay una asociación entre `clave'
  y algún valor.
  El tiempo de ejecución es O(1) en promedio.
 */
bool existe_asociacion(int clave, hash_t h);

/*
  Devuelve el valor correspondiente a la asociacion de `clave' en `h'.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
char *valor_en_hash(int clave, hash_t h);

/*
  Devuelve `true' si y sólo si `h' tiene `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool esta_lleno_hash(hash_t h);
