#include "log.h"

void creaLog(char nome[LUNG_NOMI]){
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
        fp = fopen("log.txt", "a");
        fprintf(fp, "\n");
    }
    fclose(fp);
    fp = fopen("log.txt", "a");
    // Si segna l'inizio della partita
    fprintf(fp, "INIZIO PARTITA: %s\n", nome);
    fclose(fp);
}

void logTurno(int nTurno){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "TURNO %d:\n", nTurno);
    fclose(fp);
}

void logCartaCfu(Giocatore giocatore, CartaCfu carta){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s gioca %s (%d CFU)\n", giocatore.nomeUtente, carta.nome, carta.cfu);
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
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s pesca l'ostacolo %s\n", giocatore.nomeUtente, carta.nome);
    fclose(fp);
}

void logVince(Giocatore giocatore, bool punti){
    FILE *fp = fopen("log.txt", "a");
    if(punti)
        fprintf(fp, "%s vince perche' ha abbastanza CFU\n", giocatore.nomeUtente);
    else
        fprintf(fp, "%s vince perche' e' l'ultimo giocatore rimasto\n", giocatore.nomeUtente);
    fclose(fp);
}

void logCfu(Giocatore giocatore){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s ha %d CFU\n", giocatore.nomeUtente, giocatore.cfu);
    fclose(fp);
}

void logRuba(Giocatore ladro, Giocatore vittima, CartaCfu carta){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s ruba %s a %s\n", ladro.nomeUtente, carta.nome, vittima.nomeUtente);
    fclose(fp);
}

void prendiCfu(Giocatore giocatore, int nCfu, bool carte){
    FILE *fp = fopen("log.txt", "a");
    if(carte)
        fprintf(fp, "%s prende %d CFU grazie alle carte giocate\n", giocatore.nomeUtente, nCfu);
    else
        fprintf(fp, "%s prende %d CFU grazie alle carte ostacolo\n", giocatore.nomeUtente, nCfu);
    fclose(fp);
}

void logTesto(char string[256]){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s", string);
    fclose(fp);
}

void logArrende(Giocatore giocatore){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s si arrende\n", giocatore.nomeUtente);
    fclose(fp);
}