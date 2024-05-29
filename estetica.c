//
// Created by eic17 on 25/03/2024.
//

#include "estetica.h"

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

/**
 * Stampa la descrizione dell'effetto di una carta cfu
 * @param carta
 */
void stampaEffetto(CartaCfu carta){
    switch(carta.effetto){
        case NESSUNO:
            printf("Nessun effetto.\n");
            break;
        case SCARTAP:
            printf("Scarta una" YEL " carta CFU punto " RESET "e aggiungi il suo punteggio a quello del turno.\n");
            break;
        case RUBA:
            printf("Guarda la mano di un collega e ruba una carta a scelta.\n");
            break;
        case SCAMBIADS:
            printf("Scambia questa carta con quella di un altro giocatore, purche' senza effetto.\n");
            break;
        case SCARTAE:
            printf("Scarta una" YEL " carta CFU punto " RESET "con" CYN " effetto " RESET "e aggiungi il suo punteggio a quello del turno.\n");
            break;
        case SCARTAC:
            printf("Scarta da uno a tre carte dalla tua mano.\n");
            break;
        case SCAMBIAP:
            printf("Scambia il punteggio del turno maggiore e minore dopo il calcolo del punteggio di base.\n");
            break;
        case DOPPIOE:
            printf("Raddoppia gli" CYN " effetti " RESET "delle carte che aumentano o diminuiscono il punteggio (per tutti).\n");
            break;
        case SBIRCIA:
            printf("Guarda due carte in cima al mazzo, prendine una e scarta l'altra.\n");
            break;
        case SCAMBIAC:
            printf("Scambia la carta punto giocata nel turno da un giocatore G1 con quella di un giocatore G2, con G1 e G2 scelti dal giocatore che ha giocato la carta.\n");
            break;
        case ANNULLA:
            printf("Annulla gli" CYN " effetti " RESET "di tutte le carte punto durante il turno.\n");
            break;
        case AUMENTA:
            printf("Aumenta di 2" YEL " CFU " RESET "il punteggio del turno di un giocatore a scelta.\n");
            break;
        case DIMINUISCI:
            printf("Diminuisci di 2" YEL " CFU " RESET "il punteggio del turno di un giocatore a scelta.\n");
            break;
        case INVERTI:
            printf("Inverti punteggio minimo e massimo del turno.\n");
            break;
        case SALVA:
            printf("Metti la carta" RED " Ostacolo " RESET "che stai per prendere in fondo al mazzo.\n");
            break;
        case DIROTTA:
            printf("Dai la carta" RED " Ostacolo " RESET "che stai per prendere ad un altro giocatore a tua scelta.\n");
            break;
        default:
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

void stampaPlancia(Giocatore* giocatori, int nGiocatori, int numeri[PUNTI_PER_VINCERE]){
    FILE *fp = fopen("plancia.txt", "r");
    if(fp == NULL)
        exit(-1);
    // Una riga del txt è di 51 caratteri, sono 3 righe per casella + 1 riga per il bordo
    int letto;
    char c;
    letto = fscanf(fp, "%c", &c);
    int cont=1, col, rig, casella;

    // Un array che contiene i giocatori, per non dover scrivere segnalino(*(*giocatori).prossimo, rig+col);
    Giocatore *arrayGiocatori[4], *giocatore=giocatori;
    for(int i=0; i<nGiocatori; i++){
        if(i>nGiocatori)
            arrayGiocatori[i] = NULL;
        else{
            arrayGiocatori[i] = giocatore;
            giocatore = giocatore->prossimo;
        }
    }

    while(letto>=0){
        // TODO: aggiungere in plancia.txt questi magic number
        // Numero della riga nella plancia
        // (saltiamo la prima riga di caratteri, 51 caratteri per riga, 3 righe di testo per riga di plancia)
        rig = (cont-51)/51/3;
        // si ripete dopo ogni riga, 7 caratteri per colonna
        col = cont%51/7;

        casella = rig*7+col;
        // TODO: colore personaggio
        switch(c){
            case 'A':
                coloreNumero(1);
                segnalino(arrayGiocatori[0], casella, numeri);
                printf(RESET);
                break;
            case 'B':
                coloreNumero(2);
                segnalino(arrayGiocatori[1], casella, numeri);
                printf(RESET);
                break;
            case 'C':
                coloreNumero(3);
                segnalino(arrayGiocatori[2], casella, numeri);
                printf(RESET);
                break;
            case 'D':
                coloreNumero(4);
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

void colorePersonaggio(Personaggio personaggio, Personaggio* personaggi){
    // TODO: in effetti faccio scegliere che personaggio prendere, ignorando i colori nell'inserimento del nome utente
    // TODO: consistenza, forse
    // I personaggi partono da 0, ma i giocatori sono numerati da 1
    for(int i=0; i<N_PERSONAGGI; i++){
        if(strcmp(personaggio.nome, personaggi[i].nome) == 0)
            coloreNumero(i+1);
    }
}

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