//
// Created by eic17 on 27/05/2024.
//

#include "estetica.h"
#include "utilita.h"

/**
 * Scambia due interi
 * @param a Puntatore al primo intero
 * @param b Puntatore al secondo intero
 */
void scambiaInt(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Gestisce l'input di un intero a una cifra, evitando i problemi che ha scanf() quando si immette una lettera
 * @return Un numero da 0 a 9 se non ci sono errori, -1 altrimenti
 */
int inputCifra(){
    char c;
    scanf("%c", &c);
    getchar();
    if(c<'0' || c>'9')
        return -1;
    return c - '0';
}

/**
 * Stampa il nome di un giocatore con il colore del suo personaggio
 * @param giocatore Il giocatore
 * @param personaggi L'array dei personaggi
 */
void stampaNomeGiocatoreColore(Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI]){
    coloreGiocatore(giocatore, personaggi);
    printf("%s" RESET, giocatore->nomeUtente);
}

/**
 * Dealloca una lista di carte cfu
 * @param mazzo La lista da deallocare
 */
void freeCfu(CartaCfu** mazzo){
    CartaCfu* prima = *mazzo;
    CartaCfu* seconda = prima->prossima;
    while(prima != NULL){
        if(prima->prossima != NULL)
            seconda = prima->prossima;
        free(prima);
        prima = seconda;
    }
}

/**
 * Dealloca una lista di carte ostacolo
 * @param mazzo La lista da deallocare
 */
void freeOstacoli(CartaOstacolo** mazzo){
    CartaOstacolo* prima = *mazzo;
    CartaOstacolo* seconda = prima->prossima;
    while(prima != NULL){
        if(prima->prossima != NULL)
            seconda = prima->prossima;
        free(prima);
        prima = seconda;
    }
}

/**
 * Dealloca una lista di giocatori e le liste associate a ciascun giocatore
 * @param lista La lista da deallocare
 */
void freeGiocatori(Giocatore** lista){
    Giocatore* primo = *lista;
    Giocatore* secondo = primo->prossimo;
    while(primo != NULL){
        if(primo->prossimo != NULL)
            secondo = primo->prossimo;
        freeCfu(&(primo->primaCfu));
        freeOstacoli(&(primo->primaOstacolo));
        free(primo);
        primo = secondo;
    }
}