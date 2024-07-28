#ifndef HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H
#define HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H

#include "turno.h"
#include "tipi.h"
#include "estetica.h"
#include <stdbool.h>
#include <stdio.h>

void pescaOstacolo(Giocatore* giocatore, CartaOstacolo** mazzo, Personaggio personaggi[N_PERSONAGGI]);
void mischiaOstacoli(CartaOstacolo** mazzo);
bool troppiOstacoli(int carte[4]);
void controlloOstacoli(Giocatore** giocatori, int* nGiocatori, Personaggio personaggi[N_PERSONAGGI]);
void rimettiOstacoloNelMazzo(CartaOstacolo* mazzo, CartaOstacolo* ostacolo);
CartaOstacolo* togliOstacolo(CartaOstacolo** mazzo);
void annullaOstacolo(CartaOstacolo** mazzo);
void stampaOstacolo(CartaOstacolo);
void stampaNomeOstacolo(CartaOstacolo);
void stampaDescOstacolo(CartaOstacolo);

#endif //HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H
