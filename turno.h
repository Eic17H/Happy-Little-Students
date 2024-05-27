#include "tipi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ANSI-color-codes.h"
#include "costanti.h"
#include "estetica.h"
#include "utilita.h"

#ifndef HAPPY_LITTLE_STUDENTS_TURNO_H
#define HAPPY_LITTLE_STUDENTS_TURNO_H

void mostraCarte(Giocatore);
int contaCarteMano(Giocatore);
void inizializzaGiocatori(Giocatore*);
void pescaRotazione(Giocatore*, CartaCfu**);
void pescaCarta(Giocatore*, CartaCfu**);
void mostraCarteDiTutti(Giocatore*);
void mischiaMazzo(CartaCfu**);
void mischiaOstacoli(CartaOstacolo**);
void giocaCarta(Giocatore*, CartaCfu**, int*);
void turno(Giocatore*, int, CartaCfu**, CartaCfu**, CartaOstacolo**);
void pescaOstacolo(Giocatore*, CartaOstacolo**);
Giocatore* vince(Giocatore*);
Giocatore* spareggio(Giocatore*, int, int*, CartaCfu**);
void perdereOstacolo(Giocatore**);

#endif //HAPPY_LITTLE_STUDENTS_TURNO_H