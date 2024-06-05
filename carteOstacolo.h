#ifndef HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H
#define HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H

#include "turno.h"
#include "tipi.h"
#include <stdbool.h>
#include <stdio.h>

void pescaOstacolo(Giocatore*, CartaOstacolo**);
void mischiaOstacoli(CartaOstacolo**);

bool troppiOstacoli(int[4], int nGiocatori);
void controlloOstacoli(Giocatore**, int*, Personaggio[]);

#endif //HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H
