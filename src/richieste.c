#include <stdio.h>
#include "richieste.h"

/* Percorso del file dati richieste */
#define FILE_RICHIESTE "data/richieste.txt"

/*
 * Formato di ogni riga nel file:
 * id;nome;cognome;dispositivo;problema;priorita;stato;
 * costo_stimato;costo_finale;data_apertura;codice_tecnico
 */

void caricaRichieste(richiesta_t richieste[], int *nRichieste) {
    FILE *fp = fopen(FILE_RICHIESTE, "r");
    if (fp == NULL) {
        printf("  [AVVISO] File '%s' non trovato. Si parte da zero.\n", FILE_RICHIESTE);
        *nRichieste = 0;
        return;
    }

    *nRichieste = 0;

    while (*nRichieste < MAX_RICHIESTE) {
        richiesta_t *r = &richieste[*nRichieste];

        int campi_letti = fscanf(fp,
            "%d;"
            "%29[^;];%29[^;];"
            "%99[^;];%99[^;];"
            "%29[^;];%29[^;];"
            "%f;%f;"
            "%10[^;];%d\n",
            &r->id_richiesta,
            r->nome_cliente,
            r->cognome_cliente,
            r->tipologia_dispositivo,
            r->descrizione_problema,
            r->priorita,
            r->stato,
            &r->costo_stimato,
            &r->costo_finale,
            r->data_apertura,
            &r->codice_tecnico_associato);

        if (campi_letti != 11) {
            break; /* fine file o riga malformata */
        }

        (*nRichieste)++;
    }

    fclose(fp);
    printf("  [OK] Caricate %d richieste da '%s'.\n", *nRichieste, FILE_RICHIESTE);
}

void salvaRichieste(richiesta_t richieste[], int nRichieste) {
    FILE *fp = fopen(FILE_RICHIESTE, "w");
    if (fp == NULL) {
        printf("  [ERRORE] Impossibile aprire '%s' in scrittura.\n", FILE_RICHIESTE);
        return;
    }

    int i;
    for (i = 0; i < nRichieste; i++) {
        richiesta_t *r = &richieste[i];

        fprintf(fp,
            "%d;%s;%s;%s;%s;%s;%s;%.2f;%.2f;%s;%d\n",
            r->id_richiesta,
            r->nome_cliente,
            r->cognome_cliente,
            r->tipologia_dispositivo,
            r->descrizione_problema,
            r->priorita,
            r->stato,
            r->costo_stimato,
            r->costo_finale,
            r->data_apertura,
            r->codice_tecnico_associato);
    }

    fclose(fp);
    printf("  [OK] Salvate %d richieste su '%s'.\n", nRichieste, FILE_RICHIESTE);
}
