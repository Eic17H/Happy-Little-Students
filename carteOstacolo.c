#include "carteOstacolo.h"
#include "estetica.h"

/** Questa funzione permette di pescare una carta.
 * La toglie dalla cima del mazzo e la mette in cima alla mano di un giocatore
 * @param giocatore puntatore al giocatore che deve pescare
 * @param mazzo puntatore al "mazzo", che a sua volta è un puntatore alla carta in cima
 */
void pescaOstacolo(Giocatore* giocatore, CartaOstacolo** mazzo, Personaggio personaggi[N_PERSONAGGI]){
    stampaNomeGiocatoreColore(giocatore, personaggi);
    printf(" pesca la carta ostacolo.\n");
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

/**
 * Rimuove la carta in cima al mazzo degli ostacoli e la restituisce
 * @param mazzo Puntatore al mazzo degli ostacoli
 * @return La carta che era in cima al mazzo
 */
CartaOstacolo* togliOstacolo(CartaOstacolo** mazzo){
    CartaOstacolo* carta = *mazzo;
    // Il mazzo comincia dalla carta successiva
    *mazzo = carta->prossima;
    // La carta viene scollegata dal mazzo
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
    // L'ultima carta della lista non punta a niente
    carta->prossima = NULL;
}

/**
 * Controlla se un giocatore ha abbastanza carte ostacolo per perdere
 * @param carte L'array del conteggio di ciascun tipo di ostacolo
 * @return Vero se ha perso, falso altrimenti
 */
bool troppiOstacoli(int carte[4]){

    // L'enum comincia da 1, l'array comincia da 0

    // Tre carte dello stesso colore (le carte esame contano in ogni caso)
    if(carte[STUDIO-1]+carte[ESAME-1]>=N_TIPI_OSTACOLI)
        return true;
    if(carte[SOPRAVVIVENZA-1]+carte[ESAME-1]>=N_TIPI_OSTACOLI)
        return true;
    if(carte[SOCIALE-1]+carte[ESAME-1]>=N_TIPI_OSTACOLI)
        return true;

    // Tre carte di colore diverso (considerando le carte esame come ciascun colore)
    if(carte[STUDIO-1]+carte[ESAME-1]>=1 && carte[SOPRAVVIVENZA-1]>=1 && carte[SOCIALE-1]>=1)
        return true;
    if(carte[STUDIO-1]>=1 && carte[SOPRAVVIVENZA-1]+carte[ESAME-1]>=1 && carte[SOCIALE-1]>=1)
        return true;
    if(carte[STUDIO-1]>=1 && carte[SOPRAVVIVENZA-1]>=1 && carte[SOCIALE-1]+carte[ESAME-1]>=1)
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
    int carte[N_TIPI_OSTACOLI] = {0};
    int precedente = 0;
    for(giocatore = *giocatori; giocatore!=NULL; giocatore = giocatore->prossimo){
        precedente = giocatore->cfu;
        for(int i=0; i<N_TIPI_OSTACOLI; i++)
            carte[i] = 0;
        // scorre le carte ostacolo
        for(carta = giocatore->primaOstacolo; carta!=NULL; carta = carta->prossima){
            // Aumento CFU per ogni carta ostacolo
            giocatore->cfu++;
            // Evita problemi se l'enum e la macro non corrispondono
            if(carta->tipo - 1 < N_TIPI_OSTACOLI)
                carte[carta->tipo - 1]++;
        }
        // Stampa l'avviso solo se il punteggio è cambiato
        if(giocatore->cfu - precedente != 0){
            logPrendiCfu(*giocatore, giocatore->cfu - precedente, false);
            coloreGiocatore(giocatore, personaggi);
            printf("%s ha preso %d CFU grazie alle carte ostacolo.\n" RESET, giocatore->nomeUtente, giocatore->cfu - precedente);
        }
        if(troppiOstacoli(carte)){
            // Testo rosso
            coloreProblema();
            printf("\n\n");
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
    // Scorre fino al fondo del mazzo
    for(carta = mazzo; carta->prossima != NULL; carta = carta->prossima);
    // Collega la carta al mazzo
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

/**
 * Stampa nome e descrizione di una carta ostacolo
 * @param carta La carta da stampare
 */
void stampaOstacolo(CartaOstacolo carta){
    stampaNomeOstacolo(carta);
    printf("\n");
    stampaDescOstacolo(carta);
    printf("\n\n");
}

/**
 * Stampa il nome di una carta ostacolo
 * @param carta La carta da stampare
 */
void stampaNomeOstacolo(CartaOstacolo carta){
    coloreOstacoli(carta.tipo);
    printf("%s" RESET, carta.nome);
}

/**
 * Stampa la descrizione di una carta ostacolo
 * @param carta La carta da stampare
 */
void stampaDescOstacolo(CartaOstacolo carta){
    coloreOstacoli(carta.tipo);
    printf("%s" RESET, carta.descrizione);
}