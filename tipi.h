#ifndef HAPPY_LITTLE_STUDENTS_TIPI_H
#define HAPPY_LITTLE_STUDENTS_TIPI_H

#include "costanti.h"

typedef struct Personaggio Personaggio;
typedef struct Giocatore Giocatore;
typedef enum EffettoCarta EffettoCarta;
typedef struct CartaCfu CartaCfu;
typedef struct CartaOstacolo CartaOstacolo;
typedef enum TipoOstacolo TipoOstacolo;
typedef struct Punteggio Punteggio;
typedef struct GiocatoreCarta GiocatoreCarta;

enum EffettoCarta {
    // Nessun effetto
    NESSUNO,
    // Scarta una carta CFU punto e aggiungi il suo punteggio a quello del turno
    SCARTAP,
    // Guarda la mano di un collega e ruba una carta a scelta.
    RUBA,
    // Scambia questa carta con quella di un altro giocatore, purché senza effetto
    SCAMBIADS,
    // Scarta una carta CFU punto con effetto e aggiungi il suo punteggio a quello del turno
    SCARTAE,
    // Scarta da uno a tre carte dalla tua mano
    SCARTAC,
    // Scambia il punteggio del turno maggiore e minore dopo il calcolo del punteggio di base
    SCAMBIAP,
    // Raddoppia gli effetti delle carte che aumentano o diminuiscono il punteggio (per tutti)
    DOPPIOE,
    // Guarda due carte in cima al mazzo, prendine una e scarta l’altra
    SBIRCIA,
    // Scambia la carta punto giocata nel turno da un giocatore G1 con quella di un giocatore G2, con G1 e G2 scelti dal giocatore che ha giocato la carta SCAMBIAC
    SCAMBIAC,
    // Annulla gli effetti di tutte le carte punto durante il turno
    ANNULLA,
    // Aumenta di 2 CFU il punteggio del turno di un giocatore a scelta
    AUMENTA,
    // Diminuisci di 2 CFU il punteggio del turno di un giocatore a scelta
    DIMINUISCI,
    // Inverti punteggio minimo e massimo del turno (istantanea)
    INVERTI,
    // Metti la carta Ostacolo che stai per prendere in fondo al mazzo (istantanea)
    SALVA,
    // Dai la carta che stai per prendere ad un altro giocatore a tua scelta (istantanea)
    DIROTTA
};

enum TipoOstacolo {
    STUDIO = 1,
    SOPRAVVIVENZA=2,
    SOCIALE=3,
    ESAME=4
};

struct CartaCfu{
    // Nome della carta
    char nome[LUNG_NOMI];
    // Valore della carta (ignorato per le carte istantanee)
    int cfu;
    // Effetto della carta (inclusi gli effetti istantanei)
    enum EffettoCarta effetto;
    // Puntatore alla prossima carta nel mazzo o nella mano
    struct CartaCfu *prossima;
};

struct CartaOstacolo{
    // Nome della carta
    char nome[LUNG_NOMI];
    // Descrizione della carta
    char descrizione[LUNG_DESCR];
    // Tipo dell'ostacolo
    enum TipoOstacolo tipo;
    // Puntatore alla prossima carta, nel mazzo o nel gruppo di ostacoli del giocatore
    struct CartaOstacolo *prossima;
};

struct Personaggio{
    // Nome del personaggio
    char nome[LUNG_NOMI];
    // Lista di bonus e malus per ciascun tipo di ostacolo
    int ostacoli[N_TIPI_OSTACOLI];
};

struct Giocatore{
    // Nome utente (immesso da tastiera)
    char nomeUtente[LUNG_NOMI];
    // Personaggio (selezionato all'inizio della partita)
    struct Personaggio personaggio;
    // Cfu correnti (0 all'inizio della partita)
    int cfu;
    // Puntatore alla prima carta cfu in mano
    struct CartaCfu *primaCfu;
    // Puntatore alla prima carta ostacolo pescata
    struct CartaOstacolo *primaOstacolo;
    // Puntatore al prossimo giocatore nella lista
    struct Giocatore *prossimo;
};

/**
 * Tiene traccia del punteggio provvisorio di un giocatore durante il turno, separando i punti per metodo di ottenimento
 */
struct Punteggio{
    // Punti ottenuti dalla carta giocata in questo turno
    int carta;
    // Punti ottenuti o persi dal bonus o malus del personaggio
    int personaggio;
    // Numero delle carte "diminuisci" attive sul giocatore, sottratto dal numero di carte "aumenta"
    int aumenta;
    // Punti totali (da ricalcolare con una funzione prima di essere letto)
    int totale;
};

#endif //HAPPY_LITTLE_STUDENTS_TIPI_H
