#ifndef HAPPY_LITTLE_STUDENTS_UTILITA_H
#define HAPPY_LITTLE_STUDENTS_UTILITA_H

#include <stdio.h>
#include <string.h>
#include "ANSI-color-codes.h"
#include "tipi.h"
#include <stdlib.h>

void scambiaInt(int*, int*);
int inputCifra();
void freeCfu(CartaCfu** mazzo);
void freeOstacoli(CartaOstacolo** mazzo);
void freeGiocatori(Giocatore** lista);
void stampaNomeGiocatoreColore(Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI]);

#endif //HAPPY_LITTLE_STUDENTS_UTILITA_H