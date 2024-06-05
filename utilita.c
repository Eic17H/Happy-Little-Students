//
// Created by eic17 on 27/05/2024.
//

#include "estetica.h"
#include "utilita.h"

/**
 * Scambia due interi
 * @param a
 * @param b
 */
void scambiaInt(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Desinenza di una parola
 * @param n Una quantità
 * @return 'o' per il singolare, 'i' per il plurale
 */
char numeroOI(int n){
    if(n == 1)
        return 'o';
    else
        return 'i';
}