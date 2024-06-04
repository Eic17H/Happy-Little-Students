#include "turno.h"

int contaCarteMano(Giocatore giocatore){
    int conta = 0;
    CartaCfu* carta = giocatore.primaCfu;
    while(carta != NULL){
        conta++;
        carta = carta->prossima;
    }
    return conta;
}

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

/** Questa funzione permette di pescare una carta.
 * La toglie dalla cima del mazzo e la mette in cima alla mano di un giocatore
 * @param giocatore puntatore al giocatore che deve pescare
 * @param mazzo puntatore al "mazzo", che a sua volta è un puntatore alla carta in cima
 */
void pescaCarta(Giocatore* giocatore, CartaCfu** mazzo, CartaCfu** scarti){
    // Se è finito il mazzo si mischiano gli scarti
    if(mazzo==NULL){
        mazzo = scarti;
        scarti = NULL;
        mischiaMazzo(mazzo);
    }
    // Si mette il puntatore alla carta in cima in una variabile
    CartaCfu *carta;
    carta = *mazzo;
    // Il puntatore alla carta in cima (variabile del programma chiamante) viene spostato una carta in avanti
    // La carta precedentemente in cima è puntata solo dalla variabile ausiliare e non più dal mazzo: è stata pescata
    *mazzo = (*mazzo)->prossima;
    // La mano del giocatore viene impostata come carta successiva a quella pescata
    carta->prossima = giocatore->primaCfu;
    // La carta pescata è impostata come prima carta in mano al giocatore
    giocatore->primaCfu = carta;
}

/** Questa funzione permette di pescare una carta.
 * La toglie dalla cima del mazzo e la mette in cima alla mano di un giocatore
 * @param giocatore puntatore al giocatore che deve pescare
 * @param mazzo puntatore al "mazzo", che a sua volta è un puntatore alla carta in cima
 */
void pescaOstacolo(Giocatore* giocatore, CartaOstacolo** mazzo){
    // Si mette il puntatore alla carta in cima in una variabile
    CartaOstacolo *carta;
    carta = *mazzo;
    // Il puntatore alla carta in cima (variabile del programma chiamante) viene spostato una carta in avanti
    // La carta precedentemente in cima è puntata solo dalla variabile ausiliare e non più dal mazzo: è stata pescata
    *mazzo = (*mazzo)->prossima;
    // La mano del giocatore viene impostata come carta successiva a quella pescata
    carta->prossima = giocatore->primaOstacolo;
    // La carta pescata è impostata come prima carta in mano al giocatore
    giocatore->primaOstacolo = carta;
}

/** Tutti i giocatori pescano a rotazione finché non hanno tutti N_CARTE_MANO carte in mano
 * @param giocatori puntatore al primo giocatore
 * @param mazzo puntatore al mazzo, che a sua volta è un puntatore alla prima carta del mazzo
 */
void pescaRotazione(Giocatore* giocatori, CartaCfu** mazzo, CartaCfu** scarti){
    Giocatore* giocatore;
    int finito = 0;
    while(!finito) {
        giocatore = giocatori;
        finito = 1;
        while (giocatore != NULL) {
            if (contaCarteMano(*giocatore) < N_CARTE_MANO) {
                finito=0;
                pescaCarta(giocatore, mazzo, scarti);
            }
            giocatore = giocatore->prossimo;
        }
    }
}

/** Mischia il mazzo delle carte CFU
 * @param mazzo puntatore al mazzo, che a sua volta punta alla sua prima carta
 */
