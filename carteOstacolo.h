#ifndef HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H
#define HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H

#include "turno.h"
#include "output.h"
#include "tipi.h"
#include <stdbool.h>
#include <stdio.h>

void pescaOstacolo(Giocatore*, CartaOstacolo**);
void mischiaOstacoli(CartaOstacolo**);
bool troppiOstacoli(int[ESAME]);
void controlloOstacoli(Giocatore**, int*, Personaggio[]);

#endif //HAPPY_LITTLE_STUDENTS_CARTEOSTACOLO_H
