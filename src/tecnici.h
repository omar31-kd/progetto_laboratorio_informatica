#ifndef TECNICI_H
#define TECNICI_H

#include "structs.h"

/**
 * @brief Carica i tecnici dal file "data/tecnici.txt" nell'array.
 *        Se il file non esiste, nTecnici viene posto a 0 e la funzione ritorna.
 * @param tecnici   Array di tecnico_t da riempire
 * @param nTecnici  Puntatore al contatore, aggiornato con il numero di righe lette
 */
void caricaTecnici(tecnico_t tecnici[], int *nTecnici);

/**
 * @brief Salva tutti i tecnici su "data/tecnici.txt" (sovrascrive il file).
 * @param tecnici   Array di tecnico_t da salvare
 * @param nTecnici  Numero di tecnici presenti nell'array
 */
void salvaTecnici(tecnico_t tecnici[], int nTecnici);

#endif
