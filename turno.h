#ifndef HAPPY_LITTLE_STUDENTS_TURNO_H
#define HAPPY_LITTLE_STUDENTS_TURNO_H

#include "tipi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "ANSI-color-codes.h"
#include "costanti.h"
#include "estetica.h"
#include "utilita.h"
#include "output.h"

int contaCarteMano(Giocatore);
void inizializzaGiocatori(Giocatore*);
void pescaRotazione(Giocatore*, CartaCfu**, CartaCfu**);
void pescaCarta(Giocatore*, CartaCfu**, CartaCfu**);
void mischiaMazzo(CartaCfu**);
void mischiaOstacoli(CartaOstacolo**);
void turno(Giocatore*, int, CartaCfu**, CartaCfu**, CartaOstacolo**, int, Personaggio*);
void pescaOstacolo(Giocatore*, CartaOstacolo**);
Giocatore* vince(Giocatore*);
Giocatore* spareggio(Giocatore*, int, int[], CartaCfu**);
void perdereOstacolo(Giocatore**, int*);
void assegnaPersonaggi(Giocatore*, Personaggio*);
bool troppiOstacoli(int[]);
void rimuoviGiocatore(Giocatore**, Giocatore*, int*);

#endif //HAPPY_LITTLE_STUDENTS_TURNO_H