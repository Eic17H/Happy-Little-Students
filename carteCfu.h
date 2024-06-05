#ifndef HAPPY_LITTLE_STUDENTS_CARTECFU_H
#define HAPPY_LITTLE_STUDENTS_CARTECFU_H

#include "utilita.h"
#include "estetica.h"
#include "costanti.h"
#include "ANSI-color-codes.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tipi.h"
#include "turno.h"

CartaCfu* daiCarta(Giocatore*, CartaCfu*);
void scartaCarta(CartaCfu**, CartaCfu*);
bool haQuestaCarta(Giocatore*, CartaCfu*);
void giocaCarta(Giocatore*, CartaCfu**, int*);
int contaCarteMano(Giocatore);
void pescaCarta(Giocatore*, CartaCfu**, CartaCfu**);
void pescaRotazione(Giocatore*, CartaCfu**, CartaCfu**);
void mischiaMazzo(CartaCfu**);
void mostraCarte(Giocatore);

#endif //HAPPY_LITTLE_STUDENTS_CARTECFU_H
