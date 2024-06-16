#ifndef HAPPY_LITTLE_STUDENTS_SALVATAGGIO_H
#define HAPPY_LITTLE_STUDENTS_SALVATAGGIO_H

#include "costanti.h"
#include "tipi.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "letturaFile.h"
#include "input.h"
#include "turno.h"

void leggiSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, char nomeSav[LUNG_NOMI]);
void scriviSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, char nomeSav[LUNG_NOMI]);
void nomePartita(char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)]);
bool esisteSalvataggio(char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)]);
void inizializzaSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, Personaggio personaggi[N_PERSONAGGI]);

#endif //HAPPY_LITTLE_STUDENTS_SALVATAGGIO_H
