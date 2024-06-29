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
 * Gestisce l'input di un intero a una cifra, evitando i problemi che ha scanf() quando si immette una lettera
 * @return Un numero da 0 a 9 se non ci sono errori, -1 altrimenti
 */
int inputCifra(){
    char c;
    scanf("%c", &c);
    getchar();
    if(c<'0' || c>'9')
        return -1;
    return c - '0';
}