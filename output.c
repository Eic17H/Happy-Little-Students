//
// Created by eic17 on 27/05/2024.
//

#include "output.h"

/**
 * Mostra le carte in mano a un giocatore
 * @param giocatore
 */
void mostraCarte(Giocatore giocatore){
    printf("\t===== Mano di %s =====\n", giocatore.nomeUtente);
    CartaCfu* carta = giocatore.primaCfu;
    int i = 1;
    while(carta != NULL) {
        // Stampa il nome, se è una carta con effetto, e il valore
        printf("%d: %-32s %c %d CFU :%d\n", i, carta->nome, cartaSpeciale(*carta), carta->cfu, i);
        carta = carta->prossima;
        i++;
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