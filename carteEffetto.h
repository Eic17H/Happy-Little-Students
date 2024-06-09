#ifndef HAPPY_LITTLE_STUDENTS_CARTEEFFETTO_H
#define HAPPY_LITTLE_STUDENTS_CARTEEFFETTO_H

#include "turno.h"
#include <stdbool.h>
#include <time.h>
#include "costanti.h"
#include <string.h>
#include "ANSI-color-codes.h"
#include "tipi.h"
#include <stdlib.h>
#include <stdio.h>
#include "utilita.h"
#include "estetica.h"
#include "carteCfu.h"
#include "log.h"

void stampaEffetto(CartaCfu);
void usaEffetto(CartaCfu, Giocatore *, Punteggio *, CartaCfu **, Personaggio[4], Giocatore **, int,
                int *moltiplicatoreAumenta);
void scartaPE(Giocatore*, Punteggio*, CartaCfu**, bool);
void ruba(Giocatore**, Giocatore*, Personaggio[N_PERSONAGGI], int);
void scambiaDS();
void scartaC();
void scambiaP();
void doppioE(int *moltiplicatoreAumenta);
void sbircia();
void scambiaC();
void annulla();
void aumenta();
void diminuisci();
void inverti();
void salva();
void dirotta();
void ordinaEffetti(int nGiocatori, int ordine[nGiocatori], CartaCfu carte[nGiocatori]);
bool controllaAnnulla(int nGiocatori, CartaCfu carte[nGiocatori]);

#endif //HAPPY_LITTLE_STUDENTS_CARTEEFFETTO_H
