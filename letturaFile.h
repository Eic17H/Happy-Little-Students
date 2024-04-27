#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipi.h"
#include "costanti.h"

#ifndef HAPPY_LITTLE_STUDENTS_LETTURAFILE_H
#define HAPPY_LITTLE_STUDENTS_LETTURAFILE_H

void leggiPersonaggi(Personaggio*);
void stampaPersonaggi(Personaggio*);
CartaCfu* leggiCarte();
CartaOstacolo* leggiOstacoli();

#endif //HAPPY_LITTLE_STUDENTS_LETTURAFILE_H