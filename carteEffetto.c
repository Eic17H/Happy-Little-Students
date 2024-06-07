#include "carteCfu.h"
#include "carteEffetto.h"

/**
 * Stampa la descrizione dell'effetto di una carta cfu
 * @param carta La carta
 */
void stampaEffetto(CartaCfu carta){
    switch(carta.effetto){
        case NESSUNO:
            printf("Nessun effetto.\n");
            break;
        case SCARTAP:
            printf("Scarta una" YEL " carta CFU punto " RESET "e aggiungi il suo punteggio a quello del turno.\n");
            break;
        case RUBA:
            printf("Guarda la mano di un collega e ruba una carta a scelta.\n");
            break;
        case SCAMBIADS:
            printf("Scambia questa carta con quella di un altro giocatore, purche' senza effetto.\n");
            break;
        case SCARTAE:
            printf("Scarta una" YEL " carta CFU punto " RESET "con" CYN " effetto " RESET "e aggiungi il suo punteggio a quello del turno.\n");
            break;
        case SCARTAC:
            printf("Scarta da uno a tre carte dalla tua mano.\n");
            break;
        case SCAMBIAP:
            printf("Scambia il punteggio del turno maggiore e minore dopo il calcolo del punteggio di base.\n");
            break;
        case DOPPIOE:
            printf("Raddoppia gli" CYN " effetti " RESET "delle carte che aumentano o diminuiscono il punteggio (per tutti).\n");
            break;
        case SBIRCIA:
            printf("Guarda due carte in cima al mazzo, prendine una e scarta l'altra.\n");
            break;
        case SCAMBIAC:
            printf("Scambia la carta punto giocata nel turno da un giocatore G1 con quella di un giocatore G2, con G1 e G2 scelti dal giocatore che ha giocato la carta.\n");
            break;
        case ANNULLA:
            printf("Annulla gli" CYN " effetti " RESET "di tutte le carte punto durante il turno.\n");
            break;
        case AUMENTA:
            printf("Aumenta di 2" YEL " CFU " RESET "il punteggio del turno di un giocatore a scelta.\n");
            break;
        case DIMINUISCI:
            printf("Diminuisci di 2" YEL " CFU " RESET "il punteggio del turno di un giocatore a scelta.\n");
            break;
        case INVERTI:
            printf("Inverti punteggio minimo e massimo del turno.\n");
            break;
        case SALVA:
            printf("Metti la carta" RED " Ostacolo " RESET "che stai per prendere in fondo al mazzo.\n");
            break;
        case DIROTTA:
            printf("Dai la carta" RED " Ostacolo " RESET "che stai per prendere ad un altro giocatore a tua scelta.\n");
            break;
        default:
            break;
    }
}

/**
 * Usa l'effetto di una carta cfu
 * @param carta La carta
 */
void
usaEffetto(CartaCfu carta, Giocatore *giocatore, Punteggio *punteggio, CartaCfu **scarti, Personaggio personaggi[4], Giocatore **giocatori, int nGiocatori, int *moltiplicatoreAumenta){
    switch(carta.effetto){
        case NESSUNO:
            debug("NESSUN EFFETTO\n");
            break;
        case SCARTAP:
            scartaPE(giocatore, punteggio, scarti, false);
            break;
        case RUBA:
            ruba(giocatori, giocatore, personaggi, nGiocatori);
            break;
        case SCAMBIADS:
            scambiaDS();
            break;
        case SCARTAE:
            scartaPE(giocatore, punteggio, scarti, true);
            break;
        case SCARTAC:
            scartaC();
            break;
        case SCAMBIAP:
            scambiaP();
            break;
        case DOPPIOE:
            doppioE();
            break;
        case SBIRCIA:
            sbircia();
            break;
        case SCAMBIAC:
            scambiaC();
            break;
        case ANNULLA:
            annulla();
            break;
        case AUMENTA:
            aumenta();
            break;
        case DIMINUISCI:
            diminuisci();
            break;
        case INVERTI:
            inverti();
            break;
        case SALVA:
            salva();
            break;
        case DIROTTA:
            dirotta();
            break;
        default:
            break;
    }
}

