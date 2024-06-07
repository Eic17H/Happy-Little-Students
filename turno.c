#include "turno.h"
#include "carteCfu.h"
#include "carteOstacolo.h"
#include "carteEffetto.h"

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
        return giocatori;
    }
    Giocatore* giocatore = giocatori;
    // se ha abbastanza punti, ha vinto
    for(giocatore = giocatori; giocatore != NULL; giocatore = giocatore->prossimo){
        if(giocatore->cfu >= PUNTI_PER_VINCERE){
            printf("%s ha abbastanza CFU per vincere.\n", giocatore->nomeUtente);
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

// TODO: scartaTutteLeCarte(), in questo momento ci si può softlockare

/**
 * Spareggio per gli sconfitti
 * @param giocatori puntatore al primo giocatore
 * @param nGiocatori numero di giocatori
 * @param sconfitti array degli spareggianti
 * @return puntatore al giocatore che perde
 */
// TODO: Colore personaggio
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
            if(contaCarteMano(*giocatore)==0)
                return giocatore;
            // consideriamo solo chi partecipa allo spareggio
            if (sconfitti[i] == 1) {
                punti[i]=0;
                giocaCarta(giocatore, scarti, &punti[i], NULL);
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

    Punteggio punteggi[nGiocatori];
    // Controllo che ci siano giocatori
    if(giocatori == NULL || nGiocatori<=0)
        return;

    int i=0;

    // Variabile che scorre la lista di giocatori
    Giocatore* giocatore = giocatori;
    // TODO: usare la struct
    int cfuTurno[nGiocatori];
    // Punteggio minimo e punteggio massimo del turno
    int min=0, max=0;
    // Numero ed elenco di sconfitti, per lo spareggio
    int nSconfitti = 0;
    // Vero se il personaggio in quella posizione deve spareggiare, falso altrimenti
    bool sconfitti[nGiocatori];

    stampaOstacolo(**carteOstacolo);

    // Conterrà le coppie giocatore-carta per eseguire gli effetti in ordine
    GiocatoreCarta effetti[nGiocatori];

    for(giocatore=giocatori, i=0; giocatore!=NULL; giocatore=giocatore->prossimo, i++){
        // Se il giocatore ha solo carte istantanee, scarta tutta la mano e pesca altre carte
        while(soloIstantanee(*giocatore)){
            printf("%s ha solo carte istantanee, scarta tutta la sua mano.\n", giocatore->nomeUtente);
            scartaMano(giocatore, carteCfu, scarti);
        }
        cfuTurno[i] = 0;
        colorePersonaggio(giocatore->personaggio, personaggi);
        printf("= Turno di %s\n", giocatore->nomeUtente);
        giocaCarta(giocatore, scarti, &cfuTurno[i], &effetti[i]);
        printf(RESET);
    }
    for(i=0; i<nGiocatori; i++){
        if(cfuTurno[i] > cfuTurno[max])
            max = i;
        if(cfuTurno[i] < cfuTurno[min])
            min = i;
    }
    ordinaEffetti(nGiocatori, effetti);
    for(i=0; i<nGiocatori; i++){
        usaEffetto(effetti[i].carta, effetti[i].giocatore, &punteggi[i], scarti, personaggi, &giocatori, nGiocatori);
    }
    // Vincitori
    for(i=0, giocatore=giocatori; i<nGiocatori; i++, giocatore = giocatore->prossimo){
        if(cfuTurno[i]==cfuTurno[max]){
            colorePersonaggio(giocatore->personaggio, personaggi);
            printf("%s ha preso %d cfu per le carte giocate.\n" RESET, giocatore->nomeUtente, cfuTurno[i]);
            giocatore->cfu += cfuTurno[i];
        }
    }
    // Perdente
    for(i=0; i<nGiocatori; i++){
        if(cfuTurno[i] == cfuTurno[min]){
            nSconfitti++;
            sconfitti[i] = 1;
        }else
            sconfitti[i] = 0;
    }
    if(nSconfitti==1)
        for(i=0, giocatore=giocatori; i<min; i++)
            giocatore = giocatore->prossimo;
    else {
        giocatore = spareggio(giocatori, nGiocatori, sconfitti, scarti);
        pescaRotazione(giocatori, carteCfu, scarti);
    }
    pescaOstacolo(giocatore, carteOstacolo);
}