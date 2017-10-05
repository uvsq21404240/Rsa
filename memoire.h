#ifndef MEMOIRE_H_INCLUDED
#define MEMOIRE_H_INCLUDED
#define TAILLE 10000
#include <gmp.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <time.h>
#include <stddef.h>
#include <string.h>


GtkWidget *Fenetre;

gchar* ID_user;
gchar* ID_user2;

extern gchar* adr_fichier;
extern gchar* adr_fichier2;
extern gchar* adr_fichier3;


extern mpz_t nA;
extern mpz_t eA;
extern mpz_t dA;
//clefs de la personne 	B 
extern mpz_t nB;
extern mpz_t eB;
extern mpz_t dB;

char* Renvoie_ligne(char* ID);
char* Renvoie_ligne2(char* ID);
char* Renvoie_n(char* ID);
char* Renvoie_e(char* ID);
char* Renvoie_d(char* ID);
void set_crypte();
void set_clair();

#endif
