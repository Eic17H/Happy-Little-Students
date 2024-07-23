#include "letturaFile.h"
#include "salvataggio.h"

/** La funzione leggiPersonaggi legge i personaggi da personaggi.txt e li mette in un array dichiarato nel main.
 * @param lista puntatore all'array
 */
void leggiPersonaggi(Personaggio* lista){
    // Aprire il file personaggi.txt
    FILE *fp;
    fp = fopen("personaggi.txt", "r");
    if(fp == NULL){
        coloreErrore();
        printf("Errore: impossibile aprire personaggi.txt\n" RESET);
        exit(-1);
    }

    // Leggere dal file
    for(int i=0; i<N_PERSONAGGI; i++){
        for (int j = 0; j<N_TIPI_OSTACOLI; j++){
            fscanf(fp, "%d", &(lista[i].ostacoli[j]));
        }
        fscanf(fp, "%s", (&lista[i])->nome);
    }

    // Chiudere il file
    fclose(fp);
}

/**
 * Stampa le informazioni sui personaggi
 * @param personaggi
 */
void stampaPersonaggi(Personaggio personaggi[]){
    printf("\n\n\nOgni personaggio ha un bonus e un malus\n");
    printf("I bonus e i malus sono legati al tipo di ostacolo mostrato all'inizio del turno\n");
    printf("Se il tuo personaggio ha un malus legato a quel tipo,\nil tuo punteggio provvisorio sara' minore di quello che dovrebbe essere\n");
    printf("Nel caso dei bonus, sara' maggiore.\n");
    for(int i=0; i<N_PERSONAGGI; i++) {
        colorePersonaggio(personaggi[i], personaggi);
        printf("%i: %32s: ", i+1, personaggi[i].nome);
        for (int j = 0; j < N_TIPI_OSTACOLI; j++)
            if(personaggi[i].ostacoli[j] > 0){
                coloreOstacoli(j+1);
                printf("Bonus ");
            }
        for (int j = 0; j < N_TIPI_OSTACOLI; j++)
            if(personaggi[i].ostacoli[j] < 0){
                coloreOstacoli(j+1);
                printf("Malus\n");
            }
    }
    printf(RESET "\n\n");
}

/** La funzione leggiCarte restituisce una lista di carte lette da carte.txt
 * @return puntatore alla prima carta del mazzo cfu
 */
CartaCfu* leggiCarte(){
    // Creazione variabili e apertura file
    FILE *fp;
    int quantita, valore, letti;
    EffettoCarta effetto;
    char nome[LUNG_NOMI];
    CartaCfu *mazzo, *carta, *prossima;
    fp = fopen("carte.txt", "r");
    if(fp == NULL){
        coloreErrore();
        printf("Errore: impossibile aprire carte.txt\n" RESET);
        exit(-1);
    }

    mazzo = (CartaCfu*) malloc(sizeof(CartaCfu));
    carta = mazzo;
    prossima = carta;

    // A ogni ciclo, imposto la "prossima" carta, lavoro su quella, e poi vado avanti di una.
    do{
        // Si legge il file e si controlla che ci sia qualcosa da leggere
        letti = fscanf(fp, "%d %d %d %[^\n]", &quantita, &effetto, &valore, nome);

        // Se non c'e' niente da leggere, il mazzo è finito: la prossima è l'ultima carta
        if (letti <= 0) {
            prossima = NULL;
            carta->prossima = prossima;
        }else
            // Si usano gli stessi dati piu' volte se ci sono carte uguali
            for (int i = 0; i < quantita; i++) {
                // Si assegnano effetto, valore e nome della prossima
                prossima->effetto = effetto;
                prossima->cfu = valore;
                strcpy(prossima->nome, nome);
                // Si va avanti di una carta: la carta che era la prossima diventa quella corrente, e una nuova carta è la prossima
                carta = prossima;
                carta->prossima = (CartaCfu *) malloc(sizeof(CartaCfu));
                prossima = carta->prossima;
            }
    }while(letti>0);
    fclose(fp);
    return mazzo;
}

/** La funzione leggiOstacoli restituisce una lista di carte lette da ostacoli.txt
 * @return puntatore alla prima carta del mazzo ostacoli
 */
CartaOstacolo* leggiOstacoli(){
    // Apertura file
    FILE *fp;
    fp = fopen("ostacoli.txt", "r");
    if(fp == NULL){
        coloreErrore();
        printf("Errore: impossibile aprire ostacoli.txt\n" RESET);
        exit(-1);
    }
    // I tipi partono da 1
    TipoOstacolo tipo = 1;

    // Creazione variabili
    // Quante carte ha il tipo che si sta leggendo
    int quantita;
    // Quanti valori sono stati letti. Quando non sono stati letti valori, il file è finito
    int letti;
    // Nome e descrizione della carta che si sta leggendo
    char nome[LUNG_NOMI], descrizione[LUNG_DESCR];
    // Puntatore alla prima carta, puntatore alla carta che si sta leggendo, puntatore alla carta successiva
    CartaOstacolo *mazzo, *carta, *prossima;

    // Si comincia dall'inizio del mazzo
    // Lavoro sempre sulla "prossima", poi vado avanti di una
    mazzo = (CartaOstacolo*) malloc(sizeof(CartaOstacolo));
    carta = mazzo;
    prossima = carta;

    do{
        // Si controlla quante carte si devono leggere, e se è stata letta una quantità
        letti = fscanf(fp, "%d", &quantita);
        // Se non è stata letta una quantità, il file è finito, quindi è la fine del mazzo
        if (letti < 1) {
            prossima = NULL;
            carta->prossima = prossima;
        }
        else
            // Il numero di carte da leggere è salvato in quantita
            for (int i = 0; i < quantita; i++) {
                fscanf(fp, " %[^\n]\n", nome);
                strcpy(prossima->nome, nome);
                fscanf(fp, " %[^\n]\n", descrizione);
                strcpy(prossima->descrizione, descrizione);
                prossima->tipo = tipo;
                // Si va avanti di una carta
                carta = prossima;
                carta->prossima = (CartaOstacolo *) malloc(sizeof(CartaOstacolo));
                prossima = carta->prossima;
            }
        // Lette le carte di questo gruppo, si cambia tipo
        tipo++;
    }while(letti>0);
    fclose(fp);
    return mazzo;
}