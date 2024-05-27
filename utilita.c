//
// Created by eic17 on 27/05/2024.
//

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