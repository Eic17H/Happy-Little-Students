#ifndef HAPPY_LITTLE_STUDENTS_SALVATAGGIO_H
#define HAPPY_LITTLE_STUDENTS_SALVATAGGIO_H

#include "costanti.h"
#include "tipi.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void leggiSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno);
void scriviSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno);

#endif //HAPPY_LITTLE_STUDENTS_SALVATAGGIO_H
