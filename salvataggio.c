#include "salvataggio.h"

void leggiSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno){
    FILE* fp = fopen("savegame.sav", "rb");

    // Puntatori che si useranno per scorrere la lista
    Giocatore *giocatore;
    CartaCfu *carta;
    CartaOstacolo *ostacolo;

    // Conterrà il numero di ostacoli del giocatore che si sta leggendo
    int nOstacoli;

    // Conterrà il numero di carte nel mazzo che si sta leggendo
    int nCarte;

    // Si legge il numero di giocatori
    fread(nGiocatori, sizeof(int), 1, fp);

    // Si alloca spazio per il primo giocatore
    *giocatori = malloc(sizeof(Giocatore));
    giocatore = *giocatori;
    for(int i=0; i<*nGiocatori; i++){
        // Si leggono i dati del giocatore corrente
        fread(giocatore, sizeof(Giocatore), 1, fp);

        // Si alloca spazio per la prima carta
        giocatore->primaCfu = malloc(sizeof(CartaCfu));
        carta = giocatore->primaCfu;
        for(int j=0; j<N_CARTE_MANO; j++){
            // Si leggono i dati della prima carta
            fread(carta, sizeof(CartaCfu), 1, fp);
            // Solo se non è l'ultima carta, si alloca spazio per la prossima carta
            if(j == N_CARTE_MANO-1)
                carta->prossima = NULL;
            else{
                carta->prossima = malloc(sizeof(CartaCfu));
                carta = carta->prossima;
            }
        }

        // Si usa lo stesso procedimento per tutte le liste
        giocatore->primaOstacolo = malloc(sizeof(CartaOstacolo));
        ostacolo = giocatore->primaOstacolo;
        fread(&nOstacoli, sizeof(int), 1, fp);
        // La lista può essere vuota
        if(nOstacoli == 0)
            giocatore->primaOstacolo = NULL;
        else{
            for (int j = 0; j < nOstacoli; j++) {
                fread(ostacolo, sizeof(CartaOstacolo), 1, fp);
                if(j==nOstacoli-1)
                    ostacolo->prossima = NULL;
                else {
                    ostacolo->prossima = malloc(sizeof(CartaOstacolo));
                    ostacolo = ostacolo->prossima;
                }
            }
        }

        // Lo stesso procedimento che si fa per l'ultima carta
        if(i==*nGiocatori-1)
            giocatore->prossimo = NULL;
        else{
            giocatore->prossimo = malloc(sizeof(Giocatore));
            giocatore = giocatore->prossimo;
        }
    }

    // Lo stesso procedimento usato per le altre liste si usa anche per i tre mazzi

    *carteCfu = malloc(sizeof(CartaCfu));
    carta = *carteCfu;
    fread(&nCarte, sizeof(int), 1, fp);
    for(int j=0; j<nCarte; j++){
        fread(carta, sizeof(CartaCfu), 1, fp);
        if(j == nCarte-1)
            carta->prossima = NULL;
        else {
            carta->prossima = malloc(sizeof(CartaCfu));
            carta = carta->prossima;
        }
    }

    *scarti = malloc(sizeof(CartaCfu));
    carta = *scarti;
    fread(&nCarte, sizeof(int), 1, fp);
    for(int j=0; j<nCarte; j++){
        fread(carta, sizeof(CartaCfu), 1, fp);
        if(j == nCarte-1)
            carta->prossima = NULL;
        else {
            carta->prossima = malloc(sizeof(CartaCfu));
            carta = carta->prossima;
        }
    }

    *carteOstacolo = malloc(sizeof(CartaOstacolo));
    ostacolo = *carteOstacolo;
    fread(&nCarte, sizeof(int), 1, fp);
    for(int j=0; j<nCarte; j++){
        fread(ostacolo, sizeof(CartaOstacolo), 1, fp);
        if(j==nCarte-1)
            ostacolo->prossima = NULL;
        else{
            ostacolo->prossima = malloc(sizeof(CartaOstacolo));
            ostacolo = ostacolo->prossima;
        }
    }

    // Si legge il numero del turno, e se non è presente si resetta
    int letti = fread(nTurno, sizeof(int), 1, fp);
    if(letti == 0)
        *nTurno = 0;

    fclose(fp);
}