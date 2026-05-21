#include <stdio.h>
#include "tecnici.h"

/* Percorso del file dati tecnici */
#define FILE_TECNICI "data/tecnici.txt"

void caricaTecnici(tecnico_t tecnici[], int *nTecnici) {
    FILE *fp = fopen(FILE_TECNICI, "r");
    if (fp == NULL) {
        printf("  [AVVISO] File '%s' non trovato. Si parte da zero.\n", FILE_TECNICI);
        *nTecnici = 0;
        return;
    }

    *nTecnici = 0;

    while (*nTecnici < MAX_TECNICI) {
        tecnico_t *t = &tecnici[*nTecnici];

        int campi_letti = fscanf(fp,
            "%d;"
            "%29[^;];%29[^;];"
            "%99[^;];"
            "%d;%d\n",
            &t->id_tecnico,
            t->nome_tecnico,
            t->cognome_tecnico,
            t->specializzazione,
            &t->richieste_assegnabili,
            &t->richieste_assegnate);

        if (campi_letti != 6) {
            break; 
        }

        (*nTecnici)++;
    }

    fclose(fp);
    printf("  [OK] Caricati %d tecnici da '%s'.\n", *nTecnici, FILE_TECNICI);
}

void salvaTecnici(tecnico_t tecnici[], int nTecnici) {
    FILE *fp = fopen(FILE_TECNICI, "w");
    if (fp == NULL) {
        printf("  [ERRORE] Impossibile aprire '%s' in scrittura.\n", FILE_TECNICI);
        return;
    }

    int i;
    for (i = 0; i < nTecnici; i++) {
        tecnico_t *t = &tecnici[i];

        fprintf(fp,
            "%d;%s;%s;%s;%d;%d\n",
            t->id_tecnico,
            t->nome_tecnico,
            t->cognome_tecnico,
            t->specializzazione,
            t->richieste_assegnabili,
            t->richieste_assegnate);
    }

    fclose(fp);
    printf("  [OK] Salvati %d tecnici su '%s'.\n", nTecnici, FILE_TECNICI);
}
