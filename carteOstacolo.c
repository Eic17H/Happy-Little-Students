#include "carteOstacolo.h"

/** Questa funzione permette di pescare una carta.
 * La toglie dalla cima del mazzo e la mette in cima alla mano di un giocatore
 * @param giocatore puntatore al giocatore che deve pescare
 * @param mazzo puntatore al "mazzo", che a sua volta è un puntatore alla carta in cima
 */
void pescaOstacolo(Giocatore* giocatore, CartaOstacolo** mazzo){
    // TODO: colore personaggio
    printf("%s pesca la carta ostacolo.\n", giocatore->nomeUtente);
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

CartaOstacolo* togliOstacolo(CartaOstacolo** mazzo){
    CartaOstacolo* carta = *mazzo;
    *mazzo = carta->prossima;
    carta->prossima = NULL;
    return carta;
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

bool troppiOstacoli(int carte[4], int nGiocatori){
    int limite;
    if(nGiocatori == 2)
        limite = OSTACOLI_PER_PERDERE_2GIOCATORI;
    else
        limite = OSTACOLI_PER_PERDERE;
    // Per rendere più leggibili le espressioni sotto
    int limiteMiste = limite/(N_TIPI_OSTACOLI-1);

    // Tre/sei carte dello stesso colore (le carte esame contano in ogni caso)
    if(carte[STUDIO-1]+carte[ESAME-1]>=limite)
        return true;
    if(carte[SOPRAVVIVENZA-1]+carte[ESAME-1]>=limite)
        return true;
    if(carte[SOCIALE-1]+carte[ESAME-1]>=limite)
        return true;

    // Tre/sei carte di colore diverso (considerando le carte esame come ciascun colore)
    if(carte[STUDIO-1]+carte[ESAME-1]>=limiteMiste && carte[SOPRAVVIVENZA-1]>=limiteMiste && carte[SOCIALE-1]>=limiteMiste)
        return true;
    if(carte[STUDIO-1]>=limiteMiste && carte[SOPRAVVIVENZA-1]+carte[ESAME-1]>=limiteMiste && carte[SOCIALE-1]>=limiteMiste)
        return true;
    if(carte[STUDIO-1]>=limiteMiste && carte[SOPRAVVIVENZA-1]>=limiteMiste && carte[SOCIALE-1]+carte[ESAME-1]>=limiteMiste)
        return true;

    return false;
}

/**
 * Controlla quanti ostacoli hanno i giocatori, assegna i punti, e squalifica chi ha perso
 * @param giocatori Puntatore alla lista dei giocatori
 * @param nGiocatori Puntatore al numero di giocatori
 * @param personaggi Array dei personaggi
 */
void controlloOstacoli(Giocatore** giocatori, int* nGiocatori, Personaggio personaggi[N_PERSONAGGI]){
    if((*giocatori)->prossimo == NULL)
        return;
    Giocatore *giocatore=*giocatori, *giocatorePrec;
    CartaOstacolo *carta;
    int carte[4] = {0, 0, 0, 0};
    int precedente = 0;
    for(giocatore = *giocatori; giocatore!=NULL; giocatore = giocatore->prossimo){
        precedente = giocatore->cfu;
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
        if(giocatore->cfu-precedente != 0){
            prendiCfu(*giocatore, giocatore->cfu - precedente, false);
            coloreGiocatore(giocatore, personaggi);
            printf("%s ha preso %d CFU grazie alle carte ostacolo.\n" RESET, giocatore->nomeUtente,
                   giocatore->cfu - precedente);
        }
        // TODO: 2 giocatori (forse)
        if(troppiOstacoli(carte, *nGiocatori)){
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
 * Rimette un ostacolo in fondo al mazzo
 * @param mazzo Prima carta del mazzo (puntatore a struct)
 * @param ostacolo Carta da mettere nel mazzo (puntatore a struct)
 */
void rimettiOstacoloNelMazzo(CartaOstacolo* mazzo, CartaOstacolo* ostacolo){
    CartaOstacolo* carta;
    for(carta = mazzo; carta->prossima != NULL; carta = carta->prossima);
    carta->prossima = ostacolo;
    ostacolo->prossima = NULL;
}

/**
 * La carta ostacolo di questo turno viene rimessa in fondo al mazzo
 * @param mazzo Prima carta del mazzo, quella da mettere in fondo (puntatore a struct)
 */
void annullaOstacolo(CartaOstacolo** mazzo){
    rimettiOstacoloNelMazzo(*mazzo, togliOstacolo(mazzo));
}