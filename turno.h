#ifndef HAPPY_LITTLE_STUDENTS_TURNO_H
#define HAPPY_LITTLE_STUDENTS_TURNO_H

#include "tipi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "ANSI-color-codes.h"
#include "costanti.h"
#include "estetica.h"
#include "utilita.h"

void inizializzaGiocatori(Giocatore*);
void
faseCfu(Giocatore *giocatori, int nGiocatori, Personaggio[4], CartaCfu **carteCfu, CartaCfu **scarti,
        CartaOstacolo **carteOstacolo);
Giocatore* vince(Giocatore*);
Giocatore* spareggio(Giocatore*, int, bool[], CartaCfu**);
void assegnaPersonaggi(Giocatore*, Personaggio*);
void rimuoviGiocatore(Giocatore**, Giocatore*, int*);

#endif //HAPPY_LITTLE_STUDENTS_TURNO_H