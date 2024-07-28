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
void coloreOstacoli(TipoOstacolo);
void coloreNumero(int);
void colorePersonaggio(Personaggio, Personaggio[N_PERSONAGGI]);
void coloreGiocatore(Giocatore*, Personaggio[N_PERSONAGGI]);
void coloreErrore();
void coloreComunicazioni();
void coloreProblema();

#endif //HAPPY_LITTLE_STUDENTS_ESTETICA_H