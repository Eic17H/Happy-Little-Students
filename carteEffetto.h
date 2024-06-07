#ifndef HAPPY_LITTLE_STUDENTS_CARTEEFFETTO_H
#define HAPPY_LITTLE_STUDENTS_CARTEEFFETTO_H

#include <string.h>
#include "ANSI-color-codes.h"
#include "tipi.h"
#include <stdlib.h>
#include <stdio.h>
#include "utilita.h"
#include "estetica.h"
#include "carteCfu.h"

void stampaEffetto(CartaCfu);
void usaEffetto(CartaCfu, Giocatore*, Punteggio*, CartaCfu**);
void scartaPE(Giocatore*, Punteggio*, CartaCfu**, bool);
void ruba();
void scambiaDS();
void scartaC();
void scambiaP();
void doppioE();
void sbircia();
void scambiaC();
void annulla();
void aumenta();
void diminuisci();
void inverti();
void salva();
void dirotta();

#endif //HAPPY_LITTLE_STUDENTS_CARTEEFFETTO_H
