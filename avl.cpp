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

// Representación de `avl_t'.
// Se debe definir en avl.cpp.
struct rep_avl { // PNG
  info_t dato;
	nat altura;
  nat cantidad;
  avl_t izq, der;
};

// Declaración del tipo `avl_t'.
typedef rep_avl *avl_t;

struct avl_ultimo { // PNG
  avl_t avl;
  int ultimo;
};

/* FUNCIONES AUXILIARES */

static avl_ultimo avl_min_rec(nat h, nat primero) {
  avl_ultimo res;
  if (h == 0) {
    res.avl = NULL;
    res.ultimo = primero - 1;
  } else if (h == 1) {
    // COMPLETAR
  } else {
    // COMPLETAR
  }
  return res;
};

static info_t *en_orden_rec(info_t *res, nat &tope, avl_t avl){ // PNG
  if (!es_vacio_avl(avl)){
    res = en_orden_rec(res, tope, izq_avl(avl));
    res[tope] = raiz_avl(avl);
    tope ++;
    res = en_orden_rec(res, tope, der_avl(avl));
  }
  return res;
};

static avl_t a2avl_rec(info_t *infos, int inf, int sup) { // PNG
  avl_t res;
  if (inf > sup)
    res = NULL;
  else {
    nat medio = (inf + sup) / 2;
    res = new rep_avl;
    res->dato = infos[medio];
    res->izq = a2avl_rec(infos, inf, medio - 1);
    res->der = a2avl_rec(infos, medio + 1, sup);
    // AJUSTAR res->altura y res->cantidad;
  }
  return res;
};

static nat maximo(nat n1, nat n2) { return (n1 >= n2) ? n1: n2; };

static void rotacion_simple_derecha(avl_t &avl){
  avl_t *aux = avl->izq;
  avl->izq = aux->der;
  aux->der = avl;
  avl = aux;
};

static void rotacion_simple_izquierda(avl_t &avl){
  avl_t *aux = avl;

};

static bool signo(int a, int b){ // Compara los signos y devuelve true si son de igual signo.
  bool res=false;
  if ((a>=0) && (b>=0)){
    res = true;
  }else if((a<0) && (b<0)){
    res = true;
  }
  return res;
};

static avl_t arreglo_a_avl_aux(info_t *infos, nat n, avl_t res){
  int i;
  for ((i = 0); (i = n-1); i++){
    insertar_en_avl(infos[i],res);
  }
  return res;
};

/* FUNCIONES AUXILIARES */

/*
  Devuelve un avl_t vacío (sin elementos).
  El tiempo de ejecución es O(1).
 */
avl_t crear_avl() {
  avl_t res = new rep_avl;
  res->altura = 0;
  res->cantidad = 0;
  res = NULL;
  return res;

};

/*
  Devuelve `true' si y sólo si `avl' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool es_vacio_avl(avl_t avl){
  return (avl == NULL);
};

/*
  Inserta `i' en `avl' respetando la propiedad de orden definida.
  Precondición: es_vacio_avl(buscar_en_avl(numero_info(i), avl).
  Precondición: numero_info(i) != INT_MAX.
  El tiempo de ejecución es O(log n), donde `n' es la cantidad de elementos
  de `avl'.
*/
void insertar_en_avl(info_t i, avl_t &avl){
  int alturaizq = 0;
  int alturader = 0;
  if (es_vacio_avl(avl)) {
    avl_t *nuevo = new rep_avl;
    nuevo->dato = i;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    avl = nuevo;
  } else { // Si el avl dado NO es vacío..
    if ((numero_info(i)) < (numero_info(avl->dato))) {
      alturaizq ++;
      insertar_en_avl(i, avl->izq);
    } else {
      alturader++;
      insertar_en_avl(i, avl->der);
    }
  }
  avl->altura = (maximo(alturader, alturaizq) + 1);
  avl->cantidad++;
  int comp1 = ((altura_de_avl(avl->der)) - (altura_de_avl(avl->izq)));
  int comp2 = ((altura_de_avl(avl->der->der)) - (altura_de_avl(avl->der->izq))); // ERROR
  if ((comp1 < -1) && (!signo(comp1, comp2))) {
    rotacion_simple_derecha(avl);
    rotacion_simple_izquierda(avl);
  } else {
    if ((comp1 < -1)) {
      rotacion_simple_derecha(avl);
    }
  }
  if ((comp1 > 1)  && (!signo(comp1,comp2))) {
    rotacion_simple_izquierda(avl);
    rotacion_simple_derecha(avl);
  } else {
    if (comp1 > 1) {
      rotacion_simple_izquierda(avl);
    }
  }
};

