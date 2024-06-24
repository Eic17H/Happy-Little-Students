#include "carteCfu.h"
#include "carteEffetto.h"

/**
 * Stampa la descrizione dell'effetto di una carta cfu
 * @param carta La carta
 */
void stampaEffetto(CartaCfu carta){
    debug("\t\tstampaEffetto()\n");
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

// TODO: passa tutti i punteggi

/**
 * Usa l'effetto di una carta cfu
 * @param carta La carta
 */
void
usaEffetto(CartaCfu carta, Giocatore *giocatore, Punteggio *punteggio, CartaCfu **scarti, Personaggio personaggi[4],
           Giocatore **giocatori, int nGiocatori, int *moltiplicatoreAumenta, int indice,
           Punteggio punteggi[nGiocatori], CartaCfu**mazzo) {
    debug("\t\tusaEffetto()\n");
    coloreGiocatore(giocatore, personaggi);
    printf("\nSi attiva l'effetto della carta di %s!\n" RESET, giocatore->nomeUtente);
    stampaEffetto(carta);
    printf("\n");
    switch(carta.effetto){
        case NESSUNO:
            debug("\t\tNESSUN EFFETTO\n");
            break;
        case SCARTAP:
            logEffettoCarta(*giocatore, carta, "SCARTAP");
            scartaPE(giocatore, punteggio, scarti, false);
            break;
        case RUBA:
            logEffettoCarta(*giocatore, carta, "RUBA");
            ruba(giocatori, giocatore, personaggi, nGiocatori);
            break;
        case SCAMBIADS: // TODO
            logEffettoCarta(*giocatore, carta, "SCAMBIADS");
            scambiaDS(giocatori, giocatore, personaggi, nGiocatori);
            break;
        case SCARTAE:
            logEffettoCarta(*giocatore, carta, "SCARTAE");
            scartaPE(giocatore, punteggio, scarti, true);
            break;
        case SCARTAC:
            logEffettoCarta(*giocatore, carta, "SCARTAC");
            scartaC(giocatore, scarti);
            break;
        case SCAMBIAP:
            logEffettoCarta(*giocatore, carta, "SCAMBIAP");
            scambiaP(nGiocatori, punteggi, *moltiplicatoreAumenta);
            break;
        case DOPPIOE:
            logEffettoCarta(*giocatore, carta, "DOPPIOE");
            doppioE(moltiplicatoreAumenta);
            break;
        case SBIRCIA:
            logEffettoCarta(*giocatore, carta, "SBIRCIA");
            sbircia(giocatore, mazzo, scarti);
            break;
        case SCAMBIAC: // TODO
            logEffettoCarta(*giocatore, carta, "SCAMBIAC");
            scambiaC();
            break;
        case ANNULLA:
            logEffettoCarta(*giocatore, carta, "ANNULLA");
            annulla();
            break;
        case AUMENTA:
            logEffettoCarta(*giocatore, carta, "AUMENTA");
            aumentaDiminuisci(giocatore, giocatori, 1, personaggi, punteggi, *moltiplicatoreAumenta);
            break;
        case DIMINUISCI:
            logEffettoCarta(*giocatore, carta, "DIMINUISCI");
            aumentaDiminuisci(giocatore, giocatori, -1, personaggi, punteggi, *moltiplicatoreAumenta);
            break;
        case INVERTI:
            logEffettoCarta(*giocatore, carta, "INVERTI");
            inverti(nGiocatori, punteggi, *moltiplicatoreAumenta);
            break;
        case SALVA: // TODO
            logEffettoCarta(*giocatore, carta, "SALVA");
            //salva();
            break;
        case DIROTTA: // TODO
            logEffettoCarta(*giocatore, carta, "DIROTTA");
            //dirotta();
            break;
        default:
            break;
    }

    // TODO: spostare
    int i;
    Giocatore* giocatoreCerca;
    printf(RESET "\nSituazione provvisoria:\n");
    for(i=1, giocatoreCerca = *giocatori; giocatoreCerca != NULL; i++, giocatoreCerca = giocatoreCerca->prossimo){
        calcolaPunteggio(&punteggi[i-1], *moltiplicatoreAumenta);
        coloreGiocatore(giocatoreCerca, personaggi);
        printf("%d: %s (%d CFU)\n" RESET, i, giocatoreCerca->nomeUtente, punteggi[i-1].totale);
    }
    printf("\n");
}

/**
 * Scarta una carta CFU punto e aggiungi il suo punteggio a quello del turno
 * @param giocatore Il giocatore che ha giocato la carta
 * @param punteggio Puntatore al punteggio del giocatore
 * @param scarti Puntatore alla pila degli scarti
 * @param soloEffetto Vero se sono permesse solo le carte con un effetto, falso altrimenti
 */
void scartaPE(Giocatore *giocatore, Punteggio *punteggio, CartaCfu **scarti, bool soloEffetto) {
    debug("\t\tscartaPE()\n");
    CartaCfu* carta = daiCarta(giocatore, selezionaCarta(giocatore, false, true, !soloEffetto, false));
    punteggio->carta += carta->cfu;
    cartaNegliScarti(scarti, carta);
}

/**
 * Guarda la mano di un collega e ruba una carta a scelta.
 * @param giocatori Puntatore alla lista di giocatori
 * @param giocatore Giocatore che sta rubando
 * @param personaggi Array dei personaggi
 * @param nGiocatori Numero corrente di giocatori
 */
void ruba(Giocatore **giocatori, Giocatore *giocatore, Personaggio personaggi[N_PERSONAGGI], int nGiocatori){
    debug("\t\truba()\n");

    // Si seleziona un avversario
    printf("Seleziona un avversario a cui rubare una carta:\n");
    Giocatore* avversario = selezionaAvversario(giocatori, giocatore, personaggi, nGiocatori);

    CartaCfu* carta = selezionaCarta(avversario, true, true, true, false);
    logRuba(*giocatore, *avversario, *carta);

    // Il giocatore seleziona e prende una carta qualunque dalla mano dell'avversario scelto
    prendiCarta(giocatore, daiCarta(avversario, carta));
}

/**
 * Scambia questa carta con quella di un altro giocatore, purché senza effetto
 */
void scambiaDS(Giocatore** giocatori, Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI], int nGiocatori){
    debug("\t\tscambiaDS()\n");
    return;

    // Seleziona un avver-
    // TODO: rifare, questo è praticamente inutile
    Giocatore* avversario = selezionaAvversario(giocatori, giocatore, personaggi, nGiocatori);


    CartaCfu* carta = selezionaCarta(avversario, true, true, true, false);
}

