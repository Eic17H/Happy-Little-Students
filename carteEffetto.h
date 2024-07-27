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

void stampaCfu(CartaCfu);
void stampaNomeCfu(CartaCfu);
void stampaEffetto(CartaCfu);
void usaEffetto(int nGiocatori, CartaCfu carte[nGiocatori], Giocatore* arrayGiocatori[nGiocatori], Giocatore** giocatori, Punteggio punteggi[nGiocatori], int indice, CartaCfu** mazzo, CartaCfu** scarti, Personaggio personaggi[N_PERSONAGGI], int* moltiplicatoreAumenta);
void scartaPE(Giocatore*, Punteggio*, CartaCfu**, bool);
void ruba(Giocatore**, Giocatore*, Personaggio[N_PERSONAGGI], int);
void scambiaDS(Giocatore** giocatori, CartaCfu carte[], Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI], int nGiocatori, Punteggio punteggi[nGiocatori]);
void scartaC(Giocatore *giocatore, CartaCfu**);
void scambiaP(int nGiocatori, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta);
void doppioE(int *moltiplicatoreAumenta);
void sbircia(Giocatore *giocatore, CartaCfu **mazzo, CartaCfu **scarti);
void scambiaC(int, Giocatore**, CartaCfu*, Personaggio*, int);
void annulla();
void ordinaEffetti(int nGiocatori, int ordine[nGiocatori], CartaCfu carte[nGiocatori]);
bool controllaAnnulla(int nGiocatori, Giocatore* giocatori, CartaCfu carte[nGiocatori], Personaggio personaggi[N_PERSONAGGI]);
Giocatore* selezionaAvversario(Giocatore* giocatori, Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI], int nGiocatori);

void scambiaPunteggi(Punteggio*a, Punteggio*b);

#endif //HAPPY_LITTLE_STUDENTS_CARTEEFFETTO_H
