#include "carteCfu.h"
#include "carteEffetto.h"
#include "interfaccia.h"

/**
 * Stampa le informazioni di una carta cfu (nome, valore, effetto)
 * @param carta
 */
void stampaCfu(CartaCfu carta){
    stampaNomeCfu(carta);
    stampaEffetto(carta);
}

/**
 * Stampa il nome e il valore (se applicabile) di una carta cfu
 * @param carta
 */
void stampaNomeCfu(CartaCfu carta){
    if(carta.effetto<PRIMA_ISTANTANEA)
        printf("%s (%d CFU)\n", carta.nome, carta.cfu);
    else
        printf("%s (istantanea)\n", carta.nome);
}

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
    printf("\n");
}

/**
 * Usa l'effetto di una carta cfu
 * @param carta La carta
 */
void usaEffetto(int nGiocatori, CartaCfu carte[nGiocatori], Giocatore* arrayGiocatori[nGiocatori], Giocatore** giocatori, Punteggio punteggi[nGiocatori], int indice, CartaCfu** mazzo, CartaCfu** scarti, Personaggio personaggi[N_PERSONAGGI], int* moltiplicatoreAumenta){

    coloreGiocatore(arrayGiocatori[indice], personaggi);
    printf("\nSi attiva l'effetto della carta di %s!\n" RESET, arrayGiocatori[indice]->nomeUtente);
    stampaEffetto(carte[indice]);
    printf("\n");
    switch(carte[indice].effetto){
        case NESSUNO:
            break;
        case SCARTAP:
            logEffettoCarta(*arrayGiocatori[indice], carte[indice], "SCARTAP");
            scartaPE(arrayGiocatori[indice], &punteggi[indice], scarti, false);
            break;
        case RUBA:
            logEffettoCarta(*arrayGiocatori[indice], carte[indice], "RUBA");
            ruba(giocatori, arrayGiocatori[indice], personaggi, nGiocatori);
            break;
        case SCAMBIADS:
            logEffettoCarta(*arrayGiocatori[indice], carte[indice], "SCAMBIADS");
            scambiaDS(giocatori, carte, arrayGiocatori[indice], personaggi, nGiocatori, punteggi);
            break;
        case SCARTAE:
            logEffettoCarta(*arrayGiocatori[indice], carte[indice], "SCARTAE");
            scartaPE(arrayGiocatori[indice], &punteggi[indice], scarti, true);
            break;
        case SCARTAC:
            logEffettoCarta(*arrayGiocatori[indice], carte[indice], "SCARTAC");
            scartaC(arrayGiocatori[indice], scarti);
            break;
        case SCAMBIAP:
            logEffettoCarta(*arrayGiocatori[indice], carte[indice], "SCAMBIAP");
            scambiaP(nGiocatori, punteggi, *moltiplicatoreAumenta);
            break;
        case DOPPIOE:
            logEffettoCarta(*arrayGiocatori[indice], carte[indice], "DOPPIOE");
            doppioE(moltiplicatoreAumenta);
            break;
        case SBIRCIA:
            logEffettoCarta(*arrayGiocatori[indice], carte[indice], "SBIRCIA");
            sbircia(arrayGiocatori[indice], mazzo, scarti);
            break;
        case SCAMBIAC:
            logEffettoCarta(*arrayGiocatori[indice], carte[indice], "SCAMBIAC");
            scambiaC(nGiocatori, arrayGiocatori, carte, personaggi, indice, punteggi);
            break;
        case ANNULLA:
            logEffettoCarta(*arrayGiocatori[indice], carte[indice], "ANNULLA");
            break;
        default:
            break;
    }
    int i;
    Giocatore* giocatoreCerca;

    // Ogni volta che si attiva un effetto, stampo di nuovo le informazioni aggiornate
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

    CartaCfu* carta = daiCarta(giocatore, selezionaCarta(giocatore, false, true, !soloEffetto, true));
    if(carta != NULL){
        logScarta(*giocatore, *carta);
        punteggio->carta += carta->cfu;
        cartaNegliScarti(scarti, carta);
    }
}

/**
 * Guarda la mano di un collega e ruba una carta a scelta.
 * @param giocatori Puntatore alla lista di giocatori
 * @param giocatore Giocatore che sta rubando
 * @param personaggi Array dei personaggi
 * @param nGiocatori Numero corrente di giocatori
 */
void ruba(Giocatore **giocatori, Giocatore *giocatore, Personaggio personaggi[N_PERSONAGGI], int nGiocatori){

    // Si seleziona un avversario
    printf("Seleziona un avversario a cui rubare una carta:\n");
    Giocatore* avversario = selezionaAvversario(*giocatori, giocatore, personaggi, nGiocatori);

    CartaCfu* carta = selezionaCarta(avversario, true, true, true, false);
    logRuba(*giocatore, *avversario, *carta);

    // Il giocatore seleziona e prende una carta qualunque dalla mano dell'avversario scelto
    prendiCarta(giocatore, daiCarta(avversario, carta));
}

