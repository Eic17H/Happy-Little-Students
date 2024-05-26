//
// Created by eic17 on 23/03/2024.
//


#include "letturaFile.h"

/** La funzione leggiPersonaggi legge i personaggi da personaggi.txt e li mette in un array dichiarato nel main
 * @param lista puntatore all'array
 */
void leggiPersonaggi(Personaggio* lista){
    // Aprire il file personaggi.txt
    FILE *fp;
    fp = fopen("personaggi.txt", "r");
    if(fp == NULL)
        exit(-1);

    // Leggere dal file
    for(int i=0; i<N_PERSONAGGI; i++){
        for (int j = 0; j<4; j++) {
            fscanf(fp, "%i", &(lista[i].ostacoli[j]));
        }
        fscanf(fp, "%s", (&lista[i])->nome);
    }

    // Chiudere il file
    fclose(fp);
}

// TODO: rimuovere
void stampaPersonaggi(Personaggio test[]){
    for(int i=0; i<N_PERSONAGGI; i++) {
        for (int j = 0; j < 4; j++)
            printf("%i ", test[i].ostacoli[j]);
        printf("%s\n", test[i].nome);
    }
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
    if(fp == NULL)
        exit(-1);

    mazzo = (CartaCfu*) malloc(sizeof(CartaCfu));
    carta = mazzo;
    prossima = carta;

    do{
        // Si legge il file e si controlla che ci sia qualcosa da leggere
        letti = fscanf(fp, "%d %d %d %[^\n]", &quantita, &effetto, &valore, nome);
        // Se non c'e' niente da leggere, il mazzo è finito: la prossima è l'ultima carta
        if (letti < 0) {
            prossima->prossima = NULL;
            carta->prossima = prossima;
        }
        else
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
// TODO: Capire come leggere un file con gli spazi
CartaOstacolo* leggiOstacoli(){
    // Apertura file
    FILE *fp;
    fp = fopen("ostacoli.txt", "r");
    if(fp == NULL)
        exit(-1);

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
    mazzo = (CartaOstacolo*) malloc(sizeof(CartaOstacolo));
    carta = mazzo;
    prossima = carta;

    do{
        // Si controlla quante carte si devono leggere, e se è stata letta una quantità
        letti = fscanf(fp, "%d", &quantita);
        // Se non è stata letta una quantità, il file è finito, quindi è la fine del mazzo
        if (letti < 0) {
            prossima->prossima = NULL;
            carta->prossima = prossima;
        }
        else
            // Il numero di carte da leggere è salvato in quantita
            for (int i = 0; i < quantita; i++) {
                fscanf(fp, " %[^\n]\n", nome);
                strcpy(prossima->nome, nome);
                fscanf(fp, " %[^\n]\n", descrizione);
                strcpy(prossima->descrizione, descrizione);
                // Si va avanti di una carta
                carta = prossima;
                carta->prossima = (CartaOstacolo *) malloc(sizeof(CartaOstacolo));
                prossima = carta->prossima;
            }
    }while(letti>0);
    fclose(fp);
    return mazzo;
}