#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "costanti.h"
#include "tipi.h"
#include "letturaFile.h"
#include "turno.h"
#include "input.h"
#include "estetica.h"
#include "utilita.h"
#include "ANSI-color-codes.h"

int main() {
    srand(time(NULL));
    stampaLogo();
    // File e input

    // Array contenente i quattro personaggi (le plance di gioco)
    Personaggio personaggi[N_PERSONAGGI];
    leggiPersonaggi(personaggi);

    // Puntatore alla prima carta del mazzo di carte CFU
    CartaCfu* carteCfu = leggiCarte();
    // Puntatore alla prima carta degli scarti CFU
    CartaCfu* scarti = NULL;
    // Puntatore generico a una carta CFU
    CartaCfu* cartaCfu = carteCfu;

    // Puntatore alla prima carta del mazzo di carte ostacolo
    CartaOstacolo* carteOstacolo = leggiOstacoli();

    // Puntatore al giocatore che ha vinto
    Giocatore* vincitore = NULL;

    // Si mischiano le carte
    mischiaMazzo(&carteCfu);
    mischiaOstacoli(&carteOstacolo);

    // Input del numero dei giocatori, input delle informazioni, assegnazione personaggi
    int nGiocatori = inputNGiocatori();
    Giocatore *giocatori = inputGiocatori(nGiocatori, 1);
    inizializzaGiocatori(giocatori);
    assegnaPersonaggi(giocatori, personaggi);

    // Si parte dal primo turno
    int nTurno = 1;

    do{
        printf("stampaSituazione(giocatori, nGiocatori);\n"); // TODO: rimuovere
        stampaSituazione(giocatori, nGiocatori);
        printf("turno\n"); // TODO: rimuovere
        turno(giocatori, nGiocatori, &carteCfu, &scarti, &carteOstacolo, nTurno);
        // Controlliamo se ha perso qualcuno
        printf("perdereOstacolo(&giocatori);\n"); // TODO: rimuovere
        perdereOstacolo(&giocatori);
        // Controlliamo se ha vinto qualcuno
        printf("vincitore = vince(giocatori);\n"); // TODO: rimuovere
        vincitore = vince(giocatori);
        printf("nTurno++;\n"); // TODO: rimuovere
        // Se non ha vinto nessuno, si continua a giocare
        nTurno++;
    }while(vincitore == NULL);

    // Se qualcuno ha vinto si esce dal loop
    printf("Ha vinto %s!", vincitore->nomeUtente);
    free(carteCfu);
    free(scarti);
    free(carteOstacolo);
    free(giocatori);
    return 0;
}