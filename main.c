//Nome: Lorenzo Derosas (l.derosas@studenti.unica.it)
//Matricola: 60/61/66478
//Tipologia progetto: medio
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "costanti.h"
#include "tipi.h"
#include "letturaFile.h"
#include "turno.h"
#include "estetica.h"
#include "utilita.h"
#include "carteCfu.h"
#include "carteOstacolo.h"
#include "log.h"
#include "salvataggio.h"
#include "interfaccia.h"

int main() {
    srand(time(NULL));
    stampaLogo();

    // Array contenente i quattro personaggi (le plance di gioco)
    Personaggio personaggi[N_PERSONAGGI];
    leggiPersonaggi(personaggi);

    // Liste delle carte e dei giocatori
    CartaCfu* carteCfu=NULL;
    CartaCfu* scarti=NULL;
    CartaOstacolo* carteOstacolo=NULL;
    Giocatore* giocatori=NULL;

    // Variabile che tiene traccia del conteggio dei turni
    int nTurno;
    // Variabile che tiene traccia del numero di giocatori (cambia se perdono o si arrendono)
    int nGiocatori;

    // Caricamento o inizializzazione del file di salvataggio e del log
    char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)];
    nomePartita(nomeFile);
    iniziaSalvataggio(&nGiocatori, &giocatori, &carteCfu, &scarti, &carteOstacolo, &nTurno, nomeFile, personaggi);
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

        // È importante che il salvataggio avvenga dopo la pesca a rotazione, il formato richiede che si abbiano 5 carte in mano
        scriviSalvataggio(&nGiocatori, &giocatori, &carteCfu, &scarti, &carteOstacolo, &nTurno, nomeFile);

        // Si stampano le informazioni correnti
        stampaSituazione(giocatori, personaggi);

        // Le due fasi del turno, l'eventuale spareggio e la pesca dell'ostacolo
        faseCfu(&giocatori, personaggi, &nGiocatori, &carteCfu, &scarti, &carteOstacolo, punteggi, &moltiplicatoreAumenta);
        // Non si continua il turno se si sono arresi tutti
        if(nGiocatori > 1){
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

    // Si deallocano le liste
    freeCfu(&carteCfu);
    freeCfu(&scarti);
    freeOstacoli(&carteOstacolo);
    freeGiocatori(&giocatori);

    printf("\n\nPremi invio per chiudere.\n");
    // Prima di chiudere il gioco, attende che si prema invio
    getchar();
    return 0;
}