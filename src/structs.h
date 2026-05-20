#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_RICHIESTE 100
#define MAX_TECNICI 50
#define MAX_CARATTERI_TESTO_LUNGO 100
#define MAX_CARATTERI_TESTO_CORTO 30
#define MAX_CARATTERI_NOME 20
#define MAX_CARATTERI_COGNOME 20

typedef struct
{
    int id_richiesta;
    char nome_cliente[MAX_CARATTERI_NOME];
    char cognome_cliente[MAX_CARATTERI_COGNOME];
    char tipologia_dispositivo[MAX_CARATTERI_TESTO_LUNGO];
    char descrizione_problema[MAX_CARATTERI_TESTO_LUNGO];
    char priorita[MAX_CARATTERI_TESTO_CORTO];
    char stato[MAX_CARATTERI_TESTO_CORTO];
    float costo_stimato;
    float costo_finale;
    char data_apertura[MAX_CARATTERI_TESTO_CORTO];
    int codice_tecnico_associato;
} Richiesta;

typedef struct
{
    int id_tecnico;
    char nome_tecnico[MAX_CARATTERI_NOME];
    char specializzazione[MAX_CARATTERI_TESTO_LUNGO];
    int richieste_assegnabili;
    int richieste_assegnate;
} Tecnico;

#endif