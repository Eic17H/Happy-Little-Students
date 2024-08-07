#ifndef HAPPY_LITTLE_STUDENTS_INTERFACCIA_H
#define HAPPY_LITTLE_STUDENTS_INTERFACCIA_H


#include "carteIstantanee.h"
#include "carteCfu.h"
#include "costanti.h"
#include <stdbool.h>
#include <time.h>
#include "carteOstacolo.h"
#include "carteEffetto.h"
#include "utilita.h"
#include "log.h"
#include <string.h>
#include "ANSI-color-codes.h"
#include "tipi.h"
#include <stdlib.h>
#include <stdio.h>
#include "estetica.h"
#include "letturaFile.h"

void stampaSituazione(Giocatore* giocatori, Personaggio personaggi[N_PERSONAGGI]);
char cartaSpeciale(CartaCfu);
void stampaVincitori(Giocatore* giocatori, Personaggio personaggi[N_PERSONAGGI]);
void stampaGiocatori(Giocatore* giocatori, Punteggio punteggi[], Personaggio personaggi[N_PERSONAGGI]);
Giocatore* inputGiocatori(int nGiocatori, int nGiocatore);
int inputNGiocatori();
void stampaPersonaggi(Personaggio personaggi[N_PERSONAGGI]);

#endif //HAPPY_LITTLE_STUDENTS_INTERFACCIA_H
