#ifndef HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H
#define HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H

#include "turno.h"
#include "tipi.h"
#include <stdbool.h>
#include <stdio.h>

void pescaOstacolo(Giocatore*, CartaOstacolo**, Personaggio[N_PERSONAGGI]);
void mischiaOstacoli(CartaOstacolo**);
bool troppiOstacoli(int[4], int nGiocatori);
void controlloOstacoli(Giocatore**, int*, Personaggio[N_PERSONAGGI]);
void rimettiOstacoloNelMazzo(CartaOstacolo* mazzo, CartaOstacolo* ostacolo);
CartaOstacolo* togliOstacolo(CartaOstacolo** mazzo);
void annullaOstacolo(CartaOstacolo** mazzo);

#endif //HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H
