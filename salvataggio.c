#include "salvataggio.h"

void leggiSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)]){

    FILE* fp = fopen(nomeFile, "rb");

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

void scriviSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)]){

    Giocatore *giocatore = *giocatori;
    int nCarte, nOstacoli;
    CartaCfu *carta;
    CartaOstacolo *ostacolo;

    FILE *fp = fopen(nomeFile, "wb");

    // Si scrive il numero di giocatori
    fwrite(nGiocatori, sizeof(int), 1, fp);

    // Per ogni giocatore:
    for(int i=0; i<*nGiocatori; i++){
        // Si scrive il giocatore
        fwrite(giocatore, sizeof(Giocatore), 1, fp);

        // Si scrivono le carte cfu
        carta = giocatore->primaCfu;
        for(carta = giocatore->primaCfu; carta != NULL; carta = carta->prossima)
            fwrite(carta, sizeof(CartaCfu), 1, fp);

        // Si trova e si scrive il numero di ostacoli
        nOstacoli = 0;
        for(ostacolo = giocatore->primaOstacolo; ostacolo != NULL; ostacolo = ostacolo->prossima)
            nOstacoli++;
        fwrite(&nOstacoli, sizeof(int), 1, fp);

        // Si scrivono gli ostacoli
        for(ostacolo = giocatore->primaOstacolo; ostacolo != NULL; ostacolo = ostacolo->prossima)
            fwrite(ostacolo, sizeof(CartaOstacolo), 1, fp);

        giocatore = giocatore->prossimo;
    }

    // Per ognuno dei mazzi, si trova e si scrive il numero di carte e poi si scrive la lista in ordine

    nCarte = 0;
    for(carta = *carteCfu; carta != NULL; carta = carta->prossima)
        nCarte++;
    fwrite(&nCarte, sizeof(int), 1, fp);
    for(carta = *carteCfu; carta != NULL; carta = carta->prossima)
        fwrite(carta, sizeof(CartaCfu), 1, fp);

    nCarte = 0;
    for(carta = *scarti; carta != NULL; carta = carta->prossima)
        nCarte++;
    fwrite(&nCarte, sizeof(int), 1, fp);
    for(carta = *scarti; carta != NULL; carta = carta->prossima)
        fwrite(carta, sizeof(CartaCfu), 1, fp);

    nCarte = 0;
    for(ostacolo = *carteOstacolo; ostacolo != NULL; ostacolo = ostacolo->prossima)
        nCarte++;
    fwrite(&nCarte, sizeof(int), 1, fp);
    for(ostacolo = *carteOstacolo; ostacolo != NULL; ostacolo = ostacolo->prossima)
        fwrite(ostacolo, sizeof(CartaOstacolo), 1, fp);

    fwrite(nTurno, sizeof(int), 1, fp);

    fclose(fp);
}

void nomePartita(char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)]){
    nomeFile[LUNG_NOMI-1] = 0;
    printf("Dai un nome alla partita:\n");
    scanf("%s", nomeFile);
    while(nomeFile[LUNG_NOMI-1] != 0){
        printf("E' un nome troppo lungo!\nMassimo %d caratteri.\n", LUNG_NOMI);
        nomeFile[LUNG_NOMI-1] = 0;
        scanf("%s", nomeFile);
    }
    getchar();
    strcat(nomeFile, ESTENSIONE_SAV);
}

bool esisteSalvataggio(char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)]){
    FILE *fp;
    fp = fopen(nomeFile, "rb");
    if(fp==NULL){
        fclose(fp);
        return false;
    }else{
        fclose(fp);
        return true;
    }
}

void inizializzaSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, Personaggio personaggi[N_PERSONAGGI]){
    *nTurno = 0;
    // Puntatore alla prima carta del mazzo di carte CFU
    *carteCfu = leggiCarte();
    // Puntatore alla prima carta degli scarti CFU
    *scarti = NULL;

    // Puntatore alla prima carta del mazzo di carte ostacolo
    *carteOstacolo = leggiOstacoli();

    // Input del numero dei giocatori, input delle informazioni, assegnazione personaggi
    *nGiocatori = inputNGiocatori();
    *giocatori = inputGiocatori(*nGiocatori, 1);
    inizializzaGiocatori(*giocatori);
    assegnaPersonaggi(*giocatori, personaggi);
}