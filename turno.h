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
#include "carteEffetto.h"
#include "carteCfu.h"
#include "carteOstacolo.h"
#include "log.h"

void inizializzaGiocatori(Giocatore*);
void faseCfu(Giocatore *giocatori, Personaggio[4], int nGiocatori, CartaCfu **carteCfu, CartaCfu **scarti,
             CartaOstacolo **carteOstacolo, Punteggio punteggi[nGiocatori], int *moltiplicatoreAumenta);
Giocatore* vince(Giocatore*);
Giocatore* spareggio(Giocatore*, int, bool[], CartaCfu**);
void assegnaPersonaggi(Giocatore*, Personaggio*);
void rimuoviGiocatore(Giocatore**, Giocatore*, int*);
void calcolaPunteggio(Punteggio *punteggio, int moltiplicatoreAumenta);
void resetPunteggi(int, Punteggio[], int*);


#endif //HAPPY_LITTLE_STUDENTS_TURNO_H