//
// Created by eic17 on 27/06/2024.
//

#ifndef HAPPY_LITTLE_STUDENTS_CARTEISTANTANEE_H
#define HAPPY_LITTLE_STUDENTS_CARTEISTANTANEE_H

#include "turno.h"
#include <stdbool.h>
#include <time.h>
#include "costanti.h"
#include <string.h>
#include "ANSI-color-codes.h"
#include "tipi.h"
#include <stdlib.h>
#include <stdio.h>
#include "utilita.h"
#include "estetica.h"
#include "carteCfu.h"
#include "log.h"

void usaIstantanea(CartaCfu carta, int nGiocatori, int indice, Giocatore* arrayGiocatori[nGiocatori], Punteggio punteggi[nGiocatori], Personaggio personaggi[N_PERSONAGGI], int moltiplicatoreAumenta);
void aumentaDiminuisci(int nGiocatori, int indice, int valore, Giocatore* giocatori[nGiocatori], Punteggio punteggi[nGiocatori], Personaggio personaggi[N_PERSONAGGI], int moltiplicatore);
void inverti(int nGiocatori, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta);
void salvaDirotta(int nGiocatori, Giocatore* giocatori, Giocatore** sconfitto, Personaggio personaggi[N_PERSONAGGI]);

#endif //HAPPY_LITTLE_STUDENTS_CARTEISTANTANEE_H
