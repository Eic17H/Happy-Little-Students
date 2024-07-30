#ifndef HAPPY_LITTLE_STUDENTS_SALVATAGGIO_H
#define HAPPY_LITTLE_STUDENTS_SALVATAGGIO_H

#include "carteIstantanee.h"
#include "log.h"
#include "carteEffetto.h"
#include "utilita.h"
#include "estetica.h"
#include "ANSI-color-codes.h"
#include <time.h>
#include "costanti.h"
#include "tipi.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "letturaFile.h"
#include "turno.h"
#include "carteCfu.h"
#include "carteOstacolo.h"

void iniziaSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)], Personaggio personaggi[N_PERSONAGGI]);
void leggiSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, char nomeSav[LUNG_NOMI]);
void scriviSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, char nomeSav[LUNG_NOMI]);
void nomePartita(char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)]);
bool esisteSalvataggio(char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)]);
void inizializzaSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, Personaggio personaggi[N_PERSONAGGI]);
void inizializzaGiocatori(Giocatore* giocatori);
void assegnaPersonaggi(Giocatore* giocatori, Personaggio personaggi[N_PERSONAGGI]);

#endif //HAPPY_LITTLE_STUDENTS_SALVATAGGIO_H
