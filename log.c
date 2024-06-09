#include "log.h"

void creaLog(){
    // Si prova ad aprire il file del log
    FILE *fp = fopen("log.txt", "r");

    // Se non esiste, lo si crea, vuoto
    if(fp == NULL){
        fclose(fp);
        fp = fopen("log.txt", "w");
        fprintf(fp, "");
    // Se esiste già, si va a capo per separare questa partita dalla precedente
    }else{
        fclose(fp);
        fp = fopen("log.txt", "w");
        fprintf(fp, "\n");
    }
    // Si segna l'inizio della partita
    fprintf(fp, "INIZIO PARTITA\n");
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