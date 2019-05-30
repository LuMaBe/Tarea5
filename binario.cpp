/* 5223744 - 4937759 */

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/uso_cadena.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rep_binario {
	info_t dato;
	rep_binario *izq;
	rep_binario *der;
};

/* FUNCIONES AUXILIARES: */

static int absoluto(int n) { return (n >= 0) ? (n) : (-n); };

static nat maximo(nat n1, nat n2) { return (n1 >= n2) ? n1: n2; };

static nat cantidad_binario_AUX(binario_t b) {
	nat Cant = 1;
	if (b->izq != NULL)
		Cant = Cant + cantidad_binario_AUX(b->izq);
	if (b->der != NULL)
		Cant = Cant + cantidad_binario_AUX(b->der);
	return (Cant);
};

static bool esHoja(binario_t b) {
	return ((b->izq == NULL) && (b->der == NULL));
};

static bool MayorQueRaiz(cadena_t cad, localizador_t loc, binario_t b) {
	bool res;
	int comp = strcmp(frase_info(info_cadena(loc, cad)), frase_info(raiz(b)));
	if (comp < 0)
		res = false;
	else if (comp > 0)
		res = true;
	return res;
};

static binario_t Nodo_mayor(binario_t b) {
	binario_t res;
	if (b->der == NULL)
		res = b;
	else
		Nodo_mayor(b->der);
	return res;
};

static binario_t menor(binario_t b) {
	binario_t res;
	if (b->izq == NULL) /* Encontré el menor */
		res = b;
	else
		menor(b->izq);
	return res;
};

static void Linealizacion_Aux(binario_t b, cadena_t &cad) {
	if (b != NULL) {

		if (b->izq != NULL) {
			Linealizacion_Aux(b->izq, cad);
		}
		info_t InfoCopy = copia_info(b->dato);
		insertar_al_final(InfoCopy, cad);
		if (b->der != NULL) {
			Linealizacion_Aux(b->der, cad);
		}
	}
};

static void nivel_en_binario_AUX(nat l, binario_t b, cadena_t &res) {
	if (!es_vacio_binario(b)) {
		if (l == 1) {
			info_t CopyInfo = copia_info(b->dato);
			insertar_al_final(CopyInfo, res);
		} else {
			nivel_en_binario_AUX(l-1, b->izq, res);
			nivel_en_binario_AUX(l-1,b->der, res);
		}
	}
};

static bool es_par(int num) {
	if ((absoluto(num)%2) == 0)
		return true;
	else
		return false;
};

static void s_u_p_AUX2(nat &i, int &suma, binario_t b) {
	if ((i > 0) && (es_par(numero_info(b->dato)))) {
		i -= 1;
		suma += numero_info(b->dato);
	}
};

static void suma_ultimos_pares_AUX(nat &i, int &suma, binario_t b) {
	if ((i > 0) && (!es_vacio_binario(b))) {
		if (b->der != NULL)
			suma_ultimos_pares_AUX(i, suma, b->der);
		s_u_p_AUX2(i, suma, b);
		if (b->izq != NULL)
			suma_ultimos_pares_AUX(i, suma, b->izq);
	}
};

static void guiones(nat n) {
	for(nat i = 0; (i < n); i += 1) {
           printf("-");
           }
}

static void imprimir_aux(binario_t b, nat n) {
    if (!es_vacio_binario(b)) {
		imprimir_aux(b->der, (n+1));
		guiones(n);
        printf("%s%d%s%s%s\n", "(", numero_info(b->dato), ",", frase_info(b->dato), ")");
		imprimir_aux(b->izq, (n+1));
    }
};

