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
// TODO: log istantanee

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
    // Puntatore al primo giocatore nella lista
    Giocatore *giocatori;

    // Variabile che tiene traccia del conteggio dei turni
    int nTurno;
    // Variabile che tiene traccia del numero di giocatori (cambia se perdono o si arrendono)
    int nGiocatori;

    int scelta;

    // Caricamento o inizializzazione del file di salvataggio e del log

    char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)];
    nomePartita(nomeFile);

    if(esisteSalvataggio(nomeFile)){
        printf("Vuoi caricare il file di salvataggio? 1 per si', no altrimenti\n");
        scelta = inputCifra();
    }else{
        scelta = 0;
    }

    if(scelta == 1)
        leggiSalvataggio(&nGiocatori, &giocatori, &carteCfu, &scarti, &carteOstacolo, &nTurno, nomeFile);
    else
        inizializzaSalvataggio(&nGiocatori, &giocatori, &carteCfu, &scarti, &carteOstacolo, &nTurno, personaggi);

    creaLog(nomeFile);

    // Conterrà i punteggi provvisori durante i turni
    Punteggio punteggi[nGiocatori];
    // Tiene traccia delle carte che cambiano il valore delle carte Aumenta e Diminuisci
    int moltiplicatoreAumenta = 1;

    do{
        // Comincia un turno
        logTurno(nTurno);
        resetPunteggi(nGiocatori, punteggi, &moltiplicatoreAumenta);
        pescaRotazione(giocatori, &carteCfu, &scarti);

        // È importante salvare dopo aver pescato, il formato richiede che si abbiano 5 carte in mano
        scriviSalvataggio(&nGiocatori, &giocatori, &carteCfu, &scarti, &carteOstacolo, &nTurno, nomeFile);

        // Si stampano le informazioni correnti
        stampaSituazione(giocatori, nGiocatori, personaggi);

        // TODO: abbellire le stampe
        // Le due fasi del turno, l'eventuale spareggio e la pesca dell'ostacolo
        faseCfu(&giocatori, personaggi, &nGiocatori, &carteCfu, &scarti, &carteOstacolo, punteggi, &moltiplicatoreAumenta);
        // Non si continua il turno se si sono arresi tutti
        if(nGiocatori > 1) {
            faseIstantanee(giocatori, personaggi, nGiocatori, &scarti, &carteOstacolo, punteggi, moltiplicatoreAumenta);
            fineTurno(giocatori, personaggi, nGiocatori, &scarti, &carteOstacolo, punteggi, moltiplicatoreAumenta);
            // Si controlla se qualcuno ha vinto o perso
            controlloOstacoli(&giocatori, &nGiocatori, personaggi);
        }

        // È alla fine per evitare che il numero aumenti se si carica un salvataggio ma non si termina un turno
        nTurno++;
        // Se non ha vinto nessuno, si continua a giocare
    }while(!vince(&giocatori, &nGiocatori));

    // Se qualcuno ha vinto si esce dal loop
    stampaVincitori(giocatori, personaggi);
    // TODO: freeare le intere liste credo
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