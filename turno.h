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

// Le fasi principali del turno
void faseCfu(Giocatore **giocatori, Personaggio[4], int *nGiocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[*nGiocatori], int *moltiplicatoreAumenta);
void faseIstantanee(Giocatore* giocatori, Personaggio personaggi[4], int nGiocatori, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta);
void fineTurno(Giocatore *giocatori, Personaggio personaggi[4], int nGiocatori, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta);

bool vince(Giocatore** giocatori, int* nGiocatori);
Giocatore* spareggio(Giocatore* giocatori, int nGiocatori, bool sconfitti[nGiocatori], CartaCfu** scarti, Personaggio personaggi[N_PERSONAGGI]);
void rimuoviGiocatore(Giocatore** giocatori, Giocatore* giocatore, int* nGiocatori);
void calcolaPunteggio(Punteggio *punteggio, int moltiplicatoreAumenta);
void resetPunteggi(int nGiocatori, Punteggio punteggi[nGiocatori], int *moltiplicatore);
void arrendi(Giocatore** giocatori, Giocatore* giocatore, int* nGiocatori, int indice, Punteggio punteggi[*nGiocatori]);


#endif //HAPPY_LITTLE_STUDENTS_TURNO_H