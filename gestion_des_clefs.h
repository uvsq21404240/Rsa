#ifndef GESTION_DES_CLEFS_H
#define GESTION_DES_CLEFS_H
#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "memoire.h"
extern gchar* ID_user;
void exponentiation_modulaire(mpz_t exp, mpz_t a, mpz_t p, mpz_t m);
void inverse_modulaire(mpz_t inv, mpz_t a, mpz_t m);
bool test_fermat(mpz_t var);
void creation_clef();
void test_unitaire_exponentiation_modulaire(mpz_t exp, mpz_t a, mpz_t p, mpz_t m);
void test_unitaire_inverse_modulaire(mpz_t inv, mpz_t a, mpz_t m);
bool test_premier(mpz_t p);

#endif
