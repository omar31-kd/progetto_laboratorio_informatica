# Sistema per la gestione di richieste di assistenza tecnica

Progetto sviluppato per l'esame di Laboratorio di informatica, finalizzato alla realizzazione di un sistema completo per la gestione delle richieste di un centro di assistenza tecnica.

l'applicazione permette di amministrare richieste di supporto tecnico, gestire tecnici specializzati, assegnare interventi e generare report dettagliati sull'operatività del sistema.

## Componenti del gruppo
| Nome | Cognome | Matricola | Corso |
|------|---------|-----------|-------|
| Omar | Saafi | 853622 | NZ |
| Martin | Vulpio | 862992 | NZ |
| Loris | Panaro | 854237 | NZ |

## Suddivisione del Lavoro
| Studente | Ruolo | Responsabilità |
|----------|-------|----------------|
| Martin Vulpio | I/O File & Filtri | Caricamento/salvataggio file, inserimento e modifica richieste, filtri per stato/priorità/cliente, Report 1 |
| Loris Panaro | UI/Menu & Ordinamenti | Schermata iniziale, menu e sottomenu, messaggi utente, inserimento/modifica tecnici, assegnazioni, ordinamenti, Report 2 |
| Omar Saafi | Visualizzazione & Statistiche | Visualizzazione richieste e tecnici, ricerca, modifica assegnazioni, statistiche per dispositivo e priorità, Report 3 |

### Dettaglio per Fasi
| Fase | Attività | Responsabile |
|------|----------|--------------|
| Fase 0 | Setup repository, strutture dati, file di esempio | Gruppo completo |
| Fase 1 | I/O file (caricamento e salvataggio) | Martin Vulpio |
| Fase 1 | Schermata iniziale, menu e messaggi | Loris Panaro |
| Fase 1 | Visualizzazione richieste/tecnici, ricerca | Omar Saafi |
| Fase 2 | Inserimento/modifica richieste, costo finale | Martin Vulpio |
| Fase 2 | Inserimento/modifica tecnici, assegnazioni | Loris Panaro |
| Fase 2 | Modifica assegnazioni, richieste non assegnate, suggerimento automatico | Omar Saafi |
| Fase 3 | Filtri per stato, priorità, cliente | Martin Vulpio |
| Fase 3 | Ordinamenti e statistiche per priorità | Loris Panaro |
| Fase 3 | Statistiche per tipologia di dispositivo | Omar Saafi |
| Fase 4 | Report 1 – Report generale richieste | Martin Vulpio |
| Fase 4 | Report 2 – Report operativo richieste | Loris Panaro |
| Fase 4 | Report 3 – Report tecnici e assegnazioni | Omar Saafi |
| Fase 5 | Dashboard HTML | Gruppo completo |
| Fase 6 | Testing e integrazione | Gruppo completo |
| Fase 7 | Consegna finale e pulizia repository | Gruppo completo |

## Obiettivi del progetto
Il progetto ha lo scopo di realizzare un sistema completo per la gestione delle richieste di un centro di assistenza tecnica, con i seguenti obiettivi:
- Gestione completa delle richieste di assistenza tecnica
- Assegnazione delle richieste ai tecnici specializzati
- Monitoraggio dello stato delle richieste
- Analisi statistiche e generazione di report avanzati
- Salvataggio dei dati tramite file (``` .txt ```)
- Dashboard HTML per la consultazione web dei dati generati

## Funzionalità Implementate
### Gestione File
- [x] Caricamento richieste da file (`richieste.txt`)
- [x] Caricamento tecnici da file (`tecnici.txt`)
- [x] Salvataggio richieste su file
- [x] Salvataggio tecnici su file

### Gestione Richieste
- [x] Visualizzazione di tutte le richieste
- [x] Inserimento di una nuova richiesta
- [x] Ricerca richiesta tramite codice
- [x] Modifica stato, descrizione e costo stimato
- [x] Aggiornamento costo finale di una richiesta completata
- [x] Visualizzazione richieste non ancora assegnate

### Gestione Tecnici
- [x] Visualizzazione elenco tecnici
- [x] Inserimento di un nuovo tecnico
- [x] Modifica dati di un tecnico

### Assegnazioni
- [x] Associazione di una richiesta a un tecnico
- [x] Modifica dell'assegnazione di una richiesta
- [x] Suggerimento automatico del tecnico adatto

### Ricerca e Filtri
- [x] Filtro richieste per stato
- [x] Filtro richieste per priorità
- [x] Filtro richieste per cliente

### Ordinamenti
- [x] Ordinamento per costo stimato
- [x] Ordinamento per priorità
- [x] Ordinamento per data di apertura

### Statistiche
- [x] Statistiche per tipologia di dispositivo (costo medio, costo più alto)
- [x] Statistiche per priorità
- [x] Distinzione tra richieste concluse, aperte, annullate e in lavorazione

### Report
- [x] Report 1 – Report generale richieste
- [x] Report 2 – Report operativo richieste
- [x] Report 3 – Report tecnici e assegnazioni

### Consultazione Web
- [x] Generazione file `dashboard.html`
- [x] Visualizzazione riepilogo richieste e tecnici
- [x] Sezione richieste urgenti e non assegnate
- [x] Statistiche e report nella dashboard

## Tecnologie utilizzate
| Tecnologia | Utilizzo |
|------------|----------|
| C | Linguaggio principale del progetto |
| GCC | Compilatore |
| File .txt | Persistenza dei dati |
| HTML/CSS | Dashboard per la consultazione web |

## Supporto alla Progettazione
Durante lo sviluppo del progetto è stato utilizzato il supporto
dell'intelligenza artificiale (Claude - Anthropic) per:
- Progettazione della schermata iniziale e struttura del menu testuale
- Organizzazione delle schermate e dei sottomenu
- Definizione dei messaggi all'utente (errori, conferme riepilogo)
- Progettazione e sviluppo del file `dashboard.html`
- Testi descrittivi e riepilogativi dei risultati nei report

## Struttura del progetto
Sistema gestionale testuale scritto in C per la gestione delle richieste di un centro di assistenza tecnica. Permette di gestire richieste e tecnici tramite file di testo, con generazione automatica di report e pagina web di riepilogo.

### Albero delle directory
```
progetto_laboratorio_informatica/
├── src/                        → codice sorgente
│   ├── structs.h
│   ├── richieste.h / richieste.c
│   ├── tecnici.h / tecnici.c
│   ├── report.h / report.c
│   └── main.c
├── data/                       → dati del programma
│   ├── richieste.txt
│   └── tecnici.txt
├── docs/                       → documentazione e web
│   └── dashboard.html
├── traccia/                    → traccia del progetto
│   └── Gruppo3.pdf
├── .gitignore
└── README.md
```
### src/

### data/

### docs/


## Compilazione ed Esecuzione
### Requisiti
- gcc installato sul sistema
- Sistema operativo: Linux / macOS / Windows (con MinGW)

### Compilazione
Dalla cartella principale del progetto:

```bash
gcc src/main.c src/richieste.c src/tecnici.c src/report.c -o assistenza
```

### Esecuzione
```bash
./assistenza
```

## Formato dei file di dati

## Dashboard HTML

