#include "interfaccia.h"
#include "carteOstacolo.h"
#include "turno.h"
#include "salvataggio.h"

/**
 * Se esiste un salvataggio con il nome selezionato, chiede se caricarlo.
 * Se si è deciso di non caricare il salvataggio, o se non esiste, inizializza le variabili
 * @param nGiocatori Puntatore al numero corrente di giocatori
 * @param giocatori Puntatore alla lista di giocatori
 * @param carteCfu Puntatore al mazzo delle carte cfu
 * @param scarti Puntatore al mazzo degli scarti
 * @param carteOstacolo Puntatore al mazzo degli ostacoli
 * @param nTurno Puntatore al numero del turno
 * @param nomeFile Nome del file (inclusa l'estensione .sav)
 * @param personaggi Array dei personaggi letti dal file
 */
void iniziaSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)], Personaggio personaggi[N_PERSONAGGI]){
    int scelta=0;
    if(esisteSalvataggio(nomeFile)){
        printf("Vuoi caricare il file di salvataggio? 1 per si', no altrimenti\n");
        scelta = inputCifra();
    }else{
        scelta = 0;
    }
    if(scelta==1)
        leggiSalvataggio(nGiocatori, giocatori, carteCfu, scarti, carteOstacolo, nTurno, nomeFile);
    else
        inizializzaSalvataggio(nGiocatori, giocatori, carteCfu, scarti, carteOstacolo, nTurno, personaggi);
}

/**
 * Salva la partita dentro un file binario
 * @param nGiocatori Puntatore al numero corrente di giocatori
 * @param giocatori Puntatore alla lista di giocatori
 * @param carteCfu Puntatore al mazzo delle carte cfu
 * @param scarti Puntatore al mazzo degli scarti
 * @param carteOstacolo Puntatore al mazzo degli ostacoli
 * @param nTurno Puntatore al numero del turno
 * @param nomeFile Nome del file (inclusa l'estensione .sav)
 */
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
    // Se ha un valore impossibile da ottenere, si resetta
    if(*nTurno<0 || *nTurno>PUNTI_PER_VINCERE*N_PERSONAGGI)
        *nTurno = 0;

    fclose(fp);
}

/**
 * Salva la partita dentro un file binario
 * @param nGiocatori Puntatore al numero corrente di giocatori
 * @param giocatori Puntatore alla lista di giocatori
 * @param carteCfu Puntatore al mazzo delle carte cfu
 * @param scarti Puntatore al mazzo degli scarti
 * @param carteOstacolo Puntatore al mazzo degli ostacoli
 * @param nTurno Puntatore al numero del turno
 * @param nomeFile Nome del file (inclusa l'estensione .sav)
 */
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

    // Per ognuno dei mazzi, si trova e si scrive il numero di carte e poi si scrivono gli elementi della lista in ordine

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

    // Si scrive il numero del turno
    fwrite(nTurno, sizeof(int), 1, fp);

    fclose(fp);
}

/**
 * Permette di immettere il nome della partita, controllando che non sia troppo lungo
 * @param nomeFile
 */
void nomePartita(char nomeFile[LUNG_NOMI+strlen(ESTENSIONE_SAV)]){
    nomeFile[LUNG_NOMI-1] = '\0';
    printf("Dai un nome alla partita:\n");
    scanf("%s", nomeFile);
    // Se l'ultimo carattere è stato rimpiazzato e non è il carattere di terminazione, il nome inserito è troppo lungo
    while(nomeFile[LUNG_NOMI-1] != '\0'){
        printf("E' un nome troppo lungo!\nMassimo %d caratteri.\n", LUNG_NOMI-1);
        nomeFile[LUNG_NOMI-1] = '\0';
        scanf("%s", nomeFile);
    }
    getchar();
    // Si aggiunge l'estenzione .sav al file
    strcat(nomeFile, ESTENSIONE_SAV);
}

/**
 * Dato un nome, restituisce vero se un salvataggio con quel nome esiste, falso altrimenti
 * @param nomeFile Nome del file (inclusa estensione .sav)
 * @return Vero o falso, a seconda della presenza del file
 */
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

/**
 * Assegna valori default alle variabili quando si inizia una nuova partita
 * @param nGiocatori Puntatore alla variabile che conterrà il numero di giocatori
 * @param giocatori Puntatore alla lista di giocatori
 * @param carteCfu Puntatore al mazzo delle carte cfu
 * @param scarti Puntatore al mazzo degli scarti
 * @param carteOstacolo Puntatore al mazzo degli ostacoli
 * @param nTurno Puntatore alla variabile che conterrà il numero del turno
 * @param personaggi Array dei personaggi letti dal file
 */
void inizializzaSalvataggio(int *nGiocatori, Giocatore **giocatori, CartaCfu **carteCfu, CartaCfu **scarti, CartaOstacolo **carteOstacolo, int *nTurno, Personaggio personaggi[N_PERSONAGGI]){
    *nTurno = 1;

    // Si leggono i mazzi dai file e si mischiano. All'inizio non ci sono carte scartate
    *scarti = NULL;
    *carteCfu = leggiCarte();
    *carteOstacolo = leggiOstacoli();
    mischiaMazzo(carteCfu);
    mischiaOstacoli(carteOstacolo);

    // Input del numero dei giocatori, input delle informazioni, assegnazione personaggi
    *nGiocatori = inputNGiocatori();
    *giocatori = inputGiocatori(*nGiocatori, 1);
    inizializzaGiocatori(*giocatori);
    stampaPersonaggi(personaggi);
    assegnaPersonaggi(*giocatori, personaggi);
}

/** Inizializza i giocatori:
 * nessuna carta CFU,
 * nessuna carta ostacolo,
 * 0 CFU
 * @param giocatori puntatore al primo giocatore
 */
void inizializzaGiocatori(Giocatore* giocatori){
    Giocatore* giocatore = giocatori;
    while(giocatore != NULL){
        giocatore->primaCfu = NULL;
        giocatore->primaOstacolo = NULL;
        giocatore->cfu = 0;
        giocatore = giocatore->prossimo;
    }
}

/**
 * Permette ai giocatori di selezionare, in ordine, il proprio personaggio
 * @param giocatori Puntatore al primo giocatore
 * @param personaggi Array dei personaggi letti dal file
 */
void assegnaPersonaggi(Giocatore* giocatori, Personaggio personaggi[N_PERSONAGGI]){
    Giocatore *giocatore = giocatori;
    bool selezionati[N_PERSONAGGI] = {false};
    int i=0, scelta=-1;

    // Si scorre la lista di giocatori, e si fa scegliere un personaggio, ripetendo l'input se non e' valido
    for(i=0, giocatore=giocatori; giocatore != NULL; i++, giocatore=giocatore->prossimo){
        printf("%s, seleziona un personaggio (1-%d): ", giocatore->nomeUtente, N_PERSONAGGI);
        scelta = inputCifra()-1;
        while(scelta<0 || scelta>=N_PERSONAGGI || selezionati[scelta]){
            if(scelta<0 || scelta>=N_PERSONAGGI)
                printf("Seleziona un'opzione\n");
            else if(selezionati[scelta])
                printf("Questo personaggio e' gia' stato selezionato\n");
            scelta = inputCifra()-1;
        }
        selezionati[scelta] = true;
        giocatore->personaggio = personaggi[scelta];
    }
}