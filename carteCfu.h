#ifndef HAPPY_LITTLE_STUDENTS_CARTECFU_H
#define HAPPY_LITTLE_STUDENTS_CARTECFU_H

#include "utilita.h"
#include "estetica.h"
#include "costanti.h"
#include "ANSI-color-codes.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tipi.h"
#include "turno.h"
#include "log.h"

// Subroutine che gestiscono le fondamenta dello spostamento delle carte
CartaCfu* daiCarta(Giocatore*, CartaCfu*);
void cartaNegliScarti(CartaCfu**, CartaCfu*);
CartaCfu* cartaDalMazzo(CartaCfu**);
void prendiCarta(Giocatore*, CartaCfu*);
CartaCfu *selezionaCarta(Giocatore *, bool, bool, bool, bool annulla);

// Subroutine che usano quelle precedenti
void giocaCarta(Giocatore *, CartaCfu **, int *);
void pescaCarta(Giocatore*, CartaCfu**, CartaCfu**);
void pescaRotazione(Giocatore*, CartaCfu**, CartaCfu**);
void scartaMano(Giocatore*, CartaCfu**, CartaCfu**);

// Altre cose utili
bool haQuestaCarta(Giocatore*, CartaCfu*);
int contaCarteMano(Giocatore);
int contaCarteManoNoInst(Giocatore);
void mischiaMazzo(CartaCfu**);
void mostraCarte(Giocatore);
bool soloIstantanee(Giocatore);

#endif //HAPPY_LITTLE_STUDENTS_CARTECFU_H
