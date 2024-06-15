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
#include "log.h"

int main() {
    srand(time(NULL));
    stampaLogo();

    creaLog();

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
    //int nGiocatori = inputNGiocatori();
    //Giocatore *giocatori = inputGiocatori(nGiocatori, 1);
    //inizializzaGiocatori(giocatori);
    //assegnaPersonaggi(giocatori, personaggi);

    FILE* fp = fopen("savegame.sav", "rb");
    int nGiocatori;
    fread(&nGiocatori, sizeof(int), 1, fp);
    Giocatore *giocatori, *giocatore;
    CartaCfu *carta;
    CartaOstacolo *ostacolo;
    int nOstacoli;

    giocatori = malloc(sizeof(Giocatore));
    giocatore = giocatori;
    for(int i=0; i<nGiocatori-1; i++){
        fread(giocatore, sizeof(Giocatore), 1, fp);
        giocatore->prossimo = malloc(sizeof(Giocatore));

        giocatore->primaCfu = malloc(sizeof(CartaCfu));
        carta = giocatore->primaCfu;
        for(int j=0; j<N_CARTE_MANO-1; j++){
            fread(carta, sizeof(CartaCfu), 1, fp);
            carta->prossima = malloc(sizeof(CartaCfu));
            carta = carta->prossima;
        }
        fread(carta, sizeof(CartaCfu), 1, fp);
        carta->prossima = NULL;

        giocatore->primaOstacolo = malloc(sizeof(CartaOstacolo));
        ostacolo = giocatore->primaOstacolo;
        fread(&nOstacoli, sizeof(int), 1, fp);
        for(int j=0; j<nOstacoli-1; j++){
            fread(ostacolo, sizeof(CartaOstacolo), 1, fp);
            ostacolo->prossima = malloc(sizeof(CartaOstacolo));
            ostacolo = ostacolo->prossima;
        }
        fread(ostacolo, sizeof(CartaOstacolo), 1, fp);
        ostacolo->prossima = NULL;

        giocatore = giocatore->prossimo;
    }
    fread(giocatore, sizeof(Giocatore), 1, fp);
    giocatore->prossimo = NULL;

    int nCarte, nScarti, nOstacolis;

    CartaCfu *mazzo, *scartis;
    CartaOstacolo *ostacolis;

    mazzo = malloc(sizeof(CartaCfu));
    carta = mazzo;
    fread(&nCarte, sizeof(CartaCfu), 1, fp);
    for(int j=0; j<nCarte-1; j++){
        fread(carta, sizeof(CartaCfu), 1, fp);
        carta->prossima = malloc(sizeof(CartaCfu));
        carta = carta->prossima;
    }
    fread(carta, sizeof(CartaCfu), 1, fp);
    carta->prossima = NULL;

    scartis = malloc(sizeof(CartaCfu));
    carta = scartis;
    fread(&nCarte, sizeof(CartaCfu), 1, fp);
    for(int j=0; j<nCarte-1; j++){
        fread(carta, sizeof(CartaCfu), 1, fp);
        carta->prossima = malloc(sizeof(CartaCfu));
        carta = carta->prossima;
    }
    fread(carta, sizeof(CartaCfu), 1, fp);
    carta->prossima = NULL;

    ostacolis = malloc(sizeof(CartaOstacolo));
    ostacolo = ostacolis;
    fread(&nCarte, sizeof(CartaOstacolo), 1, fp);
    for(int j=0; j<nCarte-1; j++){
        fread(ostacolo, sizeof(CartaOstacolo), 1, fp);
        ostacolo->prossima = malloc(sizeof(CartaOstacolo));
        ostacolo = ostacolo->prossima;
    }
    fread(ostacolo, sizeof(CartaOstacolo), 1, fp);
    ostacolo->prossima = NULL;

    // Variabile che tiene traccia del conteggio dei turni
    int nTurno = 0;

    int numeriPlancia[PUNTI_PER_VINCERE];
    leggiNumeriPlancia(numeriPlancia);

    do{
        // Comincia un turno
        nTurno++;
        logTurno(nTurno);
        pescaRotazione(giocatori, &carteCfu, &scarti);

        // Si stampano le informazioni correnti
        stampaSituazione(giocatori, nGiocatori, personaggi);
        stampaPlancia(giocatori, nGiocatori, numeriPlancia, personaggi);

        // Le due fasi del turno
        faseCfu(giocatori, nGiocatori, personaggi, &carteCfu, &scarti, &carteOstacolo);

        // Si controlla se qualcuno ha vinto o perso
        controlloOstacoli(&giocatori, &nGiocatori, personaggi);
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