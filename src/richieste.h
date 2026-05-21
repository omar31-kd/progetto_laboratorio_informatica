#ifndef RICHIESTE_H
#define RICHIESTE_H

#include "structs.h"

/**
 * @brief Carica le richieste dal file "data/richieste.txt" nell'array.
 *        Se il file non esiste, nRichieste viene posto a 0 e la funzione ritorna.
 * @param richieste   Array di richiesta_t da riempire
 * @param nRichieste  Puntatore al contatore, aggiornato con il numero di righe lette
 */
void caricaRichieste(richiesta_t richieste[], int *nRichieste);

/**
 * @brief Salva tutte le richieste su "data/richieste.txt" (sovrascrive il file).
 * @param richieste   Array di richiesta_t da salvare
 * @param nRichieste  Numero di richieste presenti nell'array
 */
void salvaRichieste(richiesta_t richieste[], int nRichieste);

#endif
