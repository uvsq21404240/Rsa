#ifndef IG_H
#include "gestion_des_clefs.h"
#include "cryptage_signature.h"
#include "decryptage_verification.h"
#include "memoire.h"

#define IG_H
//clefs de la personne A (generer a partir d'un site)
extern mpz_t nA;
extern mpz_t eA;
extern mpz_t dA;
//clefs de la personne 	B (generer a partir d'un site)
extern mpz_t nB;
extern mpz_t eB;
extern mpz_t dB;

extern char* adr_fichier;
extern char* adr_fichier2;
extern char* adr_fichier3;





void A_propos(Fenetre);
void avertissement(GtkWidget* Fenetre);
void avertissement2(GtkWidget* Fenetre);
void Menu_principale2(GtkWidget* Fenetre);
void Menu(GtkWidget* Fenetre);
void Choix_expe(GtkWidget* Fenetre);
void Menu_test(GtkWidget* Fenetre);
void Menu_test2(GtkWidget* Fenetre);
void Menu_principale(GtkWidget* Fenetre);
void Menu_creation_de_cle(GtkWidget* Fenetre);
void MenuPrincipal(GtkWidget *Fenetre);
void ViderContenir(GtkContainer * container);
void Ouvrir_un_fichier(GtkWidget* Fenetre);
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection);
void quitter(GtkWidget* widget);
void creer_file_selection();
void signerr();
void verifierr();
void Save(GtkWidget* Fenetre);
void creer_file_selection2();
void recuperer_chemin2(GtkWidget *bouton, GtkWidget *file_selection);
void verifier_dialogue(GtkWidget* Fenetre);
void signer_dialogue(GtkWidget* Fenetre);

#endif
