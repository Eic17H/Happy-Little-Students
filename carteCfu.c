#include "carteCfu.h"
#include "carteEffetto.h"
#include "interfaccia.h"

/**
 * Questa funzione toglie una carta da una mano e la restituisce.
 * Da usare solo se il giocatore ha la carta.
 * Esempio di utilizzo: daiCarta(giocatore, selezionaCarta(giocatore, ...))
 * @param giocatore Puntatore al giocatore che deve dare la carta
 * @param carta Puntatore alla carta da dare, che dovrebbe essere presente nella mano del giocatore
 * @return Puntatore alla carta data (NULL se la carta non c'è)
 */
CartaCfu* daiCarta(Giocatore* giocatore, CartaCfu* carta){

    if(giocatore==NULL || carta==NULL)
        return NULL;

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
        // Non sarà mai NULL perché abbiamo controllato con haQuestaCarta()
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
void cartaNegliScarti(CartaCfu** scarti, CartaCfu* carta){
    if(carta != NULL){
        carta->prossima = *scarti;
        *scarti = carta;
    }
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
 * @param giocatore Puntatore al giocatore di turno
 * @param scarti Puntatore alla pila degli scarti, che a sua volta è un puntatore alla sua prima carta
 * @param cfuTurno Puntatore alla variabile che registra i CFU correnti del giocatore
 * @param effetto Puntatore alla struct che contiene informazioni sul giocatore e sulla sua carta
 */
void giocaCarta(Giocatore *giocatore, CartaCfu **scarti, int *cfuTurno){

    // Il giocatore seleziona una carta dalla propria mano (le carte istantanee non sono ammesse)
    CartaCfu *carta = daiCarta(giocatore, selezionaCarta(giocatore, false, true, true, false));

    // In teoria non può succedere, ma è meglio metterla
    if(carta == NULL){
        coloreErrore();
        printf("Errore: il giocatore sta provando a usare una carta non presente nella sua mano.\n" RESET);
        return;
    }
    // Si aggiungono i CFU della carta scartata al conteggio dei CFU del giocatore
    *cfuTurno += carta->cfu;
    logCartaCfu(*giocatore, *carta);
    // Si mette la carta nella pila degli scarti
    cartaNegliScarti(scarti, carta);
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

/**
 * Toglie una carta dal mazzo e la restituisce
 * @param mazzo Il mazzo da cui pescare
 * @return La carta pescata
 */
CartaCfu* cartaDalMazzo(CartaCfu** mazzo, CartaCfu** scarti){
    if(*mazzo == NULL && *scarti == NULL){
        printf("ERRORE: Il mazzo e gli scarti sono vuoti.\n");
        getchar();
        exit(-1);
    }
    if(*mazzo == NULL){
        coloreComunicazioni();
        printf("Si rimescolano gli scarti nel mazzo\n" RESET);
        logRimescola();
        *mazzo = *scarti;
        *scarti = NULL;
        mischiaMazzo(mazzo);
    }
    CartaCfu *carta = *mazzo;
    *mazzo = carta->prossima;
    carta->prossima = NULL;
    return carta;
}

/**
 * Inserisce una carta in cima alla mano di un giocatore
 * @param giocatore Il giocatore che deve prendere la carta
 * @param carta La carta da prendere
 */
void prendiCarta(Giocatore* giocatore, CartaCfu* carta){
    if(giocatore!=NULL && carta!=NULL){
        carta->prossima = giocatore->primaCfu;
        giocatore->primaCfu = carta;
    }
}

/** Questa funzione permette di pescare una carta.
 * La toglie dalla cima del mazzo e la mette in cima alla mano di un giocatore
 * @param giocatore Puntatore al giocatore che deve pescare
 * @param mazzo Puntatore al "mazzo", che a sua volta è un puntatore alla carta in cima
 * @param scarti Puntatore alla carta in cima al mazzo (serve quando il mazzo è vuoto)
 */
void pescaCarta(Giocatore* giocatore, CartaCfu** mazzo, CartaCfu** scarti){
    CartaCfu* carta = cartaDalMazzo(mazzo, scarti);
    logPescaCfu(*giocatore, *carta);
    // Il giocatore prende la carta in cima al mazzo
    carta->prossima = NULL;
    prendiCarta(giocatore, carta);
}

/** Tutti i giocatori pescano a rotazione finché non hanno tutti N_CARTE_MANO carte in mano
 * @param giocatori puntatore al primo giocatore
 * @param mazzo puntatore al mazzo, che a sua volta è un puntatore alla prima carta del mazzo
 */
void pescaRotazione(Giocatore* giocatori, CartaCfu** mazzo, CartaCfu** scarti){
    Giocatore* giocatore;
    bool finito = false;
    while(!finito) {
        giocatore = giocatori;
        finito = true;
        while (giocatore != NULL) {
            if (contaCarteMano(*giocatore) < N_CARTE_MANO) {
                finito = false;
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
    // Numero di carte nel mazzo
    int nCarte=0;
    int i=0, j=0;
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

    // Array che poi conterrà una permutazione casuale di interi da 0 a nCarte-1
    // Per adesso li contiene in ordine
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
    printf("=== Carte di %s:\n", giocatore.nomeUtente);
    CartaCfu* carta = giocatore.primaCfu;
    int i = 1;
    while(carta != NULL) {
        // Stampa il nome, se è una carta con effetto, e il valore
        if(carta->effetto<PRIMA_ISTANTANEA)
            printf("%d: %-32s %d CFU :%d %c\n", i, carta->nome, carta->cfu, i, cartaSpeciale(*carta));
        else
            printf("%d: %-32s       :%d %c\n", i, carta->nome, i, cartaSpeciale(*carta));
        carta = carta->prossima;
        i++;
    }
}

/**
 * Scarta tutte le carte e ne pesca altre N_CARTE_MANO
 * @param giocatore Il giocatore che deve scartare le carte e pescarne altre N_CARTE_MANO
 * @param mazzo Puntatore alla cima del mazzo, che a sua volta è un puntatore
 * @param scarti Puntatore alla cima degli scarti, che a sua volta è un puntatore
 */
void scartaMano(Giocatore* giocatore, CartaCfu** mazzo, CartaCfu** scarti){
    // Scarta tutte le carte
    while(giocatore->primaCfu != NULL){
        cartaNegliScarti(scarti, daiCarta(giocatore, giocatore->primaCfu));
    }
    for(int i=0; i<N_CARTE_MANO; i++){
        pescaCarta(giocatore, mazzo, scarti);
    }
}

/**
 * Controlla se il giocatore ha solo carte istantanee
 * @param giocatore Il giocatore da controllare
 * @return Vero se il giocatore ha solo carte istantanee in mano, falso altrimenti
 */
bool soloIstantanee(Giocatore giocatore){
    bool soloIstantanee = true;
    for(CartaCfu* carta = giocatore.primaCfu; soloIstantanee==true && carta != NULL; carta = carta->prossima)
        if(carta->effetto < PRIMA_ISTANTANEA)
            soloIstantanee = false;
    return soloIstantanee;
}

/**
 * Scambia due carte cfu
 * @param a Una carta
 * @param b L'altra carta
 */
void scambiaCarte(CartaCfu* a, CartaCfu* b){
    CartaCfu temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Mostra un menù per selezionare una carta dalla mano di un giocatore, e restituisce la carta selezionata
 * @param giocatore Il giocatore di cui si deve selezionare una carta
 * @param istantanee Vero se sono permesse le istantanee, falso altrimenti
 * @param effetto Vero se sono permesse le carte punto con effetto, falso altrimenti
 * @param normali Vero se sono permesse le carte senza effetto, falso altrimenti
 * @param annulla Vero se si può annullare la scelta, falso altrimenti
 * @return Puntatore alla carta selezionata, NULL se si annulla
 */
CartaCfu *selezionaCarta(Giocatore *giocatore, bool istantanee, bool effetto, bool normali, bool annulla) {

    // Secondo le regole del gioco, questo non dovrebbe mai succedere. Restituisce NULL solo se la chiamata lo può gestire
    if(!istantanee && !effetto && !normali){
        if(annulla)
            return NULL;
        istantanee = true;
        effetto = true;
        normali = true;
    }
    mostraCarte(*giocatore);
    if(annulla)
        printf("0: Annulla\n");
    int carteInMano = contaCarteMano(*giocatore);
    // Puntatori a due carte
    CartaCfu *carta = giocatore->primaCfu;
    int scelta=0;

    // Un array contenente le carte del giocatore
    CartaCfu* mano[carteInMano];
    for(int i=0; carta != NULL; carta = carta->prossima, i++){
        mano[i] = carta;
    }

    printf("Seleziona: ");
    bool sceltaValida = false;
    while(!sceltaValida){
        sceltaValida = false;
        scelta = inputCifra();
        // Si ripete l'input se almeno una delle condizioni è vera
        if(scelta==0){
            if(annulla)
                return NULL;
            else
                printf("Le carte sono numerate a partire da 1.\n");
        }
        else if(scelta<0)
            printf("Immetti un numero\n");
        else if(scelta-0>carteInMano)
            printf("Hai solo %d carte in mano.\n", carteInMano);
        else if(mano[scelta-1]->effetto == NESSUNO && !normali)
            printf("Non puoi selezionare una carta senza effetto.\n");
        else if(mano[scelta-1]->effetto != NESSUNO && mano[scelta-1]->effetto < PRIMA_ISTANTANEA && !effetto)
            printf("Non puoi selezionare una carta cfu con effetto.\n");
        else if(mano[scelta-1]->effetto >= PRIMA_ISTANTANEA && !istantanee)
            printf("Non e' la fase delle carte istantanee (%c).\n", SIMBOLO_CARTA_ISTANTANEA);
        else
            sceltaValida = true;
    }
    printf("\n");
    return mano[scelta-1];
}

