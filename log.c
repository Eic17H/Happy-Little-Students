#include "log.h"

void creaLog(){
    FILE *fp = fopen("log.txt", "r");
    if(fp == NULL){
        fclose(fp);
        fp = fopen("log.txt", "w");
        fprintf(fp, "");
    }
    fclose(fp);
}

void logTurno(int nTurno){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "TURNO %d:\n", nTurno);
    fclose(fp);
}

void logCartaCfu(Giocatore giocatore, CartaCfu carta){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s gioca %s\n", giocatore.nomeUtente, carta.nome);
    fclose(fp);
}

void logEffettoCarta(Giocatore giocatore, CartaCfu carta, char effetto[]){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s attiva l'effetto di %s (%s)\n", giocatore.nomeUtente, carta.nome, effetto);
    fclose(fp);
}

void logPescaCfu(Giocatore giocatore, CartaCfu carta){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s pesca %s\n", giocatore.nomeUtente, carta.nome);
    fclose(fp);
}

void logOstacolo(Giocatore giocatore, CartaOstacolo carta){
    FILE *fp = fopen("log.txt", "w");
    fprintf(fp, "%s pesca l'ostacolo %s\n", giocatore.nomeUtente, carta.nome);
    fclose(fp);
}