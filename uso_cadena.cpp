/* 5223744 - 4937759 */
#include "../include/info.h"
#include "../include/cadena.h"
#include "../include/uso_cadena.h"
#include <string.h> 
#include <stdio.h>  
#include <limits.h> 
#include <assert.h>
#include <cstddef>

/*
  Devuelve `true' si y sólo si en `cad' hay un elemento cuyo dato numérico es
  `i'.
 */
bool pertenece(int i, cadena_t cad) {
    bool res;
    if (es_vacia_cadena(cad))
        res = false;
    else {
        localizador_t loc = inicio_cadena(cad);
        int numeroActual = numero_info(info_cadena(loc, cad)); 
        bool termine = false;
        while ((loc != NULL) && (numeroActual != i) && (!termine)) {
            if (siguiente(loc, cad) != NULL) {
                loc = siguiente(loc, cad);
                numeroActual = numero_info(info_cadena(loc, cad));
            }
            else 
                termine = true;
        }
        res = (numeroActual == i); 
    }
    return res;
} 

/*  Devuelve la cantidad de elementos de `cad'. */
nat longitud(cadena_t cad) {
    nat contador = 0;
    if (!es_vacia_cadena(cad)){
        localizador_t loc = inicio_cadena(cad);
        while (loc!=NULL){
            loc = siguiente(loc, cad);
            contador++;
        }
    }
     return contador;
}

/*
  Devuelve `true' si y sólo si `cad' está ordenada de forma no decreciente
  (= creciente de manera no estricta) según los datos numéricos de sus
  elementos.
  Si es_vacia_cadena (cad) devuelve `true'.
 */
bool esta_ordenada(cadena_t cad) {
	bool res;
	if ((es_vacia_cadena(cad)) || (longitud(cad) == 1))
		res = true;
	else {
		localizador_t locAnalizo = inicio_cadena(cad);
		localizador_t demasElem = siguiente(locAnalizo, cad);
		while ((siguiente(locAnalizo,cad) != NULL) && ((numero_info(info_cadena(locAnalizo, cad))) <= (numero_info(info_cadena(demasElem, cad))))) {
			if (siguiente(demasElem, cad) == NULL) {
				locAnalizo = siguiente(locAnalizo, cad);
				demasElem = siguiente(locAnalizo, cad);
			} else
				demasElem = siguiente(demasElem, cad);
		}
		bool resultado = (siguiente(locAnalizo,cad) == NULL);
		res = resultado;
	}
	return res;
}

/*
  Devuelve una cadena_t con todos los elementos de `c1' y `c2' ordenada de
  manera  creciente segun sus datos numéricos.
  Si hay elementos cuyos datos numéricos son iguales los elementos de `c1'
  quedan antes de los de `c2'.
  La cadena_t resultado no comparte memoria ni con `c1' ni con `c2'.
  Precondición: esta_ordenada (c1) y esta_ordenada (c2).
 */
cadena_t mezcla(cadena_t c1, cadena_t c2) {
    cadena_t res = crear_cadena();
		localizador_t Menor_c1, Menor_c2;
		Menor_c1 = inicio_cadena(c1);
		Menor_c2 = inicio_cadena(c2);
		while ((Menor_c1 != NULL) && (Menor_c2 != NULL)) {
			if ((numero_info(info_cadena(Menor_c1, c1))) <= (numero_info(info_cadena(Menor_c2, c2)))) {
				char *PtrCharAux = new char[strlen(frase_info(info_cadena(Menor_c1, c1))) + 1];
                strcpy(PtrCharAux, frase_info(info_cadena(Menor_c1, c1)));
                info_t InfoCopiar = crear_info((numero_info(info_cadena(Menor_c1, c1))), PtrCharAux);
				res = insertar_al_final(InfoCopiar, res);
				Menor_c1 = siguiente(Menor_c1, c1);
			} else {
				char *PtrCharAux = new char[strlen(frase_info(info_cadena(Menor_c2, c2))) + 1];
                strcpy(PtrCharAux, frase_info(info_cadena(Menor_c2, c2)));
                info_t InfoCopiar = crear_info((numero_info(info_cadena(Menor_c2, c2))), PtrCharAux);
				res = insertar_al_final(InfoCopiar, res);
				Menor_c2 = siguiente(Menor_c2, c2);
			}
		}
		while (Menor_c1 != NULL) {
			char *PtrCharAux = new char[strlen(frase_info(info_cadena(Menor_c1, c1))) + 1];
            strcpy(PtrCharAux, frase_info(info_cadena(Menor_c1, c1)));
            info_t InfoCopiar = crear_info((numero_info(info_cadena(Menor_c1, c1))), PtrCharAux);
			insertar_al_final(InfoCopiar, res);
			Menor_c1 = siguiente(Menor_c1, c1);
		}
		while (Menor_c2 != NULL) {
			char *PtrCharAux = new char[strlen(frase_info(info_cadena(Menor_c2, c2))) + 1];
            strcpy(PtrCharAux, frase_info(info_cadena(Menor_c2, c2)));
            info_t InfoCopiar = crear_info((numero_info(info_cadena(Menor_c2, c2))), PtrCharAux);
            insertar_al_final(InfoCopiar, res);
			Menor_c2 = siguiente(Menor_c2, c2);
		}
	return res;
}

