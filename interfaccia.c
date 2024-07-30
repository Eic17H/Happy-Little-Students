#include "interfaccia.h"
#include "estetica.h"

/**
 * Stampa le carte ostacolo e i CFU di ciascun giocatore
 * @param giocatori Puntatore al primo giocatore
 * @param nGiocatori Numero corrente di giocatori
 * @param personaggi Array dei personaggi
 */
void stampaSituazione(Giocatore* giocatori, Personaggio personaggi[N_PERSONAGGI]){
    Giocatore* giocatore = giocatori;
    CartaOstacolo *carta;
    int i=0, continua=0;

    printf("\n");

    // Nomi
    for(giocatore=giocatori, i=0; giocatore!=NULL; giocatore=giocatore->prossimo, i++){
        colorePersonaggio(giocatore->personaggio, personaggi);
        printf("%32s: %2d CFU\t", giocatore->nomeUtente, giocatore->cfu);
        logCfu(*giocatore);
        for(carta = giocatore->primaOstacolo; carta != NULL; carta = carta->prossima) {
            stampaNomeOstacolo(*carta);
            printf("\t");
        }
        printf(RESET);
        printf("\n");
    }
    printf("\n\n");
}

/**
 * Indica se una carta ha un effetto
 * @param carta una carta cfu
 * @return un indicatore se la carta ha un effetto, uno spazio altrimenti
 */
char cartaSpeciale(CartaCfu carta){
    if(carta.effetto == 0)
        return ' ';
    else if(carta.effetto>=PRIMA_ISTANTANEA)
        return SIMBOLO_CARTA_ISTANTANEA;
    else
        return SIMBOLO_CARTA_EFFETTO;
}

void stampaVincitori(Giocatore* giocatori, Personaggio personaggi[N_PERSONAGGI]){
    // Non dovrebbe poter succedere, ma per sicurezza lo gestisco
    if(giocatori == NULL){
        coloreErrore();
        printf("Errore: la partita è terminata senza nessun vincitore.\n" RESET);
        return;
    }

    // Stampo il nome del primo vincitore
    stampaNomeGiocatoreColore(giocatori, personaggi);
    // Se non ci sono altri vincitori, il verbo è al singolare
    if(giocatori->prossimo == NULL)
        printf(" ha vinto!\n");
    // Altrimenti, stampo "e" e le virgole, e il verbo è al plurale
    else{
        while(giocatori->prossimo != NULL){
            giocatori = giocatori->prossimo;
            // Se sto per stampare l'ultimo, stampo "e", altrimenti una virgola.
            if(giocatori->prossimo == NULL)
                printf("e ");
            else
                printf(", ");
            stampaNomeGiocatoreColore(giocatori, personaggi);
        }
        printf(" hanno vinto!\n");
    }
}

/**
 * Stampa nome e punteggio provvisorio di ciascun giocatore
 * @param giocatori Puntatore al primo giocatore
 * @param punteggi Array dei punteggi provvisori
 * @param personaggi Array dei personaggi (serve per i colori)
 */
void stampaGiocatori(Giocatore* giocatori, Punteggio punteggi[], Personaggio personaggi[N_PERSONAGGI]){
    for(int i=1; giocatori!=NULL; i++, giocatori=giocatori->prossimo){
        coloreGiocatore(giocatori, personaggi);
        printf("%d: %s (%d CFU)\n" RESET, i, giocatori->nomeUtente, punteggi[i-1].totale);
    }
}

/** La funzione inputGiocatori chiede in input i nomi dei giocatori e li assegna al campo nomeUtente dei giocatori in una lista.
 * @param nGiocatori il numero di giocatori, preso in input dal main
 * @param nGiocatore da quale indice si comincia, di default 1
 * @return puntatore al primo giocatore
 */
Giocatore* inputGiocatori(int nGiocatori, int nGiocatore){
    if(nGiocatori==0)
        return NULL;
    Giocatore* giocatori = malloc(sizeof(Giocatore));
    printf("\n\n");
    printf("Giocatore %d:\n", nGiocatore);
    printf("=== INSERIRE NOME UTENTE ===\n");
    scanf("%s", giocatori->nomeUtente);
    getchar();
    giocatori->prossimo = inputGiocatori(nGiocatori-1, nGiocatore+1);
    printf(RESET);
    return giocatori;
}

/** La funzione nGiocatori legge in input il numero di giocatori, da 2 a 4.
 * @return il numero di giocatori
 */
int inputNGiocatori(){
    int nGiocatori=-1;
    while(nGiocatori > 4 || nGiocatori < 2){
        printf("Numero di giocatori (da 2 a 4):\n");
        nGiocatori = inputCifra();
    }
    return nGiocatori;
}

/**
 * Stampa le informazioni sui personaggi
 * @param personaggi
 */
void stampaPersonaggi(Personaggio personaggi[N_PERSONAGGI]){
    printf("\n\n\nOgni personaggio ha un bonus e un malus\n");
    printf("I bonus e i malus sono legati al tipo di ostacolo mostrato all'inizio del turno\n");
    printf("Se il tuo personaggio ha un malus legato a quel tipo,\nil tuo punteggio provvisorio sara' minore di quello che dovrebbe essere\n");
    printf("Nel caso dei bonus, sara' maggiore.\n");
    printf("Le carte ostacolo ");
    coloreOstacoli(ESAME);
    printf("esame" RESET " sono piu' rare e piu' pericolose.\n");
    for(int i=0; i<N_PERSONAGGI; i++) {
        // Stampa il nome del personaggio
        colorePersonaggio(personaggi[i], personaggi);
        printf("%i: %32s: ", i+1, personaggi[i].nome);
        // Stampa il colore del tipo associato al bonus
        for (int j = 0; j < N_TIPI_OSTACOLI; j++)
            if(personaggi[i].ostacoli[j] > 0){
                coloreOstacoli(j+1);
                printf("Bonus ");
            }
        // Stampa il colore del tipo associato al malus
        for (int j=0; j <N_TIPI_OSTACOLI; j++)
            if(personaggi[i].ostacoli[j] < 0){
                coloreOstacoli(j+1);
                printf("Malus\n");
            }
    }
    printf(RESET "\n\n");
}