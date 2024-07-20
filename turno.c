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

/**
 * Permette ai giocatori di selezionare, in ordine, il proprio personaggio
 * @param giocatori Puntatore al primo giocatore
 * @param personaggi Array dei personaggi letti dal file
 */
void assegnaPersonaggi(Giocatore* giocatori, Personaggio personaggi[N_PERSONAGGI]){
    Giocatore *giocatore = giocatori;
    bool selezionati[N_PERSONAGGI] = {false};
    int i=0, scelta=-1;

    // Si scorre la lista di giocatori, e si fa scegliere un personaggio, ripetendo l'input se non e' valido
    for(i=0, giocatore=giocatori; giocatore != NULL; i++, giocatore=giocatore->prossimo){
        printf("%s, seleziona un personaggio (1-%d): ", giocatore->nomeUtente, N_PERSONAGGI);
        scelta = inputCifra()-1;
        while(scelta<0 || scelta>=N_PERSONAGGI || selezionati[scelta]){
            if(scelta<0 || scelta>=N_PERSONAGGI)
                printf("Seleziona un'opzione\n");
            else if(selezionati[scelta])
                printf("Questo personaggio e' gia' stato selezionato\n");
            scelta = inputCifra()-1;
        }
        selezionati[scelta] = true;
        giocatore->personaggio = personaggi[i];
    }
}

/**
 * Controlla se qualcuno ha vinto. Se qualcuno ha vinto, rimuove tutti i giocatori che non hanno vinto
 * @param giocatori puntatore al primo giocatore
 * @return NULL se nessuno ha vinto, il vincitore se qualcuno ha vinto
 */
bool vince(Giocatore** giocatori, int* nGiocatori){
    // Se rimane un solo giocatore, ha vinto
    if((*giocatori)->prossimo == NULL){
        printf("%s e' l'ultimo giocatore rimasto.\n", (*giocatori)->nomeUtente);
        logVince(**giocatori, false);
        return true;
    }

    // Controlla se c'è almeno un giocatore con abbastanza punti per vincere. Aggiunge ciascun vincitore al log
    Giocatore* giocatore = *giocatori;
    bool trovato = false;
    for(giocatore = *giocatori; giocatore != NULL; giocatore = giocatore->prossimo){
        if(giocatore->cfu >= PUNTI_PER_VINCERE) {
            logVince(**giocatori, true);
            trovato = true;
        }
    }

    // Se almeno un giocatore ha vinto, rimuove tutti quelli che non hanno vinto
    if(trovato)
        for(giocatore = *giocatori; giocatore != NULL; giocatore = giocatore->prossimo)
            if(giocatore->cfu < PUNTI_PER_VINCERE)
                rimuoviGiocatore(giocatori, giocatore, nGiocatori);

    return trovato;
}

