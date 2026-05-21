#include <stdio.h>
#include "richieste.h"

//FUNZIONE CARICA RICHIESTE
void caricaRichieste(Richiesta richieste[], int *nRichieste)
{
    FILE *fp = fopen("data/richieste.txt", "r");

    if (fp == NULL)
    {
        printf("Errore apertura richieste.txt\n");
        return;
    }

    *nRichieste = 0;

    while (fscanf(fp,
                  "%d;%19[^;];%19[^;];%99[^;];%99[^;];%29[^;];%29[^;];%f;%f;%29[^;];%d\n",
                  &richieste[*nRichieste].id_richiesta,
                  richieste[*nRichieste].nome_cliente,
                  richieste[*nRichieste].cognome_cliente,
                  richieste[*nRichieste].tipologia_dispositivo,
                  richieste[*nRichieste].descrizione_problema,
                  richieste[*nRichieste].priorita,
                  richieste[*nRichieste].stato,
                  &richieste[*nRichieste].costo_stimato,
                  &richieste[*nRichieste].costo_finale,
                  richieste[*nRichieste].data_apertura,
                  &richieste[*nRichieste].codice_tecnico_associato) == 11)
    {
        (*nRichieste)++;
    }

    fclose(fp);
}


//FUNZIONE SALVA RICHIESTE
void salvaRichieste(Richiesta richieste[], int nRichieste)
{
    FILE *fp = fopen("data/richieste.txt", "w");

    if (fp == NULL)
    {
        printf("Errore salvataggio richieste.txt\n");
        return;
    }

    for (int i = 0; i < nRichieste; i++)
    {
        fprintf(fp,
                "%d;%s;%s;%s;%s;%s;%s;%.2f;%.2f;%s;%d\n",
                richieste[i].id_richiesta,
                richieste[i].nome_cliente,
                richieste[i].cognome_cliente,
                richieste[i].tipologia_dispositivo,
                richieste[i].descrizione_problema,
                richieste[i].priorita,
                richieste[i].stato,
                richieste[i].costo_stimato,
                richieste[i].costo_finale,
                richieste[i].data_apertura,
                richieste[i].codice_tecnico_associato);
    }

    fclose(fp);
}