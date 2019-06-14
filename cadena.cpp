/* 5223744 - 4937759 */
#include "../include/info.h"
#include "../include/cadena.h"
#include "../include/uso_cadena.h"
#include <string.h> 
#include <stdio.h>  
#include <limits.h> 
#include <assert.h>
#include <cstddef>

struct nodo {
    info_t dato;
    nodo *anterior;
    nodo *siguiente;
};

struct rep_cadena {
    nodo *inicio;
    nodo *final;
};

cadena_t crear_cadena() {
    cadena_t res = new rep_cadena;
    res->inicio = res->final = NULL;
    return res;
}

cadena_t insertar_al_final(info_t i, cadena_t cad) {
    nodo *nuevo = new nodo;
    nuevo->dato = i;
    nuevo->siguiente = NULL;
    nuevo->anterior = cad->final;
    if (cad->final == NULL) {
        cad->inicio = nuevo;
    } else {
        cad->final->siguiente = nuevo;
    }
    cad->final = nuevo;
    return cad;
}

/*
  Se inserta `i' como un nuevo elemento inmediatamente antes de `loc'.
  Devuelve `cad'.
  Precondición: localizador_en_cadena(loc, cad).
 */
cadena_t insertar_antes(info_t i, localizador_t loc, cadena_t cad) {
	if ((es_final_cadena(loc,cad)) && (es_vacia_cadena(cad)))
        insertar_al_final(i,cad);
    else if (es_inicio_cadena(loc,cad)){
        nodo *nuevo = new nodo;
        nuevo->dato = i;
        nuevo->anterior = NULL;
        nuevo->siguiente = cad->inicio;
        if (cad->inicio == NULL)
            cad->inicio = nuevo;
        else {
            cad->inicio->anterior = nuevo;
        }
    cad->inicio = nuevo;
    } else {
        nodo *nuevo = new nodo;
        nuevo->dato = i;
        nuevo->siguiente = loc;
        nuevo->anterior = loc->anterior;
        loc->anterior->siguiente = nuevo;
        loc->anterior = nuevo;
    }
    return cad;
}

cadena_t insertar_segmento_despues(cadena_t &sgm, localizador_t loc, cadena_t cad) {
    //assert(es_vacia_cadena(cad) || localizador_en_cadena(loc, cad));
    if (es_vacia_cadena(cad)) {
        cad->inicio = sgm->inicio;
        cad->final = sgm->final;
    } else {
        if (!es_vacia_cadena(sgm)) {
            sgm->inicio->anterior = loc;
            sgm->final->siguiente = loc->siguiente;
            if (es_final_cadena(loc, cad))
                cad->final = sgm->final;
            else
                loc->siguiente->anterior = sgm->final;
            loc->siguiente = sgm->inicio;
        }
    }
    sgm->inicio = sgm->final = NULL;
    return cad;
}

cadena_t copiar_segmento(localizador_t desde, localizador_t hasta, cadena_t cad) {
    cadena_t res = crear_cadena();
    if (!es_vacia_cadena(cad)) {
        localizador_t loc = desde;
        while (loc != siguiente(hasta, cad)) {
            info_t info = copia_info((loc->dato));
            insertar_al_final(info, res);
            loc = siguiente(loc, cad);
        }
    }
    return res;
}

/*
  Remueve de `cad' los elementos que se encuentran  entre `desde' y `hasta',
  incluidos y libera la memoria que tenían asignada y la de sus nodos.
  Devuelve `cad'.
  Si es_vacia_cadena(cad) devuelve la cadena_t vacía.
  Precondición: es_vacia_cadena(cad) o precede_en_cadena(desde, hasta, cad).
 */
cadena_t cortar_segmento(localizador_t desde, localizador_t hasta, cadena_t cad) {
	//assert(es_vacia_cadena(cad) || precede_en_cadena(desde, hasta, cad));
	if  (!es_vacia_cadena(cad)) {
                localizador_t aux1 = desde;
                localizador_t aux2 = hasta;
                localizador_t aux3 = NULL;
                while((aux1 != aux2)){
                    aux3 = aux1->siguiente;
                    cad = remover_de_cadena(aux1,cad);
                    aux1 = aux3;
                }
                cad = remover_de_cadena(aux2,cad);
        }
	return cad;
}

