//
// Created by eic17 on 05/06/2024.
//

#include "carte.h"

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