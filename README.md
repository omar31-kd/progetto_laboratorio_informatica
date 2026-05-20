# Sistema per la gestione di richieste di assistenza tecnica

Progetto sviluppato per l'esame di Laboratorio di informatica, finalizzato alla realizzazione di un sistema completo per la gestione delle richieste di un centro di assistenza tecnica.

l'applicazione permette di amministrare richieste di supporto tecnico, gestire tecnici specializzati, assegnare interventi e generare report dettagliati sull'operatività del sistema.

## Componenti del gruppo
- Omar Saafi
- Martin Vulpio
- Loris Panaro

## Suddivisione del lavoro

## Obiettivi del progetto
- Gestione completa delle richieste di assistenza tecnica
- Assegnazione delle richieste ai tecnici specializzati
- Monitoraggio dello stato delle richieste
- Analisi statistiche e generazione di report avanzati
- Salvataggio dei dati tramite file ``` .txt ```
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
- Linguaggio C
- HTML per la dashboard di consultazione dati web
- Claude AI-assisted design

## Supporto alla progettazione
Claude AI-assisted design per:
- schermata iniziale;
- menu principale numerato;
- sottomenu per area funzionale;
- accesso alle operazioni principali;
- area gestione richieste;
- area ricerca e filtri;
- area ordinamenti;
- area report;
- area salvataggio;
- area statistiche;
- area consultazione dati web
- messaggi di errore comprensibili;
- messaggi di conferma;

## Struttura del progetto

## Come compilare il progetto

## Formato dei file di dati

## Dashboard HTML

