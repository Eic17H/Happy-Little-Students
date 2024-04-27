#include "costanti.h"


#ifndef HAPPY_LITTLE_STUDENTS_TIPI_H
#define HAPPY_LITTLE_STUDENTS_TIPI_H

typedef struct Personaggio Personaggio;
typedef struct Giocatore Giocatore;
typedef enum EffettoCarta EffettoCarta;
typedef struct CartaCfu CartaCfu;
typedef struct CartaOstacolo CartaOstacolo;
typedef enum TipoOstacolo TipoOstacolo;

enum EffettoCarta {
    NESSUNO,    // Nessun effetto
    SCARTAP,    // Scarta una carta CFU punto e aggiungi il suo punteggio a quello del turno
    RUBA,       // Guarda la mano di un collega e ruba una carta a scelta.
    SCAMBIADS,  // Scambia questa carta con quella di un altro giocatore, purché senza effetto
    SCARTAE,    // Scarta una carta CFU punto con effetto e aggiungi il suo punteggio a quello del turno
    SCARTAC,    // Scarta da uno a tre carte dalla tua mano
    SCAMBIAP,   // Scambia il punteggio del turno maggiore e minore dopo il calcolo del punteggio di base
    DOPPIOE,    // Raddoppia gli effetti delle carte che aumentano o diminuiscono il punteggio (per tutti)
    SBIRCIA,    // Guarda due carte in cima al mazzo, prendine una e scarta l’altra
    SCAMBIAC,   // Scambia la carta punto giocata nel turno da un giocatore G1 con quella di un giocatore G2, con G1 e G2 scelti dal giocatore che ha giocato la carta SCAMBIAC
    ANNULLA,    // Annulla gli effetti di tutte le carte punto durante il turno
    AUMENTA,    // Aumenta di 2 CFU il punteggio del turno di un giocatore a scelta
    DIMINUISCI, // Diminuisci di 2 CFU il punteggio del turno di un giocatore a scelta
    INVERTI,    // Inverti punteggio minimo e massimo del turno
    SALVA,      // Metti la carta Ostacolo che stai per prendere in fondo al mazzo
    DIROTTA     // Dai la carta che stai per prendere ad un altro giocatore a tua scelta
};

enum TipoOstacolo {
    STUDIO = 1,
    SOPRAVVIVENZA,
    SOCIALE,
    ESAME
};

struct CartaCfu{
    char nome[LUNG_NOMI];
    int cfu;
    enum EffettoCarta effetto;
    struct CartaCfu *prossima;
};

struct CartaOstacolo{
    char nome[LUNG_NOMI];
    char descrizione[LUNG_DESCR];
    enum TipoOstacolo tipo;
    struct CartaOstacolo *prossima;
};

struct Personaggio{
    char nome[LUNG_NOMI];
    int ostacoli[N_TIPI_OSTACOLI];
};

struct Giocatore{
    char nomeUtente[LUNG_NOMI];
    struct Personaggio personaggio;
    int cfu;
    struct CartaCfu *primaCfu;
    struct CartaOstacolo *primaOstacolo;
    struct Giocatore *prossimo;
};

#endif //HAPPY_LITTLE_STUDENTS_TIPI_H
