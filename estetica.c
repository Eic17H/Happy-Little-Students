//
// Created by eic17 on 25/03/2024.
//

#include "estetica.h"

void stampaLogo(){
    printf(" _   _  ___ ______________   __  _    _____ _____ _____ _     _____   _____ _____ _   _______ _____ _   _ _____ _____ \n");
    printf("| | | |/ _ \\| ___ \\ ___ \\ \\ / / | |  |_   _|_   _|_   _| |   |  ___| /  ___|_   _| | | |  _  \\  ___| \\ | |_   _/  ___|\n");
    printf("| |_| / /_\\ \\ |_/ / |_/ /\\ V /  | |    | |   | |   | | | |   | |__   \\ `--.  | | | | | | | | | |__ |  \\| | | | \\ `--. \n");
    printf("|  _  |  _  |  __/|  __/  \\ /   | |    | |   | |   | | | |   |  __|   `--. \\ | | | | | | | | |  __|| . ` | | |  `--. \\\n");
    printf("| | | | | | | |   | |     | |   | |____| |_  | |   | | | |___| |___  /\\__/ / | | | |_| | |/ /| |___| |\\  | | | /\\__/ /\n");
    printf("\\_| |_|_| |_|_|   \\_|     \\_/   \\_____|___/  \\_/   \\_/ \\_____|____/  \\____/  \\_/  \\___/|___/ \\____/\\_| \\_/ \\_/ \\____/ \n");
    printf("\t \t \t \t \t   SMILE, IT'S ALMOST OVER");
    printf("\n\n\n");
}

char cartaSpeciale(CartaCfu carta){
    if(carta.effetto == 0)
        return ' ';
    else
        return SIMBOLO_CARTA_EFFETTO;
}

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