Giocatore* selezionaAvversario(Giocatore** giocatori, Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI], int nGiocatori){

    Giocatore* avversari[nGiocatori - 1];
    arrayAvversari(giocatori, giocatore, nGiocatori, avversari);

    int scelta = 0;
    coloreGiocatore(giocatore, personaggi);
    for(int i=0; i<nGiocatori-1; i++){
        coloreGiocatore(avversari[i], personaggi);
        printf("\t%d: %s\n", i+1, avversari[i]->nomeUtente);
    }
    scanf("%d", &scelta);
    while(scelta<1 || scelta>nGiocatori-1){
        printf("Seleziona un numero tra 1 e %d.\n", nGiocatori-1);
        scanf("%d", &scelta);
    }
    printf(RESET);
    return avversari[scelta-1];
}

void arrayAvversari(Giocatore** giocatori, Giocatore* giocatore, int nGiocatori, Giocatore* avversari[nGiocatori-1]){
    Giocatore* cerca = *giocatori;
    for(int i=0; i<nGiocatori-1; i++){
        if(cerca != giocatore)
            avversari[i] = cerca;
        else
            i--;
        cerca = cerca->prossimo;
    }
}

// TODO: più bello
void scartaC(Giocatore *giocatore, CartaCfu** scarti) {
    debug("\t\tscartaC()\n");
    const int nCarte = 3;
    CartaCfu* carta;
    char continua='1';
    // va avanti per 3 carte o finché non decide di smettere. può annullare l'azione
    for(int i=0; i<nCarte && continua!='0'; i++){
        carta = daiCarta(giocatore, selezionaCarta(giocatore, true, true, true, true));
        if(carta==NULL){
            i--;
            printf("Vuoi terminare l'effetto?\n0 per no, qualunque altro tasto per sì\n");
            scanf("%c", &continua);
            getchar();
        }else
        {
            cartaNegliScarti(scarti, carta);
        if(i<nCarte-1){
            printf("Vuoi scartare un'altra carta?\n0 per no, qualunque altro tasto per sì\n");
            scanf("%c", &continua);
            getchar();
        }}
    }
}

void scambiaP(int nGiocatori, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta){
    debug("\t\tscambiaP()\n");
    int i, min=0, max=0;

    // Si trovano il punteggio minimo e il punteggio massimo
    for(i=0; i<nGiocatori; i++){
        calcolaPunteggio(&punteggi[i], moltiplicatoreAumenta);
        if(punteggi[i].totale > punteggi[max].totale)
            max=i;
        if(punteggi[i].totale < punteggi[min].totale)
            min=i;
    }

    // Si scambiano tutti i campi, per evitare che l'effetto si annulli quando vengono ricalcolati i punteggi
    scambiaPunteggi(&punteggi[min], &punteggi[max]);
}

