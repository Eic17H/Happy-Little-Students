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
void faseCfu(Giocatore *giocatori, int nGiocatori, Personaggio personaggi[4], CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo){
    int i=0;

    // Un array per le carte giocate e uno per i giocatori, utili per mantenere l'ordine nelle subroutine
    CartaCfu carte[nGiocatori];
    Giocatore* arrayGiocatori[nGiocatori];

    // Conterrà l'ordine in cui verranno eseguiti gli effetti, relativamente all'ordine dei giocatori
    int ordineEffetti[nGiocatori];
    for(i=0; i<nGiocatori; i++)
        ordineEffetti[i] = i;

    // TODO: spostare nel main
    int moltiplicatoreAumenta = 1;

    // Controllo che ci siano giocatori
    if(giocatori == NULL || nGiocatori<=0)
        return;

    // Variabile che scorre la lista di giocatori
    Giocatore* giocatore = giocatori;

    // TODO: spostare nel main
    Punteggio punteggi[nGiocatori];

    // Punteggio minimo e punteggio massimo del turno
    int min=0, max=0;
    // Numero ed elenco di sconfitti, per lo spareggio
    int nSconfitti = 0;
    // Vero se il personaggio in quella posizione deve spareggiare, falso altrimenti
    bool sconfitti[nGiocatori];

    stampaOstacolo(**carteOstacolo);

    for(giocatore=giocatori, i=0; giocatore!=NULL; giocatore=giocatore->prossimo, i++){
        // Se il giocatore ha solo carte istantanee, scarta tutta la mano e pesca altre carte
        while(soloIstantanee(*giocatore)){
            printf("%s ha solo carte istantanee, scarta tutta la sua mano.\n", giocatore->nomeUtente);
            scartaMano(giocatore, carteCfu, scarti);
        }
        // Il punteggio dato dalla carta per ora è 0
        punteggi[i].carta = 0;
        // Si legge il bonus/malus
        punteggi[i].personaggio = giocatore->personaggio.ostacoli[(**carteOstacolo).tipo-1];
        // Si parte senza aumenta/diminuisci
        punteggi[i].aumenta = 0;
        colorePersonaggio(giocatore->personaggio, personaggi);
        printf("= Turno di %s\n", giocatore->nomeUtente);
        giocaCarta(giocatore, scarti, &punteggi[i].carta);
        arrayGiocatori[i] = giocatore;
        carte[i] = **scarti;
        printf(RESET);
    }

    // Attiva gli effetti solo se non ci sono carte annulla
    if(!controllaAnnulla(nGiocatori, carte)){
        // Le carte con più CFU vengono attivate prima
        ordinaEffetti(nGiocatori, ordineEffetti, carte);
        for (i = 0; i < nGiocatori; i++) {
            // TODO: più bello
            if (carte[ordineEffetti[i]].effetto != NESSUNO && carte[ordineEffetti[i]].effetto < PRIMA_ISTANTANEA)
                usaEffetto(carte[ordineEffetti[i]], arrayGiocatori[ordineEffetti[i]], &punteggi[ordineEffetti[i]],
                           scarti, personaggi, &giocatori, nGiocatori, &moltiplicatoreAumenta, i, punteggi, carteCfu);
        }
    }
    // TODO: carte, arrayGiocatori, punteggi, ordineEffetti[i], nGiocatori, carteCfu, scarti, personaggi, &moltiplicatoreAumenta

    // Trova punteggio minimo e massimo
    for(i=0; i<nGiocatori; i++){
        calcolaPunteggio(&punteggi[i], moltiplicatoreAumenta);
        if(punteggi[i].totale > punteggi[max].totale)
            max = i;
        if(punteggi[i].totale < punteggi[min].totale)
            min = i;
    }

    // Controlla chi ha il punteggio minore
    for(i=0; i<nGiocatori; i++){
        if(punteggi[i].totale == punteggi[min].totale){
            nSconfitti++;
            sconfitti[i] = 1;
        }else
            sconfitti[i] = 0;
    }

    if(nSconfitti == nGiocatori){
        // rimettiOstacoloNelMazzo();
        return;
    }

    // Dà i punti ai vincitori
    for(i=0; i<nGiocatori; i++){
        if(punteggi[i].totale==punteggi[max].totale){
            colorePersonaggio(arrayGiocatori[i]->personaggio, personaggi);
            printf("%s ha preso %d cfu per le carte giocate.\n" RESET, arrayGiocatori[i]->nomeUtente, punteggi[i].totale);
            prendiCfu(*arrayGiocatori[i], punteggi[i].totale, true);
            arrayGiocatori[i]->cfu += punteggi[i].totale;
        }
    }

    // Se ci sono più giocatori con il punteggio minore, si spareggia
    if(nSconfitti==1)
        giocatore = arrayGiocatori[min];
    else
        giocatore = spareggio(giocatori, nGiocatori, sconfitti, scarti);
    logOstacolo(*giocatore, **carteOstacolo);
    pescaOstacolo(giocatore, carteOstacolo);
}

void calcolaPunteggio(Punteggio *punteggio, int moltiplicatoreAumenta){
    punteggio->totale = 0;
    punteggio->totale += punteggio->carta;
    punteggio->totale += punteggio->personaggio;
    punteggio->totale += punteggio->aumenta * 2 * moltiplicatoreAumenta;
}