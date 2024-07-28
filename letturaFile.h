#ifndef HAPPY_LITTLE_STUDENTS_LETTURAFILE_H
#define HAPPY_LITTLE_STUDENTS_LETTURAFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipi.h"
#include "costanti.h"

void leggiPersonaggi(Personaggio personaggi[N_PERSONAGGI]);
void stampaPersonaggi(Personaggio personaggi[N_PERSONAGGI]);
CartaCfu* leggiCarte();
CartaOstacolo* leggiOstacoli();

#endif //HAPPY_LITTLE_STUDENTS_LETTURAFILE_H