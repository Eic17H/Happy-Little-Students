#include "carteEffetto.h"

/**
 * Stampa la descrizione dell'effetto di una carta cfu
 * @param carta La carta
 */
void stampaEffetto(CartaCfu carta){
    switch(carta.effetto){
        case NESSUNO:
            printf("Nessun effetto.\n");
            break;
        case SCARTAP:
            printf("Scarta una" YEL " carta CFU punto " RESET "e aggiungi il suo punteggio a quello del turno.\n");
            break;
        case RUBA:
            printf("Guarda la mano di un collega e ruba una carta a scelta.\n");
            break;
        case SCAMBIADS:
            printf("Scambia questa carta con quella di un altro giocatore, purche' senza effetto.\n");
            break;
        case SCARTAE:
            printf("Scarta una" YEL " carta CFU punto " RESET "con" CYN " effetto " RESET "e aggiungi il suo punteggio a quello del turno.\n");
            break;
        case SCARTAC:
            printf("Scarta da uno a tre carte dalla tua mano.\n");
            break;
        case SCAMBIAP:
            printf("Scambia il punteggio del turno maggiore e minore dopo il calcolo del punteggio di base.\n");
            break;
        case DOPPIOE:
            printf("Raddoppia gli" CYN " effetti " RESET "delle carte che aumentano o diminuiscono il punteggio (per tutti).\n");
            break;
        case SBIRCIA:
            printf("Guarda due carte in cima al mazzo, prendine una e scarta l'altra.\n");
            break;
        case SCAMBIAC:
            printf("Scambia la carta punto giocata nel turno da un giocatore G1 con quella di un giocatore G2, con G1 e G2 scelti dal giocatore che ha giocato la carta.\n");
            break;
        case ANNULLA:
            printf("Annulla gli" CYN " effetti " RESET "di tutte le carte punto durante il turno.\n");
            break;
        case AUMENTA:
            printf("Aumenta di 2" YEL " CFU " RESET "il punteggio del turno di un giocatore a scelta.\n");
            break;
        case DIMINUISCI:
            printf("Diminuisci di 2" YEL " CFU " RESET "il punteggio del turno di un giocatore a scelta.\n");
            break;
        case INVERTI:
            printf("Inverti punteggio minimo e massimo del turno.\n");
            break;
        case SALVA:
            printf("Metti la carta" RED " Ostacolo " RESET "che stai per prendere in fondo al mazzo.\n");
            break;
        case DIROTTA:
            printf("Dai la carta" RED " Ostacolo " RESET "che stai per prendere ad un altro giocatore a tua scelta.\n");
            break;
        default:
            break;
    }
}

/**
 * Usa l'effetto di una carta cfu
 * @param carta La carta
 */
void usaEffetto(CartaCfu carta){
    switch(carta.effetto){
        case NESSUNO:
            break;
        case SCARTAP:
            scartaP();
            break;
        case RUBA:
            ruba();
            break;
        case SCAMBIADS:
            scambiaDS();
            break;
        case SCARTAE:
            scartaE();
            break;
        case SCARTAC:
            scartaC();
            break;
        case SCAMBIAP:
            scambiaP();
            break;
        case DOPPIOE:
            doppioE();
            break;
        case SBIRCIA:
            sbircia();
            break;
        case SCAMBIAC:
            scambiaC();
            break;
        case ANNULLA:
            annulla();
            break;
        case AUMENTA:
            aumenta();
            break;
        case DIMINUISCI:
            diminuisci();
            break;
        case INVERTI:
            inverti();
            break;
        case SALVA:
            salva();
            break;
        case DIROTTA:
            dirotta();
            break;
        default:
            break;
    }
}

void scartaP(){
    return;
}
void ruba(){
    return;
}
void scambiaDS(){
    return;
}
void scartaE(){
    return;
}
void scartaC(){
    return;
}
void scambiaP(){
    return;
}
void doppioE(){
    return;
}
void sbircia(){
    return;
}
void scambiaC(){
    return;
}
void annulla(){
    return;
}
void aumenta(){
    return;
}
void diminuisci(){
    return;
}
void inverti(){
    return;
}
void salva(){
    return;
}
void dirotta(){
    return;
}