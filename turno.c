#include "turno.h"

/** Inizializza i giocatori:
 * nessuna carta CFU,
 * nessuna carta ostacolo,
 * 0 CFU
 * @param giocatori puntatore al primo giocatore
 */
void inizializzaGiocatori(Giocatore* giocatori){
    Giocatore* giocatore = giocatori;
    while(giocatore != NULL){
        giocatore->primaCfu = NULL;
        giocatore->primaOstacolo = NULL;
        giocatore->cfu = 0;
        giocatore = giocatore->prossimo;
    }
}

// TODO: input
void assegnaPersonaggi(Giocatore* giocatori, Personaggio* personaggi){
    Giocatore *giocatore = giocatori;
    int i=0;
    while(giocatore != NULL){
        giocatore->personaggio = personaggi[i];
        giocatore = giocatore->prossimo;
        i++;
    }
}

/**
 * controlla se qualcuno ha vinto
 * @param giocatori puntatore al primo giocatore
 * @return NULL se nessuno ha vinto, il vincitore se qualcuno ha vinto
 */
Giocatore* vince(Giocatore* giocatori){
    // TODO: più vincitori: se qualcuno ha vinto restituisce vero e rimuove tutti i non-vincitori dal gioco
    // se rimane un solo giocatore, ha vinto
    if(giocatori->prossimo == NULL){
        printf("%s e' l'ultimo giocatore rimasto.\n", giocatori->nomeUtente);
        logVince(*giocatori, false);
        return giocatori;
    }
    Giocatore* giocatore = giocatori;
    // se ha abbastanza punti, ha vinto
    for(giocatore = giocatori; giocatore != NULL; giocatore = giocatore->prossimo){
        if(giocatore->cfu >= PUNTI_PER_VINCERE){
            printf("%s ha abbastanza CFU per vincere.\n", giocatore->nomeUtente);
            logVince(*giocatori, true);
            return giocatore;
        }
    }
    return NULL;
}

/**
 * Rimuove un giocatore
 * @param giocatori Puntatore alla lista di giocatori, che a sua volta è un puntatore
 * @param giocatore Il giocatore da eliminare
 */
void rimuoviGiocatore(Giocatore** giocatori, Giocatore* giocatore, int* nGiocatori){
    // Non rimuovere l'ultimo giocatore rimasto
    if(*giocatori == giocatore && giocatore->prossimo == NULL)
        return;
    Giocatore* precedente;
    (*nGiocatori)--;

    // Se si elimina il primo giocatore, bisogna spostare il puntatore al primo
    if(giocatore == *giocatori){
        *giocatori = giocatore->prossimo;
        free(giocatore);
    }else{
        for(precedente=*giocatori; precedente->prossimo!=giocatore; precedente=precedente->prossimo);
        precedente->prossimo = giocatore->prossimo;
        free(giocatore);
    }
}

/**
 * Spareggio per gli sconfitti
 * @param giocatori puntatore al primo giocatore
 * @param nGiocatori numero di giocatori
 * @param sconfitti array degli spareggianti
 * @return puntatore al giocatore che perde
 */
// TODO: Colore personaggio
// TODO: Si è rotto
Giocatore* spareggio(Giocatore* giocatori, int nGiocatori, bool sconfitti[nGiocatori], CartaCfu** scarti){
    printf("\n\n=== SPAREGGIO ===\n\n");
    int punti[nGiocatori], continuare=1, min=0;
    Giocatore* giocatore = giocatori;
    while(continuare!=0){
        continuare=1;
        giocatore = giocatori;
        // scorriamo tutti i giocatori
        for (int i = 0; i < nGiocatori; i++, giocatore = giocatore->prossimo) {
            // i giocatori che non stanno spareggiando avranno un punteggio di default per il calcolo del minimo
            punti[i]=PUNTI_PER_VINCERE+1;
            // perdi automaticamente se non hai più carte in mano
            if(contaCarteMano(*giocatore)==0 || soloIstantanee(*giocatore))
                return giocatore;
            // consideriamo solo chi partecipa allo spareggio
            if (sconfitti[i] == 1) {
                punti[i]=0;
                giocaCarta(giocatore, scarti, &punti[i]);
            }
        }
        // trovare il punteggio minimo
        for (int i = 0; i < nGiocatori; i++) {
            if (sconfitti[i] == 1){
                if(punti[i]<punti[min])
                    min=i;
            }
        }
        // controllare se ci sono due giocatori col punteggio minimo
        // c'è almeno un giocatore col punteggio minimo
        // se ce n'è solo uno, continuare sarà 0, altrimenti sarà diverso da 0
        continuare = -1;
        for (int i = 0; i < nGiocatori; i++) {
            if (sconfitti[i] == 1){
                if(punti[i]==punti[min])
                    continuare++;
                else
                    sconfitti[i] = 0;
            }
        }
    }
    giocatore = giocatori;
    // trovato il punteggio minimo, vediamo di chi è
    for (int i = 0; i < nGiocatori; i++, giocatore = giocatore->prossimo)
        if(i==min) {
            return giocatore;
        }
    for (int i = 0; i < min; i++)
        giocatore = giocatore->prossimo;
    for(int i=0; i<nGiocatori; i++)
        sconfitti[i] = 0;
    return giocatore;
}

