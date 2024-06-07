//
// Created by eic17 on 25/03/2024.
//

#include "estetica.h"
#include "utilita.h"
#include "carteEffetto.h"

/**
 * Stampa il logo leggendolo da immagine.txt e logo.txt
 */
void stampaLogo(){
    FILE *fp = fopen("immagine.txt", "r");
    if(fp == NULL)
        exit(-1);
    char c;
    int letto;
    letto = fscanf(fp, "%c", &c);
    // Una R rende il testo rosso, una Y giallo, una W bianco, gli altri caratteri vengono stampati
    while(letto>=0){
        switch(c){
            case 'R':
                printf(RED);
                break;
            case 'Y':
                printf(YEL);
                break;
            case 'W':
                printf(RESET);
                break;
            default:
                printf("%c", c);
                break;
        }
        letto = fscanf(fp, "%c", &c);
    }
    fclose(fp);

    printf("\n");

    fp = fopen("logo.txt", "r");
    if(fp == NULL)
        exit(-1);
    letto = fscanf(fp, "%c", &c);
    while(letto>=0){
        printf("%c", c);
        letto = fscanf(fp, "%c", &c);
    }
    printf("\n\n\n");
}

/**
 * Indica se una carta ha un effetto
 * @param carta una carta cfu
 * @return un indicatore se la carta ha un effetto, uno spazio altrimenti
 */
char cartaSpeciale(CartaCfu carta){
    if(carta.effetto == 0)
        return ' ';
    else if(carta.effetto>=13)
        return SIMBOLO_CARTA_ISTANTANEA;
    else
        return SIMBOLO_CARTA_EFFETTO;
}

/**
 * Colora il testo basandosi sul tipo di una carta ostacolo. Poi va resettato.
 * Studio: rosso
 * Sopravvivenza: blu
 * Sociale: verde
 * Esame: giallo
 * @param tipo il tipo della carta.
 */
void coloreOstacoli(TipoOstacolo tipo){
    switch(tipo){
        case STUDIO:
            printf(RED);
            break;
        case SOPRAVVIVENZA:
            printf(BLU);
            break;
        case SOCIALE:
            printf(GRN);
            break;
        case ESAME:
            printf(YEL);
            break;
        default:
            printf(RESET);
            break;
    }
}

void stampaOstacolo(CartaOstacolo carta){
    stampaNomeOstacolo(carta);
    printf("\n");
    stampaDescOstacolo(carta);
    printf("\n\n");
}

void stampaNomeOstacolo(CartaOstacolo carta){
    coloreOstacoli(carta.tipo);
    printf("%s" RESET, carta.nome);
}

void stampaDescOstacolo(CartaOstacolo carta){
    coloreOstacoli(carta.tipo);
    printf("%s" RESET, carta.descrizione);
}

/**
 * Legge i numeri che segnano il valore di una casella in plancia.txt, e li mette in un array
 * @param numeri Array dei numeri, letti da sinistra a destra, dall'alto verso il basso
 */
void leggiNumeriPlancia(int numeri[PUNTI_PER_VINCERE]){
    FILE *fp = fopen("plancia.txt", "r");
    char c;
    int i=0, letti=0;
    do{
        letti=fscanf(fp, "%c", &c);
        if(c>='0' && c<='9'){
            fseek(fp, -1, SEEK_CUR);
            fscanf(fp, "%d", &numeri[i]);
            i++;
        }
    }while(i<PUNTI_PER_VINCERE && letti>=0);
}

/**
 * Stampa la plancia di gioco e i segnalini dei giocatori
 * @param giocatori Puntatore al primo giocatore
 * @param nGiocatori Numero di giocatori corrente
 * @param numeri Array contenente l'ordine in cui si trovano le caselle (letto dal file della plancia)
 */
