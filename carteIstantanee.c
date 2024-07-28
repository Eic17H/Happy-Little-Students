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
        case SALVA:
        case DIROTTA:
            coloreProblema();
            printf("Questa carta si puo' usare solo quando stai per pescare una carta ostacolo.\n\n\n" RESET);
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

    int i;
    int scelta;

    // Si stampano tutti i giocatori
    for(i=0; i<nGiocatori; i++){
        calcolaPunteggio(&punteggi[i], moltiplicatore);
        coloreGiocatore(giocatori[i], personaggi);
        printf("%d: %s (%d CFU)\n" RESET, i+1, giocatori[i]->nomeUtente, punteggi[i].totale);
    }

    // Input
    coloreGiocatore(giocatori[indice], personaggi);
    printf("Seleziona un giocatore:\n");
    scelta = inputCifra()-1;
    while(scelta<0 || scelta>nGiocatori){
        coloreErrore();
        printf("Seleziona un giocatore!!\n" RESET);
        coloreGiocatore(giocatori[indice], personaggi);
        scelta = inputCifra()-1;
    }
    printf(RESET);

    // Si applica l'effetto sul punteggio del giocatore scelto e si ricalcola
    logAumentaDiminuisci(*giocatori[indice], *giocatori[scelta], valore);
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

/**
 * Permette di giocare una carta Salva o una carta Dirotta
 * @param nGiocatori Il numero corrente di giocatori
 * @param giocatori Puntatore al primo giocatore nella lista
 * @param sconfitto Il giocatore che deve salvarsi
 * @param personaggi
 */
void salvaDirotta(int nGiocatori, Giocatore* giocatori, Giocatore** sconfitto, Personaggio personaggi[N_PERSONAGGI]){
    CartaCfu *salva=NULL, *dirotta=NULL, *carta=NULL;
    Giocatore *vittima=NULL;
    int scelta=-1;

    // Si trovano la carta annulla e la carta dirotta, se esistono
    for(carta=(*sconfitto)->primaCfu; carta!=NULL; carta=carta->prossima){
        if(carta->effetto == SALVA)
            salva = carta;
        if(carta->effetto == DIROTTA)
            dirotta = carta;
    }

    // Se non ha nessuna delle due carte, non può fare niente
    if(salva == NULL && dirotta == NULL)
        return;

    stampaNomeGiocatoreColore(*sconfitto, personaggi);
    printf(", hai perso il turno");

    // Se ci sono entrambe, ha due opzioni
    if(salva!=NULL && dirotta!=NULL){
        printf(", ma puoi usare %s per rimettere l'ostacolo nel mazzo, o %s per darlo a un altro giocatore!\n", salva->nome, dirotta->nome);
        printf("0: Pesca l'ostacolo\n1: Salva\n2: Dirotta\n");
        printf("Seleziona: ");
        scelta = inputCifra();
        while(scelta<0 || scelta>2){
            printf("Seleziona un'opzione\n");
            printf("Seleziona: ");
            scelta = inputCifra();
        }
    }else if(salva!=NULL){
        printf(", ma puoi usare %s per rimettere l'ostacolo nel mazzo!\n", salva->nome);
        printf("0: Pesca l'ostacolo\n1: Salva\n");
        printf("Seleziona: ");
        scelta = inputCifra();
        while(scelta<0 || scelta>1){
            printf("Seleziona un'opzione\n");
            printf("Seleziona: ");
            scelta = inputCifra();
        }
    }else if(dirotta!=NULL){
        printf(", ma puoi usare %s per dare l'ostacolo a un altro giocatore!\n", dirotta->nome);
        printf("0: Pesca l'ostacolo\n1: Dirotta\n");
        printf("Seleziona: ");
        scelta = inputCifra();
        while(scelta<0 || scelta>1){
            printf("Seleziona un'opzione\n");
            printf("Seleziona: ");
            scelta = inputCifra();
        }
        // L'input per dirotta in questo caso è 1, ma il valore deve essere comunque 2
        if(scelta==1)
            scelta = 2;
    }

    switch(scelta){
        case 1:
            logSalva(**sconfitto, *salva);
            *sconfitto = NULL;
            break;
        case 2:
            vittima = selezionaAvversario(giocatori, *sconfitto, personaggi, nGiocatori);
            logDirotta(**sconfitto, *dirotta, *vittima);
            *sconfitto = vittima;
            break;
        default:
            break;
    }
}