#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "costanti.h"
#include "tipi.h"
#include "letturaFile.h"
#include "turno.h"
#include "input.h"
#include "estetica.h"
#include "ANSI-color-codes.h"

int main() {
    CartaCfu effeffe;
    for(effeffe.effetto=0; effeffe.effetto<16; effeffe.effetto++){
        stampaEffetto(effeffe);
    }
    srand(time(NULL));
    stampaLogo();
    // File e input

    // Array contenente i quattro personaggi (le plance di gioco)
    Personaggio personaggi[N_PERSONAGGI];
    leggiPersonaggi(personaggi);
    // Puntatore alla prima carta del mazzo di carte CFU
    CartaCfu* carteCfu = leggiCarte();
    CartaCfu* scarti = NULL;
    CartaCfu* cartaCfu = carteCfu;
    // Puntatore alla prima carta del mazzo di carte ostacolo
    CartaOstacolo* carteOstacolo = leggiOstacoli();
    Giocatore* vincitore = NULL;

    //mischiaMazzo(&carteCfu);
    //mischiaOstacoli(&carteOstacolo);

    int nGiocatori = inputNGiocatori();
    Giocatore *giocatori = inputGiocatori(nGiocatori);
    inizializzaGiocatori(giocatori);
    int cfuTurno[nGiocatori];
    for(int i=0; i<nGiocatori; i++)
        cfuTurno[i] = 0;
    printf("\n\n\n");
    do{
        perdereOstacolo(&giocatori);
        vincitore = vince(giocatori);
        if(vincitore == NULL)
            turno(giocatori, nGiocatori, &carteCfu, &scarti, &carteOstacolo);
    }while(vincitore == NULL);
    printf("Ha vinto %s!", vincitore->nomeUtente);
    free(carteCfu);
    free(scarti);
    free(carteOstacolo);
    free(giocatori);
    return 0;
}