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

struct nodo {
  info_t dato;
  nodo *sig;
};

struct rep_iterador {
  nodo *inicio, *fin, *actual;
  bool bloqueado;
};

iterador_t crear_iterador() {
  iterador_t res = new rep_iterador;
  res->actual = res->inicio = res->fin = NULL;
  res->bloqueado = false;
  return res;
} // crear_iterador

void liberar_iterador(iterador_t &iter) {
  iter->actual = iter->inicio;
  while (iter->actual != NULL) {
    nodo *a_borrar = iter->actual;
    iter->actual = iter->actual->sig;
    liberar_info(a_borrar->dato);
    delete a_borrar;
  }
  delete iter;
} // liberar_iterador

void bloquear_iterador(iterador_t &iter) { iter->bloqueado = true; }

void agregar_a_iterador(info_t info, iterador_t &iter) {
  if (!iter->bloqueado) {
    nodo *nuevo = new nodo;
    nuevo->dato = copia_info(info);
    nuevo->sig = NULL;
    if (iter->fin != NULL)
      iter->fin->sig = nuevo;
    else
      iter->inicio = nuevo;
    iter->fin = nuevo;
  }
}

void reiniciar_iterador(iterador_t &iter) {
  if (iter->inicio != NULL)
    iter->actual = iter->inicio;
}

void avanzar_iterador(iterador_t &iter) {
  if (iter->actual != NULL)
    iter->actual = iter->actual->sig;
}

info_t actual_en_iterador(iterador_t &iter) {
  return (iter->actual != NULL) ? (iter->actual->dato) : NULL;
}

bool hay_siguiente_en_iterador(iterador_t iter) {
  return (iter->actual->sig != NULL);
}

bool esta_definida_actual(iterador_t iter) { return iter->actual != NULL; }