/*
  Se quita el elemento al que se accede desde `loc' y se libera la memoria 
  asignada al mismo y al nodo apuntado por el localizador.
  Devuelve `cad'.
  El valor de `loc' queda indeterminado.
  Precondición: localizador_en_cadena(loc, cad).
 */
cadena_t remover_de_cadena(localizador_t &loc, cadena_t cad) {
    if (es_inicio_cadena(loc,cad) && (es_final_cadena(loc,cad))){
        cad->inicio = NULL;
        cad->final = NULL;
    }else {
        if (es_inicio_cadena(loc,cad)) {
            loc->siguiente->anterior = NULL;
            cad->inicio = loc->siguiente;
        } else {
            if (es_final_cadena(loc, cad)) {
                loc->anterior->siguiente = NULL;
                cad->final = loc->anterior;
            } else {
                loc->anterior->siguiente = loc->siguiente;
                loc->siguiente->anterior = loc->anterior;
            }
        }
    }  
    liberar_info(loc->dato);
    delete loc;
    loc = NULL;
    return cad;
}


cadena_t liberar_cadena(cadena_t cad) {
    nodo *a_borrar;
    while (cad->inicio != NULL) {
        a_borrar = cad->inicio;
        cad->inicio = cad->inicio->siguiente;
        liberar_info(a_borrar->dato);
        delete (a_borrar);
    }
    delete cad;
    return cad;
}

bool es_localizador(localizador_t loc) {return loc != NULL; }

bool es_vacia_cadena(cadena_t cad){
    return ((cad->inicio == NULL) && (cad->final == NULL));
}

/*
  Devuelve `true' si y sólo si con `loc' se accede al último elemento de `cad'.
  Si es_vacia_cadena (cad) devuelve `false'.
 */
bool es_final_cadena(localizador_t loc, cadena_t cad) {
	return ((loc == cad->final) && !(es_vacia_cadena(cad))); 
}

/*
  Devuelve `true' si y sólo si con `loc' se accede al primer elemento de `cad'.
  Si es_vacia_cadena (cad) devuelve `false'.
 */
bool es_inicio_cadena(localizador_t loc, cadena_t cad) {
	if (es_vacia_cadena(cad))
        return false;
    else
        return (loc == cad->inicio);
}

bool localizador_en_cadena(localizador_t loc, cadena_t cad){
    localizador_t cursor = inicio_cadena(cad);
    while(es_localizador(cursor) && (cursor != loc))
        cursor = siguiente(cursor, cad);
    return es_localizador(cursor);
}

/*
  Devuelve `true' si y sólo si `loc1' es igual o precede a `loc2` en `cad`.
  Si es_vacia_cadena (cad) devuelve `false'.
 */
bool precede_en_cadena(localizador_t loc1, localizador_t loc2, cadena_t cad) {
	bool precede = false;
    if ((es_inicio_cadena(loc1, cad)) || (es_final_cadena(loc2, cad)) || (loc1 == loc2))
        precede = true;
    else if (!es_vacia_cadena(cad)) {
        localizador_t aux = loc1->siguiente;
        while ((aux != NULL) && (aux != loc2))
            aux = aux->siguiente;
        precede = (aux == loc2);
    }
    return precede;
}


localizador_t inicio_cadena(cadena_t cad){
    localizador_t res;
    if (es_vacia_cadena(cad)){
        res = NULL;
    }else{
        res = cad->inicio;
    }
    return res;
}

/*
  Devuelve el localizador_t con el que se accede al final de `cad'.
  Si es_vacia_cadena(cad) devuelve un localizador_t no válido.
 */
localizador_t final_cadena(cadena_t cad) {
    localizador_t res;
    if (es_vacia_cadena(cad)) {
        res = NULL;
    } else {
        res = cad->final;
    }
    return res;
}

/*
  Devuelve el localizador_t con el que se accede al k-esimo elemento de `cad'.
  Si `k' es 0 o mayor a la cantidad de elementos de `cad' devuelve un localizdor
  no válido.
 */