/*
  Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo dato
  numérico es `clave'.
  Si ningún nodo cumple esa condición devuelve el árbol vacío.
  El tiempo de ejecución es O(log n), donde `n' es la cantidad de elementos de
  `avl'.
 */
avl_t buscar_en_avl(int clave, avl_t avl){
  avl_t res;
  if (!es_vacio_avl(avl)){
    int comp = numero_info(avl->dato);
		if (clave < comp)
			res = buscar_en_avl(clave, avl->izq);
		else if (clave > comp)
			res = buscar_en_avl(clave, avl->der);
		else
			res = avl;
	}else{
    res =crear_avl();
  }
  return res;
};

/*
  Devuelve el elemento asociado a la raíz de `avl'.
  Precondición: ! es_vacio_avl(b).
  El tiempo de ejecución es O(1).
 */
info_t raiz_avl(avl_t avl){ return avl->dato; };

/*
  Devuelve el subárbol izquierdo de `avl'.
  Precondición: ! es_vacio_avl(avl).
  El tiempo de ejecución es O(1).
 */
avl_t izq_avl(avl_t avl){ return avl->izq; };

/*
  Devuelve el subárbol derecho de `avl'.
  Precondición: ! es_vacio_avl(avl).
  El tiempo de ejecución es O(1).
 */
avl_t der_avl(avl_t avl){ return avl->der; };

/*
  Devuelve la cantidad de elementos en `avl'.
  El tiempo de ejecución es O(1).
 */
nat cantidad_en_avl(avl_t avl){ return avl->cantidad; };

/*
  Devuelve la altura de  `avl'.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución es O(1).
 */
nat altura_de_avl(avl_t avl){
  nat altura = 0;
  if (!es_vacio_avl(avl))
    altura = avl->altura;
  return altura;
};

/*
  Devuelve un arreglo con los elementos de `avl'.
  Los elementos en el arreglo deben estar en orden creciente según los datos
  numericos.
 */
info_t *en_orden_avl(avl_t avl){ // PNG
  info_t *res;
  if (es_vacio_avl(avl))
    res = NULL;
  else {
    res = new info_t[cantidad_en_avl(avl)];
    nat tope = 0;
    res = en_orden_rec(res, tope, avl);
  }
  return res;
};

/*
  Devuelve un avl_t con los `n' elementos que están en el rango [0 .. n - 1]
  del arreglo `infos'.
  Los elementos están ordenados de manera creciente estricto (creciente y sin
  repetidos) según los datos numércos.
  En cada nodo del árbol resultado la cantidad de elementos de su subárbol
  izquierdo es igual a, o 1 menos que, la cantidad de elementos de su subárbol
  derecho.
  El tiempo de ejecución es O(n).
 */
avl_t arreglo_a_avl(info_t *infos, nat n){
  avl_t res = crear_avl();
  arreglo_a_avl_aux(infos, n, res);
  return res;
};

/*
  Devuelve un avl_t de altura `h' con `n' nodos, siendo `n' la mínima cantidad
  de elementos que puede tener un avl de altura `h'.
  Los datos numéricos de los elementos van desde 1 hasta `n'.
  El dato de texto de cada elemento es la cadena vacia.
  En ningún nodo puede ocurrir que el subárbol derecho tenga más nodos que el
  subárbol izquierdo.
  El tiempo de ejecución es O(n).
  Ver ejemplos en la letra y en el caso 408.
 */
avl_t avl_min(nat h) {
  avl_ultimo res = avl_min_rec(h, 1);
  return res.avl;
};

/*
  Imprime los datos numéricos de los nodos de cada nivel de `avl'.
  Imprime una línea por nivel, primero el más profundo y al final el que
  corresponde a la raíz.
  Cada nivel se imprime de izquierda a derecha. Se debe dejar un espacio en
  blanco después de cada número.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de nodos de `avl'.
  Ver ejemplos en la letra y en el caso 404.
 */
void imprimir_avl(avl_t avl){

};

/*
  Libera la memoria asignada a `avl' y la de sus elementos.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de
  `avl'.
 */
void liberar_avl(avl_t &avl){
  if (avl != NULL) {
		liberar_avl(avl->izq);
		liberar_avl(avl->der);
		liberar_info(avl->dato);
		delete(avl);
		avl = NULL;
	}
};
