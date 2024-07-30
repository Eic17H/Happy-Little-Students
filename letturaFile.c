#include "letturaFile.h"
#include "salvataggio.h"
#include "interfaccia.h"

/** La funzione leggiPersonaggi legge i personaggi da personaggi.txt e li mette in un array dichiarato nel main.
 * @param personaggi puntatore all'array
 */
void leggiPersonaggi(Personaggio personaggi[N_PERSONAGGI]){
    // Aprire il file personaggi.txt
    FILE *fp;
    fp = fopen("personaggi.txt", "r");
    if(fp == NULL){
        coloreErrore();
        printf("Errore: impossibile aprire personaggi.txt\n" RESET);
        exit(-1);
    }

    // Leggere dal file
    // Per ogni personaggio: un int per ogni tipo di ostacolo, e poi una stringa
    for(int i=0; i<N_PERSONAGGI; i++){
        for (int j = 0; j<N_TIPI_OSTACOLI; j++){
            fscanf(fp, "%d", &(personaggi[i].ostacoli[j]));
        }
        fscanf(fp, "%s", (&personaggi[i])->nome);
    }

    // Chiudere il file
    fclose(fp);
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