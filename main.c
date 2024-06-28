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
#include "salvataggio.h"

// TODO: controllare e spostare tutti i getchar()

int main() {
    srand(time(NULL));
    stampaLogo();

    // Array contenente i quattro personaggi (le plance di gioco)
    Personaggio personaggi[N_PERSONAGGI];
    leggiPersonaggi(personaggi);

    // Puntatore alla prima carta del mazzo di carte CFU
    CartaCfu* carteCfu;
    // Puntatore alla prima carta degli scarti CFU
    CartaCfu* scarti;

    // Puntatore alla prima carta del mazzo di carte ostacolo
    CartaOstacolo* carteOstacolo;

    // Puntatore al giocatore che ha vinto
    Giocatore* vincitore = NULL;

    Giocatore *giocatori;

    // Variabile che tiene traccia del conteggio dei turni
    int nTurno;

    int nGiocatori;

    /** TODO:
     * Ultimi effetti delle carte
     * Menù di scelta per ogni turno (easy)
     * Pareggio di 4 giocatori (easy)
     * Ultime cose 2 giocatori (easy credo)
     * Selezione personaggi (easy credo)
     */

    char scelta;
    char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)];
    nomePartita(nomeFile);

    if(esisteSalvataggio(nomeFile)){
        printf("Vuoi caricare il file di salvataggio? 1 per sì, no altrimenti\n");
        scanf("%c", &scelta);
    }else
        scelta = '0';

    if(scelta == '1')
        leggiSalvataggio(&nGiocatori, &giocatori, &carteCfu, &scarti, &carteOstacolo, &nTurno, nomeFile);
    else
        inizializzaSalvataggio(&nGiocatori, &giocatori, &carteCfu, &scarti, &carteOstacolo, &nTurno, personaggi);

    int numeriPlancia[PUNTI_PER_VINCERE];
    bool planciaOk = leggiNumeriPlancia(numeriPlancia);

    creaLog(nomeFile);

    Punteggio punteggi[nGiocatori];

    int moltiplicatoreAumenta = 1;
    getchar();

    do{
        // Comincia un turno
        logTurno(nTurno);
        resetPunteggi(nGiocatori, punteggi, &moltiplicatoreAumenta);
        pescaRotazione(giocatori, &carteCfu, &scarti);

        // È importante salvare dopo aver pescato, il formato richiede che si abbiano 5 carte in mano
        scriviSalvataggio(&nGiocatori, &giocatori, &carteCfu, &scarti, &carteOstacolo, &nTurno, nomeFile);

        // Si stampano le informazioni correnti
        stampaSituazione(giocatori, nGiocatori, personaggi);
        if(planciaOk)
            stampaPlancia(giocatori, nGiocatori, numeriPlancia, personaggi);

        // TODO: abbellire le stampe
        // Le due fasi del turno, l'eventuale spareggio e la pesca dell'ostacolo
        faseCfu(&giocatori, personaggi, &nGiocatori, &carteCfu, &scarti, &carteOstacolo, punteggi, &moltiplicatoreAumenta);
        faseIstantanee(giocatori, personaggi, nGiocatori, &scarti, &carteOstacolo, punteggi, moltiplicatoreAumenta);
        fineTurno(&giocatori, personaggi, nGiocatori, &scarti, &carteOstacolo, punteggi, moltiplicatoreAumenta);

        // Si controlla se qualcuno ha vinto o perso
        controlloOstacoli(&giocatori, &nGiocatori, personaggi);
        vincitore = vince(giocatori);

        // È alla fine per evitare che il numero aumenti se si carica un salvataggio ma non si termina un turno
        nTurno++;
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