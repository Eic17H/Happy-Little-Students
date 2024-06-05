#include "carteOstacolo.h"

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

bool troppiOstacoli(int carte[ESAME]){
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

void controlloOstacoli(Giocatore** giocatori, int* nGiocatori, Personaggio personaggi[N_PERSONAGGI]){
    if((*giocatori)->prossimo == NULL)
        return;
    Giocatore *giocatore=*giocatori, *giocatorePrec;
    CartaOstacolo *carta;
    int carte[4] = {0, 0, 0, 0};
    int punteggioprima=0;
    // scorri i giocatori
    for(giocatore = *giocatori; giocatore!=NULL; giocatore = giocatore->prossimo){
        punteggioprima = giocatore->cfu;
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
        // Solo se il giocatore non ha perso, diciamo se ha preso punti per le carte ostacolo
        }else if(giocatore->cfu != punteggioprima){
                colorePersonaggio(giocatore->personaggio, personaggi);
                printf("%s ha preso %d cfu per le carte ostacolo.\n" RESET, giocatore->nomeUtente, giocatore->cfu-punteggioprima);
            }
    }
}