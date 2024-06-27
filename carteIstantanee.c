//
// Created by eic17 on 27/06/2024.
//

#include "carteIstantanee.h"

void usaIstantanea(CartaCfu carta, int nGiocatori, int indice, Giocatore* arrayGiocatori[nGiocatori], Punteggio punteggi[nGiocatori], Personaggio personaggi[N_PERSONAGGI], int moltiplicatoreAumenta){
    switch(carta.effetto){
        case AUMENTA:
            logEffettoCarta(*arrayGiocatori[indice], carta, "AUMENTA");
            aumentaDiminuisci(nGiocatori, indice, 1, arrayGiocatori, punteggi, personaggi, moltiplicatoreAumenta);
            break;
        case DIMINUISCI:
            logEffettoCarta(*arrayGiocatori[indice], carta, "DIMINUISCI");
            aumentaDiminuisci(nGiocatori, indice, -1, arrayGiocatori, punteggi, personaggi, moltiplicatoreAumenta);
            break;
        case INVERTI:
            logEffettoCarta(*arrayGiocatori[indice], carta, "INVERTI");
            inverti(nGiocatori, punteggi, moltiplicatoreAumenta);
            break;
        default:
            break;
    }
}

/**
 * Aumenta o diminuisce di un certo valore (di default 2) il punteggio del turno di un giocatore a scelta
 * @param giocante Il giocatore che sta attivando l'effetto
 * @param giocatori Puntatore al primo giocatore
 * @param valore Il valore dell'aumento: per le regole del gioco, 1 per AUMENTA e -1 per DIMINUISCI
 * @param personaggi Array dei personaggi (le plance)
 * @param punteggi Array dei punteggi provvisori
 * @param moltiplicatore Il corrente moltiplicatore dell'effetto di AUMENTA e DIMINUISCI
 */
void aumentaDiminuisci(int nGiocatori, int indice, int valore, Giocatore* giocatori[nGiocatori], Punteggio punteggi[nGiocatori], Personaggio personaggi[N_PERSONAGGI], int moltiplicatore){
    debug("\t\taumenta()\n");
    int i;
    char scelta;

    // TODO: fare questo con una funzione
    // Si stampano tutti i giocatori
    for(i=0; i<nGiocatori; i++){
        calcolaPunteggio(&punteggi[i], moltiplicatore);
        coloreGiocatore(giocatori[i], personaggi);
        printf("%d: %s (%d CFU)\n" RESET, i+1, giocatori[i]->nomeUtente, punteggi[i].totale);
    }

    // Input
    coloreGiocatore(giocatori[indice], personaggi);
    printf("Seleziona un giocatore:\n");
    scanf("%c", &scelta);
    scelta -= '1';

    // Si applica l'effetto sul punteggio del giocatore scelto e si ricalcola
    punteggi[scelta].aumenta += valore;
    calcolaPunteggio(&punteggi[scelta], moltiplicatore);
}

/**
 * Scambia il punteggio totale minore e quello maggiore
 * @param nGiocatori
 * @param punteggi
 * @param moltiplicatoreAumenta
 */
void inverti(int nGiocatori, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta){
    debug("\t\tinverti()\n");
    int i, min=0, max=0;

    // Si trovano l'indice del punteggio maggiore e quello del punteggio minore
    for(i=0; i<nGiocatori; i++){
        calcolaPunteggio(&punteggi[i], moltiplicatoreAumenta);
        if(punteggi[i].totale>punteggi[max].totale)
            max = i;
        if(punteggi[i].totale<punteggi[min].totale)
            min = i;
    }

    // Scambia i due punteggi trovati
    scambiaPunteggi(&punteggi[min], &punteggi[max]);
}

// TODO: è orrenda, magari invece cambio l'indirizzo di "sconfitto" nella routine e separo usaEffetto() e usaInst() e se sconfitto==NULL nessuno pesca
void salva(bool* devePescare){
    debug("\t\tsalva()\n");
    *devePescare = false;
}

// TODO: è orrenda
void dirotta(Giocatore** giocatori, Giocatore* giocatore, int nGiocatori, Personaggio personaggi[N_PERSONAGGI], CartaOstacolo** ostacoli, bool*devePescare){
    debug("\t\tdirotta()\n");
    devePescare = false;
    Giocatore*vittima = selezionaAvversario(giocatori, giocatore, personaggi, nGiocatori);
    pescaOstacolo(vittima, ostacoli);
}