/**
 * Scambia questa carta con quella di un altro giocatore, purché senza effetto
 * @param giocatori Puntatore alla lista di giocatori
 * @param carte Array delle carte appena giocate
 * @param giocante Giocatore che ha attivato l'effetto
 * @param personaggi Array dei personaggi (serve per i colori)
 * @param nGiocatori Numero corrente di giocatori
 */
void scambiaDS(Giocatore** giocatori, CartaCfu carte[], Giocatore* giocante, Personaggio personaggi[N_PERSONAGGI], int nGiocatori, Punteggio punteggi[nGiocatori]){

    int scelta = -1;
    int indice = -1;
    // i si usa per scorrere l'array, j per il codice dell'input
    int i=0, j=1;
    Giocatore* giocatore = *giocatori;

    // Si stampano le informazioni di tutti gli avversari e delle loro carte
    for(i=0, j=1, giocatore=*giocatori; giocatore != NULL; i++, giocatore = giocatore->prossimo){
        if(giocatore != giocante){
            coloreGiocatore(giocatore, personaggi);
            printf("%d: %32s - %32s (%2d CFU) %c\n" RESET, j, giocatore->nomeUtente, carte[i].nome, carte[i].cfu, cartaSpeciale(carte[i]));
            j++;
        }else{
            // Sapere la posizione del giocatore serve poi per sapere dove si salta un numero
            indice = i;
        }
    }
    printf("0 per annullare\n");
    printf("Seleziona: ");
    scelta = inputCifra()-1;

    // Un input di 0 diventa un valore di -1, quindi non si fa più nulla
    if(scelta == -1)
        return;

    // Nell'input salto il giocatore, quindi, rispetto all'array, dopo il giocatore c'è un offset di 1
    if(scelta >= indice)
        scelta++;

    // L'input è invalido se si seleziona un numero negativo, un giocatore che non esiste, o una carta senza effetto
    while(scelta<0 || scelta>nGiocatori-1 || carte[scelta].effetto!=NESSUNO){
        printf("Riseleziona: ");
        scelta = inputCifra()-1;
        if(scelta >= indice)
            scelta++;
    }

    // Si scambiano le carte e i loro contributi ai punteggi
    scambiaCarte(&carte[indice], &carte[scelta]);
    scambiaInt(&(punteggi[indice].carta), &(punteggi[scelta].carta));
}

/**
 * Permette a un giocatore di selezionare uno degli avversari
 * @param giocatori Primo giocatore nella lista
 * @param giocatore Giocatore che deve selezionare (da escludere dalla lista)
 * @param personaggi Array dei personaggi (per i colori)
 * @param nGiocatori Numero corrente di giocatori
 * @return Il giocatore selezionato
 */
Giocatore* selezionaAvversario(Giocatore* giocatori, Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI], int nGiocatori){
    int scelta = -1;
    int indice = -1;
    int i=0;
    Giocatore* cerca = giocatori;

    // Si stampano gli avversari
    for(i=1, cerca=giocatori; cerca != NULL; cerca = cerca->prossimo, i++){
        if(cerca != giocatore){
            coloreGiocatore(cerca, personaggi);
            printf("%d: %32s\n" RESET, i, cerca->nomeUtente);
        }else{
            // Si salta il giocatore, e tornando indietro si evita che l'input salti un numero
            // Sapere la posizione del giocatore serve poi per sapere dove si salta un numero
            indice = i;
            i--;
        }
    }
    printf("Seleziona: ");
    scelta = inputCifra();

    // L'input è invalido se si seleziona un numero negativo o un giocatore che non esiste
    while(scelta<1 || scelta>nGiocatori-1){
        printf("Riseleziona: ");
        scelta = inputCifra();
    }

    // Nell'input salto il giocatore, quindi, rispetto alla lista, dal giocatore in poi c'è un offset di 1
    if(scelta >= indice)
        scelta++;

    // Scorro finché cerca non è l'i-esimo avversario
    for(i=1, cerca=giocatori; i<scelta; i++, cerca=cerca->prossimo);
    return cerca;
}

/**
 * Scarta da uno a tre carte dalla tua mano
 * @param giocatore Il giocatore che ha attivato l'effetto
 * @param scarti Puntatore alla pila degli scarti
 */
void scartaC(Giocatore *giocatore, CartaCfu** scarti) {

    const int nCarte = 3;
    CartaCfu* carta;
    int finito=0;

    // Va avanti per 3 carte o finché non decide di smettere. Può annullare l'azione
    for(int i=0; i<nCarte && finito!=1; i++){
        carta = daiCarta(giocatore, selezionaCarta(giocatore, true, true, true, true));
        logScarta(*giocatore, *carta);
        // Se la carta è NULL, vuole dire che ha scelto annulla, quindi si chiede conferma
        if(carta==NULL){
            i--;
            printf("Vuoi terminare l'effetto?\n1 per si', qualunque altro tasto per no\n");
            finito = inputCifra();
        }else
            cartaNegliScarti(scarti, carta);
    }
}

void scambiaP(int nGiocatori, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta){

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
    *moltiplicatoreAumenta *= 2;
}