void stampaVincitori(Giocatore* giocatori, Personaggio personaggi[N_PERSONAGGI]){
    // Non dovrebbe poter succedere, ma per sicurezza lo gestisco
    if(giocatori == NULL){
        printf(RED "Errore: la partita è terminata senza nessun vincitore.\n" RESET);
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
 * Rimuove un giocatore
 * @param giocatori Puntatore alla lista di giocatori, che a sua volta è un puntatore
 * @param giocatore Il giocatore da eliminare
 * @param nGiocatori Puntatore al numero corrente di giocatori
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
 * @param giocatori Puntatore al primo giocatore
 * @param nGiocatori Numero corrente di giocatori
 * @param sconfitti Determina se ciascun giocatore sta spareggiando
 * @param scarti Puntatore al mazzo degli scarti
 * @param personaggi Array dei personaggi (serve per i colori)
 * @return Il giocatore che ha perso lo spareggio
 */
Giocatore* spareggio(Giocatore* giocatori, int nGiocatori, bool sconfitti[nGiocatori], CartaCfu** scarti, Personaggio personaggi[N_PERSONAGGI]){
    // Contiene il punteggio di spareggio di ciascun giocatore
    int punti[nGiocatori];
    int spareggianti=nGiocatori;
    int min=0;
    int i=0;
    Giocatore* giocatore = giocatori;

    // Si continua a spareggiare finché non ne rimane solo uno
    printf("\n\n=== SPAREGGIO ===\n\n");
    while(spareggianti>1){
        giocatore = giocatori;
        // scorriamo tutti i giocatori
        for (i = 0; i < nGiocatori; i++, giocatore = giocatore->prossimo) {
            // i giocatori che non stanno spareggiando avranno un punteggio di default per il calcolo del minimo
            punti[i]=PUNTI_PER_VINCERE+1;
            // perdi automaticamente se non hai più carte in mano
            if(contaCarteMano(*giocatore)==0 || soloIstantanee(*giocatore))
                return giocatore;
            // consideriamo solo chi partecipa allo spareggio
            if (sconfitti[i] == 1) {
                punti[i]=0;
                coloreGiocatore(giocatore, personaggi);
                giocaCarta(giocatore, scarti, &punti[i]);
            }
        }
        // trovare il punteggio minimo
        for (i = 0; i < nGiocatori; i++) {
            if (sconfitti[i] == 1){
                if(punti[i]<punti[min])
                    min=i;
            }
        }

        // Si ricontrolla ogni giocatore, se non sta spareggiando si indica nell'array, se sta spareggiando lo si conta
        spareggianti = 0;
        for (int i = 0; i < nGiocatori; i++) {
            if (sconfitti[i] == 1){
                if(punti[i]==punti[min])
                    spareggianti++;
                else
                    sconfitti[i] = 0;
            }
        }
    }
    // trovato il punteggio minimo, vediamo di chi è
    for(i = 0, giocatore=giocatori; i<nGiocatori; i++, giocatore = giocatore->prossimo)
        if(i==min)
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

    // Un array per le carte giocate e uno per i giocatori, per attivare gli effetti nell'ordine giusto
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
    bool selezionato = false;
    bool arrende = false;
    CartaCfu *carta;

    stampaOstacolo(**carteOstacolo);

    for(giocatore=*giocatori, i=0; giocatore!=NULL; giocatore=giocatore->prossimo, i++){
        punteggi[i].personaggio = giocatore->personaggio.ostacoli[(**carteOstacolo).tipo-1];
        // Se il giocatore ha solo carte istantanee, scarta tutta la mano e pesca altre carte
        while(soloIstantanee(*giocatore)){
            printf("%s ha solo carte istantanee, scarta tutta la sua mano.\n", giocatore->nomeUtente);
            scartaMano(giocatore, carteCfu, scarti);
        }
        coloreGiocatore(giocatore, personaggi);
        printf("= Turno di %s\n", giocatore->nomeUtente);
        selezionato = false;
        arrende = false;
        while(!selezionato){
            coloreGiocatore(giocatore, personaggi);
            printf("1: Gioca una carta\n");
            printf("2: Visualizza informazioni sulle carte\n");
            printf("3: Arrenditi\n");
            printf(RESET);
            switch(inputCifra()){
                case 1:
                    selezionato = true;
                    break;
                case 2:
                    stampaCfu(*selezionaCarta(giocatore, true, true, true, false));
                    break;
                case 3:
                    selezionato = true;
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
    if(!controllaAnnulla(*nGiocatori, *giocatori, carte, personaggi)){
        // Le carte con più CFU vengono attivate prima
        ordinaEffetti(*nGiocatori, ordineEffetti, carte);
        for (i = 0; i < *nGiocatori; i++){
            // Se la carta ha un effetto e non è istantanea, attiva l'effetto
            if (carte[ordineEffetti[i]].effetto > NESSUNO && carte[ordineEffetti[i]].effetto < PRIMA_ISTANTANEA)
                usaEffetto(*nGiocatori, carte, arrayGiocatori, giocatori, punteggi, ordineEffetti[i], carteCfu, scarti, personaggi, moltiplicatoreAumenta);
        }
    }

    for(i=0; i<*nGiocatori; i++)
        calcolaPunteggio(&punteggi[i], *moltiplicatoreAumenta);
}

/**
 * La fase delle carte istantanee, seconda fase del turno
 * @param giocatori Puntatore al primo giocatore
 * @param personaggi Array dei personaggi (serve per i colori)
 * @param nGiocatori Numero corrente di giocatori
 * @param scarti Puntatore al mazzo degli scarti, a sua volta puntatore alla carta in cima
 * @param carteOstacolo Puntatore al mazzo degli ostacoli, a sua volta puntatore alla carta in cima
 * @param punteggi Array dei punteggi provvisori
 * @param moltiplicatoreAumenta Valore corrente del moltiplicatore dell'effetto delle carte aumenta e diminuisci
 */
void faseIstantanee(Giocatore* giocatori, Personaggio personaggi[4], int nGiocatori, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta){
    Giocatore* giocatore = giocatori;
    Giocatore* arrayGiocatori[nGiocatori];
    int i=0;
    int scelta = 1;
    CartaCfu *carta;

    // È più efficiente scorrere la lista solo una volta, all'inizio
    for(i=0, giocatore=giocatori; giocatore!=NULL; i++, giocatore=giocatore->prossimo){
        arrayGiocatori[i] = giocatore;
    }


    printf("Qualcuno vuole giocare una carta istantanea?\n");
    stampaGiocatori(giocatori, punteggi, personaggi);
    printf("0 per terminare.\n");
    scelta = inputCifra();

    while(scelta!=0){
        if(scelta<0 || scelta>nGiocatori){
            printf(BRED "Seleziona un'opzione\n" RESET);
        }else{
            // L'input parte da 1, ma gli indici partono da 0
            scelta--;
            // La carta viene selezionata
            carta = selezionaCarta(arrayGiocatori[scelta], true, false, false, true);
            if(carta!=NULL) {
                stampaCfu(*carta);
                printf("Vuoi usare questa carta? 1 per si', qualunque altro tasto per no\nSeleziona: ");
                if (inputCifra() == 1) {
                    // Solo se il giocatore conferma la scelta, la carta viene rimossa dalla mano e attivata
                    carta = daiCarta(arrayGiocatori[scelta], carta);
                    // Ricontrollo che non sia NULL dopo daiCarta(). Non dovrebbe essere possibile, ma è meglio evitare
                    if (carta != NULL) {
                        stampaEffetto(*carta);
                        usaIstantanea(*carta, nGiocatori, scelta, arrayGiocatori, punteggi, personaggi, moltiplicatoreAumenta);
                        cartaNegliScarti(scarti, carta);
                    }
                }
            }
            printf("Qualcun altro vuole giocare una carta istantanea?\n");
            stampaGiocatori(giocatori, punteggi, personaggi);
            printf("0 per terminare.\n");
        }
        scelta = inputCifra();
    }
}

/**
 * Fase finale del turno, dove si assegnano i punti, si spareggia, e si pescano gli ostacoli
 * @param giocatori Puntatore al primo giocatore
 * @param personaggi Array dei personaggi (serve per i colori)
 * @param nGiocatori Numero corrente di giocatori
 * @param scarti Puntatore al mazzo degli scarti, a sua volta puntatore alla carta in cima
 * @param carteOstacolo Puntatore al mazzo degli ostacoli, a sua volta puntatore alla carta in cima
 * @param punteggi Array dei punteggi provvisori
 * @param moltiplicatoreAumenta Moltiplicatore corrente delle carte aumenta e diminuisci (serve per ricalcolare i punteggi)
 */
void fineTurno(Giocatore *giocatori, Personaggio personaggi[4], int nGiocatori, CartaCfu **scarti, CartaOstacolo **carteOstacolo, Punteggio punteggi[nGiocatori], int moltiplicatoreAumenta){
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
    for(giocatore = giocatori, i=0; i<nGiocatori; giocatore = giocatore->prossimo, i++){
        if(punteggi[i].totale==punteggi[max].totale){
            coloreGiocatore(giocatore, personaggi);
            printf("%s ha preso %d cfu per le carte giocate.\n" RESET, giocatore->nomeUtente, punteggi[i].totale);
            prendiCfu(*giocatore, punteggi[i].totale, true);
            giocatore->cfu += punteggi[i].totale;
        }
    }

    // Eventuale spareggio, pesca dell'ostacolo
    if(nSconfitti==1) {
        giocatore = giocatori;
        for(i=0; i<min; i++)
            giocatore = giocatore->prossimo;
    }else
        giocatore = spareggio(giocatori, nGiocatori, sconfitto, scarti, personaggi);

    // Si permette di giocare una carta salva o dirotta
    salvaDirotta(nGiocatori, giocatori, &giocatore, personaggi);

    // Se il giocatore si è salvato, il puntatore è NULL
    if(giocatore != NULL) {
        logOstacolo(*giocatore, **carteOstacolo);
        pescaOstacolo(giocatore, carteOstacolo);
    }else{
        annullaOstacolo(carteOstacolo);
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

/**
 * Calcola il punteggio provvisorio
 * @param punteggio Array dei punteggi provvisori (contiene informazioni sui punti ottenuti in modi diversi)
 * @param moltiplicatoreAumenta Moltiplicatore corrente delle carte aumenta e diminuisci
 */
void calcolaPunteggio(Punteggio *punteggio, int moltiplicatoreAumenta){
    punteggio->totale = 0;
    punteggio->totale += punteggio->carta;
    punteggio->totale += punteggio->personaggio;
    punteggio->totale += punteggio->aumenta * 2 * moltiplicatoreAumenta;
}

/**
 * Inizializza i punteggi provvisori a 0, e il moltiplicatore delle carte aumenta e diminuisci a 1
 * @param nGiocatori Numero corrente di giocatori
 * @param punteggi Array dei punteggi provvisori
 * @param moltiplicatore Puntatore al moltiplicatore delle carte aumenta e diminuisci
 */
void resetPunteggi(int nGiocatori, Punteggio punteggi[], int *moltiplicatore){
    for(int i=0; i<nGiocatori; i++){
        punteggi[i].totale=0;
        punteggi[i].carta=0;
        punteggi[i].aumenta=0;
        punteggi[i].personaggio=0;
    }
    *moltiplicatore = 1;
}