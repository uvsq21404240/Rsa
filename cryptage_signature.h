#ifndef CRYPTAGE_SIGNATURE_H_INCLUDED
#define CRYPTAGE_SIGNATURE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include "memoire.h"
//clefs de la personne A (generer a partir d'un site)
extern mpz_t nA;
extern mpz_t eA;
extern mpz_t dA;
//clefs de la personne 	B (generer a partir d'un site)
extern mpz_t nB;
extern mpz_t eB;
extern mpz_t dB;
extern gchar* adr_fichier;

int tailleFichier(FILE * f);
int nombreDebloc(char* nomFichier);
void decoupage_Blocs(mpz_t* m_Clair_Decouper,mpz_t* m_Clair_ASCII);
void chiffrement(mpz_t* m_chiffre,mpz_t* m_Claire_Decouper);
void signer(mpz_t* m_signe,mpz_t* m_chiffre);
void ecriture1(mpz_t* m_signe);
void crypter_Signer(char* nomFichier);

#endif 