localizador_t kesimo(nat k, cadena_t cad){
    localizador_t loc;
    loc = cad->inicio;
    while((loc != NULL) && (k!=1)){
        loc = loc->siguiente;
        k--;
    }
    return loc;
};


/*
  Devuelve el localizador_t con el que se accede al elemento de `cad'
  inmediatamente siguiente a `loc'.
  Si es_final_cadena(loc, cad) devuelve un localizador_t no válido.
  Precondición: localizador_en_cadena(loc, cad).
 */
localizador_t siguiente(localizador_t loc, cadena_t cad) {
	//assert(localizador_en_cadena(loc, cad));
	localizador_t loc_sig;
	if (es_final_cadena(loc, cad))
		loc_sig = NULL;
	else
		loc_sig = loc->siguiente;
	return loc_sig;
}

/*
  Devuelve el localizador_t con el que se accede al elemento de `cad'
  inmediatamente anterior a `loc'.
  Si es_inicio_cadena(loc, cad) devuelve un localizador_t no válido.
  Precondición: localizador_en_cadena(loc, cad).
 */
localizador_t anterior(localizador_t loc, cadena_t cad) {
	//assert(localizador_en_cadena(loc, cad));
	localizador_t loc_ant;
	if (es_inicio_cadena(loc, cad))
		loc_ant = NULL;
	else
		loc_ant = loc->anterior;
	return loc_ant;
}

localizador_t menor_en_cadena(localizador_t loc, cadena_t cad){
    //assert(localizador_en_cadena(loc,cad));
    localizador_t res = loc;
    while(es_localizador(siguiente(loc, cad))){
        loc = siguiente(loc, cad);
        if (numero_info(info_cadena(loc, cad)) < numero_info(info_cadena(res, cad)))
            res = loc;
    }
    return res;
}

localizador_t siguiente_clave(int clave, localizador_t loc, cadena_t cad){
    //assert((es_vacia_cadena(cad)) || (localizador_en_cadena(loc, cad)));
    localizador_t res = loc;
    if (es_vacia_cadena(cad))
        res = NULL;
    else{
        while((es_localizador(res)) && (numero_info(info_cadena(res, cad)) != clave))
            res = siguiente(res, cad);
    }
    return res;
}

/*
  Devuelve el elemento de `cad' al que se accede con `loc'.
  Precondición: localizador_en_cadena(loc, cad).
 */
info_t info_cadena(localizador_t loc, cadena_t cad) {
	//assert(localizador_en_cadena(loc, cad));
		info_t res = loc->dato;
		return res;
}

cadena_t cambiar_en_cadena(info_t i, localizador_t loc, cadena_t cad){
    //assert(localizador_en_cadena(loc, cad));
    loc->dato = i;
    return cad;
} 

/*
  Intercambia los elementos a los que se accede con `loc1' y `loc2'.
  `loc1' y `loc2' mantienen su relación de precedencia.
  Devuelve `cad'.
  Precondición:
    localizador_en_cadena (loc1, cad)
  y localizador_en_cadena (loc2, cad).
 */
cadena_t intercambiar(localizador_t loc1, localizador_t loc2, cadena_t cad) {
    //assert(localizador_en_cadena (loc1, cad) && localizador_en_cadena (loc2, cad));
    if (!son_iguales(loc1->dato,loc2->dato)) {
        info_t info = loc1->dato;
        loc1->dato = loc2->dato;
        loc2->dato = info;
    }
    return cad;
}

/*
  Imprime los elementos de `cad` de la siguiente forma:
  (dn de pos1,fr de pos1)(dn de pos2,fr de pos2) ...
  donce `dn` es el dato numérico y `fr` es la frase.
  Antes de terminar, se debe imprimir un fin de linea.
  Si es_vacia_cadena(cad) sólo se imprime el fin de línea.
 */
void imprimir_cadena(cadena_t cad) {
    if (!es_vacia_cadena(cad)){
        localizador_t recorre = cad->inicio;
        while (recorre != NULL) {
            int copiaNumero = numero_info(recorre->dato);
            printf("(%d,%s)",copiaNumero, frase_info(recorre->dato));
            recorre = recorre->siguiente;
        }
    }
        printf("\n");
        
}
