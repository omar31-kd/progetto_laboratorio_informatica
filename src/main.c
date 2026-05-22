/*
 * ==========================================================================
 *  SISTEMA DI GESTIONE RICHIESTE - CENTRO ASSISTENZA TECNICA
 * ==========================================================================
 *
 *  File:    main.c
 *  Autore:  Loris Panaro (schermata iniziale, menu, messaggi)
 *  Corso:   Laboratorio di Informatica – Gruppo 3
 *
 *  Descrizione:
 *    Entry point del programma. Gestisce la schermata di benvenuto,
 *    il menu principale numerato e i sottomenu per le diverse aree
 *    funzionali (richieste, tecnici, assegnazioni, ricerca/filtri,
 *    statistiche/report, gestione file).
 *    Implementa messaggi di errore comprensibili e messaggi di conferma.
 * ==========================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "richieste.h"
#include "tecnici.h"
#include "report.h"

/* ========================== COSTANTI UI ================================= */

#define LARGHEZZA_LINEA 60

/* Codici colore ANSI (per terminali che li supportano) */
#define COLORE_RESET   "\033[0m"
#define COLORE_VERDE   "\033[1;32m"
#define COLORE_GIALLO  "\033[1;33m"
#define COLORE_ROSSO   "\033[1;31m"
#define COLORE_CIANO   "\033[1;36m"
#define COLORE_BLU     "\033[1;34m"
#define COLORE_MAGENTA "\033[1;35m"
#define COLORE_GRIGIO  "\033[0;37m"
#define COLORE_BOLD    "\033[1m"

/* ========================== PROTOTIPI =================================== */

/* --- Utilita' schermo e input --- */
void pulisciSchermo(void);
void stampaLinea(char carattere);
void stampaLineaDecorativa(void);
void premiPerContinuare(void);
int  leggiSceltaMenu(int min, int max);
void svuotaBuffer(void);

/* --- Messaggi utente --- */
void stampaErrore(const char *messaggio);
void stampaConferma(const char *messaggio);
void stampaAvviso(const char *messaggio);
void stampaInfo(const char *messaggio);

/* --- Schermate --- */
void mostraSchermataIniziale(void);
void mostraMenuPrincipale(void);

/* --- Sottomenu --- */
void menuGestioneRichieste(richiesta_t richieste[], int *nRichieste,
                           tecnico_t tecnici[], int nTecnici);
void menuGestioneTecnici(tecnico_t tecnici[], int *nTecnici);
void menuAssegnazioni(richiesta_t richieste[], int nRichieste,
                      tecnico_t tecnici[], int nTecnici);
void menuRicercaFiltri(richiesta_t richieste[], int nRichieste);
void menuStatisticheReport(richiesta_t richieste[], int nRichieste,
                           tecnico_t tecnici[], int nTecnici);
void menuGestioneFile(richiesta_t richieste[], int *nRichieste,
                      tecnico_t tecnici[], int *nTecnici);

/* ========================================================================
 *                              MAIN
 * ======================================================================== */

