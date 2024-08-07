#ifndef HAPPY_LITTLE_STUDENTS_LOG_H
#define HAPPY_LITTLE_STUDENTS_LOG_H

#include <stdio.h>
#include "tipi.h"
#include <stdbool.h>
#include <string.h>

void creaLog(char nome[]);
void logTurno(int nTurno);
void logCartaCfu(Giocatore giocatore, CartaCfu carta);
void logEffettoCarta(Giocatore giocatore, CartaCfu carta, char effetto[]);
void logPescaCfu(Giocatore giocatore, CartaCfu carta);
void logVince(Giocatore giocatore, bool punti);
void logCfu(Giocatore giocatore);
void logOstacolo(Giocatore giocatore, CartaOstacolo carta);
void logRuba(Giocatore ladro, Giocatore vittima, CartaCfu carta);
void logPrendiCfu(Giocatore giocatore, int nCfu, bool carte);
void logArrende(Giocatore giocatore);
void logSalva(Giocatore giocatore, CartaCfu carta);
void logDirotta(Giocatore giocatore, CartaCfu carta, Giocatore vittima);
void logScarta(Giocatore giocatore, CartaCfu carta);
void logAumentaDiminuisci(Giocatore giocatore, Giocatore vittima, int valore);
void logRimescola();
void logSpareggio();
void logScambiaC(Giocatore scambiante, Giocatore scambiato1, Giocatore scambiato2, CartaCfu carta1, CartaCfu carta2);

#endif //HAPPY_LITTLE_STUDENTS_LOG_H