void mischiaMazzo(CartaCfu** mazzo){
    int nCarte=0, i=0, j=0;
    CartaCfu *carta = *mazzo;

    // Contiamo quante carte ci sono
    while(carta != NULL){
        nCarte++;
        carta = carta->prossima;
    }
    // Array che punterà a tutte le carte
    CartaCfu* carte[nCarte];
    // Facciamo puntare ciascun elemento dell'array a una carta
    carta = *mazzo;
    while(carta != NULL){
        carte[i] = carta;
        carta = carta->prossima;
        i++;
    }
    // Le carte non formano più una lista, ma sono ancora in ordine nell'array
    for(i=0; i<nCarte; i++)
        carte[i]->prossima = NULL;

    // Array che conterrà una permutazione casuale di interi da 0 a nCarte-1
    int random[nCarte];
    for(i=0; i<nCarte; i++)
        random[i] = i;

    // Andiamo dalla fine all'inizio. Scambiamo ogni numero con un numero casuale che viene prima
    // Non arriviamo a i==0 perché non si può dividere per 0
    for(i=nCarte-1; i>0; i--){
        j=rand()%i;
        scambiaInt(&random[j], &random[i]);
    }

    // Creiamo una nuova lista:
    // Usiamo la sequenza di random[] come ordine degli indici di carte[]
    // "carta" resta un posto indietro, così possiamo agire su carta->prossima senza che carta sia NULL
    // Quindi il primo passo è fuori dal loop
    carta = carte[random[0]];
    *mazzo = carta;
    for(i=1; i<nCarte; i++){
        carta->prossima = carte[random[i]];
        carta = carta->prossima;
    }
    carta->prossima = NULL;
}

/** Mischia il mazzo degli ostacoli
 * @param mazzo puntatore al mazzo degli ostacoli, che a sua volta è un puntatore alla sua prima carta
 */
void mischiaOstacoli(CartaOstacolo** mazzo){
    int nCarte=0, i=0, j=0;
    CartaOstacolo *carta = *mazzo;

    // Contiamo quante carte ci sono
    while(carta != NULL){
        nCarte++;
        carta = carta->prossima;
    }
    // Array che punterà a tutte le carte
    CartaOstacolo* carte[nCarte];
    // Facciamo puntare ciascun elemento dell'array a una carta
    carta = *mazzo;
    while(carta != NULL){
        carte[i] = carta;
        carta = carta->prossima;
        i++;
    }
    // Le carte non formano più una lista, ma sono ancora in ordine nell'array
    for(i=0; i<nCarte; i++)
        carte[i]->prossima = NULL;

    // Array che conterrà una permutazione casuale di interi da 0 a nCarte-1
    int random[nCarte];
    for(i=0; i<nCarte; i++)
        random[i] = i;

    // Andiamo dalla fine all'inizio. Scambiamo ogni numero con un numero casuale che viene prima
    // Non arriviamo a i==0 perché non si può dividere per 0
    for(i=nCarte-1; i>0; i--){
        j=rand()%i;
        scambiaInt(&random[j], &random[i]);
    }

    // Creiamo una nuova lista:
    // Usiamo la sequenza di random[] come ordine degli indici di carte[]
    // "carta" resta un posto indietro, così possiamo agire su carta->prossima senza che carta sia NULL
    // Quindi il primo passo è fuori dal loop
    carta = carte[random[0]];
    *mazzo = carta;
    for(i=1; i<nCarte; i++){
        carta->prossima = carte[random[i]];
        carta = carta->prossima;
    }
    carta->prossima = NULL;
}

/**
 * controlla se qualcuno ha vinto
 * @param giocatori puntatore al primo giocatore
 * @return NULL se nessuno ha vinto, il vincitore se qualcuno ha vinto
 */
