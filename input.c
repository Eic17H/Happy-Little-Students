#include "input.h"

/** La funzione inputGiocatori chiede in input i nomi dei giocatori e li assegna al campo nomeUtente dei giocatori in una lista.
 * @param nGiocatori il numero di giocatori, preso in input dal main
 * @param nGiocatore da quale indice si comincia, di default 1
 * @return puntatore al primo giocatore
 */
Giocatore* inputGiocatori(int nGiocatori, int nGiocatore){
    coloreNumero(nGiocatore);
    if(nGiocatori==0)
        return NULL;
    Giocatore* giocatori = malloc(sizeof(Giocatore));
    printf("\n\n");
    printf("Giocatore %d:\n", nGiocatore);
    printf("=== INSERIRE NOME UTENTE ===\n");
    scanf("%s", giocatori->nomeUtente);
    giocatori->prossimo = inputGiocatori(nGiocatori-1, nGiocatore+1);
    printf(RESET);
    return giocatori;
}

/** La funzione nGiocatori legge in input il numero di giocatori, da 2 a 4.
 * @return il numero di giocatori
 */
int inputNGiocatori(){
    int nGiocatori;
    do{
        printf("Numero di giocatori (da 2 a 4):\n");
        scanf("%d", &nGiocatori);
        getc(NULL);
    }while(nGiocatori > 4 || nGiocatori < 2);
    return nGiocatori;
}

// TODO: rimuovere
void stampaNomiGiocatori(Giocatore* test){
    while(test != NULL){
        printf("%s ", test->nomeUtente);
        test = test->prossimo;
    }
    printf("\n");
}