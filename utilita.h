#ifndef HAPPY_LITTLE_STUDENTS_UTILITA_H
#define HAPPY_LITTLE_STUDENTS_UTILITA_H

#include <stdio.h>
#include <string.h>
#include "ANSI-color-codes.h"
#include "tipi.h"
#include <stdlib.h>

// TODO: rimuovere tutti gli utilizzi
// "printf" per attivare, "//" per disattivare (senza virgolette)
#define debug //

void scambiaInt(int*, int*);
int inputCifra();
void stampaNomeGiocatoreColore(Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI]);

#endif //HAPPY_LITTLE_STUDENTS_UTILITA_H