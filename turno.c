#include "turno.h"

void mostraCarte(Giocatore giocatore){
    printf("\t===== Mano di %s =====\n", giocatore.nomeUtente);
    CartaCfu* carta = giocatore.primaCfu;
    while(carta != NULL) {
        printf("%-32s %d CFU\n", carta->nome, carta->cfu);
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
    int nCarte=0, i=0, rand1, rand2;
    CartaCfu *carta = *mazzo, *r1, *r2, *p1, *p2, *pp1, *pp2;
    while(carta != NULL){
        nCarte++;
        carta = carta->prossima;
    }
    CartaCfu* carte[nCarte];
    carta = *mazzo;
    while(carta != NULL){
        carte[i] = carta;
        carta = carta->prossima;
        i++;
    }
    for(i=0; i<nCarte; i++){
        rand1 = rand()%(nCarte-2);
        rand2 = rand()%(nCarte-2);
        r1 = carte[rand1];
        r2 = carte[rand2];
        p1 = r1->prossima;
        p2 = r2->prossima;
        pp1 = p1->prossima;
        pp2 = p2->prossima;
        r1->prossima->prossima = pp2;
        r2->prossima->prossima = pp1;
        r1->prossima = p2;
        r2->prossima = p1;
    }
}

/** Mischia il mazzo degli ostacoli
 * @param mazzo puntatore al mazzo degli ostacoli, che a sua volta è un puntatore alla sua prima carta
 */
void mischiaOstacoli(CartaOstacolo** mazzo){
    int nCarte=0, i=0, rand1, rand2;
    CartaOstacolo *carta = *mazzo, *r1, *r2, *p1, *p2, *pp1, *pp2;
    while(carta != NULL){
        nCarte++;
        carta = carta->prossima;
    }
    CartaOstacolo* carte[nCarte];
    carta = *mazzo;
    while(carta != NULL){
        carte[i] = carta;
        carta = carta->prossima;
        i++;
    }
    for(i=0; i<nCarte; i++){
        rand1 = rand()%(nCarte-2);
        rand2 = rand()%(nCarte-2);
        r1 = carte[rand1];
        r2 = carte[rand2];
        p1 = r1->prossima;
        p2 = r2->prossima;
        pp1 = p1->prossima;
        pp2 = p2->prossima;
        r1->prossima->prossima = pp2;
        r2->prossima->prossima = pp1;
        r1->prossima = p2;
        r2->prossima = p1;
    }
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
    Giocatore* giocatore = giocatori;
    for(giocatore = giocatori; giocatore != NULL; giocatore = giocatore->prossimo){
        if(giocatore->cfu >= PUNTI_PER_VINCERE)
            return giocatore;
    }
    return NULL;
}

/**
 * Spareggio per gli sconfitti
 * @param giocatori puntatore al primo giocatore
 * @param nGiocatori numero di giocatori
 * @param sconfitti array degli spareggianti
 * @return puntatore al giocatore che perde
 */
Giocatore* spareggio(Giocatore* giocatori, int nGiocatori, int* sconfitti){
    return giocatori;
}

/** Il turno
 * @param giocatori puntatore al primo giocatore
 * @param nGiocatori il numero di giocatori
 * @param carteCfu mazzo cfu
 * @param scarti pila degli scarti
 * @param carteOstacolo mazzo degli ostacoli
 */
void turno(Giocatore* giocatori, int nGiocatori, CartaCfu** carteCfu, CartaCfu** scarti, CartaOstacolo** carteOstacolo){
    Giocatore* giocatore = giocatori;
    int i=0, cfuTurno[nGiocatori], min=0, max=0;
    int nSconfitti = 0, sconfitti[nGiocatori];
    pescaRotazione(giocatori, carteCfu);

    printf("%s\n%s\n\n", (*carteOstacolo)->nome, (*carteOstacolo)->descrizione);

    for(giocatore=giocatori; giocatore!=NULL; giocatore=giocatore->prossimo){
        printf("%s: %d cfu\n", giocatore->nomeUtente, giocatore->cfu);
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
    printf("AAAAA\n");
    // Vincitori
    for(i=0, giocatore=giocatori; i<nGiocatori; i++, giocatore = giocatore->prossimo){
        if(cfuTurno[i]==cfuTurno[max])
            giocatore->cfu += cfuTurno[i];
    }
    printf("BBBBB\n");
    // Perdente
    for(i=0; i<nGiocatori; i++){
        if(cfuTurno[i] == cfuTurno[min])
            sconfitti[i] = 1;
        else
            sconfitti[i] = 0;
    }
    giocatore = spareggio(giocatori, nGiocatori, sconfitti);
    pescaOstacolo(giocatore, carteOstacolo);
}