Giocatore* vince(Giocatore* giocatori){
    // se rimane un solo giocatore, ha vinto
    if(giocatori->prossimo == NULL)
        return giocatori;
    Giocatore* giocatore = giocatori;
    // se ha abbastanza punti, ha vinto
    for(giocatore = giocatori; giocatore != NULL; giocatore = giocatore->prossimo){
        if(giocatore->cfu >= PUNTI_PER_VINCERE)
            return giocatore;
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

bool troppiOstacoli(int carte[4]){
    // Tre carte dello stesso colore (le carte esame contano in ogni caso)
    if(carte[0]+carte[3]>=3)
        return true;
    if(carte[1]+carte[3]>=3)
        return true;
    if(carte[2]+carte[3]>=3)
        return true;
    // Tre carte di colore diverso (considerando le carte esame come ciascun colore)
    if(carte[0]+carte[3]>0 && carte[1]>0 && carte[2]>0)
        return true;
    if(carte[0]>0 && carte[1]+carte[3]>0 && carte[2]>0)
        return true;
    if(carte[0]>0 && carte[1]>0 && carte[2]+carte[3]>0)
        return true;
    return false;
}

void controlloOstacoli(Giocatore** giocatori, int* nGiocatori){
    if((*giocatori)->prossimo == NULL)
        return;
    Giocatore *giocatore=*giocatori, *giocatorePrec;
    CartaOstacolo *carta;
    int carte[4] = {0, 0, 0, 0};
    // scorri i giocatori
    for(giocatore = *giocatori; giocatore!=NULL; giocatore = giocatore->prossimo){
        carte[0] = 0;
        carte[1] = 0;
        carte[2] = 0;
        carte[3] = 0;
        // scorre le carte ostacolo
        for(carta = giocatore->primaOstacolo; carta!=NULL; carta = carta->prossima){
            // Aumento CFU per ogni carta ostacolo
            giocatore->cfu++;
            // conta le carte di ciascun tipo
            switch(carta->tipo){
                case STUDIO:
                    carte[0]++;
                    break;
                case SOPRAVVIVENZA:
                    carte[1]++;
                    break;
                case SOCIALE:
                    carte[2]++;
                    break;
                case ESAME:
                    carte[3]++;
                    break;
                default:
                    break;
            }
        }
        // TODO: 2 giocatori
        if(troppiOstacoli(carte)){
            // Testo rosso
            printf(BHRED "\n\n");
            // Abbastanza "=" per raggiungere la lunghezza del nome del giocatore
            for(int i=0; i<strlen(giocatore->nomeUtente); i++)
                printf("=");
            // Il messaggio
            printf("==========\n%s ha perso.\n==========", giocatore->nomeUtente);
            // Di nuovo, raggiungere la lunghezza del nome
            for(int i=0; i<strlen(giocatore->nomeUtente); i++)
                printf("=");
            // Andare a capo e mettere il colore normale
            printf("\n\n" RESET);
            rimuoviGiocatore(giocatori, giocatore, nGiocatori);
        }
    }
}

/**
 * Spareggio per gli sconfitti
 * @param giocatori puntatore al primo giocatore
 * @param nGiocatori numero di giocatori
 * @param sconfitti array degli spareggianti
 * @return puntatore al giocatore che perde
 */
Giocatore* spareggio(Giocatore* giocatori, int nGiocatori, int sconfitti[nGiocatori], CartaCfu** scarti){
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
 // TODO: cambiare nGiocatori quando perde qualcuno, capire che fare coi colori quando perde qualcuno
 // TODO: forse posso direttamente assegnare un colore a ciascun personaggio
void faseCfu(Giocatore* giocatori, int nGiocatori, CartaCfu** carteCfu, CartaCfu** scarti, CartaOstacolo** carteOstacolo, int nTurno, Personaggio personaggi[], int numeriPlancia[PUNTI_PER_VINCERE]){
    stampaPlancia(giocatori, nGiocatori, numeriPlancia);
    Giocatore* giocatore = giocatori;
    int i=0, cfuTurno[nGiocatori], min=0, max=0;
    int nSconfitti = 0, sconfitti[nGiocatori];
    pescaRotazione(giocatori, carteCfu, scarti);
    char colore[16];
    CartaOstacolo *cartaOstacolo;

    stampaOstacolo(**carteOstacolo);

    for(giocatore=giocatori, i=0; giocatore!=NULL; giocatore=giocatore->prossimo, i++){
        cfuTurno[i] = 0;
        colorePersonaggio(giocatore->personaggio, personaggi);
        printf("___===---!!! Turno di %s !!!---===___\n", giocatore->nomeUtente);
        giocaCarta(giocatore, scarti, cfuTurno + i);
        printf(RESET);
    }
    for(i=0; i<nGiocatori; i++){
        if(cfuTurno[i] > cfuTurno[max])
            max = i;
        if(cfuTurno[i] < cfuTurno[min])
            min = i;
    }
    // Vincitori
    for(i=0, giocatore=giocatori; i<nGiocatori; i++, giocatore = giocatore->prossimo){
        if(cfuTurno[i]==cfuTurno[max])
            giocatore->cfu += cfuTurno[i];
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