/** La fase delle carte CFU
 * @param giocatori puntatore al primo giocatore
 * @param nGiocatori il numero di giocatori
 * @param carteCfu mazzo cfu
 * @param scarti pila degli scarti
 * @param carteOstacolo mazzo degli ostacoli
 */
void faseCfu(Giocatore **giocatori, Personaggio personaggi[4], int *nGiocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[*nGiocatori], int *moltiplicatoreAumenta){
    int i=0;

    // Un array per le carte giocate e uno per i giocatori, serviranno per l'ordine degli effetti
    CartaCfu carte[*nGiocatori];
    Giocatore* arrayGiocatori[*nGiocatori];

    // Conterrà l'ordine in cui verranno eseguiti gli effetti, relativamente all'ordine dei giocatori
    int ordineEffetti[*nGiocatori];
    for(i=0; i<*nGiocatori; i++)
        ordineEffetti[i] = i;

    // Controllo che ci siano giocatori
    if(*giocatori == NULL || *nGiocatori<=0)
        return;

    // Variabile che scorre la lista di giocatori
    Giocatore* giocatore = *giocatori;

    // Punteggio minimo e punteggio massimo del turno
    int min=0, max=0;
    // Numero ed elenco di sconfitti, per lo spareggio
    int nSconfitti = 0;
    bool continua = false;
    bool arrende = false;
    CartaCfu *carta;

    stampaOstacolo(**carteOstacolo);

    for(giocatore=*giocatori, i=0; giocatore!=NULL; giocatore=giocatore->prossimo, i++){
        continua = 0;
        // Se il giocatore ha solo carte istantanee, scarta tutta la mano e pesca altre carte
        while(soloIstantanee(*giocatore)){
            printf("%s ha solo carte istantanee, scarta tutta la sua mano.\n", giocatore->nomeUtente);
            scartaMano(giocatore, carteCfu, scarti);
        }
        coloreGiocatore(giocatore, personaggi);
        printf("= Turno di %s\n", giocatore->nomeUtente);
        continua = false;
        arrende = false;
        while(!continua){
            coloreGiocatore(giocatore, personaggi);
            printf("1: Gioca una carta\n");
            printf("2: Visualizza informazioni sulle carte\n");
            printf("3: Arrenditi\n");
            printf(RESET);
            switch(inputCifra()){
                case '1':
                    continua = true;
                    break;
                case '2':
                    stampaCfu(*selezionaCarta(giocatore, true, true, true, false));
                    break;
                case '3':
                    continua = true;
                    arrende = true;
                    printf("\n");
                    break;
                default:
                    printf("Seleziona un'opzione!\n");
                    break;
            }
        }
        if(arrende){
            rimuoviGiocatore(giocatori, giocatore, nGiocatori);
            // Se quando si è arreso erano rimasti solo due giocatori, l'altro vince
            if(*nGiocatori == 1)
                return;
        }else{
            coloreGiocatore(giocatore, personaggi);
            giocaCarta(giocatore, scarti, &punteggi[i].carta);
            arrayGiocatori[i] = giocatore;
            carte[i] = **scarti;
            printf(RESET);
        }
    }

    // Attiva gli effetti solo se non ci sono carte annulla
    if(!controllaAnnulla(*nGiocatori, carte)){
        // Le carte con più CFU vengono attivate prima
        ordinaEffetti(*nGiocatori, ordineEffetti, carte);
        for (i = 0; i < *nGiocatori; i++) {
            // TODO: più bello
            if (carte[ordineEffetti[i]].effetto > NESSUNO && carte[ordineEffetti[i]].effetto < PRIMA_ISTANTANEA)
                usaEffetto(*nGiocatori, carte, arrayGiocatori, giocatori, punteggi, ordineEffetti[i], carteCfu, scarti, personaggi, moltiplicatoreAumenta);
        }
    }else{
        printf(UCYN "\nGli effetti secondari delle carte sono stati annullati\n\n" RESET);
    }

    for(i=0; i<*nGiocatori; i++)
        calcolaPunteggio(&punteggi[i], *moltiplicatoreAumenta);
}

