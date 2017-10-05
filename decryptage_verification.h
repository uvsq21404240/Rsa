#ifndef DECRYPTAGE_VERIFICATION_H_INCLUDED
#define DECRYPTAGE_VERIFICATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <ctype.h>
#include <string.h>
#include "memoire.h"
//clefs de la personne A 
extern mpz_t nA;
extern mpz_t eA;
extern mpz_t dA;
//clefs de la personne 	B 
extern mpz_t nB;
extern mpz_t eB;
extern mpz_t dB;
extern gchar* adr_fichier;

int nombreDeBlocs(char* nomFichier);
void verification(mpz_t* m_Chiffree);
void dechiffrement(mpz_t* m_Chiffree);
char* convertir_en_Caractere(mpz_t* m_Chiffree);
void ecriture2(char* m_dechiffree);
void decrypter_Verifier(char* nomFichier);

#endif 