static binario_t menores_AUX(int clave, binario_t b, binario_t res){
	if (es_vacio_binario(b))
		return NULL;
    else {
		if ((numero_info(b->dato)) < clave) {
			info_t CopiaInfo = copia_info(b->dato);
			res = insertar_en_binario(CopiaInfo, res);
			res->der = menores_AUX(clave, b->der, res->der);
			res->izq = menores_AUX(clave, b->izq, res->izq);
		} else {
			res = menores_AUX(clave, b->izq, res);
			if (res == NULL)
				res = menores_AUX(clave, b->der, res);
			else if (esHoja(res))
				res->der = menores_AUX(clave, b->der, res->der);
		}
	}
	return res;
};

static void es_AVL_aux(binario_t b, nat &alt, bool &aux){
    nat altizq, altder;
    if (b == NULL){
        alt = 0; 
    }else{
        es_AVL_aux(b->der, altder, aux);
        es_AVL_aux(b->izq, altizq, aux);
        alt = (1 + maximo(altizq, altder));
        aux = ((b->izq == NULL) || aux) && ((b->der == NULL) || aux) && absoluto(altizq - altder) <= 1 && aux;
    }
    
}

/* FIN FUNCIONES AUXILIARES */

binario_t crear_binario() { return NULL; };

/*
  Inserta `i' en `b' respetando la propiedad de orden definida.
  Devuelve `b'.
  Precondición: es_vacio_binario(buscar_subarbol(frase_info(i), b).
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
binario_t insertar_en_binario(info_t i, binario_t b) {
	if (es_vacio_binario(b)) {
		rep_binario *nuevo = new rep_binario;
		nuevo->dato = i;
		nuevo->izq = NULL;
		nuevo->der = NULL;
		b = nuevo;
		return b;
	} else {
		char *FraseRaiz = frase_info(b->dato);
		int comp = strcmp(frase_info(i), FraseRaiz);
		if (comp < 0)
			b->izq = insertar_en_binario(i, b->izq);
		else
			b->der = insertar_en_binario(i, b->der);
		}
	return b;
};

/*
  Devuelve el elemento mayor (según la propiedad de orden definida) de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
info_t mayor(binario_t b) {
	while ((b->der) != NULL) {
		b = b->der;
	}
	return b->dato;
};

binario_t remover_mayor(binario_t b) {
	if (b->der == NULL) {
		binario_t izq = b->izq;
		delete (b);
		b = izq;
	} else {
		b->der = remover_mayor(b->der);
	}
	return b;
};

/*
  Remueve de `b' el nodo en el que el dato de texto de su elemento es `t'.
  Si los dos subárboles del nodo a remover son no vacíos, en sustitución del
  elemento removido debe quedar el que es el mayor (segun la propiedad de orden
  definida) en el subárbol izquierdo.
  Devuelve `b'.
  Precondición: !es_vacio_binario(buscar_subarbol(frase_info(i), b).
  Libera la memoria del nodo y del elemento.
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
binario_t remover_de_binario(const char *t, binario_t b) {
		int comp = strcmp(t, frase_info(b->dato));
		if (comp < 0) { // SI `t' es menor que el dato->frase del `b' actual, lo busco por la rama izquierda...
			b->izq = remover_de_binario(t, b->izq); // (Para poder conectar el anterior del que voy a borrar, al que acabo de sustituir)
		}
		else if (comp > 0) { // SI `t' es mayor que el dato->frase del `b' actual, lo busco por la rama derecha...
			b->der = remover_de_binario(t, b->der); // (Para poder conectar el anterior del que voy a borrar, al que acabo de sustituir)
		} else { // SI comp == 0, entonces lo encontré y procedo a eliminar...
			if (esHoja(b)) { // CASO 1: El nodo a borrar es una hoja (no tiene hijos).
				liberar_info(b->dato);
				delete(b); // ¡¡Como no tiene hijos, simplemente borro el nodo y lo igualo a NULL, no necesito sustituirlo por otro nodo!!
				b = NULL;
			} else if (b->izq == NULL) { // Si entra a este 'else if' entonces significa que tiene un hijo derecho...
				rep_binario *AUX = b;
				b = b->der;
				liberar_info(AUX->dato);
				delete(AUX);
			} else if (b->der == NULL) { // Si entra a este 'else if' entonces significa que tiene un hijo izquierdo...
				rep_binario *AUX = b;
				b = b->izq;
				liberar_info(AUX->dato);
				delete(AUX);
			} else { // Si entra a este 'else' entonces significa que tiene dos hijos...
				liberar_info(b->dato);
				b->dato = mayor(b->izq);
				b->izq = remover_mayor(b->izq);
			}
		}	
	return b;
};

binario_t liberar_binario(binario_t b) {
	if (b != NULL) {
		b->izq = liberar_binario(b->izq);
		b->der = liberar_binario(b->der);
		liberar_info(b->dato);
		delete (b);
		b = NULL;
	}
	return b;
};

bool es_vacio_binario(binario_t b) { return b == NULL; };

/*
  Devuelve `true' si y sólo si cada nodo de `b' cumple la condición de balanceo
  AVL. El árbol vacío cumple la condición.
  Un nodo cumple la condición de balanceo AVL si el valor absoluto de la
  diferencia de las alturas de sus subárboles izquierdo y derecho en menor o
  igual a 1.
  Cada nodo se puede visitar una sola vez.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
bool es_AVL(binario_t b) {
	bool res;
    if (b == NULL){
        res = true;
    } else {
        bool aux = true;
        nat alt;
        es_AVL_aux(b, alt, aux);
        res = aux;
    }
    return res;
};

/*
  Devuelve el elemento asociado a la raíz de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(1).
 */
