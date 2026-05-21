#ifndef STRUCTS_H
#define STRUCTS_H

//LIMITI SULLE DIMENSIONI
#define MAX_RICHIESTE 100
#define MAX_TECNICI 50
#define MAX_CARATTERI_TESTO_LUNGO 100
#define MAX_CARATTERI_TESTO_CORTO 30
#define MAX_CARATTERI_NOME 30
#define MAX_CARATTERI_COGNOME 30
#define MAX_CARATTERI_DATA 11  

//COSTANTI PER LO STATO DELLA RICHIESTA
#define STATO_APERTA "Aperta"
#define STATO_IN_LAVORAZIONE "InLavorazione"
#define STATO_COMPLETATA "Completata"
#define STATO_ANNULLATA "Annullata"

//COSTANTI PER LA PRIORITA'
#define PRIORITA_ALTA "Alta"
#define PRIORITA_MEDIA "Media"
#define PRIORITA_BASSA "Bassa"

/**
 * @brief Struttura che rappresenta una richiesta di assistenza.
 *
 * @param id_richiesta Identificatore univoco della richiesta
 * @param nome_cliente Nome del cliente
 * @param cognome_cliente Cognome del cliente
 * @param tipologia_dispositivo Tipo di dispositivo (es. "Laptop", "Stampante")
 * @param descrizione_problema Descrizione testuale del problema riscontrato
 * @param priorita Priorita' della richiesta: PRIORITA_ALTA/MEDIA/BASSA
 * @param stato Stato corrente: STATO_APERTA/IN_LAVORAZIONE/COMPLETATA/ANNULLATA
 * @param costo_stimato Costo stimato dell'intervento (>= 0)
 * @param costo_finale Costo finale a lavoro completato; COSTO_NON_DISPONIBILE se assente
 * @param data_apertura Data di apertura nel formato GG/MM/AAAA
 * @param codice_tecnico_associato ID del tecnico assegnato; NESSUN_TECNICO se non ancora assegnata
 */
typedef struct {
    int   id_richiesta;
    char  nome_cliente[MAX_CARATTERI_NOME];
    char  cognome_cliente[MAX_CARATTERI_COGNOME];
    char  tipologia_dispositivo[MAX_CARATTERI_TESTO_LUNGO];
    char  descrizione_problema[MAX_CARATTERI_TESTO_LUNGO];
    char  priorita[MAX_CARATTERI_TESTO_CORTO];
    char  stato[MAX_CARATTERI_TESTO_CORTO];
    float costo_stimato;
    float costo_finale;
    char  data_apertura[MAX_CARATTERI_DATA];
    int   codice_tecnico_associato;
} richiesta_t;

/**
 * @brief Struttura che rappresenta un tecnico del centro assistenza.
 *
 * @param id_tecnico Identificatore univoco del tecnico
 * @param nome_tecnico Nome del tecnico
 * @param cognome_tecnico Cognome del tecnico
 * @param specializzazione Area di specializzazione (es. "Hardware", "Software")
 * @param richieste_assegnabili Numero massimo di richieste che il tecnico puo' gestire
 * @param richieste_assegnate  Numero di richieste attualmente assegnate al tecnico
 */
typedef struct {
    int  id_tecnico;
    char nome_tecnico[MAX_CARATTERI_NOME];
    char cognome_tecnico[MAX_CARATTERI_COGNOME];
    char specializzazione[MAX_CARATTERI_TESTO_LUNGO];
    int  richieste_assegnabili;
    int  richieste_assegnate;
} tecnico_t;

#endif
