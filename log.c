#include "log.h"

/**
 * Segnala l'inizio della partita nel file log.txt, creandolo se non esiste già
 * @param nome Nome della partita (inclusa l'estensione)
 */
void creaLog(char nome[LUNG_NOMI+strlen(ESTENSIONE_SAV)]){
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

/**
 * Segna l'inizio di un turno nel log
 * @param nTurno Numero del turno corrente
 */
void logTurno(int nTurno){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "TURNO %d:\n", nTurno);
    fclose(fp);
}

/**
 * Segna l'utilizzo di una carta CFU nel log
 * @param giocatore Giocatore che ha giocato la carta
 * @param carta Carta giocata
 */
void logCartaCfu(Giocatore giocatore, CartaCfu carta){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s gioca %s (%d CFU)\n", giocatore.nomeUtente, carta.nome, carta.cfu);
    fclose(fp);
}

/**
 * Segna l'attivazione dell'effetto di una carta nel log
 * @param giocatore Giocatore che ha giocato la carta
 * @param carta Carta giocata
 * @param effetto Nome dell'effetto
 */
void logEffettoCarta(Giocatore giocatore, CartaCfu carta, char effetto[LUNG_NOMI]){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s attiva l'effetto di %s (%s)\n", giocatore.nomeUtente, carta.nome, effetto);
    fclose(fp);
}

/**
 * Segna che un giocatore ha pescato una carta nel log
 * @param giocatore Il giocatore che ha pescato
 * @param carta La carta pescata
 */
void logPescaCfu(Giocatore giocatore, CartaCfu carta){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s pesca %s\n", giocatore.nomeUtente, carta.nome);
    fclose(fp);
}

/**
 * Segna che un giocatore ha pescato una carta ostacolo
 * @param giocatore Il giocatore che ha pescato l'ostacolo
 * @param carta L'ostacolo
 */
void logOstacolo(Giocatore giocatore, CartaOstacolo carta){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s pesca l'ostacolo %s\n", giocatore.nomeUtente, carta.nome);
    fclose(fp);
}

/**
 * Segna nel log che un giocatore ha vinto
 * @param giocatore Il giocatore che ha vinto
 * @param punti Vero se ha vinto perché ha abbastanza punti, falso se ha vinto perché è l'ultimo rimasto
 */
void logVince(Giocatore giocatore, bool punti){
    FILE *fp = fopen("log.txt", "a");
    if(punti)
        fprintf(fp, "%s vince perche' ha abbastanza CFU\n", giocatore.nomeUtente);
    else
        fprintf(fp, "%s vince perche' e' l'ultimo giocatore rimasto\n", giocatore.nomeUtente);
    fclose(fp);
}

/**
 * Segna nel log quanti punti ha un giocatore
 * @param giocatore Il giocatore
 */
void logCfu(Giocatore giocatore){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s ha %d CFU\n", giocatore.nomeUtente, giocatore.cfu);
    fclose(fp);
}

/**
 * Segna nel log che è stato usato l'effetto ruba
 * @param ladro Il giocatore che ha attivato l'effetto
 * @param vittima Il giocatore che ha subito l'effetto
 * @param carta La carta usata
 */
void logRuba(Giocatore ladro, Giocatore vittima, CartaCfu carta){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s ruba %s a %s\n", ladro.nomeUtente, carta.nome, vittima.nomeUtente);
    fclose(fp);
}

/**
 * Segna nel log che un giocatore ha guadagnato CFU
 * @param giocatore Il giocatore
 * @param nCfu Quanti CFU ha guadagnato
 * @param carte Vero se sono dovuti alle carte CFU, falso se sono dovuti alle carte ostacolo
 */
void logPrendiCfu(Giocatore giocatore, int nCfu, bool carte){
    FILE *fp = fopen("log.txt", "a");
    if(carte)
        fprintf(fp, "%s prende %d CFU grazie alle carte giocate\n", giocatore.nomeUtente, nCfu);
    else
        fprintf(fp, "%s prende %d CFU grazie alle carte ostacolo\n", giocatore.nomeUtente, nCfu);
    fclose(fp);
}

/**
 * Segna nel log che un giocatore si è arreso
 * @param giocatore Il giocatore che si è arreso
 */
void logArrende(Giocatore giocatore){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s si arrende\n", giocatore.nomeUtente);
    fclose(fp);
}

/**
 * Segna nel log che un giocatore ha messo in fondo al mazzo la carta ostacolo che stava per pescare
 * @param giocatore Il giocatore
 * @param carta La carta rimessa nel mazzo
 */
void logSalva(Giocatore giocatore, CartaCfu carta){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s si salva usando la carta %s\n", giocatore.nomeUtente, carta.nome);
    fclose(fp);
}

/**
 * Segna nel log che un giocatore, anziché pescare una carta ostacolo, l'ha fatta pescare a un altro giocatore
 * @param giocatore Il giocatore che stava per pescare l'ostacolo
 * @param carta L'ostacolo
 * @param vittima Il giocatore che ha dovuto pescare l'ostacolo
 */
void logDirotta(Giocatore giocatore, CartaCfu carta, Giocatore vittima){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s da' l'ostacolo a %s usando la carta %s\n", giocatore.nomeUtente, vittima.nomeUtente, carta.nome);
    fclose(fp);
}

/**
 * Segna nel log che un giocatore ha scartato una carta cfu (istantanea o punto)
 * @param giocatore Il giocatore che ha scartato la carta
 * @param carta La carta scartata
 */
void logScarta(Giocatore giocatore, CartaCfu carta){
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "%s scarta la carta %s\n", giocatore.nomeUtente, carta.nome);
    fclose(fp);
}

/**
 * Segna nel log che un giocatore ha aumentato o diminuito il punteggio di un altro giocatore
 * @param giocatore Il giocatore che ha giocato la carta per aumentare o diminuire il punteggio
 * @param vittima Il giocatore che subisce l'aumento o la diminuzione
 * @param valore Il valore con cui è stata chiamata la funzione che attiva la carta (positivo per aumentare, negativo per diminuire, 0 non fa niente)
 */
void logAumentaDiminuisci(Giocatore giocatore, Giocatore vittima, int valore){
    FILE *fp = fopen("log.txt", "a");
    if(valore>0)
        fprintf(fp, "%s aumenta il punteggio di %s\n", giocatore.nomeUtente, vittima.nomeUtente);
    if(valore<0)
        fprintf(fp, "%s diminuisce il punteggio di %s\n", giocatore.nomeUtente, vittima.nomeUtente);
    fclose(fp);
}