#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "costanti.h"
#include "tipi.h"
#include "letturaFile.h"
#include "turno.h"
#include "input.h"
#include "estetica.h"

int main() {
    printf("\n\n\n\n\n\n\n");
    srand(17);
    stampaLogo();
    // File e input

    // Array contenente i quattro personaggi (le plance di gioco)
    Personaggio personaggi[N_PERSONAGGI];
    leggiPersonaggi(personaggi);
    // Puntatore alla prima carta del mazzo di carte CFU
    CartaCfu* carteCfu = leggiCarte();
    CartaCfu* scarti = NULL;
    // Puntatore alla prima carta del mazzo di carte ostacolo
    CartaOstacolo* carteOstacolo = leggiOstacoli();

    mischiaMazzo(&carteCfu);
    mischiaOstacoli(&carteOstacolo);

    int nGiocatori = inputNGiocatori();
    Giocatore *giocatori = inputGiocatori(nGiocatori);
    inizializzaGiocatori(giocatori);
    int cfuTurno[nGiocatori];
    for(int i=0; i<nGiocatori; i++)
        cfuTurno[i] = 0;
    pescaRotazione(giocatori, &carteCfu);
    printf("\n\n\n");

    mostraCarteDiTutti(giocatori);
    giocaCarta(giocatori, &scarti, cfuTurno);
    mostraCarteDiTutti(giocatori);
    printf("%d", cfuTurno[0]);
    pescaRotazione(giocatori, &carteCfu);
    mostraCarteDiTutti(giocatori);
    return 0;
}