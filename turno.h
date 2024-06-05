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
void faseCfu(Giocatore *giocatori, int nGiocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int nTurno, Personaggio[], int[50]);
Giocatore* vince(Giocatore*);
Giocatore* spareggio(Giocatore*, int, int[], CartaCfu**);
void assegnaPersonaggi(Giocatore*, Personaggio*);
void rimuoviGiocatore(Giocatore**, Giocatore*, int*);

#endif //HAPPY_LITTLE_STUDENTS_TURNO_H