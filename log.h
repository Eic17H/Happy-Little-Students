#ifndef HAPPY_LITTLE_STUDENTS_LOG_H
#define HAPPY_LITTLE_STUDENTS_LOG_H

#include <stdio.h>
#include "tipi.h"
#include <stdbool.h>

void logTurno(int nTurno);
void logCartaCfu(Giocatore giocatore, CartaCfu carta);
void logEffettoCarta(Giocatore giocatore, CartaCfu carta, char effetto[]);
void logPescaCfu(Giocatore giocatore, CartaCfu carta);
void creaLog();
void logVince(Giocatore giocatore, bool punti);
void logCfu(Giocatore giocatore);
void logOstacolo(Giocatore giocatore, CartaOstacolo carta);

#endif //HAPPY_LITTLE_STUDENTS_LOG_H