// TODO: sembra che quando ci sono due giocatori, il secondo non venga stampato
void stampaPlancia(Giocatore *giocatori, int nGiocatori, int numeri[50], Personaggio personaggi[N_PERSONAGGI]){
    FILE *fp = fopen("plancia.txt", "r");
    if(fp == NULL)
        exit(-1);
    // Una riga del txt è di 51 caratteri, sono 3 righe per casella + 1 riga per il bordo
    int letto;
    char c;
    letto = fscanf(fp, "%c", &c);
    int cont=1, col, rig, casella;

    // Un array che contiene i giocatori, per non dover scrivere segnalino(*(*giocatori).prossimo, rig+col);
    Giocatore *arrayGiocatori[N_PERSONAGGI], *giocatore=giocatori;
    // Se ci sono due giocatori, i segnalini si spostano a destra per essere centrati
    int offset;
    if(nGiocatori == 2){
        arrayGiocatori[0] = NULL;
        offset = 1;
    }else{
        offset = 0;
    }
    // Tutti gli slot giocatore vuoti sono NULL
    for(int i=0; i<N_PERSONAGGI; i++){
        if(i+offset>nGiocatori-1){
            arrayGiocatori[i + offset] = NULL;
        }else{
            arrayGiocatori[i+offset] = giocatore;
            giocatore = giocatore->prossimo;
        }
    }

    while(letto>=0){
        /**
         * TODO: trovarli con delle funzioni
         * rig = caratteri prima del primo \n
         * col = caratteri tra un A e l'altro
         * magari aggiungere anche la lista di segnalini all'interno del file
         */
        // Numero della riga nella plancia
        // (saltiamo la prima riga di caratteri, 51 caratteri per riga, 3 righe di testo per riga di plancia)
        rig = (cont-51)/51/3;
        // si ripete dopo ogni riga, 7 caratteri per colonna
        col = cont%51/7;

        /**
         * 4 g: G1 G2 G3 G4
         * 3 g: G1 G2 G3
         * 2 g:    G1 G2
         */

        /**
         * in plancia.txt metto un numero (npersonaggi)
         * poi metto (seconda riga) tipo "ABCD"
         * li metto in char[npersonaggi]
         * poi faccio for int i=0 i<npersonaggi i++ if c==char[i] colore giocatore[i] segnalino giocatore[i] etc
         */

        casella = rig*7+col;
        // TODO: colore personaggio
        switch(c){
            case 'A':
                coloreGiocatore(arrayGiocatori[0], personaggi);
                segnalino(arrayGiocatori[0], casella, numeri);
                printf(RESET);
                break;
            case 'B':
                coloreGiocatore(arrayGiocatori[1], personaggi);
                segnalino(arrayGiocatori[1], casella, numeri);
                printf(RESET);
                break;
            case 'C':
                coloreGiocatore(arrayGiocatori[2], personaggi);
                segnalino(arrayGiocatori[2], casella, numeri);
                printf(RESET);
                break;
            case 'D':
                coloreGiocatore(arrayGiocatori[3], personaggi);
                segnalino(arrayGiocatori[3], casella, numeri);
                printf(RESET);
                break;
            default:
                printf(RESET "%c", c);
                break;
        }
        letto = fscanf(fp, "%c", &c);
        cont++;
    }
    printf("\n\n");
}

void segnalino(Giocatore *giocatore, int casella, int caselle[PUNTI_PER_VINCERE]){
    if(giocatore == NULL)
        printf(" ");
    else if(caselle[casella%49] == giocatore->cfu)
        printf("%c", giocatore->nomeUtente[0]);
    else
        printf(" ");
}

// TODO: usare i personaggi anziché il numero
void coloreNumero(int n){
    switch(n){
        case 1:
            printf(MAG);
            break;
        case 2:
            printf(CYN);
            break;
        case 3:
            printf(GRN);
            break;
        case 4:
            printf(YEL);
            break;
        default:
            printf(RESET);
            break;
    }
}

/**
 * Imposta il colore del testo a quello associato a un certo personaggio
 * @param personaggio Il personaggio
 * @param personaggi L'array dei personaggi
 */
void colorePersonaggio(Personaggio personaggio, Personaggio personaggi[N_PERSONAGGI]){
    // TODO: in effetti faccio scegliere che personaggio prendere, ignorando i colori nell'inserimento del nome utente
    // TODO: consistenza, forse
    // I personaggi partono da 0, ma i giocatori sono numerati da 1
    for(int i=0; i<N_PERSONAGGI; i++){
        if(strcmp(personaggio.nome, personaggi[i].nome) == 0)
            coloreNumero(i+1);
    }
}

/**
 * Imposta il colore del testo a quello associato al personaggio di un giocatore
 * @param personaggio Il giocatore
 * @param personaggi L'array dei personaggi
 */
void coloreGiocatore(Giocatore* giocatore, Personaggio personaggi[N_PERSONAGGI]){
    if(giocatore == NULL)
        return;
    colorePersonaggio(giocatore->personaggio, personaggi);
}

// TODO: interfaccia.c

/**
 * Stampa le carte ostacolo e i CFU di ciascun giocatore
 * @param giocatori Puntatore al primo giocatore
 * @param nGiocatori Numero corrente di giocatori
 * @param personaggi Array dei personaggi
 */
void stampaSituazione(Giocatore* giocatori, int nGiocatori, Personaggio* personaggi){
    Giocatore* giocatore = giocatori;
    CartaOstacolo *carta;
    int i=0, continua=0;

    // Nomi
    for(giocatore=giocatori, i=0; giocatore!=NULL; giocatore=giocatore->prossimo, i++){
        colorePersonaggio(giocatore->personaggio, personaggi);
        printf("%32s: %2d CFU\t", giocatore->nomeUtente, giocatore->cfu);
        for(carta = giocatore->primaOstacolo; carta != NULL; carta = carta->prossima) {
            stampaNomeOstacolo(*carta);
            printf("\t");
        }
        printf(RESET);
        printf("\n");
    }
    printf("\n\n");
}

void aiuto(int scelta){
    switch(scelta){
        case 0:
            printf("Una carta senza segnalino e' una carta che non ha un effetto.\n");
            break;
        case 1:
            printf("Una carta con il segnalino \"%c\" e' una carta con effetto che puoi usare nella prima fase del turno.\n", SIMBOLO_CARTA_EFFETTO);
            break;
        case 2:
            printf("Una carta con il segnalino \"%c\" e' una carta istantanea, da usare dopo il calcolo del punteggio.\n", SIMBOLO_CARTA_ISTANTANEA);
    }
}

