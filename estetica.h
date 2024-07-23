#ifndef HAPPY_LITTLE_STUDENTS_ESTETICA_H
#define HAPPY_LITTLE_STUDENTS_ESTETICA_H

#include <stdio.h>
#include <stdlib.h>
#include "tipi.h"
#include "ANSI-color-codes.h"
#include <string.h>
#include "log.h"
#include "utilita.h"
#include "carteEffetto.h"
#include "carteOstacolo.h"

void stampaLogo();
char cartaSpeciale(CartaCfu);
void coloreOstacoli(TipoOstacolo);

void coloreNumero(int);
void colorePersonaggio(Personaggio, Personaggio[N_PERSONAGGI]);
void coloreGiocatore(Giocatore*, Personaggio[N_PERSONAGGI]);
void stampaSituazione(Giocatore*, int, Personaggio*);
void coloreErrore();
void coloreComunicazioni();

#endif //HAPPY_LITTLE_STUDENTS_ESTETICA_H