/**
 * Guarda due carte in cima al mazzo, prendine una e scarta l’altra
 * @param giocatore Il giocatore che ha attivato l'effetto
 * @param mazzo Puntatore al mazzo delle carte CFU da pescare
 * @param scarti Puntatore al mazzo degli scarti delle carte CFU
 */
void sbircia(Giocatore *giocatore, CartaCfu **mazzo, CartaCfu **scarti) {

    const int nCarte=2;
    CartaCfu* carte[nCarte];

    // Si pescano le carte, si mettono nell'array e si stampano
    for(int i=0; i<nCarte; i++){
        carte[i] = cartaDalMazzo(mazzo, scarti);
        printf("%d: ", i+1);
        stampaCfu(*carte[i]);
    }

    // Input
    printf("Scegline una: ");
    int scelta;
    scelta = inputCifra();
    while(scelta<1 || scelta>nCarte){
        printf("Immetti un numero tra 1 e %d\n", nCarte);
        scelta = inputCifra();
    }

    // Si pesca la carta selezionata
    logPescaCfu(*giocatore, *carte[scelta-1]);
    prendiCarta(giocatore, carte[scelta-1]);

    // Le altre carte si scartano
    for(int i=0; i<nCarte; i++){
        if(i != scelta-1)
            cartaNegliScarti(scarti, carte[i]);
    }
}

/**
 * Scambia la carta punto giocata nel turno da un giocatore G1 con quella di un giocatore G2, con G1 e G2 scelti dal giocatore che ha giocato la carta SCAMBIAC
 * @param nGiocatori Il numero corrente di giocatori
 * @param giocatori L'array dei giocatori correnti
 * @param carte Le carte cfu punto giocate in questo turno
 * @param personaggi L'array dei personaggi (serve per i colori)
 * @param indice L'indice del giocatore che ha giocato la carta SCAMBIAC
 */
void scambiaC(int nGiocatori, Giocatore* giocatori[nGiocatori], CartaCfu carte[nGiocatori], Personaggio personaggi[N_PERSONAGGI], int indice, Punteggio punteggi[nGiocatori]){

    int selezionati[2] = {-1, -1};
    for(int i=0; i<nGiocatori; i++){
        coloreGiocatore(giocatori[i], personaggi);
        printf("%d: %32s - %32s (%2d CFU)\n" RESET, i+1, giocatori[i]->nomeUtente, carte[i].nome, carte[i].cfu);
    }

    for(int i=0; i<2; i++){
        coloreGiocatore(giocatori[indice], personaggi);
        printf("Seleziona il %do giocatore: ", i+1);
        selezionati[i] = inputCifra()-1;
        if(selezionati[i]<0 || selezionati[i]>nGiocatori-1){
            coloreErrore();
            printf("Input invalido\n" RESET);
            i--;
        }
    }
    // Si scambiano le carte e i loro contributi ai punteggi dei giocatori
    scambiaCarte(&carte[selezionati[0]], &carte[selezionati[1]]);
    scambiaInt(&(punteggi[selezionati[0]].carta), &(punteggi[selezionati[1]].carta));

    logScambiaC(*giocatori[indice], *giocatori[selezionati[0]], *giocatori[selezionati[1]], carte[selezionati[0]], carte[selezionati[1]]);
    printf(RESET "Le carte giocate da ");
    stampaNomeGiocatoreColore(giocatori[selezionati[0]], personaggi);
    printf(" e da ");
    stampaNomeGiocatoreColore(giocatori[selezionati[1]], personaggi);
    printf(" sono state scambiate!\n");
}

/**
 * Ordina un array di indici, sulla base dei CFU della carta associata
 * Selection sort in ordine decrescente
 * @param nGiocatori Il numero corrente di giocatori
 * @param effetti L'array di coppie giocatore-carta
 */
void ordinaEffetti(int nGiocatori, int ordine[nGiocatori], CartaCfu carte[nGiocatori]){

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

/**
 * Controlla se qualcuno ha giocato una carta che annulla gli effetti secondari delle altre carte
 * @param nGiocatori Il numero corrente di giocatori
 * @param giocatori Lista dei giocatori (puntatore al primo giocatore)
 * @param carte Array delle carte giocate nella fase cfu di questo turno
 * @param personaggi Array dei personaggi (serve per i colori)
 * @return
 */
bool controllaAnnulla(int nGiocatori, Giocatore* giocatori, CartaCfu carte[nGiocatori], Personaggio personaggi[N_PERSONAGGI]){
    int i=0;
    Giocatore* giocatore = giocatori;
    for(i=0, giocatore = giocatori; i<nGiocatori; i++, giocatore = giocatore->prossimo)
        if(carte[i].effetto == ANNULLA){
            logEffettoCarta(*giocatore, carte[i], "ANNULLA");
            coloreComunicazioni();
            printf("\nLa carta di " RESET);
            stampaNomeGiocatoreColore(giocatore, personaggi);
            coloreComunicazioni();
            printf(" annulla gli effetti secondari di tutte le altre carte!\n\n" RESET);
            return true;
        }
    return false;
}