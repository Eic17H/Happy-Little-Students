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
 * Dealloca una lista di carte cfu
 * @param mazzo La lista da deallocare
 */
void freeCfu(CartaCfu** mazzo){
    CartaCfu* carta = *mazzo;
    // Una a una, toglie tutte le carte dal mazzo e le dealloca, finché il mazzo non è vuoto
    while(*mazzo != NULL){
        *mazzo = (*mazzo)->prossima;
        free(carta);
        carta = *mazzo;
    }
}

/**
 * Dealloca una lista di carte ostacolo
 * @param mazzo La lista da deallocare
 */
void freeOstacoli(CartaOstacolo** mazzo){
    CartaOstacolo* carta = *mazzo;
    // Una a una, toglie tutte le carte dal mazzo e le dealloca, finché il mazzo non è vuoto
    while(*mazzo != NULL){
        *mazzo = (*mazzo)->prossima;
        free(carta);
        carta = *mazzo;
    }
}

/**
 * Dealloca una lista di giocatori e le liste associate a ciascun giocatore
 * @param lista La lista da deallocare
 */
void freeGiocatori(Giocatore** lista){
    Giocatore* giocatore = *lista;
    // Uno a uno, toglie tutti i giocatori dalla lista e opera su quello appena rimosso
    while(*lista != NULL){
        *lista = (*lista)->prossimo;
        // Dealloca le liste associate al giocatore
        freeCfu(&(giocatore->primaCfu));
        freeOstacoli(&(giocatore->primaOstacolo));
        // Dealloca il giocatore stesso
        free(giocatore);
        giocatore = *lista;
    }
}