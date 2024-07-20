//
// Created by eic17 on 25/03/2024.
//

#include "estetica.h"
#include "utilita.h"
#include "carteEffetto.h"

/**
 * Stampa il logo leggendolo da immagine.txt e logo.txt
 */
void stampaLogo(){
    FILE *fp = fopen("immagine.txt", "r");
    if(fp == NULL)
        exit(-1);
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
        exit(-1);
    letto = fscanf(fp, "%c", &c);
    while(letto>=0){
        printf("%c", c);
        letto = fscanf(fp, "%c", &c);
    }
    printf("\n\n\n");
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

void stampaOstacolo(CartaOstacolo carta){
    stampaNomeOstacolo(carta);
    printf("\n");
    stampaDescOstacolo(carta);
    printf("\n\n");
}

void stampaNomeOstacolo(CartaOstacolo carta){
    coloreOstacoli(carta.tipo);
    printf("%s" RESET, carta.nome);
}

void stampaDescOstacolo(CartaOstacolo carta){
    coloreOstacoli(carta.tipo);
    printf("%s" RESET, carta.descrizione);
}

/**
 * Assegna indirettamente i colori ai personaggi
 * @param n L'n-esimo colore viene associato all'n-esimo personaggio (personaggi[n-1] nell'array)
 */
void coloreNumero(int n){
    switch(n){
        case 1:
            printf(MAG);
            break;
        case 2:
            printf(CYN);
            break;
        case 3:
            printf(GRN);
            break;
        case 4:
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
    // I personaggi partono da 0, ma i giocatori sono numerati da 1
    for(int i=0; i<N_PERSONAGGI; i++){
        if(strcmp(personaggio.nome, personaggi[i].nome) == 0)
            coloreNumero(i+1);
    }
}

/**
 * Imposta il colore del testo a quello associato al personaggio di un giocatore
 * @param personaggio Il giocatore
 * @param personaggi L'array dei personaggi
 */
void coloreGiocatore(Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI]){
    if(giocatore == NULL)
        return;
    colorePersonaggio(giocatore->personaggio, personaggi);
}

// TODO: interfaccia.c

/**
 * Stampa le carte ostacolo e i CFU di ciascun giocatore
 * @param giocatori Puntatore al primo giocatore
 * @param nGiocatori Numero corrente di giocatori
 * @param personaggi Array dei personaggi
 */
void stampaSituazione(Giocatore* giocatori, int nGiocatori, Personaggio* personaggi){
    Giocatore* giocatore = giocatori;
    CartaOstacolo *carta;
    int i=0, continua=0;

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

void aiuto(int scelta){
    switch(scelta){
        case 0:
            printf("Una carta senza segnalino e' una carta che non ha un effetto.\n");
            break;
        case 1:
            printf("Una carta con il segnalino \"%c\" e' una carta con effetto che puoi usare nella prima fase del turno.\n", SIMBOLO_CARTA_EFFETTO);
            break;
        case 2:
            printf("Una carta con il segnalino \"%c\" e' una carta istantanea, da usare dopo il calcolo del punteggio.\n", SIMBOLO_CARTA_ISTANTANEA);
    }
}

