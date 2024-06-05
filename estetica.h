#ifndef HAPPY_LITTLE_STUDENTS_ESTETICA_H
#define HAPPY_LITTLE_STUDENTS_ESTETICA_H

#include <stdio.h>
#include <stdlib.h>
#include "tipi.h"
#include "ANSI-color-codes.h"
#include <string.h>

#endif //HAPPY_LITTLE_STUDENTS_ESTETICA_H

void stampaLogo();
char cartaSpeciale(CartaCfu);
void coloreOstacoli(TipoOstacolo);
void stampaEffetto(CartaCfu);
void stampaOstacolo(CartaOstacolo);
void stampaDescOstacolo(CartaOstacolo);
void stampaNomeOstacolo(CartaOstacolo);
void stampaPlancia(Giocatore*, int, int[]);
void segnalino(Giocatore*, int, int[]);
void leggiNumeriPlancia(int[]);
void coloreNumero(int);
void colorePersonaggio(Personaggio, Personaggio[]);
void stampaSituazione(Giocatore*, int, Personaggio*);