int main(void) {

    /* --- Dati principali del programma --- */
    richiesta_t richieste[MAX_RICHIESTE];
    tecnico_t   tecnici[MAX_TECNICI];
    int nRichieste = 0;
    int nTecnici   = 0;

    int scelta;
    int primoAvvio = 1;

    /* --- Caricamento iniziale dei dati --- */
    pulisciSchermo();
    mostraSchermataIniziale();
    premiPerContinuare();

    pulisciSchermo();
    printf("\n");
    stampaLinea('=');
    printf("  %s CARICAMENTO DATI IN CORSO...%s\n", COLORE_CIANO, COLORE_RESET);
    stampaLinea('=');
    printf("\n");

    caricaRichieste(richieste, &nRichieste);
    caricaTecnici(tecnici, &nTecnici);

    printf("\n");
    stampaConferma("Dati caricati con successo! Il sistema e' pronto.");
    premiPerContinuare();

    /* --- Ciclo principale del menu --- */
    do {
        pulisciSchermo();
        mostraMenuPrincipale();

        scelta = leggiSceltaMenu(0, 6);

        switch (scelta) {
            case 1:
                menuGestioneRichieste(richieste, &nRichieste, tecnici, nTecnici);
                break;
            case 2:
                menuGestioneTecnici(tecnici, &nTecnici);
                break;
            case 3:
                menuAssegnazioni(richieste, nRichieste, tecnici, nTecnici);
                break;
            case 4:
                menuRicercaFiltri(richieste, nRichieste);
                break;
            case 5:
                menuStatisticheReport(richieste, nRichieste, tecnici, nTecnici);
                break;
            case 6:
                menuGestioneFile(richieste, &nRichieste, tecnici, &nTecnici);
                break;
            case 0:
                /* Conferma uscita */
                pulisciSchermo();
                printf("\n");
                stampaLinea('=');
                printf("\n");
                stampaAvviso("Vuoi davvero uscire dal programma?");
                printf("  Eventuali modifiche non salvate andranno perse.\n\n");
                printf("  Confermi? (%s1 = Si%s / %s0 = No%s): ",
                       COLORE_VERDE, COLORE_RESET, COLORE_ROSSO, COLORE_RESET);

                {
                    int conferma = leggiSceltaMenu(0, 1);
                    if (conferma == 0) {
                        scelta = -1; /* annulla uscita, torna al menu */
                        stampaInfo("Uscita annullata. Ritorno al menu principale.");
                        premiPerContinuare();
                    }
                }
                break;
            default:
                break;
        }

    } while (scelta != 0);

    /* --- Schermata di chiusura --- */
    pulisciSchermo();
    printf("\n");
    stampaLinea('=');
    printf("\n");
    printf("  %s Grazie per aver utilizzato il sistema!%s\n", COLORE_CIANO, COLORE_RESET);
    printf("  %s Centro Assistenza Tecnica - Gruppo 3%s\n", COLORE_GRIGIO, COLORE_RESET);
    printf("\n");
    stampaLinea('=');
    printf("\n");

    return 0;
}

/* ========================================================================
 *                    UTILITA' SCHERMO E INPUT
 * ======================================================================== */

/**
 * @brief Pulisce lo schermo in modo cross-platform.
 */
