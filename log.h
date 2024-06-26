#ifndef HAPPY_LITTLE_STUDENTS_LOG_H
#define HAPPY_LITTLE_STUDENTS_LOG_H

#include <stdio.h>
#include "tipi.h"
#include <stdbool.h>

void logTurno(int nTurno);
void logCartaCfu(Giocatore giocatore, CartaCfu carta);
void logEffettoCarta(Giocatore giocatore, CartaCfu carta, char effetto[]);
void logPescaCfu(Giocatore giocatore, CartaCfu carta);
void creaLog(char nome[LUNG_NOMI]);
void logVince(Giocatore giocatore, bool punti);
void logCfu(Giocatore giocatore);
void logOstacolo(Giocatore giocatore, CartaOstacolo carta);
void logRuba(Giocatore ladro, Giocatore vittima, CartaCfu carta);
void prendiCfu(Giocatore giocatore, int nCfu, bool carte);
void logTesto(char string[256]);
void logArrende(Giocatore giocatore);

#endif //HAPPY_LITTLE_STUDENTS_LOG_H
