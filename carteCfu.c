#include "carteCfu.h"

/**
 * Questa funzione toglie una carta da una mano e la restituisce.
 * Da usare solo se il giocatore ha la carta.
 * @param giocatore Puntatore al giocatore che deve dare la carta
 * @param carta Puntatore alla carta da dare, che dovrebbe essere presente nella mano del giocatore
 * @return Puntatore alla carta data (NULL se la carta non c'è)
 */
CartaCfu* daiCarta(Giocatore* giocatore, CartaCfu* carta){
    // Se il giocatore non ha quella carta, restituisce NULL
    if(!haQuestaCarta(giocatore, carta))
        return NULL;
    CartaCfu* cerca = giocatore->primaCfu;
    // Caso speciale se è la prima
    if(cerca == carta){
        // La mano adesso comincia dalla carta successiva, carta viene "portata fuori dalla mano"
        giocatore->primaCfu = carta->prossima;
        carta->prossima = NULL;
    }else{
        // cerca deve essere la carta precedente a carta
        while(cerca->prossima != carta)
            cerca = cerca->prossima;
        // Il nuovo collegamento salta carta, e carta viene "portata fuori dalla mano"
        cerca->prossima = carta->prossima;
        carta->prossima = NULL;
    }
    return carta;
}

/**
 * Questa funzione mette una carta nella pila degli scarti
 * @param scarti Puntatore alla pila, che a sua volta è un puntatore alla carta in cima alla pila
 * @param carta La carta da scartare
 */
void scartaCarta(CartaCfu** scarti, CartaCfu* carta){
    carta->prossima = *scarti;
    *scarti = carta->prossima;
}

/**
 * Questa funzione controlla se un giocatore ha una specifica carta cfu (due carte uguali contano comunque come separate)
 * @param giocatore Il giocatore di cui controllare la mano
 * @param cartaCfu La carta da cercare
 * @return vero se ce l'ha, falso altrimenti
 */
bool haQuestaCarta(Giocatore* giocatore, CartaCfu* carta){
    for(CartaCfu* cerca = giocatore->primaCfu; cerca != NULL; cerca = cerca->prossima)
        if(cerca == carta)
            return true;
    return false;
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
    int scelta=0;

    // Un array contenente le carte del giocatore
    CartaCfu* mano[carteInMano];
    for(int i=0; carta != NULL; carta = carta->prossima, i++){
        mano[i] = carta;
    }

    printf("Quale vuoi giocare?\n");
    bool sceltaValida = false;
    while(!sceltaValida){
        sceltaValida = true;
        scanf("%d", &scelta);
        if(scelta<1){
            sceltaValida = false;
            printf("Le carte sono numerate a partire da 1.\n");
        }else if(scelta>carteInMano){
            sceltaValida = false;
            printf("Hai solo %d carte in mano.\n", carteInMano);
        }else if(mano[scelta-1]->effetto >= PRIMA_ISTANTANEA){
            sceltaValida = false;
            printf("Non e' la fase delle carte istantanee (%c).\n", SIMBOLO_CARTA_ISTANTANEA);
        }
    }
    // Caso speciale se è stata scelta la prima carta (non posso operare su quella precedente)
    scartata = daiCarta(giocatore, mano[scelta-1]);
    // In teoria non può succedere, ma è meglio metterla
    if(scartata == NULL){
        printf(HRED "Errore: il giocatore sta provando a usare una carta non presente nella sua mano.\n" RESET);
        return;
    }
    // Si aggiungono i CFU della carta scartata al conteggio dei CFU del giocatore
    *cfuTurno += scartata->cfu;
    // Si mette la carta nella pila degli scarti
    scartaCarta(scarti, scartata);
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

/**
 * Mostra le carte in mano a un giocatore
 * @param giocatore
 */
void mostraCarte(Giocatore giocatore){
    printf("\t===== Mano di %s =====\n", giocatore.nomeUtente);
    CartaCfu* carta = giocatore.primaCfu;
    int i = 1;
    while(carta != NULL) {
        // Stampa il nome, se è una carta con effetto, e il valore
        printf("%d: %-32s %c %d CFU :%d\n", i, carta->nome, cartaSpeciale(*carta), carta->cfu, i);
        carta = carta->prossima;
        i++;
    }
}