void pulisciSchermo(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Stampa una linea orizzontale composta dal carattere specificato.
 */
void stampaLinea(char carattere) {
    int i;
    printf("  ");
    for (i = 0; i < LARGHEZZA_LINEA; i++) {
        putchar(carattere);
    }
    printf("\n");
}

/**
 * @brief Stampa una linea decorativa con pattern alternato.
 */
void stampaLineaDecorativa(void) {
    int i;
    printf("  %s", COLORE_CIANO);
    for (i = 0; i < LARGHEZZA_LINEA; i++) {
        printf("%c", (i % 2 == 0) ? '-' : '~');
    }
    printf("%s\n", COLORE_RESET);
}

/**
 * @brief Attende che l'utente prema Invio per continuare.
 */
void premiPerContinuare(void) {
    printf("\n  %sPremere INVIO per continuare...%s", COLORE_GRIGIO, COLORE_RESET);
    svuotaBuffer();
    getchar();
}

/**
 * @brief Svuota il buffer di input (stdin).
 */
void svuotaBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Legge una scelta numerica dall'utente, validando l'intervallo.
 * @param min  Valore minimo accettabile
 * @param max  Valore massimo accettabile
 * @return     La scelta valida inserita dall'utente
 */
int leggiSceltaMenu(int min, int max) {
    int scelta;
    int risultato;
    char resto;

    while (1) {
        printf("\n  %s>> Inserisci la tua scelta [%d-%d]: %s",
               COLORE_BOLD, min, max, COLORE_RESET);

        risultato = scanf("%d%c", &scelta, &resto);

        if (risultato != 2 || resto != '\n') {
            /* L'utente ha inserito qualcosa che non e' un numero */
            if (risultato == 0 || (risultato == 2 && resto != '\n') || risultato == 1) {
                /* Svuota il buffer in caso di input non valido */
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
            stampaErrore("Input non valido! Inserisci un numero intero.");
            continue;
        }

        if (scelta < min || scelta > max) {
            printf("  %s[!] ERRORE: La scelta deve essere compresa tra %d e %d.%s\n",
                   COLORE_ROSSO, min, max, COLORE_RESET);
            continue;
        }

        return scelta;
    }
}

/* ========================================================================
 *                      MESSAGGI UTENTE
 * ======================================================================== */

/**
 * @brief Stampa un messaggio di errore formattato.
 */
void stampaErrore(const char *messaggio) {
    printf("  %s[X] ERRORE: %s%s\n", COLORE_ROSSO, messaggio, COLORE_RESET);
}

/**
 * @brief Stampa un messaggio di conferma/successo formattato.
 */
void stampaConferma(const char *messaggio) {
    printf("  %s[V] SUCCESSO: %s%s\n", COLORE_VERDE, messaggio, COLORE_RESET);
}

/**
 * @brief Stampa un messaggio di avviso formattato.
 */
void stampaAvviso(const char *messaggio) {
    printf("  %s[!] ATTENZIONE: %s%s\n", COLORE_GIALLO, messaggio, COLORE_RESET);
}

/**
 * @brief Stampa un messaggio informativo formattato.
 */
void stampaInfo(const char *messaggio) {
    printf("  %s[i] INFO: %s%s\n", COLORE_CIANO, messaggio, COLORE_RESET);
}

/* ========================================================================
 *                      SCHERMATA INIZIALE
 * ======================================================================== */

/**
 * @brief Mostra la schermata di benvenuto con logo ASCII e informazioni.
 */
void mostraSchermataIniziale(void) {
    printf("\n\n");
    stampaLinea('=');
    printf("\n");

    /* --- Logo ASCII Art --- */
    printf("  %s", COLORE_CIANO);
    printf("     ____  _     _                            \n");
    printf("    / ___|| |_  / |_  ___  _ __ ___    __ _   \n");
    printf("    \\___ \\| | |/ / __|/ _ \\| '_ ` _ \\  / _` | \n");
    printf("     ___) | |   <| |_|  __/| | | | | || (_| | \n");
    printf("    |____/|_|_|\\_\\\\__|\\___||_| |_| |_| \\__,_| \n");
    printf("  %s\n", COLORE_RESET);

    printf("  %s", COLORE_BLU);
    printf("      ___            _     _                       \n");
    printf("     / _ \\  ___  ___(_)___| |_ ___ _ __  ______ _  \n");
    printf("    / /_\\ \\/ __\\/ __| / __| __/ _ \\ '_ \\|_  / _` | \n");
    printf("   / ___  \\__  \\__  \\ \\__ \\ ||  __/ | | |/ / (_| | \n");
    printf("   \\/   \\/\\___/\\___/_|___/\\__\\___|_| |_/___\\__,_| \n");
    printf("  %s\n", COLORE_RESET);

    printf("  %s", COLORE_MAGENTA);
    printf("    ___________________________________________\n");
    printf("   |                                           |\n");
    printf("   |    CENTRO ASSISTENZA TECNICA              |\n");
    printf("   |    Sistema di Gestione Richieste          |\n");
    printf("   |___________________________________________|\n");
    printf("  %s\n", COLORE_RESET);

    stampaLinea('=');

    printf("\n");
    printf("  %sProgetto Laboratorio di Informatica%s\n", COLORE_BOLD, COLORE_RESET);
    printf("  %sGruppo 3 – A.A. 2025/2026%s\n", COLORE_GRIGIO, COLORE_RESET);
    printf("\n");
    printf("  %sComponenti:%s\n", COLORE_BOLD, COLORE_RESET);
    printf("    %s*%s Omar Saafi      (853622)\n", COLORE_CIANO, COLORE_RESET);
    printf("    %s*%s Martin Vulpio   (862992)\n", COLORE_CIANO, COLORE_RESET);
    printf("    %s*%s Loris Panaro    (854237)\n", COLORE_CIANO, COLORE_RESET);
    printf("\n");
    stampaLineaDecorativa();
    printf("  %sVersione 1.0 – Maggio 2026%s\n", COLORE_GRIGIO, COLORE_RESET);
    stampaLinea('=');
}

/* ========================================================================
 *                       MENU PRINCIPALE
 * ======================================================================== */

/**
 * @brief Mostra il menu principale con 6 aree funzionali numerate.
 */
void mostraMenuPrincipale(void) {
    printf("\n");
    stampaLinea('=');
    printf("  %s  MENU PRINCIPALE – CENTRO ASSISTENZA TECNICA%s\n",
           COLORE_CIANO, COLORE_RESET);
    stampaLinea('=');

    printf("\n");
    printf("  %s[1]%s %sGestione Richieste%s\n",
           COLORE_VERDE, COLORE_RESET, COLORE_BOLD, COLORE_RESET);
    printf("      Inserisci, visualizza e modifica le richieste\n\n");

    printf("  %s[2]%s %sGestione Tecnici%s\n",
           COLORE_VERDE, COLORE_RESET, COLORE_BOLD, COLORE_RESET);
    printf("      Inserisci, visualizza e modifica i tecnici\n\n");

    printf("  %s[3]%s %sAssegnazioni%s\n",
           COLORE_VERDE, COLORE_RESET, COLORE_BOLD, COLORE_RESET);
    printf("      Assegna richieste ai tecnici\n\n");

    printf("  %s[4]%s %sRicerca e Filtri%s\n",
           COLORE_VERDE, COLORE_RESET, COLORE_BOLD, COLORE_RESET);
    printf("      Cerca e filtra le richieste\n\n");

    printf("  %s[5]%s %sStatistiche e Report%s\n",
           COLORE_VERDE, COLORE_RESET, COLORE_BOLD, COLORE_RESET);
    printf("      Visualizza statistiche e genera report\n\n");

    printf("  %s[6]%s %sGestione File%s\n",
           COLORE_VERDE, COLORE_RESET, COLORE_BOLD, COLORE_RESET);
    printf("      Carica e salva i dati su file\n\n");

    stampaLineaDecorativa();
    printf("  %s[0]%s %sEsci dal programma%s\n",
           COLORE_ROSSO, COLORE_RESET, COLORE_GRIGIO, COLORE_RESET);
    stampaLinea('-');
}

/* ========================================================================
 *                          SOTTOMENU
 * ======================================================================== */

/* --------------- 1. GESTIONE RICHIESTE --------------- */

void menuGestioneRichieste(richiesta_t richieste[], int *nRichieste,
                           tecnico_t tecnici[], int nTecnici) {
    int scelta;

    do {
        pulisciSchermo();
        printf("\n");
        stampaLinea('=');
        printf("  %s  GESTIONE RICHIESTE%s\n", COLORE_BLU, COLORE_RESET);
        stampaLinea('=');

        printf("\n");
        printf("  %s[1]%s Visualizza tutte le richieste\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[2]%s Inserisci nuova richiesta\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[3]%s Modifica una richiesta esistente\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[4]%s Aggiorna costo finale (richiesta completata)\n", COLORE_VERDE, COLORE_RESET);
        printf("\n");
        stampaLineaDecorativa();
        printf("  %s[0]%s Torna al menu principale\n", COLORE_ROSSO, COLORE_RESET);
        stampaLinea('-');

        scelta = leggiSceltaMenu(0, 4);

        switch (scelta) {
            case 1:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sELENCO RICHIESTE%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare la funzione di visualizzazione (Omar) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 2:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sNUOVA RICHIESTA%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare la funzione di inserimento (Martin) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 3:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sMODIFICA RICHIESTA%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare la funzione di modifica (Martin) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 4:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sAGGIORNAMENTO COSTO FINALE%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare la funzione aggiornamento costo (Martin) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 0:
                stampaInfo("Ritorno al menu principale...");
                break;
        }

    } while (scelta != 0);
}

/* --------------- 2. GESTIONE TECNICI --------------- */

void menuGestioneTecnici(tecnico_t tecnici[], int *nTecnici) {
    int scelta;

    do {
        pulisciSchermo();
        printf("\n");
        stampaLinea('=');
        printf("  %s  GESTIONE TECNICI%s\n", COLORE_BLU, COLORE_RESET);
        stampaLinea('=');

        printf("\n");
        printf("  %s[1]%s Visualizza elenco tecnici\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[2]%s Inserisci nuovo tecnico\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[3]%s Modifica dati di un tecnico\n", COLORE_VERDE, COLORE_RESET);
        printf("\n");
        stampaLineaDecorativa();
        printf("  %s[0]%s Torna al menu principale\n", COLORE_ROSSO, COLORE_RESET);
        stampaLinea('-');

        scelta = leggiSceltaMenu(0, 3);

        switch (scelta) {
            case 1:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sELENCO TECNICI%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare la funzione di visualizzazione (Omar) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 2:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sNUOVO TECNICO%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare la funzione di inserimento (Loris - Fase 2) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 3:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sMODIFICA TECNICO%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare la funzione di modifica (Loris - Fase 2) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 0:
                stampaInfo("Ritorno al menu principale...");
                break;
        }

    } while (scelta != 0);
}

/* --------------- 3. ASSEGNAZIONI --------------- */

void menuAssegnazioni(richiesta_t richieste[], int nRichieste,
                      tecnico_t tecnici[], int nTecnici) {
    int scelta;

    do {
        pulisciSchermo();
        printf("\n");
        stampaLinea('=');
        printf("  %s  ASSEGNAZIONI%s\n", COLORE_BLU, COLORE_RESET);
        stampaLinea('=');

        printf("\n");
        printf("  %s[1]%s Assegna richiesta a un tecnico\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[2]%s Modifica assegnazione esistente\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[3]%s Visualizza richieste non assegnate\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[4]%s Suggerimento automatico tecnico\n", COLORE_VERDE, COLORE_RESET);
        printf("\n");
        stampaLineaDecorativa();
        printf("  %s[0]%s Torna al menu principale\n", COLORE_ROSSO, COLORE_RESET);
        stampaLinea('-');

        scelta = leggiSceltaMenu(0, 4);

        switch (scelta) {
            case 1:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sASSEGNA RICHIESTA%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare la funzione di assegnazione (Loris - Fase 2) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 2:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sMODIFICA ASSEGNAZIONE%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare la funzione modifica assegnazione (Omar) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 3:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sRICHIESTE NON ASSEGNATE%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare la funzione visualizzazione non assegnate (Omar) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 4:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sSUGGERIMENTO AUTOMATICO TECNICO%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: chiamare il suggerimento automatico (Omar) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 0:
                stampaInfo("Ritorno al menu principale...");
                break;
        }

    } while (scelta != 0);
}

/* --------------- 4. RICERCA E FILTRI --------------- */

void menuRicercaFiltri(richiesta_t richieste[], int nRichieste) {
    int scelta;

    do {
        pulisciSchermo();
        printf("\n");
        stampaLinea('=');
        printf("  %s  RICERCA E FILTRI%s\n", COLORE_BLU, COLORE_RESET);
        stampaLinea('=');

        printf("\n");
        printf("  %s[1]%s Ricerca richiesta per codice\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[2]%s Filtra per stato\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[3]%s Filtra per priorita'\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[4]%s Filtra per cliente\n", COLORE_VERDE, COLORE_RESET);
        printf("\n");
        printf("  %s--- Ordinamenti ---%s\n", COLORE_GRIGIO, COLORE_RESET);
        printf("  %s[5]%s Ordina per costo stimato\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[6]%s Ordina per priorita'\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[7]%s Ordina per data di apertura\n", COLORE_VERDE, COLORE_RESET);
        printf("\n");
        stampaLineaDecorativa();
        printf("  %s[0]%s Torna al menu principale\n", COLORE_ROSSO, COLORE_RESET);
        stampaLinea('-');

        scelta = leggiSceltaMenu(0, 7);

        switch (scelta) {
            case 1:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sRICERCA PER CODICE%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: ricerca per codice (Omar) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 2:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sFILTRO PER STATO%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: filtro stato (Martin) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 3:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sFILTRO PER PRIORITA'%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: filtro priorita' (Martin) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 4:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sFILTRO PER CLIENTE%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: filtro cliente (Martin) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 5:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sORDINAMENTO PER COSTO STIMATO%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: ordinamento costo (Loris - Fase 3) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 6:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sORDINAMENTO PER PRIORITA'%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: ordinamento priorita' (Loris - Fase 3) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 7:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sORDINAMENTO PER DATA%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: ordinamento data (Loris - Fase 3) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 0:
                stampaInfo("Ritorno al menu principale...");
                break;
        }

    } while (scelta != 0);
}

/* --------------- 5. STATISTICHE E REPORT --------------- */

void menuStatisticheReport(richiesta_t richieste[], int nRichieste,
                           tecnico_t tecnici[], int nTecnici) {
    int scelta;

    do {
        pulisciSchermo();
        printf("\n");
        stampaLinea('=');
        printf("  %s  STATISTICHE E REPORT%s\n", COLORE_BLU, COLORE_RESET);
        stampaLinea('=');

        printf("\n");
        printf("  %s--- Statistiche ---%s\n", COLORE_GRIGIO, COLORE_RESET);
        printf("  %s[1]%s Statistiche per tipologia dispositivo\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[2]%s Statistiche per priorita'\n", COLORE_VERDE, COLORE_RESET);
        printf("\n");
        printf("  %s--- Report ---%s\n", COLORE_GRIGIO, COLORE_RESET);
        printf("  %s[3]%s Report 1 – Report generale richieste\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[4]%s Report 2 – Report operativo richieste\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[5]%s Report 3 – Report tecnici e assegnazioni\n", COLORE_VERDE, COLORE_RESET);
        printf("\n");
        printf("  %s--- Dashboard ---%s\n", COLORE_GRIGIO, COLORE_RESET);
        printf("  %s[6]%s Genera dashboard HTML\n", COLORE_VERDE, COLORE_RESET);
        printf("\n");
        stampaLineaDecorativa();
        printf("  %s[0]%s Torna al menu principale\n", COLORE_ROSSO, COLORE_RESET);
        stampaLinea('-');

        scelta = leggiSceltaMenu(0, 6);

        switch (scelta) {
            case 1:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sSTATISTICHE PER DISPOSITIVO%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: statistiche dispositivo (Omar) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 2:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sSTATISTICHE PER PRIORITA'%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: statistiche priorita' (Loris - Fase 3) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 3:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sREPORT 1 – GENERALE RICHIESTE%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: Report 1 (Martin) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 4:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sREPORT 2 – OPERATIVO RICHIESTE%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: Report 2 (Loris - Fase 4) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 5:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sREPORT 3 – TECNICI E ASSEGNAZIONI%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: Report 3 (Omar) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 6:
                pulisciSchermo();
                printf("\n");
                stampaLinea('-');
                printf("  %sGENERAZIONE DASHBOARD HTML%s\n", COLORE_BOLD, COLORE_RESET);
                stampaLinea('-');
                /* TODO: generazione dashboard (Gruppo) */
                stampaAvviso("Funzione non ancora implementata.");
                premiPerContinuare();
                break;
            case 0:
                stampaInfo("Ritorno al menu principale...");
                break;
        }

    } while (scelta != 0);
}

/* --------------- 6. GESTIONE FILE --------------- */

void menuGestioneFile(richiesta_t richieste[], int *nRichieste,
                      tecnico_t tecnici[], int *nTecnici) {
    int scelta;

    do {
        pulisciSchermo();
        printf("\n");
        stampaLinea('=');
        printf("  %s  GESTIONE FILE%s\n", COLORE_BLU, COLORE_RESET);
        stampaLinea('=');

        printf("\n");
        printf("  %s[1]%s Carica richieste da file\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[2]%s Carica tecnici da file\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[3]%s Salva richieste su file\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[4]%s Salva tecnici su file\n", COLORE_VERDE, COLORE_RESET);
        printf("  %s[5]%s Salva tutto (richieste + tecnici)\n", COLORE_VERDE, COLORE_RESET);
        printf("\n");
        stampaLineaDecorativa();
        printf("  %s[0]%s Torna al menu principale\n", COLORE_ROSSO, COLORE_RESET);
        stampaLinea('-');

        scelta = leggiSceltaMenu(0, 5);

        switch (scelta) {
            case 1:
                printf("\n");
                stampaInfo("Caricamento richieste dal file...");
                caricaRichieste(richieste, nRichieste);
                stampaConferma("Richieste ricaricate con successo!");
                premiPerContinuare();
                break;
            case 2:
                printf("\n");
                stampaInfo("Caricamento tecnici dal file...");
                caricaTecnici(tecnici, nTecnici);
                stampaConferma("Tecnici ricaricati con successo!");
                premiPerContinuare();
                break;
            case 3:
                printf("\n");
                stampaInfo("Salvataggio richieste su file...");
                salvaRichieste(richieste, *nRichieste);
                stampaConferma("Richieste salvate con successo!");
                premiPerContinuare();
                break;
            case 4:
                printf("\n");
                stampaInfo("Salvataggio tecnici su file...");
                salvaTecnici(tecnici, *nTecnici);
                stampaConferma("Tecnici salvati con successo!");
                premiPerContinuare();
                break;
            case 5:
                printf("\n");
                stampaInfo("Salvataggio di tutti i dati...");
                salvaRichieste(richieste, *nRichieste);
                salvaTecnici(tecnici, *nTecnici);
                stampaConferma("Tutti i dati sono stati salvati con successo!");
                premiPerContinuare();
                break;
            case 0:
                stampaInfo("Ritorno al menu principale...");
                break;
        }

    } while (scelta != 0);
}
