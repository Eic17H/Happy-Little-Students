//
// Created by eic17 on 25/03/2024.
//

#include "utilita.h"
#include "estetica.h"
#include "interfaccia.h"

/**
 * Stampa il logo leggendolo da immagine.txt e logo.txt
 */
void stampaLogo(){
    FILE *fp = fopen("immagine.txt", "r");
    // Il file non è necessario per il funzionamento del gioco
    if(fp == NULL)
        return;
    char c;
    int letto;
    letto = fscanf(fp, "%c", &c);
    // Una R rende il testo rosso, una Y giallo, una W bianco, gli altri caratteri vengono stampati
    while(letto>=0){
        switch(c){
            case 'R':
                printf(RED);
                break;
            case 'Y':
                printf(YEL);
                break;
            case 'W':
                printf(RESET);
                break;
            default:
                printf("%c", c);
                break;
        }
        letto = fscanf(fp, "%c", &c);
    }
    fclose(fp);

    printf("\n");

    fp = fopen("logo.txt", "r");
    if(fp == NULL)
        return;
    letto = fscanf(fp, "%c", &c);
    while(letto>=0){
        printf("%c", c);
        letto = fscanf(fp, "%c", &c);
    }
    printf("\n\n\n");
}

/**
 * Colora il testo basandosi sul tipo di una carta ostacolo. Poi va resettato.
 * Studio: rosso
 * Sopravvivenza: blu
 * Sociale: verde
 * Esame: giallo
 * @param tipo il tipo della carta.
 */
void coloreOstacoli(TipoOstacolo tipo){
    switch(tipo){
        case STUDIO:
            printf(RED);
            break;
        case SOPRAVVIVENZA:
            printf(BLU);
            break;
        case SOCIALE:
            printf(GRN);
            break;
        case ESAME:
            printf(YEL);
            break;
        default:
            printf(RESET);
            break;
    }
}

/**
 * Assegna indirettamente i colori ai personaggi
 * @param n L'n-esimo colore viene associato all'n-esimo personaggio)
 */
void coloreNumero(int n){
    switch(n){
        case 0:
            printf(MAG);
            break;
        case 1:
            printf(CYN);
            break;
        case 2:
            printf(GRN);
            break;
        case 3:
            printf(YEL);
            break;
        default:
            printf(RESET);
            break;
    }
}

/**
 * Imposta il colore del testo a quello associato a un certo personaggio
 * @param personaggio Il personaggio
 * @param personaggi L'array dei personaggi
 */
void colorePersonaggio(Personaggio personaggio, Personaggio personaggi[N_PERSONAGGI]){
    for(int i=0; i<N_PERSONAGGI; i++){
        if(strcmp(personaggio.nome, personaggi[i].nome) == 0)
            coloreNumero(i);
    }
}

/**
 * Imposta il colore del testo a quello associato al personaggio di un giocatore
 * @param giocatore Il giocatore
 * @param personaggi L'array dei personaggi
 */
void coloreGiocatore(Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI]){
    if(giocatore == NULL)
        return;
    colorePersonaggio(giocatore->personaggio, personaggi);
}

/**
 * Il colore usato per gli errori
 */
void coloreErrore(){
    printf(URED);
}

/**
 * Il colore usato per le comunicazioni importanti
 */
void coloreComunicazioni(){
    printf(UCYN);
}

/**
 * Il colore usato quando il giocatore prova a fare qualcosa che non può fare, o quando succede qualcosa di sfavorevole
 */
void coloreProblema(){
    printf(RED);
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