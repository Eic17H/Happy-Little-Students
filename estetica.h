#ifndef HAPPY_LITTLE_STUDENTS_ESTETICA_H
#define HAPPY_LITTLE_STUDENTS_ESTETICA_H

#include <stdio.h>
#include <stdlib.h>
#include "tipi.h"
#include "ANSI-color-codes.h"
#include <string.h>
#include "log.h"

void stampaLogo();
char cartaSpeciale(CartaCfu);
void coloreOstacoli(TipoOstacolo);
void stampaOstacolo(CartaOstacolo);
void stampaDescOstacolo(CartaOstacolo);
void stampaNomeOstacolo(CartaOstacolo);
void coloreNumero(int);
void colorePersonaggio(Personaggio, Personaggio[N_PERSONAGGI]);
void coloreGiocatore(Giocatore*, Personaggio[N_PERSONAGGI]);
void stampaSituazione(Giocatore*, int, Personaggio*);

#endif //HAPPY_LITTLE_STUDENTS_ESTETICA_H