info_t raiz(binario_t b) {
	info_t res = b->dato;
	return res;
};

/*
  Devuelve el subárbol izquierdo de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(1).
 */
binario_t izquierdo(binario_t b) {
	binario_t res = b->izq;
	return res;
};

/*
  Devuelve el subárbol derecho de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(1).
 */
binario_t derecho(binario_t b) {
	binario_t res = b->der;
	return res;
};

binario_t buscar_subarbol(const char *t, binario_t b) {
	binario_t res;
	if (es_vacio_binario(b))
		res = crear_binario();
	else {
		int comp = strcmp(t, frase_info(raiz(b)));
		if (comp < 0)
			res = buscar_subarbol(t, izquierdo(b));
		else if (comp > 0)
			res = buscar_subarbol(t, derecho(b));
		else
			res = b;
		}
		return res;
};

/*
  Devuelve la altura de `b'.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
nat altura_binario(binario_t b) {
	if (es_vacio_binario(b))
		return 0;
	nat AlturaIzq = altura_binario(b->izq);
	nat AlturaDer = altura_binario(b->der);
	nat AlturaMax = maximo(AlturaIzq, AlturaDer);
	return (AlturaMax + 1);
};

/*
  Devuelve la cantidad de elementos de `b'.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
nat cantidad_binario(binario_t b) {
	nat Total = 0;
	if (!es_vacio_binario(b))
		Total = cantidad_binario_AUX(b);
	return (Total);
};

/*
  Devuelve la suma de los datos numéricos de los últimos `i' elementos
  (considerados según la propiedad de orden de los árboles binario_t)
  de `b' cuyos datos numéricos sean pares.
  Si en `b' hay menos de `i' elementos con dato numérico par devuelve la
  suma de todos los datos numéricos pares de `b'.
  No se deben crear estructuras auxiliares.
  No se deben visitar nuevos nodos después que se hayan encontrado los
  `i' elementos.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
int suma_ultimos_pares(nat i, binario_t b) {
	int suma = 0;
	if ((!es_vacio_binario(b)) && (i > 0))
		suma_ultimos_pares_AUX(i, suma, b);
	return suma;
};

/*
  Devuelve una cadena_t con los elementos de `b' en orden lexicográfico
  creciente según sus datos de texto.
  La cadena_t devuelta no comparte memoria con `b'.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
cadena_t linealizacion(binario_t b) {
	cadena_t cad = crear_cadena();
	Linealizacion_Aux(b, cad);
	return cad;
};

/*
  Devuelve un árbol balanceado cuyos elementos son los que están contenidos en
  `cad'.
  En esta función se dice que un árbol está balanceado si
  a) es vacío;
  o
  b)
    b1) el sub-árbol izquierdo tiene la misma cantidad de elementos o uno más
      que el  subárbol derecho;
    y
    b2) los subárboles izquierdo y derecho están balanceados.

  DEFINICIÓN ALTERNATIVA DE ÁRBOL BALANCEADO
  En esta función se dice que un árbol esta balanceado si en cada nodo, la
  cantidad de elementos de su subárbol izquierdo es igual a, o 1 más que, la
  cantidad de elementos de su subárbol derecho.

  Precondición: los elementos de `cad' están en orden lexicográfico creciente
  estricto según sus datos de texto.
  El árbol devuelto no comparte memoria con `cad'.
  El tiempo de ejecución es O(n . log n), siendo `n` la cantidad de elementos
  de `cad'.
 */
