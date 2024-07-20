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
#include "carteIstantanee.h"

void inizializzaGiocatori(Giocatore*);
void faseCfu(Giocatore **giocatori, Personaggio[4], int *nGiocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[*nGiocatori], int *moltiplicatoreAumenta);
void faseIstantanee(Giocatore* giocatori, Personaggio personaggi[4], int nGiocatori, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta);
void fineTurno(Giocatore *giocatori, Personaggio personaggi[4], int nGiocatori, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta);
bool vince(Giocatore**, int*);
void stampaVincitori(Giocatore* giocatori, Personaggio personaggi[N_PERSONAGGI]);
Giocatore* spareggio(Giocatore*, int, bool[], CartaCfu**, Personaggio personaggi[N_PERSONAGGI]);
void assegnaPersonaggi(Giocatore*, Personaggio[N_PERSONAGGI]);
void rimuoviGiocatore(Giocatore**, Giocatore*, int*);
void calcolaPunteggio(Punteggio *punteggio, int moltiplicatoreAumenta);
void resetPunteggi(int, Punteggio[], int*);
void stampaGiocatori(Giocatore* giocatori, Punteggio punteggi[], Personaggio personaggi[N_PERSONAGGI]);


#endif //HAPPY_LITTLE_STUDENTS_TURNO_H