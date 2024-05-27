#include "turno.h"

/**
 * Mostra le carte in mano a un giocatore
 * @param giocatore
 */
void mostraCarte(Giocatore giocatore){
    printf("\t===== Mano di %s =====\n", giocatore.nomeUtente);
    CartaCfu* carta = giocatore.primaCfu;
    while(carta != NULL) {
        // Stampa il nome, se è una carta con effetto, e il valore
        printf("%-32s %c %d CFU\n", carta->nome, cartaSpeciale(*carta), carta->cfu);
        carta = carta->prossima;
    }
}

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

/** Questa funzione permette di pescare una carta.
 * La toglie dalla cima del mazzo e la mette in cima alla mano di un giocatore
 * @param giocatore puntatore al giocatore che deve pescare
 * @param mazzo puntatore al "mazzo", che a sua volta è un puntatore alla carta in cima
 */
void pescaCarta(Giocatore* giocatore, CartaCfu** mazzo){
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
void pescaRotazione(Giocatore* giocatori, CartaCfu** mazzo){
    Giocatore* giocatore;
    int finito = 0;
    while(!finito) {
        giocatore = giocatori;
        finito = 1;
        while (giocatore != NULL) {
            if (contaCarteMano(*giocatore) < N_CARTE_MANO) {
                finito=0;
                pescaCarta(giocatore, mazzo);
            }
            giocatore = giocatore->prossimo;
        }
    }
}

// TODO: rimuovere (credo)
void mostraCarteDiTutti(Giocatore* giocatore){
    while(giocatore != NULL){
        mostraCarte(*giocatore);
        giocatore = giocatore->prossimo;
        printf("\n");
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

/** Permette di giocare una carta CFU (per ora senza effetti secondari)
 * @param giocatore puntatore al giocatore di turno
 * @param scarti puntatore alla pila degli scarti, che a sua volta è un puntatore alla sua prima carta
 * @param cfuTurno puntatore alla variabile che registra i CFU correnti del giocatore
 */
void giocaCarta(Giocatore* giocatore, CartaCfu** scarti, int* cfuTurno){
    mostraCarte(*giocatore);
    int carteInMano = contaCarteMano(*giocatore);
    // Puntatori a due carte
    CartaCfu *carta = giocatore->primaCfu, *scartata;
    int scelta;
    printf("Quale vuoi giocare?\n");
    scanf("%d", &scelta);
    while(scelta<1 || scelta>carteInMano){
        printf("Scegli una delle carte in mano (1-%d).\n", carteInMano);
        scanf("%d", &scelta);
    }
    // Caso speciale se è stata scelta la prima carta (non posso operare su quella precedente)
    if(scelta == 1){
        // Quella scartata è la prima
        scartata = giocatore->primaCfu;
        // L'inizio del mazzo è adesso la carta che prima era la seconda
        giocatore->primaCfu = giocatore->primaCfu->prossima;
    }else{
        // Scorre la lista fino a quella prima di quella scelta
        for(int i=0; i<scelta-2; i++)
            carta = carta->prossima;
        // Quella scartata è quella dopo
        scartata = carta->prossima;
        // La carta dopo "carta" è adesso quella che prima era due carte dopo (è stata tolta la carta scartata)
        // Se è stata scelta l'ultima carta, carta->prossima->prossima è NULL, quindi funziona comunque
        carta->prossima = carta->prossima->prossima;
        // La carta scartata viene messa nel mazzo degli scarti
        scartata->prossima = *scarti;
        // La prima carta nel mazzo degli scarti è quella appena scartata
        *scarti = scartata;
    }
    // Si aggiungono i CFU della carta scartata al conteggio dei CFU del giocatore
    *cfuTurno += scartata->cfu;
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

void    perdereOstacolo(Giocatore** giocatori){
    if((*giocatori)->prossimo == NULL)
        return;
    Giocatore *giocatore=*giocatori, *giocatorePrec;
    CartaOstacolo *carta;
    int carte[3] = {0, 0, 0};
    // scorri i giocatori
    for(giocatore = *giocatori; giocatore!=NULL; giocatore = giocatore->prossimo){
        carte[0] = 0;
        carte[1] = 0;
        carte[2] = 0;
        // scorre le carte ostacolo
        for(carta = giocatore->primaOstacolo; carta!=NULL && carta->prossima!=NULL; carta = carta->prossima){
            // conta le carte di ciascun tipo
            if(carta->tipo==ESAME){
                carte[0]+=1;
                carte[1]+=1;
                carte[2]+=1;
            }else
                carte[carta->tipo]+=1;
        }
        // TODO: 2 giocatori
        if(carte[0]>=3 || carte[1]>=3 || carte[2]>=3 || carte[0]>0 && carte[1]>0 && carte[2]>0){
            // caso speciale se è il primo
            if(*giocatori == giocatore){
                *giocatori = giocatore->prossimo;
                printf("\n\n%s ha perso per ostacoli\n\n", giocatore->nomeUtente);
                free(giocatore);
            }else{
                for(giocatorePrec = *giocatori; giocatorePrec->prossimo!=giocatore; giocatorePrec = giocatorePrec->prossimo){
                    giocatorePrec->prossimo = giocatore->prossimo;
                    printf("\n\n%s ha perso per ostacoli\n\n", giocatore->nomeUtente);
                    free(giocatore);
                }
            }
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
Giocatore* spareggio(Giocatore* giocatori, int nGiocatori, int* sconfitti, CartaCfu** scarti){
    printf("\n\n=== SPAREGGIO ===\n\n");
    int punti[nGiocatori], continuare=1, min=0;
    Giocatore* giocatore = giocatori;
    while(continuare!=0){
        continuare=1;
        giocatore = giocatori;
        // scorriamo tutti i giocatori
        for (int i = 0; i < nGiocatori; i++, giocatore = giocatore->prossimo) {
            // i giocatori che non stanno spareggiando avranno un punteggio di default per il calcolo del minimo
            punti[i]=500;
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
            }
        }
    }
    giocatore = giocatori;
    // trovato il punteggio minimo, vediamo di chi è
    for (int i = 0; i < nGiocatori; i++, giocatore = giocatore->prossimo)
        if(i==min) {
            return giocatore;
        }
}

/** Il turno
 * @param giocatori puntatore al primo giocatore
 * @param nGiocatori il numero di giocatori
 * @param carteCfu mazzo cfu
 * @param scarti pila degli scarti
 * @param carteOstacolo mazzo degli ostacoli
 */
 // TODO: capire che fare quando finisce il mazzo
void turno(Giocatore* giocatori, int nGiocatori, CartaCfu** carteCfu, CartaCfu** scarti, CartaOstacolo** carteOstacolo){
    Giocatore* giocatore = giocatori;
    int i=0, cfuTurno[nGiocatori], min=0, max=0;
    int nSconfitti = 0, sconfitti[nGiocatori];
    pescaRotazione(giocatori, carteCfu);
    char colore[16];
    CartaOstacolo *cartaOstacolo;

    stampaOstacolo(**carteOstacolo);

    for(giocatore=giocatori; giocatore!=NULL; giocatore=giocatore->prossimo){
        printf("%s: %d cfu\n", giocatore->nomeUtente, giocatore->cfu);
        for(cartaOstacolo = giocatore->primaOstacolo; cartaOstacolo != NULL; cartaOstacolo = cartaOstacolo->prossima)
            stampaNomeOstacolo(*cartaOstacolo);
    }
    for(giocatore=giocatori, i=0; giocatore!=NULL; giocatore=giocatore->prossimo, i++){
        cfuTurno[i] = 0;
        printf("___===---!!! Turno di %s !!!---===___\n", giocatore->nomeUtente);
        giocaCarta(giocatore, scarti, cfuTurno + i);
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
        pescaRotazione(giocatori, carteCfu);
    }
    pescaOstacolo(giocatore, carteOstacolo);
}