void scambiaPunteggi(Punteggio*a, Punteggio*b){
    Punteggio temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Raddoppia il valore del moltiplicatore degli aumenta/diminuisci punteggio
 * @param moltiplicatoreAumenta Puntatore al moltiplicatore
 */
void doppioE(int *moltiplicatoreAumenta){
    if(moltiplicatoreAumenta == NULL)
        return;
    debug("\t\tdoppioE()\n");
    *moltiplicatoreAumenta *= 2;
}


// TODO: mi sa che non si attiva se c'è uno spareggio
void sbircia(Giocatore *giocatore, CartaCfu **mazzo, CartaCfu **scarti) {
    debug("\t\tsbircia()\n");
    const int nCarte=2;
    CartaCfu* carte[nCarte];

    // Si pescano le carte, si mettono nell'array e si stampano
    for(int i=0; i<nCarte; i++){
        carte[i] = cartaDalMazzo(mazzo, scarti);
        printf("%d:\t%s (%d CFU)\n\t", i+1, carte[i]->nome, carte[i]->cfu);
        stampaEffetto(*carte[i]);
    }

    // Input
    printf("Scegline una: ");
    int scelta;
    scanf("%d", &scelta);
    while(scelta<1 || scelta>nCarte){
        printf("Immetti un numero tra 1 e %d\n", nCarte);
        scanf("%d", &scelta);
    }

    // Si pesca la carta selezionata
    prendiCarta(giocatore, carte[scelta-1]);

    // Le altre carte si scartano
    for(int i=0; i<nCarte; i++){
        if(i != scelta-1)
            cartaNegliScarti(scarti, carte[i]);
    }
}

void scambiaC(){
    debug("\t\tscambiaC()\n");
    //stampaAvversari()
    //selezionaAvversario()
    //selezionaAvversario()
    // temp = c1 = c2 = temp;
}

void annulla(){
    debug("\t\tannulla()\n");
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
void aumentaDiminuisci(Giocatore*giocante, Giocatore **giocatori, int valore, Personaggio personaggi[N_PERSONAGGI], Punteggio punteggi[], int moltiplicatore) {
    debug("\t\taumenta()\n");
    Giocatore* giocatore;
    int i, scelta;

    // TODO: fare questo con una funzione
    // Si stampano tutti i giocatori
    for(i=1, giocatore = *giocatori; giocatore != NULL; i++, giocatore = giocatore->prossimo){
        calcolaPunteggio(&punteggi[i-1], moltiplicatore);
        coloreGiocatore(giocatore, personaggi);
        printf("%d: %s (%d CFU)\n" RESET, i, giocatore->nomeUtente, punteggi[i-1].totale);
    }

    // Input
    coloreGiocatore(giocante, personaggi);
    printf("Seleziona un giocatore:\n");
    scanf("%d", &scelta);

    // Si applica l'effetto sul punteggio del giocatore scelto e si ricalcola
    punteggi[scelta-1].aumenta += valore;
    calcolaPunteggio(&punteggi[scelta-1], moltiplicatore);
}

/**
 * Scambia il punteggio totale minore e quello maggiore
 * @param nGiocatori
 * @param punteggi
 * @param moltiplicatoreAumenta
 */
void inverti(int nGiocatori, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta) {
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
    devePescare = false;
}

// TODO: è orrenda
void dirotta(Giocatore** giocatori, Giocatore* giocatore, int nGiocatori, Personaggio personaggi[N_PERSONAGGI], CartaOstacolo** ostacoli, bool*devePescare){
    debug("\t\tdirotta()\n");
    devePescare = false;
    Giocatore*vittima = selezionaAvversario(giocatori, giocatore, personaggi, nGiocatori);
    pescaOstacolo(vittima, ostacoli);
}

/**
 * Ordina un array di indici, sulla base dei CFU della carta associata
 * Selection sort in ordine decrescente
 * @param nGiocatori Il numero corrente di giocatori
 * @param effetti L'array di coppie giocatore-carta
 */
void ordinaEffetti(int nGiocatori, int ordine[nGiocatori], CartaCfu carte[nGiocatori]){
    debug("\t\tordinaEffetti()\n");
    if(nGiocatori == 1)
        return;
    int min = 0;

    // Se c'è un effetto da attivare alla fine del turno, si mette l'effetto alla fine e lo si esclude dall'ordinamento
    bool fineTurno = false;
    for(int i=1; i<nGiocatori && !fineTurno; i++)
        if(carte[ordine[i]].effetto == SCAMBIAP){
            fineTurno = true;
            scambiaInt(&ordine[nGiocatori - 1], &ordine[i]);
        }

    // Se non c'è, si ordinano normalmente
    if(!fineTurno){
        for(int i=1; i<nGiocatori; i++)
            if(carte[ordine[i]].cfu < carte[ordine[min]].cfu)
                min = i;
        scambiaInt(&ordine[nGiocatori-1], &ordine[min]);
    }
    ordinaEffetti(nGiocatori - 1, ordine, carte);
}

bool controllaAnnulla(int nGiocatori, CartaCfu carte[nGiocatori]){
    debug("\t\tcontrollaAnnulla()\n");
    // TODO: stampa nome giocatore
    for(int i=0; i<nGiocatori; i++)
        if(carte[i].effetto == ANNULLA)
            return true;
    return false;
}