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
#include "carteCfu.h"
#include "carteOstacolo.h"

int main() {
    srand(time(NULL));
    stampaLogo();

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

    // Variabile che tiene traccia del conteggio dei turni
    int nTurno = 0;

    int numeriPlancia[PUNTI_PER_VINCERE];
    leggiNumeriPlancia(numeriPlancia);


    do{
        // Comincia un turno
        nTurno++;
        pescaRotazione(giocatori, &carteCfu, &scarti);
        // Prima fase del turno
        // Stampa le carte ostacolo e il numero di cfu di ciascun giocatore
        stampaSituazione(giocatori, nGiocatori, personaggi);
        // Stampa la plancia con i segnalini
        stampaPlancia(giocatori, nGiocatori, numeriPlancia);
        // Tutti i giocatori pescano finché non hanno abbastanza carte in mano
        faseCfu(giocatori, nGiocatori, personaggi, &carteCfu, &scarti, &carteOstacolo);
        // Controlliamo se ha perso qualcuno
        controlloOstacoli(&giocatori, &nGiocatori, personaggi);
        // Controlliamo se ha vinto qualcuno
        vincitore = vince(giocatori);
        // Se non ha vinto nessuno, si continua a giocare
    }while(vincitore == NULL);

    // Se qualcuno ha vinto si esce dal loop
    colorePersonaggio(vincitore->personaggio, personaggi);
    printf("Ha vinto %s!" RESET, vincitore->nomeUtente);
    free(carteCfu);
    free(scarti);
    free(carteOstacolo);
    free(giocatori);

    // Evita che l'andata a capo già inserita sia presa dal prossimo getchar()
    getchar();
    printf("\n\nPremi invio per chiudere.\n");
    // Prima di chiudere il gioco, attende che si prema invio
    getchar();
    return 0;
}