binario_t cadena_a_binario(cadena_t cad) {
	binario_t b = crear_binario();
	if (es_vacia_cadena(cad)) {
		return NULL;
	} else {
		if ((longitud(cad) == 1)) {
			info_t CopiaInfo = copia_info(info_cadena(inicio_cadena(cad), cad));
			b = insertar_en_binario(CopiaInfo, b);
		} else {
			nat Medio = ((longitud(cad))/2) +1;
			localizador_t locMedio = kesimo(Medio, cad);
			info_t CopiaInfo = copia_info(info_cadena(locMedio, cad));
			b = insertar_en_binario(CopiaInfo, b);
			cadena_t cad_izq = copiar_segmento(inicio_cadena(cad), anterior(locMedio, cad), cad);
			b->izq = cadena_a_binario(cad_izq);
			cad_izq = liberar_cadena(cad_izq);
			cadena_t cad_der = copiar_segmento(siguiente(locMedio, cad), final_cadena(cad), cad);
			b->der = cadena_a_binario(cad_der);
			cad_der = liberar_cadena(cad_der);
		}
	}
	return b;
};

/*
  Devuelve un árbol con copias de los elementos de `b' que cumplen la condición
  "numero_info(elemento) < clave".
  La estructura del árbol resultado debe ser análoga a la de `b'. Esto
  significa que dados dos nodos `U' y `V' de `b' en los que se cumple la
  condición y tal que `U' es ancestro de `V', en el árbol resultado la copia de
  `U' debe ser ancestro de la copia de `V' cuando sea posible. Esto no siempre
  se puede lograr y al mismo tiempo mantener la propiedad de orden del árbol
  en el caso en el que en un nodo `V' no se cumple la condición y en sus dos
  subárboles hay nodos en los que se cumple. En este caso, la copia del nodo
  cuyo elemento es el mayor (según la propiedad de orden definida) de los que
  cumplen la condición en el subárbol izquierdo de `V' deberá ser ancestro de
  las copias de todos los descendientes de `V' que cumplen la condición.
  (Ver ejemplos en LetraTarea3.pdf).
  El árbol resultado no comparte memoria con `b'. *)
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
binario_t menores(int clave, binario_t b) {
	binario_t res = crear_binario();  
    if (!es_vacio_binario(b) && (!esHoja(b))){
		info_t InfoCopy = copia_info(b->dato);
        res = insertar_en_binario(InfoCopy, res); 
        res->izq = menores_AUX(clave, b->izq, res->izq);
        res->der = menores_AUX(clave, b->der, res->der);
        if (!es_vacio_binario(res->izq) && ((numero_info(b->dato)) >= clave)) {
			liberar_info(res->dato);
			res->dato = mayor(res->izq);
			res->izq = remover_mayor(res->izq);
		} else if (((numero_info(b->dato)) >= clave) && es_vacio_binario(res->der))
			res = liberar_binario(res);
	} else if (!es_vacio_binario(b) && (esHoja(b)) && ((numero_info(b->dato)) < clave)) {
		info_t InfoCopy = copia_info(b->dato);
		res = insertar_en_binario(InfoCopy, res);
	}
	return res;
};

/*
  Devuelve `true' si y solo si en `b' hay un camino desde la raiz hasta una
  hoja que sea compatible con `c'.
  Decimos que una cadena y un camino son compatibles si tienen la misma
  longitud y al recorrer la cadena desde el inicio hasta el final y el camino
  desde la raíz hasta la hoja las frases de los respectivos elementos son
  iguales.
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
bool es_camino(cadena_t c, binario_t b) {
	bool res = true;
	if (!es_vacio_binario(b) && !es_vacia_cadena(c)) {
		localizador_t loc = inicio_cadena(c);
		if (!(es_localizador(siguiente(loc, c))) && esHoja(b)) {
			if (strcmp(frase_info(info_cadena(loc, c)),frase_info(b->dato)) == 0) {
				res = true;
			}
			else {
				res = false;
			}
		} else {
		bool Termine = false;
		while ((!Termine) && (es_localizador(loc)) && (strcmp(frase_info(info_cadena(loc, c)),frase_info(b->dato)) == 0)) {
			if ((siguiente(loc, c) != NULL) && (!esHoja(b))) { 					// La condición de (cad->sig != NULL) es para que en un caso especial no
				if ((b->der != NULL) && (MayorQueRaiz(c, siguiente(loc, c), b))) { // me corra mi función MayorQueRaiz(cad->sig, b), sino me tiraría error.
					b = b->der;
					loc = siguiente(loc, c);
				} else if ((b->izq != NULL) && (!MayorQueRaiz(c, siguiente(loc, c), b))) {
					b = b->izq;
					loc = siguiente(loc, c);
				}
			}
			else
				Termine = true;
		}
		if ((!es_localizador(siguiente(loc, c))) && esHoja(b)) // Si el (cad->sig) == NULL; significa que los elementos de la cadena coincidieron con los
			res = true;											// elementos del árbol binario `b', por lo tanto, si el nodo `b' en el que estoy parado actualmente
		else															 // es un nodo hoja (no tiene hijos) ------> necesariamente es_camino devuelve true.
			res = false;
		}
	} else {
			if ((es_vacio_binario(b) && !es_vacia_cadena(c)) || (!es_vacio_binario(b) && es_vacia_cadena(c)))
				res = false;
			else
				res = true;
	}
	return res;
};

/*
  Devuelve una cadena_t con los elementos del nivel `l' de 'b'.
  La raíz es el nivel 1.
  La cadena_t resultado debe estar ordenada de manera creciente según las
  frases de sus elementos.
  La cadena_t devuelta no comparte memoria con `b'.
 */
cadena_t nivel_en_binario(nat l, binario_t b) {
	cadena_t res = crear_cadena();
	nivel_en_binario_AUX(l, b, res);
	return res;
};

/*
  Imprime los elementos de `b', uno por línea, en orden descendente de la
  propiedad de orden de los árboles `binario_t'.
  Antes del elemento imprime una cantidad de guiones igual a su nivel.
  El elemento se imprime según la especificación dada en `info_a_texto'.
  El nivel de la raíz es 0.
  Antes de terminar, se debe imprimir un fin de linea.
  Si es_vacio_binario(b) sólo se imprime el fin de línea.
  El tiempo de ejecución es O(n . log n) en promedio, donde `n' es la cantidad
  de elementos de `b'.
 */
void imprimir_binario(binario_t b){
	printf("\n");
	nat n=0;
	imprimir_aux(b, n);
};
