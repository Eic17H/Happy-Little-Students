#include "interfaccia.h"

/**
 * Stampa le carte ostacolo e i CFU di ciascun giocatore
 * @param giocatori Puntatore al primo giocatore
 * @param nGiocatori Numero corrente di giocatori
 * @param personaggi Array dei personaggi
 */
void stampaSituazione(Giocatore* giocatori, int nGiocatori, Personaggio* personaggi){
    Giocatore* giocatore = giocatori;
    CartaOstacolo *carta;
    int i=0, continua=0;

    printf("\n");

    // Nomi
    for(giocatore=giocatori, i=0; giocatore!=NULL; giocatore=giocatore->prossimo, i++){
        colorePersonaggio(giocatore->personaggio, personaggi);
        printf("%32s: %2d CFU\t", giocatore->nomeUtente, giocatore->cfu);
        logCfu(*giocatore);
        for(carta = giocatore->primaOstacolo; carta != NULL; carta = carta->prossima) {
            stampaNomeOstacolo(*carta);
            printf("\t");
        }
        printf(RESET);
        printf("\n");
    }
    printf("\n\n");
}

/**
 * Indica se una carta ha un effetto
 * @param carta una carta cfu
 * @return un indicatore se la carta ha un effetto, uno spazio altrimenti
 */
char cartaSpeciale(CartaCfu carta){
    if(carta.effetto == 0)
        return ' ';
    else if(carta.effetto>=PRIMA_ISTANTANEA)
        return SIMBOLO_CARTA_ISTANTANEA;
    else
        return SIMBOLO_CARTA_EFFETTO;
}

void stampaVincitori(Giocatore* giocatori, Personaggio personaggi[N_PERSONAGGI]){
    // Non dovrebbe poter succedere, ma per sicurezza lo gestisco
    if(giocatori == NULL){
        coloreErrore();
        printf("Errore: la partita è terminata senza nessun vincitore.\n" RESET);
        return;
    }

    // Stampo il nome del primo vincitore
    stampaNomeGiocatoreColore(giocatori, personaggi);
    // Se non ci sono altri vincitori, il verbo è al singolare
    if(giocatori->prossimo == NULL)
        printf(" ha vinto!\n");
    // Altrimenti, stampo "e" e le virgole, e il verbo è al plurale
    else{
        while(giocatori->prossimo != NULL){
            giocatori = giocatori->prossimo;
            // Se sto per stampare l'ultimo, stampo "e", altrimenti una virgola.
            if(giocatori->prossimo == NULL)
                printf("e ");
            else
                printf(", ");
            stampaNomeGiocatoreColore(giocatori, personaggi);
        }
        printf(" hanno vinto!\n");
    }
}

/**
 * Stampa nome e punteggio provvisorio di ciascun giocatore
 * @param giocatori Puntatore al primo giocatore
 * @param punteggi Array dei punteggi provvisori
 * @param personaggi Array dei personaggi (serve per i colori)
 */
void stampaGiocatori(Giocatore* giocatori, Punteggio punteggi[], Personaggio personaggi[N_PERSONAGGI]){
    for(int i=1; giocatori!=NULL; i++, giocatori=giocatori->prossimo){
        coloreGiocatore(giocatori, personaggi);
        printf("%d: %s \t (%d CFU)\n" RESET, i, giocatori->nomeUtente, punteggi[i-1].totale);
    }
}