void faseIstantanee(Giocatore* giocatori, Personaggio personaggi[4], int nGiocatori, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta){
    // TODO: permettere di leggere gli effetti delle carte (magari con vediMano() che ti fa stampaEffetto() e selezionaCarta())
    Giocatore* giocatore = giocatori;
    Giocatore* arrayGiocatori[nGiocatori];
    int i=0;
    int scelta = 1;
    CartaCfu *carta;
    // TODO: arrayGiocatori(bool soloAvversari)
    for(i, giocatore=giocatori; giocatore!=NULL; i++, giocatore=giocatore->prossimo){
        arrayGiocatori[i] = giocatore;
    }

    while(scelta!=0){
        printf("Qualcuno vuole giocare una carta istantanea?\n");
        stampaGiocatori(giocatori, punteggi, personaggi);
        printf("0 per terminare.\n");
        scelta = inputCifra();
        if(scelta<0 || scelta>nGiocatori){
            printf(BRED "Seleziona un'opzione\n" RESET);
        }else{
            // L'input parte da 1
            scelta-=1;
            carta = daiCarta(arrayGiocatori[scelta], selezionaCarta(arrayGiocatori[scelta], true, false, false, true));
            if(carta != NULL){
                stampaEffetto(*carta);
                usaIstantanea(*carta, nGiocatori, scelta, arrayGiocatori, punteggi, personaggi, moltiplicatoreAumenta);
                cartaNegliScarti(scarti, carta);
            }
        }
    }
}

void fineTurno(Giocatore **giocatori, Personaggio personaggi[4], int nGiocatori, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta){
    // Trova punteggio minimo e massimo
    int i=0, min=0, max=0, nSconfitti=0;
    bool sconfitto[nGiocatori];
    Giocatore* giocatore;
    for(i=0; i<nGiocatori; i++){
        calcolaPunteggio(&punteggi[i], moltiplicatoreAumenta);
        if(punteggi[i].totale > punteggi[max].totale)
            max = i;
        if(punteggi[i].totale < punteggi[min].totale)
            min = i;
    }

    // Controlla chi ha il punteggio minore
    for(i=0; i<nGiocatori; i++){
        calcolaPunteggio(&punteggi[i], moltiplicatoreAumenta);
        if(punteggi[i].totale == punteggi[min].totale) {
            sconfitto[i] = true;
            nSconfitti++;
        }
        else
            sconfitto[i] = false;
    }

    // Se tutti pareggiano, si rimette l'ostacolo in fondo al mazzo
    if(nSconfitti == nGiocatori){
        annullaOstacolo(carteOstacolo);
        return;
    }

    // Dà i punti ai vincitori
    for(giocatore = *giocatori, i=0; i<nGiocatori; giocatore = giocatore->prossimo, i++){
        if(punteggi[i].totale==punteggi[max].totale){
            colorePersonaggio(giocatore->personaggio, personaggi);
            printf("%s ha preso %d cfu per le carte giocate.\n" RESET, giocatore->nomeUtente, punteggi[i].totale);
            prendiCfu(*giocatore, punteggi[i].totale, true);
            giocatore->cfu += punteggi[i].totale;
        }
    }

    // Eventuale spareggio, pesca dell'ostacolo
    if(nSconfitti==1) {
        giocatore = *giocatori;
        for(i=0; i<min; i++)
            giocatore = giocatore->prossimo;
    }else
        giocatore = spareggio(*giocatori, nGiocatori, sconfitto, scarti);
    logOstacolo(*giocatore, **carteOstacolo);
    // TODO: aggiornare la funzione
    pescaOstacolo(giocatore, carteOstacolo);
}

void stampaGiocatori(Giocatore* giocatori, Punteggio punteggi[], Personaggio personaggi[N_PERSONAGGI]){
    for(int i=1; giocatori!=NULL; i++, giocatori=giocatori->prossimo){
        coloreGiocatore(giocatori, personaggi);
        printf("%d: %s \t (%d CFU)\n" RESET, i, giocatori->nomeUtente, punteggi[i-1].totale);
    }
}

void calcolaPunteggio(Punteggio *punteggio, int moltiplicatoreAumenta){
    punteggio->totale = 0;
    punteggio->totale += punteggio->carta;
    punteggio->totale += punteggio->personaggio;
    punteggio->totale += punteggio->aumenta * 2 * moltiplicatoreAumenta;
}


void resetPunteggi(int nGiocatori, Punteggio punteggi[], int *moltiplicatore){
    for(int i=0; i<nGiocatori; i++){
        punteggi[i].totale=0;
        punteggi[i].carta=0;
        punteggi[i].aumenta=0;
        punteggi[i].personaggio=0;
    }
    *moltiplicatore = 1;
}