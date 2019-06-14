/* 5223744 - 4937759 */

 /* BIBLIOTECAS */
#include "../include/hash.h"
#include "../include/cadena.h"
#include "../include/uso_cadena.h"
#include "../include/info.h"
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
  cadena_t *hash;
  nat cantAsociaciones;
};
// Declaración del tipo `hash_t'.
typedef rep_hash *hash_t;

/*
 Crea un hash_t de asociaciones numero->texto.
 Podrá haber hasta `tamanio' asociaciones.
 */
hash_t crear_hash(nat tamanio) {
  hash_t h = new rep_hash;
  h->hash = new cadena_t[tamanio];
  h->capacidad = tamanio;
  h->cantAsociaciones = 0;
  for(nat i=0; i<=(tamanio - 1); i++)
    h->hash[i] = NULL;
  return h;
};

/*
  Inserta en `h' la asociación entre `clave' y `valor'.
  Precondición: !esta_lleno_hash(t) y !existe_asociacion(clave, h).
  El tiempo de ejecución es O(1).
 */
void asociar_en_hash(int clave, char *valor, hash_t &h) {
  nat pos = (abs(clave)%(h->capacidad)); // Posición en la que voy a almacenar la asociación.
  info_t info = crear_info(clave, valor);
  if (h->hash[pos] == NULL) {
    h->hash[pos] = crear_cadena();
    h->hash[pos] = insertar_al_final(info, h->hash[pos]);
  } else
    h->hash[pos] = insertar_al_final(info, h->hash[pos]);
  h->cantAsociaciones++;
};

/*
  Sustituye en `h' el anterior valor asociado a `clave' por `valor'.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1).
 */
void actualizar_hash(int clave, char *valor, hash_t &h) {
  nat pos = (abs(clave)%(h->capacidad));
  info_t info = crear_info(clave, valor);
  h->hash[pos] = insertar_antes(info, inicio_cadena(h->hash[pos]), h->hash[pos]);
};

/*
  Elimina de `h' la asociación entre `clave' y algún valor y libera la menoria
  asignada a mantener esa asociación.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
void eliminar_de_hash(int clave, hash_t &h) {
  nat pos = (abs(clave) % h->capacidad);
  bool salir = false;
  while (!salir) {
    localizador_t loc = siguiente_clave(clave, inicio_cadena(h->hash[pos]), h->hash[pos]);
    if (es_localizador(loc))
      h->hash[pos] = remover_de_cadena(loc, h->hash[pos]);
    else
      salir = true;
  }
  h->cantAsociaciones--;
};

/*
  Libera la memoria asignada a `h' y todos sus elementos.
 */
void liberar_hash(hash_t &h) {
  if (h->cantAsociaciones > 0) {
    nat pos = 0;
    while (pos < (h->capacidad)) {
      if (h->hash[pos] != NULL)
        liberar_cadena(h->hash[pos]);
      pos++;
    }
  }
  delete [] h->hash;
  delete(h);
};

/*
  Devuelve `true' si y sólo si en `h' hay una asociación entre `clave'
  y algún valor.
  El tiempo de ejecución es O(1) en promedio.
 */
bool existe_asociacion(int clave, hash_t h) {
  nat pos = (abs(clave) % h->capacidad);
  bool res;
  if (h->hash[pos] == NULL)
    res = false;
  else
    res = pertenece(clave, h->hash[pos]);
  return res;
};

/*
  Devuelve el valor correspondiente a la asociacion de `clave' en `h'.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
char *valor_en_hash(int clave, hash_t h) {
  nat pos = (abs(clave) % h->capacidad);
  localizador_t loc = siguiente_clave(clave, inicio_cadena(h->hash[pos]), h->hash[pos]);
  char *frase = frase_info(info_cadena(loc, h->hash[pos]));
  return frase;
};

/*
  Devuelve `true' si y sólo si `h' tiene `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool esta_lleno_hash(hash_t h) {
  bool res = false;
  if (h->cantAsociaciones == h->capacidad)
    res = true;
  return res;
};