/*
  Devuelve el resultado de concatenar `c2' después de `c1'.
  La cadena_t resultado no comparte memoria ni con `c1' ni con `c2'.
 */
cadena_t concatenar(cadena_t c1, cadena_t c2) {
    
    localizador_t desde, hasta;
    desde = inicio_cadena(c1);
    hasta = final_cadena(c1);
    cadena_t res1 = (copiar_segmento(desde, hasta, c1)); 
    desde = inicio_cadena(c2);
    hasta = final_cadena(c2);
    cadena_t res2 = (copiar_segmento(desde, hasta, c2)); 
    hasta = final_cadena(res1);
    
    res1 = insertar_segmento_despues(res2,hasta,res1);
    liberar_cadena(res2);
    
	return res1;
}

/*
  Se ordena `cad' de manera creciente según los datos numéricos de sus
  elementos.
  Devuelve `cad'.
  No se debe obtener ni devolver memoria de manera dinámica.
  Si es_vacia_cadena (cad) no hace nada.
 */
cadena_t ordenar(cadena_t cad) {
	if ((!es_vacia_cadena(cad)) && (longitud(cad) > 1)) {
        localizador_t loc1, locMenor, loc2;	
	loc1 = inicio_cadena(cad);
	while(siguiente(loc1, cad) != NULL){
		locMenor = siguiente(loc1, cad);
		loc2 = siguiente(locMenor, cad);	
		while(loc2 != NULL){
			if(((numero_info(info_cadena(loc2, cad)))) < ((numero_info(info_cadena(locMenor, cad)))))
				locMenor = loc2;
                loc2 = siguiente(loc2, cad);								
		}
		if ((numero_info(info_cadena(loc1, cad))) > ((numero_info(info_cadena(locMenor, cad)))))
			intercambiar(loc1, locMenor, cad);
		loc1 = siguiente(loc1, cad);
	
    }
    }
	return cad;
}


/*
  Cambia todas las ocurrencias de `original' por `nuevo' en los elementos
   de `cad'. No debe quedar memoria inaccesible.
  Devuelve `cad'.
 */
cadena_t cambiar_todos(int original, int nuevo, cadena_t cad) {	
	if (!es_vacia_cadena(cad)){
		localizador_t locAux = inicio_cadena(cad);
        
		while (locAux != NULL) {
            if (numero_info(info_cadena(locAux,cad)) == original) {
                info_t InfoNueva;
                info_t InfoVieja;
                char *PtrCharAux = new char[strlen(frase_info(info_cadena(locAux, cad))) + 1];
                strcpy(PtrCharAux, frase_info(info_cadena(locAux, cad)));
                InfoVieja = info_cadena(locAux,cad);
                InfoNueva = crear_info(nuevo, PtrCharAux);
                cambiar_en_cadena(InfoNueva,locAux,cad); 
                liberar_info(InfoVieja);
            }
			locAux = siguiente(locAux,cad);
        }
        
    }
    
return cad;
}
