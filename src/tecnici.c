#include <stdio.h>
#include "tecnici.h"

//FUNZIONE CARICA TECNICI
void caricaTecnici(Tecnico tecnici[], int *nTecnici)
{
    FILE *fp = fopen("data/tecnici.txt", "r");

    if (fp == NULL)
    {
        printf("Errore apertura tecnici.txt\n");
        return;
    }

    *nTecnici = 0;

    while (fscanf(fp,
                  "%d;%19[^;];%19[^;];%99[^;];%d;%d\n",
                  &tecnici[*nTecnici].id_tecnico,
                  tecnici[*nTecnici].nome_tecnico,
                  tecnici[*nTecnici].cognome_tecnico,
                  tecnici[*nTecnici].specializzazione,
                  &tecnici[*nTecnici].richieste_assegnabili,
                  &tecnici[*nTecnici].richieste_assegnate) == 6)
    {
        (*nTecnici)++;
    }

    fclose(fp);
}


//FUNZIONE SALVA TECNICI
void salvaTecnici(Tecnico tecnici[], int nTecnici)
{
    FILE *fp = fopen("data/tecnici.txt", "w");

    if (fp == NULL)
    {
        printf("Errore salvataggio tecnici.txt\n");
        return;
    }

    for (int i = 0; i < nTecnici; i++)
    {
        fprintf(fp,
                "%d;%s;%s;%s;%d;%d\n",
                tecnici[i].id_tecnico,
                tecnici[i].nome_tecnico,
                tecnici[i].cognome_tecnico,
                tecnici[i].specializzazione,
                tecnici[i].richieste_assegnabili,
                tecnici[i].richieste_assegnate);
    }

    fclose(fp);
}