/**
 * Scarta una carta CFU punto e aggiungi il suo punteggio a quello del turno
 * @param giocatore Il giocatore che ha giocato la carta
 * @param punteggio Puntatore al punteggio del giocatore
 * @param scarti Puntatore alla pila degli scarti
 * @param soloEffetto Vero se sono permesse solo le carte con un effetto, falso altrimenti
 */
void scartaPE(Giocatore *giocatore, Punteggio *punteggio, CartaCfu **scarti, bool soloEffetto) {
    debug("scartaPE()\n");
    CartaCfu* carta = daiCarta(giocatore, selezionaCarta(giocatore, false, true, !soloEffetto));
    punteggio->carta += carta->cfu;
    cartaNegliScarti(scarti, carta);
    return;
}

/**
 * Scambia questa carta con quella di un altro giocatore, purché senza effetto
 * @param giocatori Puntatore alla lista di giocatori
 * @param giocatore Giocatore che sta rubando
 * @param personaggi Array dei personaggi
 * @param nGiocatori Numero corrente di giocatori
 */
void ruba(Giocatore **giocatori, Giocatore *giocatore, Personaggio personaggi[N_PERSONAGGI], int nGiocatori){
    debug("ruba()\n");
    int scelta = 0;

    // Un array contenente gli avversari
    Giocatore* avversari[nGiocatori - 1];
    Giocatore* cerca = *giocatori;
    for(int i=0; i<nGiocatori-1; i++){
        if(cerca != giocatore)
            avversari[i] = cerca;
    }

    // Si mostrano gli avversari
    coloreGiocatore(giocatore, personaggi);
    printf("%s" RESET ", seleziona un avversario a cui rubare una carta:\n", giocatore->nomeUtente);
    for(int i=0; i<nGiocatori-1; i++){
        coloreGiocatore(avversari[i], personaggi);
        printf("\t%d: %s\n", i+1, avversari[i]->nomeUtente);
    }

    // Selezione dell'avversario
    coloreGiocatore(giocatore, personaggi);
    scanf("%d", &scelta);
    printf(RESET);
    scelta--;

    // Il giocatore seleziona e prende una carta qualunque dalla mano dell'avversario scelto
    prendiCarta(giocatore, daiCarta(avversari[scelta], selezionaCarta(avversari[scelta], true, true, true)));
    return;
}
void scambiaDS(){
    debug("scambiaDS()\n");
    return;
}
void scartaC(){
    debug("scartaC()\n");
    return;
}
void scambiaP(){
    debug("scambiaP()\n");
    return;
}
void doppioE(){
    debug("doppioE()\n");
    return;
}
void sbircia(){
    debug("sbircia()\n");
    return;
}
void scambiaC(){
    debug("scambiaC()\n");
    return;
}
void annulla(){
    debug("annulla()\n");
    return;
}
void aumenta(){
    debug("aumenta()\n");
    return;
}
void diminuisci(){
    debug("diminuisci()\n");
    return;
}
void inverti(){
    debug("inverti()\n");
    return;
}
void salva(){
    debug("salva()\n");
    return;
}
void dirotta(){
    debug("dirotta()\n");
    return;
}

/**
 * Ordina le coppie giocatore-carta per eseguire gli effetti in ordine
 * Selection sort in ordine decrescente di CFU
 * @param nGiocatori Il numero corrente di giocatori
 * @param effetti L'array di coppie giocatore-carta
 */
void ordinaEffetti(int nGiocatori, GiocatoreCarta effetti[nGiocatori]){
    if(nGiocatori == 1)
        return;
    int min = 0;
    for(int i=1; i<nGiocatori; i++)
        if(effetti[i].carta.cfu < effetti[min].carta.cfu)
            min = i;
    scambiaEffetti(&effetti[nGiocatori-1], &effetti[min]);
    ordinaEffetti(nGiocatori-1, effetti);
}

/**
 * Scambia due coppie giocatore-carta
 */
void scambiaEffetti(GiocatoreCarta* a, GiocatoreCarta* b){
    GiocatoreCarta temp = *a;
    *a = *b;
    *b = temp;
}